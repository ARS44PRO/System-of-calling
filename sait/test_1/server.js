const express = require('express');
const bodyParser = require('body-parser');
const multer = require('multer');
const createCsvWriter = require('csv-writer').createObjectCsvWriter;
const csv = require('csv-parser');
const fs = require('fs');
const path = require('path');

const app = express();
const port = 3000;

app.use(bodyParser.json());
app.use(express.static('public'));

const csvWriter = createCsvWriter({
  path: 'button-states.csv',
  header: [
    { id: 'buttonId', title: 'Button ID' },
    { id: 'state', title: 'State' },
    { id: 'userId', title: 'User ID' },
    { id: 'selectedTrack', title: 'Selected Track' },
  ],
});

const storage = multer.diskStorage({
  destination: (req, file, cb) => {
    const userDir = path.join(__dirname, 'public', 'uploads', req.body.userId);
    if (!fs.existsSync(userDir)) {
      fs.mkdirSync(userDir, { recursive: true });
    }
    cb(null, userDir);
  },
  filename: (req, file, cb) => {
    cb(null, file.originalname);
  },
});

const upload = multer({ storage });

app.post('/upload', upload.single('audio'), (req, res) => {
  res.status(200).send('Audio uploaded successfully');
});

app.post('/save-button-state', (req, res) => {
  const { buttonId, state, userId, selectedTrack } = req.body;

  csvWriter
    .writeRecords([{ buttonId, state, userId, selectedTrack }])
    .then(() => {
      res.status(200).send('Button state saved successfully');
    })
    .catch((error) => {
      res.status(500).send('Error saving button state');
    });
});

app.post('/login', (req, res) => {
  const { username, password } = req.body;
  let authenticated = false;

  fs.createReadStream('users.csv')
    .pipe(csv())
    .on('data', (row) => {
      if (row.username === username && row.password === password) {
        authenticated = true;
      }
    })
    .on('end', () => {
      if (authenticated) {
        res.status(200).send({ message: 'Login successful', userId: username });
      } else {
        res.status(401).send('Invalid credentials');
      }
    });
});

app.get('/tracks', (req, res) => {
  const userId = req.query.userId;
  const userDir = path.join(__dirname, 'public', 'uploads', userId);

  fs.readdir(userDir, (err, files) => {
    if (err) {
      res.status(500).send('Error loading tracks');
    } else {
      res.status(200).send({ tracks: files });
    }
  });
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});