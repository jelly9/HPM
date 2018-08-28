.PHONY:all
all:server client



server: server.c common.c
	gcc -o $@ $^


client: client.c common.c
	gcc -o $@ $^


.PHNOY:clean
clean:
	rm -rf client server

