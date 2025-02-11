import telebot 
import requests
import os
from pydub import AudioSegment
token = '6958580930:AAFu6hp2ZWjdF7iOyebqzoxLcVeWkk-t51k'
bot = telebot.TeleBot(token)
@bot.message_handler(content_types=['voice'])
def repeat_all_message(message):
	file_info = bot.get_file(message.voice.file_id)
	file = requests.get('https://api.telegram.org/file/bot{0}/{1}'.format(token, file_info.file_path))
	with open('voice.ogg', 'wb') as f:
		f.write(file.content)
	AudioSegment.from_file('voice.ogg').export('voice.wav', format='wav')
	os.remove('voice.ogg')
bot.polling(none_stop=True, interval=0)

