# 2017年安全校招生排位赛个人答卷

1. 李辉

2. 手机恶意软件中常见的控制和信息回传方式

3. 假设对自己的工作岗位不是很感兴趣了怎么办？

如果是对本岗位技术方向不感兴趣了，那么一方面首先将本职工作做好，同时尝试扩展此方向上的其他知识及应用，不断认识此方向的技术发展，在有全面的认识之后再来思考对岗位的兴趣。另外积极做好与leader的沟通，通过leader的指导和协调解决此问题。

5. excel

=VLOOKUP($C3,$C$3:$E$12,3,TRUE)

7.  GFW原理及翻墙

GFW主要原理有IP黑名单和DNS劫持两种。其中IP黑名单就是对特定目的ip包进行丢包策略，DNS劫持则是通过对特定url做DNS解析时，进行错误的解析。
现有的翻墙方法主要有搭建代理服务器和修改host映射两种方法。通过代理的方法比较彻底，网络也相对稳定，但是一般需要一定费用购买ip，需要一定的网络技术，修改host映射的方法简单，但是不能翻墙效果受限于host文件中有效映射个数，且不稳定。


11. 实现一个守护进程

代码
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
`

12. mq 调研

此处调研kafka与nsq
kafka:

|mq|kafka|nsq|
|-----|:----:|----:|
|组成|broker,topic,partion,producer,consumer,consumer group|nsqd,lookupd,nsqadmin,topic,producer,consumer|
|服务发现|借助zookeeper|借助自带的lookupd，nsqd需向lookupd注册|
|持久化|持续将日志落地，|
|水平扩展|支持|支持|

14. 汇编

实现的循环如下:
```C
int func() {
    int i;
    int j = 12;
    for (i=0; i <=9; i ++) {
        if (j <= 100) {
            j = j << 2;
        } else {
            while (j > 100) {
                j -= 100;
            }
        }
    }

    return j;
}

```
返回结果为 352
`

16. Nginx反向代理原理

当我们要屏蔽服务器集群相关信息时，就可以找一个代理服务器，提供对外服务。此时只暴露代理服务器的ip及端口，客户端将请求发到代理服务器之后，代理服务器以负载均衡的方法，将请求转发至特定的内部服务器里。此过程内部真正提供服务的服务器对外透明。
而正向代理则是为客户端做代理，客户端因为无法直接访问服务，则通过架设正向代理服务器，将请求发往代理服务器后，由代理服务器代替客户端去访问服务器。代理服务器拿到结果后，再返回给客户端。
简言之，反向代理用于代替服务器提供服务，正向代理用来代替客户端去请求。
nginx 可以通过upstream模块及location结合proxy实现对特定uri的代理


19. string 类存取二进制

由于二进制中存在"0x00"的字符，在使用string类存储读取二进制时，可能会出现截断字符串的现象，导致存储的数据不全。这里关注string类的如下两个构造函数.
```C++
// constructor
string (const char* s);
string (const char* s, size_t n);

// raw binary data
char bData[] = {'a', 'b', 'c', '0x00', 'd'};
```
`

假设已有存储二进制数的char型数组 bData, 那么第一个构造函数在遇到'0x00'时，认为字符串结束。正确的方法应该是使用第二个构造函数。
` std::string bStrData (bData, sizeof(bData))`
这样便能保证所有的数据被存储到bStrData中。总结来说就是要通过指定长度，以避免因为字符'0x00'引起的截断现象。

23. 代码问题及g_stA初始化过程及全局类对象的构造析构函数如何被“crt”调用

类A中使用了全局变量g_p，破坏了类的封装性，在类外对g_p的修改很可能会引起程序的奔溃。同时abort()的存在导致程序的异常退出，g_stA全局类在构造完成,执行相关工作后，无法执行析构函数。

25. url 规范化

url规范化可以减少搜索引擎索引及未来爬虫压力。url规范化可以从以下几点着手。
- 大小写统一。协议名及主机名统一为小写，转义字符统一为大写。
- 默认后缀和端口可以统一为删除状态。如主页url有的带index.html，有的不带。此时可以统一为不带。
- 去除无用多余的的查询串，如多余的'?'及'#'。
- 保证查询变量的有序。
- 去除路径中的多余的'/'，缺少时应当补充完整。

26. 字符串负载

负载的base64为:  eNp7umT5i5Ydz3tWP58z/+mOVgBXawq3


28. RAID原理

基本原理:把多个便宜的小磁盘组合到一起，成为一个磁盘组，使性能达到或超过一个容量巨大、价格昂贵的磁盘
- RAID0:
将连续数据分段存储于各个磁盘中，读写均可以并行处理。至少需两块磁盘。
缺点：无冗余备份；有点：读取速度快
- RAID1:
多块磁盘互为备份。至少两块磁盘，实际容量为磁盘中最小的一个。至少需要两块磁盘
优点：安全，读快；缺点：空间利用率低，写慢。
- RAID01
RAID0与RAID1相结合，两组RAID0互为备份。空间利用率为50%。至少需要四块磁盘
- RAID10
同样是RAID0与RAID1结合，但是其是两组RAID1组成RAID0。至少需要四块磁盘。空间利用率为50%。
- RAID5:
把数据数据分段存储各个磁盘上，并将奇偶检验信息也分布在磁盘上。当有一块磁盘出现问题，可以通过奇偶校验恢复。此特性保证了其有略弱于RAID1的可靠性，但是却有了更高的磁盘利用率和读写速度。至少四块磁盘，空间利用率至少为75%。
如果有4块，RAID0坏一块，则阵列数据丢失，RAID1四块都丢才会丢。。。，RAID10如果同一个RAID1整列的两块都坏掉，则数据丢失，假设两块分别在两个阵列，则不影响。



29. 最长子串

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
`
