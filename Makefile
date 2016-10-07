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

test07-udp-dhcp: test07-udp-dhcp.c
	$(CC) -o uv-udp-dhcp test07-udp-dhcp.c $(CFLAGS)

test08dns: test08dns.c
	$(CC) -o uvdns test08dns.c $(CFLAGS)

test09nic: test09nic.c
	$(CC) -o uvnic test09nic.c $(CFLAGS)

test10threadc: test10threadc.c
	$(CC) -o uvthreadc test10threadc.c $(CFLAGS)

test11threadlock: test11threadlock.c
	$(CC) -o uvthreadlock test11threadlock.c $(CFLAGS)

test12threadq: test12threadq.c
	$(CC) -o uvthreadq test12threadq.c $(CFLAGS)

test13interthread: test13interthread.c
	$(CC) -o uvinterthread test13interthread.c $(CFLAGS)

test14procspawn: test14procspawn.c
	$(CC) -o uvprocspawn test14procspawn.c $(CFLAGS)


clean:
	rm uv*

