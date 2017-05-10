/*************************************************************************
	> File Name: MySql.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Tue 18 Apr 2017 05:41:13 PM PDT
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<mysql.h>
#include<cstring>
using namespace std;


const int SIZE = 100;

void static handing(char* &str, char* &query){

    while (*query != '=')
            query++;
    str = ++query;
    while (*query != '&'&& *query != 0)
        query++;
    *query = 0;
    query++;


}

static void hand_query(int &mod, char* &name, int &age, char *&where, char *query){
   
    char *str = NULL;
    handing(str, query);
    mod = atoi(str);
    handing(where, query);
    handing(name, query);
    if (3 == mod)
        return;
    handing(str, query);
    age = atoi(str);
}



void insert(MYSQL *conn, char *name, int age, char *where){
    char buf[100] = {0};

    sprintf(buf, "INSERT %s VALUES('%s', %d)", where, name, age);
    mysql_query(conn, buf);
    printf("Insert sucess");

}
void creat(MYSQL *conn, char *name , int age, char *where){
    
    char buf[100] = {0};

    sprintf(buf, "CREATE TABLE %s(name VARCHAR(25), age INT(2))", where);
    mysql_query(conn, buf);
    insert(conn, name, age, where);
    printf("creat sucess\n");

}


void find(MYSQL *conn, char *name, char *where){
    MYSQL_RES *result;
    MYSQL_ROW row;
    char buf[100] = {0};
    sprintf(buf, "SELECT * FROM %s", where);
    mysql_query(conn, buf);
    result = mysql_store_result(conn);
    if (NULL == result)
        cout << "NULL" << endl;
    int num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result))){
        
        if (strcmp(row[0], name) == 0)
        for (int i = 0; i < num_fields; i++){
            printf("%s ", row[i] ? row[i] : "NULL");
        }
    }
    mysql_free_result(result);

    
}



void modifier(MYSQL *conn, char *name, int age, char *where){

    char buf[100] = {0};
    char re[100] = {0};
    sprintf(buf, "delete from %s where username = '%s'", where, name);
    mysql_query(conn, buf);
    insert(conn, name, age, where);
    printf("modifier sucess");

}

void my_delete(MYSQL*conn, char *name, char *where){


    char buf[100] = {0};
    char re[100] = {0};
    sprintf(buf, "delete from %s where username = '%s'", where, name);
    mysql_query(conn, buf);
    printf("delete sucess");

}

int hand(char *query){
    
    int mod = 0;
    char *name = NULL;
    char buf[100] ={0};
    int age = 0;
    char *where = NULL;
    hand_query(mod, name, age, where, query);
    MYSQL *conn = new MYSQL;
    conn = mysql_init(NULL);
    if (conn == NULL){

        printf("ERROR %u: %s\n", mysql_errno(conn), mysql_error(conn));

        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "root", 
                           NULL, "tq", 0, NULL, 0)==NULL){

        printf("ERROR %u:%s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }
    switch(mod){

        case 1:creat(conn, name, age, where);
        break;
        case 2:insert(conn, name, age,where);
        break;
        case 3:find(conn, name,where);
        break;
        case 4:modifier(conn, name, age, where);
        break;
        case 5:my_delete(conn, name, where);
        default:
        break;
    }


    mysql_close(conn);
    



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
    
    char str[100] = "mod=1&where=tbq&name=cao&age=20";
    //char str1[100] = "mod=2&where=tbq&name=cao&age=20";
    //char str2[100] = "mod=3&where=tbq&name=cao&age=20";
    char str3[100] = "mod=4&where=tbq&name=cao&age=60";
    //hand(str);
    hand(query_string);
    printf("\n");
    return 0;
}
