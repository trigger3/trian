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
    setsid();//第一子进程成为新的会话组长和进程组长 
    if(pid=fork())
        exit(0);//是第一子进程，结束第一子进程 
    else if(pid< 0)
        exit(1);//fork失败，退出 
    
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
16. Nginx反向代理原理

网络上存在客户端与服务器，当我们要屏蔽服务器集群相关信息时，就可以找一个代理服务器，提供对外服务。此时只暴露代理服务器的ip及端口，客户端将请求发到代理服务器之后，代理服务器以负载均衡的方法，将请求转发至特定的内部服务器里。此过程内部真正提供服务的服务器对外透明。
而正向代理则是为客户端做代理，客户端因为无法直接访问服务，则通过架设正向代理服务器，将请求发往代理服务器后，由代理服务器代替客户端去访问服务器。代理服务器拿到结果后，再返回给客户端。
简言之，反向代理用于代替服务器提供服务，正向代理用来代替客户端去请求。

19. string 类存取二进制

由于二进制中存在"0x00"的字符，在使用string类存储读取二进制时，可能会出现截断字符串的现象，导致存储的数据不全。这里关注string类的如下两个构造函数.
```C++
// constructor
string (const char* s);
string (const char* s, size_t n);

// raw binary data
char bData[] = {'a', 'b', 'c', '0x00', 'd'};

```
假设已有存储二进制数的char型数组 bData, 那么第一个构造函数在遇到'0x00'时，认为字符串结束。正确的方法应该是使用第二个构造函数。
` std::string bStrData (bData, sizeof(bData))`
这样便能保证所有的数据被存储到bStrData中。总结来说就是要通过指定长度，以避免因为字符'0x00'引起的截断现象。

25. url 规范化

url规范化可以减少搜索引擎索引及未来爬虫压力。url规范化可以从以下几点着手。
- 大小写统一。协议名及主机名统一为小写，转义字符统一为大写。
- 默认后缀和端口可以统一为删除状态。如主页url有的带index.html，有的不带。此时可以统一为不带。
- 去除无用多余的的查询串，如多余的'?'及'#'。
- 保证查询变量的有序。
- 去除路径中的多余的'/'，缺少时应当补充完整。

27. 最长子串

```C++
/*
 * 主要思想：
 * 动态规划+map 
 */

#include <iostream>
#include <map>

int main() {
    std::string rawStr;
    
    while (std::cin >> rawStr) {
        int startIdx = 0, longest = 0; //最长子串的开始下标及长度
        int curLen = 0, curIdx = 0; //当前最长子串的开始下表及长度
        std::map<char, int> strMap; //存储当前最长子串每个字符及其对应的下标
        std::map<char, int>::iterator iter;

        int idx = 0;
        for (idx = 0; rawStr[idx] != '\0'; idx ++) {
            iter = strMap.find(rawStr[idx]);
            if ( iter == strMap.end()) { //当没有找到重复的字符时，当前最长子串的长度增加，开始下标不变
                strMap[rawStr[idx]] = idx;
                curLen ++;
            } else {
                if ( iter->second >= curIdx) { //当当前最长子串的开始下标小于重复的字符下标时，调整当前最长子串的开始下标及长度
                    curIdx = iter->second+1;
                    curLen = idx - curIdx + 1;
                } else { //当当前最长子串开始下标小于大于重复子串时，不用管，长度加一
                    curLen ++; 
                }
                strMap[rawStr[idx]] = idx; //更新映射
            }

            if (curLen > longest) { //修正最长子串长度
                longest = curLen;
                startIdx = curIdx;
            }
        }
        std::string longestStr(rawStr, startIdx, longest);
        std::cout << longestStr << std::endl;

    }
}
```
