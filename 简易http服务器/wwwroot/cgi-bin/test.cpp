/*************************************************************************
	> File Name: test.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Tue 18 Apr 2017 06:15:02 PM PDT
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<mysql.h>

using namespace std;


int main(){



    printf("MYSQL client version: %s\n", mysql_get_client_info());
    return 0;


}
