# 2017年安全校招生排位赛个人答卷

1. 李辉
2. 手机恶意软件中常用的控制和回传方式及优缺点
3. 假设对自己的工作岗位不是很感兴趣了怎么办？


11. 实现一个守护进程
```C
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>

void init_daemon() {
    int pid;
    int i;
    if ((pid=fork()) < 0) {
        exit(-1); //fork失败，退出 
    } else if(pid) {//是父进程，结束父进程 
        exit(0);
    }
    //是第一子进程，后台继续执行 
    setsid();//第一子进程成为新的会话组长和进程组长 
    //并与控制终端分离 
    if(pid=fork())
        exit(0);//是第一子进程，结束第一子进程 
    else if(pid< 0)
        exit(1);//fork失败，退出 
    //是第二子进程，继续 
    //第二子进程不再是会话组长 
    
    for(i=0;i< NOFILE;++i)//关闭打开的文件描述符 
        close(i);
    chdir("/tmp");//改变工作目录到/tmp 
    umask(0);//重设文件创建掩模 
    return;
}

int main() {
    init_daemon();
    // 睡眠, 以观察现象
    sleep(10);
}
```