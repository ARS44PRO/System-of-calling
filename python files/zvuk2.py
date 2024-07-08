import pygame
import time as t
pygame.mixer.init(buffer=2500)
p = pygame.mixer.music
while True:
	f = open('data\chisla.txt', 'r')
	a = f.read()
	if a == '2':
		p.load('sounds\ANNA.wav')
		p.play()
		f = open('data\chisla.txt', 'w')
		f.write('0')
	elif a == '1':
		p.stop()
		f.write('1')
	t.sleep(0.2)
	