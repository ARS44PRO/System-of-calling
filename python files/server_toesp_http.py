from flask import Flask
from flask import request 

app = Flask(__name__)

i=0

with open('C:/Users/денис/Desktop/Project/System-of-calling/data/days.txt', 'r') as f:
    a = f.read().split(', ')    
    
@app.route('/mp3', methods=['GET'])
def get():
    global i
    if i>=len(a):
        i=0
    i+=4000
    print(i)
    return a[i:i+3999]
app.run(host='0.0.0.0', port=8000)
