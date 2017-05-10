#########################################################################
# File Name: control.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: Tue 02 May 2017 11:14:39 AM PDT
#########################################################################
#!/bin/bash

Root_path=$(pwd)
main=${Root_path}/http
file=${Root_path}/log

source ${file}


function my_start(){
    ${main} $Ip $Port

}

function my_end(){

ip=$(pidof 'http')

kill -9 $ip

}

str=$1

case "$1" in
    "start")
        echo "start"
        my_start
        ;;
    "restart")
        echo "restart"
        ;;
    "stop")
        echo "stop"
        my_end
        ;;
    *)
        echo "other"
        ;;
esac
