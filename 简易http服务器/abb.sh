#########################################################################
# File Name: abb.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: Tue 02 May 2017 12:19:04 PM PDT
#########################################################################
#!/bin/bash

Root_path=$(pwd)

va=$(pidof 'http')

kill -9 $va
