from flask import Flask
from flask import request 

app = Flask(__name__)

i=0

with open('C:/Users/денис/Desktop/System-of-calling/data/days.txt', 'r') as f:
    a = f.read().split(', ')    
    
@app.route('/getaudio', methods=['GET'])
def get():
    global i
    if i+1==len(a):
        i=0
    i+=1
    print(i)
    return a[i-1]
app.run(host='0.0.0.0', port=8090)
