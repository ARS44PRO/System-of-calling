from os import environ
environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1'
import pygame
import os
import time as t
pygame.mixer.init(buffer=2500)
path = "/home/pilot/Desktop/sound/voice.wav"
p = pygame.mixer.music
a = None
r = 0
while True:
	if os.path.isfile(path):
		if r==0:
			p.load('voice.wav')
			p.play()
			r+=1
		if p.get_busy()==False:
			os.remove('voice.wav')
			r=0
	else:
		f = open('chisla.txt', 'r')
		a = f.read()
		if a == '2':
			p.load('ANNA.mp3')
			p.play()
			f = open('chisla.txt', 'w')
			f.write('3')
		elif a == '0':
			p.stop()
	t.sleep(0.2)
	

