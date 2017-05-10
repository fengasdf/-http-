#include "http.h"

using namespace std;

static int SetNonBlock(int);
static stack<task_t*> g_readwrite;
static int g_listen_fd = -1;


static void SetAddr(const char *pszIP,const unsigned short shPort,struct sockaddr_in &addr)
{
        bzero(&addr,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(shPort);
        int nIP = 0;
        if( !pszIP || '\0' == *pszIP   
                || 0 == strcmp(pszIP,"0") || 0 == strcmp(pszIP,"0.0.0.0") 
                || 0 == strcmp(pszIP,"*") 
              )
        {
                    nIP = htonl(INADDR_ANY);
                }
        else
        {
                    nIP = inet_addr(pszIP);
                }
        addr.sin_addr.s_addr = nIP;
    
}


static int CreateTcpSocket(const unsigned short shPort /* = 0 */,const char *pszIP /* = "*" */,bool bReuse /* = false */)
{
        int fd = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
        if( fd >= 0 ){
            if(shPort != 0){
                if(bReuse){
                    int nReuseAddr = 1;
                    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&nReuseAddr,sizeof(nReuseAddr));
                }
                struct sockaddr_in addr ;
                SetAddr(pszIP,shPort,addr);
                int ret = bind(fd,(struct sockaddr*)&addr,sizeof(addr));
                if( ret != 0){
                    close(fd);
                    return -1;
                }
            }
        }
        return fd;
}

int co_accept(int fd, sockaddr_in *p, socklen_t *plen){

        return accept(fd, (struct sockaddr*)p, plen);
}

void *readwrite_routine(void *arg){
    co_enable_hook_sys();
    
    task_t *task = (task_t*)arg;
    for(;;){

        if (task->fd == -1){
            g_readwrite.push(task);
            co_yield_ct();
            continue;
        }

        int fd = task->fd;
        task->fd = -1;
        for (;;){

            struct pollfd pf;
            pf.fd = fd;
            pf.events = (POLLIN|POLLERR|POLLHUP);
            co_poll(co_get_epoll_ct(), &pf, 1, 1000);
            handler_in((void*)fd);
        }

    }

}

void *acceptwrite_routine(void *arg){

    co_enable_hook_sys();
    
    for (;;){

        if (g_readwrite.empty()){
            
            struct pollfd pf;
            pf.fd = -1;
            poll(&pf, 1, 1000);//wait 1s
            continue;
        }

        struct sockaddr_in addr;
        bzero(&addr, sizeof(addr));
        socklen_t len = sizeof(addr);
        int fd = co_accept(g_listen_fd, &addr, &len);
        if (fd < 0){
            struct pollfd pf;
            pf.fd = g_listen_fd;
            pf.events = (POLLIN|POLLERR|POLLHUP);
            co_poll(co_get_epoll_ct(), &pf, 1, 1000);
            continue;
        }

        if (g_readwrite.empty()){
            close(fd);
            continue;
        }
        SetNonBlock(fd);
        task_t *task = g_readwrite.top();
        g_readwrite.pop();
        task->fd = fd;
        co_resume(task->co);

    }


}


static int SetNonBlock(int iSock){

    int iFlags;

        iFlags = fcntl(iSock, F_GETFL, 0);
        iFlags |= O_NONBLOCK;
        iFlags |= O_NDELAY;
        int ret = fcntl(iSock, F_SETFL, iFlags);
        return ret;

}




int main(int argc, char *argv[]){

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    g_listen_fd = CreateTcpSocket(port, ip, true);
    listen(g_listen_fd, 1024);

    int font = atoi(argv[3]);
    int allfont = atoi(argv[4]);
    SetNonBlock(g_listen_fd);

    for (int i = 0; i < allfont; i++){
        
        int pid = fork();
        if (pid < 0){
            cout <<"fork error"<<endl;
            break;
        }
        if (pid == 0)
            continue;

        for (int j = 0; j < font; j++){
            
            task_t *task = (task_t *)calloc(1, sizeof(task_t));
            task->fd = -1;

            co_create(&(task->co),NULL, readwrite_routine, task );
            co_resume(task->co);
        }
        stCoRoutine_t *accept_co = NULL;
        co_create(&accept_co, NULL, acceptwrite_routine, 0);
        co_resume(accept_co);

        co_eventloop(co_get_epoll_ct() ,0, 0);
        exit(0);
    }



return 0;



}
