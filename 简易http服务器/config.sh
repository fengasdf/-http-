#########################################################################
# File Name: config.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: Tue 11 Apr 2017 08:27:10 AM PDT
#########################################################################
#!/bin/bash


ROOT_PATH=$(pwd)
INCLUDE=$ROOT_PATH

#httpd src
SRC=$(ls *.cpp | tr '\n' ' ')
SDC=$(ls *.S | tr '\n' ' ')
#OBJ=$(ls *.cpp | sed -e '/^http/s/.cpp/.o/g' | tr '\n' ' ')
SERVER_NAME=http
CC=g++
LIB=-lpthread

#cgi
CGI_PATH=$ROOT_PATH/wwwroot/cgi-bin
CAL_PATH=$ROOT_PATH/wwwroot/pa
FILE=$(ls $CAL_PATH | grep '.cpp')
MATH_SRC=$(ls $CGI_PATH | grep 'My' | grep -E '.cpp$')
MATH_CGI_BIN=sql

#cgi makefile
cat << EOF > $CGI_PATH/makefile
${MATH_CGI_BIN}:$MATH_SRC
	$CC -o \$@ \$^ -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient

.PHONY:clean
clean:
	rm -f $MATH_CGI_BIN

EOF

#cal makefile
cat <<EOF > $CAL_PATH/makefile

cal:$FILE
	$CC -o \$@ \$^

.PHONY:clean
clean:
	rm -f cal
EOF

#http makefile
cat << EOF > makefile
.PHONY:all
all:${SERVER_NAME} sql cal
${SERVER_NAME}:${SRC} $SDC
	${CC} -o \$@ \$^ $LIB -ldl


.PHONY:sql
sql:
	cd $CGI_PATH; make; cd -

.PHONY:cal
cal:
	cd $CAL_PATH; make; cd -

.PHONY:clean
clean:
	rm -rf *.o $SERVER_NAME; cd $CGI_PATH; make clean; cd -; cd $CAL_PATH;make clean; cd -


.PHONY:output
output:
	mkdir ${ROOT_PATH}/output
	cp ${ROOT_PATH}/http ${ROOT_PATH}/output
	mkdir ${ROOT_PATH}/output/wwwroot
	cp ${ROOT_PATH}/wwwroot/root.html  ${ROOT_PATH}/output/wwwroot
	mkdir ${ROOT_PATH}/output/wwwroot/cgi-bin
	cp ${ROOT_PATH}/wwwroot/cgi-bin/sql ${ROOT_PATH}/output/wwwroot/cgi-bin
	cp ${ROOT_PATH}/control.sh ${ROOT_PATH}/output
	cp ${ROOT_PATH}/log ${ROOT_PATH}/output
	mkdir ${ROOT_PATH}/output/wwwroot/pa
	cp ${CAL_PATH}/cal ${ROOT_PATH}/output/wwwroot/pa
    
EOF

make


