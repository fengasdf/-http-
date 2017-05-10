#include"http.h"


int main(int argc, char* argv[]){
    
    daemon(1,1);
    if (argc < 2){
        cout << "can shu error" << endl;
        exit(0);
    }
    int socketi = socket(AF_INET, SOCK_STREAM, 0);
    
    int listeni = init_fd(socketi, argv[1]);
    
    sockaddr_in addr;
    socklen_t len = 0;
    pthread_t tid = 0;
    while (1){
        int connfd = accept(listeni, (struct sockaddr *)&addr, &len);
        if (connfd < 0){
            printf_log("连接失败\n");
            continue;
        }
        
        int err = pthread_create(&tid, 0, handler_in, (void *)connfd);

        if (err < 0){
            printf_log("服务线程错误");
        }
        

    }





}
