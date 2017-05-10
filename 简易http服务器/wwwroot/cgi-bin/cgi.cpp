/*************************************************************************
	> File Name: cgi.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sun 09 Apr 2017 11:52:48 AM PDT
 ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 1024
using namespace std;

int hand(char *q){

    char *num = NULL;
  char *num_2 = NULL;
  int num1 = 0;
  int num2 = 0;
  while (*q != '=')
  	q++;
    q++;
  num = q;
  while (*q != '&')
  	q++;
  *q = 0;
  num1 = atoi(num);
  
  while (*q != '=')
      q++;
    q++;
  num_2 = q;
  num2 = atoi(num_2);
    
    printf("<html>\n");
    printf("<head><h2>%d + %d = %d</h2></head>\r\n", num1, num2, num1+num2);
    printf("</html>\n");


}

int main(){

    printf("Content-Type:text/html;charset=ISO-8859-1\n\n");           
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
  // printf("%s\n", p);
   hand(query_string);
    printf("\n");
   // return 0;
    return 0;
}




