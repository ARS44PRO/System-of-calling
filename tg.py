import telebot 
from gtts import gTTS
import re
import pandas as pd
reg = re.compile(r'[a-zA-Z]')

token = '6958580930:AAFu6hp2ZWjdF7iOyebqzoxLcVeWkk-t51k'
bot = telebot.TeleBot(token)

def check(user):
    basa = pd.read_excel('basa.xlsx', index_col=0)
    if user in basa['user'].tolist():
        name = basa.iloc[basa['user'].tolist().index('ars44pro')]['name']
        return True, name
    else:
        return False

def text_to_waven(text, output_file):
    tts = gTTS(text=text, lang='en')
    tts.save(output_file)
def text_to_wavru(text, output_file):
    tts = gTTS(text=text, lang='ru')
    tts.save(output_file)

train = pd.read_excel('basa.xlsx', index_col=0)
for i in train['id'].tolist():
    bot.send_message(i, 'По техническим причинам сервер прекратил свою работу, чтобы восстановить работу нажмите на /start!')

@bot.message_handler(commands=['start'])
def welcome_start(mess):
    status, name = check(mess.from_user.username)
    if status:
        bot.send_message(mess.chat.id, f'Добро пожаловать, {name}!')
        @bot.message_handler(content_types=['voice'])
        def voice_processing(message):
            file_info = bot.get_file(message.voice.file_id)
            downloaded_file = bot.download_file(file_info.file_path)
            with open('sounds/voice.wav', 'wb') as new_file:
                new_file.write(downloaded_file)
        
        @bot.message_handler(content_types=['audio'])
        def audio_give(a):
            file = bot.get_file(a.audio.file_id)
            down = bot.download_file(file.file_path)
            with open('sounds/audio.wav', 'wb') as f:
                f.write(down)

        @bot.message_handler(content_types=['text'])
        def message(x):
            if reg.match(x.text): 
    	        text_to_waven(x.text, 'sounds/text.wav')
            else:
                text_to_wavru(x.text, 'sounds/text.wav')
    else:
        bot.send_message(mess.chat.id, 'Доступ запрещен!')
bot.polling(none_stop=True, interval=0)

#Нужно сделать чтобы id автоматически добавлял, а также посмотреть что будет если зайти типо неавторизованному пользователю

