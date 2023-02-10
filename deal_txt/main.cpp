#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream> // 处理文件
#include <vector>
#include <string>
#include <numeric> // 求均值
using namespace std;

#include "get_file_name.h" // 获取文件名
#include "split_str.h" // 分割字符串
#include "save.h"
#include "unique_txt.h"

bool filter(float& x) {
    if (x < 0 || x > 70) {
        return false;
    }
    return true;
}

int main() {
    unique_txt();// 生成去重数据

    dataVec d; // 操作数据
    
    const char* wdirName = "avDir"; // 写的文件夹
    vector<string> dirVec;
    const char* rdirName = "utxtFile"; // 读取的文件夹
    dirVec = list_dir(rdirName);
    
    string dirStr, fileStr, fpStr; // 拼接路径
    dirStr = rdirName;

    fstream file; // 处理文件

    for (int i = 2; i < dirVec.size(); i++) { // 遍历文件,跳过前两个（. ..）
        
        fileStr = dirVec[i].data();
        cout << "处理文件数量：" << i - 1 << " 名称：" << fileStr << '\n';

        fpStr = dirStr + "/" + fileStr; // 完成拼接
        //cout << fpStr << endl;

        file.open(fpStr, ios::in); // 读文件
        
        string tempStr;
        int _count = 0;
        while (getline(file, tempStr)) {

            // cout << tempStr << endl;

            vector<string> tokens;
            string delim = "/   \n"; // 分割符
            tokens = split(tempStr, delim);

            string dateDay = tokens[0]; // 20190101
            string valueStr = tokens[2]; // 值
            string dateMon = dateDay.substr(0, 6); // 201901

            float value = atof(valueStr.c_str()); // 转float

            if (filter(value)) {
                d.dataMap[dateDay].push_back(value); // 添加值
                d.dataMap[dateMon].push_back(value);
            }

        }
        file.close();
        char newLineStr[100]; // 生成的新行
        ofstream MyFile; // 创建写文件对象
        MyFile.open(fpStr.replace(0, 8, wdirName), ios::app); // 追加写文件

        for (auto i = d.dataMap.begin(); i != d.dataMap.end(); ++i) { // 遍历map
            // cout << i->first << "："<< i->second.size() << endl;
            float avFloat = accumulate(i->second.begin(), i->second.end(), 0.0) / i->second.size(); // accumulate累加，求均值
            // cout << i->first << "："<< avFloat << '\n';

            sprintf_s(newLineStr, sizeof(newLineStr), "%s:%f\n", i->first.c_str(), avFloat); // 生成行
            // cout << newLineStr << '\n';

            MyFile << newLineStr;
        }
        d.dataMap.clear();
        // 关闭文件
        MyFile.close();
        // break;
    }

    return 1;
}

