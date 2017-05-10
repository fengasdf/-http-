.PHONY:all
all:http sql cal
http:client.cpp coctx.cpp co_hook_sys_call.cpp co_routine.cpp http.cpp  coctx_swap.S 
	g++ -o $@ $^ -lpthread -ldl


.PHONY:sql
sql:
	cd /home/cao/linux/http/wwwroot/cgi-bin; make; cd -

.PHONY:cal
cal:
	cd /home/cao/linux/http/wwwroot/pa; make; cd -

.PHONY:clean
clean:
	rm -rf *.o http; cd /home/cao/linux/http/wwwroot/cgi-bin; make clean; cd -; cd /home/cao/linux/http/wwwroot/pa;make clean; cd -


.PHONY:output
output:
	mkdir /home/cao/linux/http/output
	cp /home/cao/linux/http/http /home/cao/linux/http/output
	mkdir /home/cao/linux/http/output/wwwroot
	cp /home/cao/linux/http/wwwroot/root.html  /home/cao/linux/http/output/wwwroot
	mkdir /home/cao/linux/http/output/wwwroot/cgi-bin
	cp /home/cao/linux/http/wwwroot/cgi-bin/sql /home/cao/linux/http/output/wwwroot/cgi-bin
	cp /home/cao/linux/http/control.sh /home/cao/linux/http/output
	cp /home/cao/linux/http/log /home/cao/linux/http/output
	mkdir /home/cao/linux/http/output/wwwroot/pa
	cp /home/cao/linux/http/wwwroot/pa/cal /home/cao/linux/http/output/wwwroot/pa
    
