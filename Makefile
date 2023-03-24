all: master
master: master.c
	gсс -Wall -Werror -o master master.c
run:
	./master
