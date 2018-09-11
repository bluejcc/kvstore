CC=g++

datastore_server: server.cc
	$(CC) -o datastore_server server.cc -I.

debug: server.cc
	$(CC) -o datastore_server -g server.cc -I.

client: client.cc
	$(CC) -o client client.cc -I.

clean :
	-rm datastore_server
