/*************************************************************************
	> File Name: abb.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Mon 08 May 2017 05:03:33 AM PDT
 ************************************************************************/

#include<iostream>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define SIZE 100
using namespace std;


int main(){
    
    char *p = NULL;
      int i_length = 0;
    char query_string[SIZE/2] = {0};
    char *length = NULL;
   p = getenv("METHOD");
   if (strcmp(p, "GET") == 0){

           char *s = getenv("QESTRING");
           memcpy(query_string, s, strlen(s)); 
   }//if
   else{
       length = getenv("Content-Length");
       i_length = atoi(length);
       char ch = 0;
       for (int i = 0; i < i_length; i++){
           ch = getc(0);
           query_string[i] = ch;
       }
   }
 //   char query_string[50] = "str=asdf";
    char calstring[100] = {0};
    int i = 0;
    for (; query_string[i] != '='; i++){        
        ;
    }
    i++;
    for (int j = 0; i < SIZE/2; i++, j++)
        calstring[j] = query_string[i];
    
    //char test[100] = "asd";
    execl("/home/cao/linux/http/wwwroot/pa/pa_chong.py", "pa_chong.py",calstring, (char*)0);
   // printf("%s\n", calstring);
    printf("\n");
    return 0;
}
