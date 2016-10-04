CC=gcc
CFLAGS=-I. -luv

test01loop: test01loop.c
	$(CC) -o uvloop test01loop.c $(CFLAGS)

test02idle: test02idle.c
	$(CC) -o uvidle test02idle.c $(CFLAGS)

test03cat: test03cat.c
	$(CC) -o uvcat test03cat.c $(CFLAGS)
	./uvcat make-note.txt

test04tee: test04tee.c
	$(CC) -o uvtee test04tee.c $(CFLAGS)
	ls | ./uvtee lsresult
	cat lsresult
	rm lsresult

test05onchange: test05onchange.c
	$(CC) -o uvonchange test05onchange.c $(CFLAGS)

test06-tcp-echo: test06-tcp-echo-server.c test06-tcp-echo-client.c
	$(CC) -o uv-tcp-echo-server test06-tcp-echo-server.c $(CFLAGS)
	echo "Test by telnet 127.0.0.1 13370"
	$(CC) -o uv-tcp-echo-client test06-tcp-echo-client.c $(CFLAGS)

clean:
	rm uv*

