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