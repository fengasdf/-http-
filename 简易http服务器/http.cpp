/*************************************************************************
	> File Name: http.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sun 02 Apr 2017 07:32:21 PM PDT
 ************************************************************************/

#include"http.h"

int ret = 0;
void printf_log(string s){

        //cout << s << endl;
}

int init_fd(int socketi, char* str){

    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(inet_addr(str));
    addr.sin_port = htons(PORT);

    int err = bind(socketi, (struct sockaddr*)&addr, sizeof(addr));
    if (err < 0){
        printf_log("bind error");
        ret = -1;
    }
    int on = 0;
    setsockopt( socketi, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
    err = listen(socketi, 5);
    if (err < 0){
        printf_log("listen error");
        ret = -1;
    }
    return socketi;
}



static int get_line(int fd, char *buf){

    char ch = 0;
    char next = 0;
    int i = 0;
    int err = 0;
    while (ch != '\n'){

        int size = read(fd, &ch, 1);
        if (size <= 0){
            ch = '\n';
        }
        
        if (ch != '\n' && ch != '\r'){

            buf[i++] = ch;
        }
        else{
            if (ch == '\r'){

                err = recv(fd, &next, 1, MSG_PEEK);
                if (err < 0){
                    printf_log("recv error");
                    return -1;
                }

                if (next == '\n'){

                    err = read(fd, &ch, 1);
                    if (err < 0){
                         printf_log("recv error");
                        return -1;
                    }

                }//if

                ch = '\n';

            }

        }//else


    }//while


buf[i] = 0;

    return 1;
}

static void clean_header(int fd){


    char ch[100] = {0};
    get_line(fd, ch);
    while (strlen(ch) != 0){

        get_line(fd, ch);
    }



}

static int hand_cgi(int fd, char* path, char * argument){
    
    char line[SIZE/2] = {0};
    char length[10] = {0};
    int i_length = 0;
    char method[10] = {0};
    if (strlen(argument) == 0){
        sprintf(method, "METHOD=POST");
        while (get_line(fd, line) > 0){
            if (strncmp(line, "Content-Length", 16) == 0){
                i_length = atoi(line + 16);
                break;
            }

        }//while
        clean_header(fd);
        sprintf(length, "Content-Length=%d", i_length);
        putenv(length);

    }//if
    else{
        sprintf(method, "METHOD=GET");   
        char str[100] = {0};
        sprintf(str, "QESTRING=%s", argument);
        if (putenv(str) < 0){
            printf_log("she zhi huai jing cuo wu");
            ret = -1;
        }
        clean_header(fd);

    }//else
    putenv(method);
    //reponse
    char request[] = "HTTP/1.0 200 OK\r\n";
    write(fd, request, strlen(request));
    int _std[2] = {0};
    int _std2[2] = {0};
    if (pipe(_std) < 0){
        printf_log("pipe error");
        ret = -1;
    }
    if (pipe(_std2) < 0){
        printf_log("pipe2 error");
        ret = -1;
    }
    pid_t pid = fork();
    if (pid < 0){
        printf_log("fork error");
        ret = -1;
        return 0;
    }
    
    if (pid == 0){
        close(_std[0]);
        close(_std2[1]);
        
          dup2(_std[1], 1);
          dup2(_std2[0], 0);
        execl(path,path, NULL);
    
        cout << "error" << endl;
    }
    else{
        close(_std[1]);
        close(_std2[0]);
        int ch = 0;
        char string[SIZE/2] = {0};
        for (int i = 0; i < i_length; i++){
            read(fd, &ch, 1);
            string[i] = ch;
        }
        //printf("%s\n", string);
        write(_std2[1], string, strlen(string));
        if (strcmp(path, "wwwroot/pa/cal") != 0){
            while (read(_std[0], &ch, 1) > 0){
                  write(fd, &ch,1);
            }
            waitpid(pid, NULL, 0);
        }
        else{
            waitpid(pid, NULL, 0);
            write(fd, "\r\n", 2);
            struct stat file;
            stat(path, &file);
            int c_fd = open("wwwroot/pa/output.html", O_RDONLY);
            int err = sendfile(fd, c_fd, 0, file.st_size);
            if (err < 0){
                ret = 5;
                printf_log("sendfile error");
                printf("%d, %s\n", errno, strerror(errno));
        }
            

        }
        close(_std[0]);
        close(_std2[1]);

    }


}

static void get(int fd){

        char buf[2*SIZE];
    char ch;
    int i = 0;
    while (read(fd, &ch, 1) > 0){
        buf[i++] = ch;
        
    }
 //   printf("%s\n", buf);
}


void *handler_in(void *arg){
    
    pthread_detach(pthread_self());
    char method[SIZE/2] = {0};
    char buf[SIZE] = {0};
    char line[SIZE/2] = {0};
    char url[SIZE/2] = {0};
    char goal[SIZE/2] = {0};
    char argument[SIZE] = {0};
    int err = 0;
    int cgi = 0;
    int i = 0;
    char request[] = "HTTP/1.1 200 OK\r\n";
    //cout << 123 << endl;
    err =  get_line((int)arg, line);
    if (err < 0){
        ret = 1;
        goto end;
    }
    
    for (i = 0; line[i] != ' '; i++){
            method[i] = line[i];
    }
    i++;
    for (int j = 0; line[i] != ' '&&line[i] != '?'; i++){
        
        url[j++] = line[i];
    }
    //printf("%s\n" ,method);

    if (line[i] == '?'){
        i++;
        for (int j = 0; line[i] != ' '&&line[i] != '?'; i++){
        
             argument[j++] = line[i];
        }
        
    }

    if (strcasecmp(method, "POSE") != 0 && strcasecmp(method, "GET") != 0){

        printf_log("i have no use");
        printf_log("method");
        ret = 2;
        goto end;
    }
    

    
    if (strcasecmp(method, "POSE") == 0)
        cgi = 1;
    if (strcasecmp(method, "GET") == 0 && argument[0] != 0)
        cgi = 1;
    
    if (strlen(url) == 1 && strcasecmp(url , "/") == 0)
        sprintf(goal, "wwwroot/root.html");
    else sprintf(goal, "wwwroot%s", url);

    //printf("%s\n", goal);
    
    //判断文件
    struct stat file;
    err = stat(goal, &file);
    //cout << "1" << endl;
    if (err < 0){
        ret = 3;
        printf_log("file not found");
        goto end;
    }
    if (file.st_mode & S_IFDIR){
        //
    }

    if (file.st_mode & S_IXUSR || file.st_mode & S_IXGRP || file.st_mode & S_IXOTH){
        if (0 == cgi){
         ret = 4;
         printf_log("文件类型与cgi不匹配");
         goto end;
        }
    }

    if (1 == cgi){

      err =   hand_cgi((int)arg, goal, argument);
    }//cgi if
    else{

    clean_header((int)arg);
    write((int)arg, request, strlen(request));
    write((int)arg, "\r\n", 2);

   int fd = open(goal, O_RDONLY);
   err = sendfile((int)arg, fd, 0, file.st_size);
        if (err < 0){
            ret = 5;
            printf_log("sendfile error");
            printf("%d, %s\n", errno, strerror(errno));
        }

    }//cgi else

end: close((int)arg);


}





