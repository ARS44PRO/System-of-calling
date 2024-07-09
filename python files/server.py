from flask import Flask
from flask import request 

app = Flask(__name__)

@app.route('/post', methods=['POST'])
def post():
	f = open('data\chisla.txt', 'w')
	b = request.data
	if b == b'2':
		f.write('2')
	elif b == b'1':
		f.write('1')
	f.close()
	print(b)	
	return ''

app.run(host='0.0.0.0', port=8090)
