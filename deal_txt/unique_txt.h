#include <map>
#include <iostream>
#include <iomanip>
#include <fstream> // 处理文件
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;


void unique_txt() {

    vector<string> dirVec;
    const char* rdirName = "txtFile"; // 读取的文件夹
    const char* udirName = "utxtFile"; // unique dir

    dirVec = list_dir(rdirName);

    string dirStr, fileStr, fpStr; // 拼接路径
    dirStr = rdirName;

    fstream file; // 处理文件
    vector<string> d; // save data
    for (int i = 2; i < dirVec.size(); i++) { // 遍历文件,跳过前两个（. ..）
        
        fileStr = dirVec[i].data();
        fpStr = dirStr + "/" + fileStr;
        // cout << fpStr << endl;

        file.open(fpStr, ios::in); // 读文件

        string tempStr;
        int _count = 0;
        while (getline(file, tempStr)) {
            if (_count < 2) { // 跳过前两行
                _count += 1;
                continue;
            }
            d.push_back(tempStr);
        }
        file.close();

        cout << fileStr << "去重前数据量：" << d.size();
        auto new_end = unique(d.begin(), d.end());
        d.erase(new_end, d.end());
        cout << "-->去重后数据量：" << d.size() << endl;
        
        char newLineStr[100]; // 生成的新行
        ofstream MyFile; // 创建写文件对象
        MyFile.open(fpStr.replace(0, 7, udirName), ios::app); // 追加写文件
        
        for (int i = 0; i < d.size(); i++) {
            sprintf_s(newLineStr, sizeof(newLineStr), "%s\n", d[i].c_str());
            //cout << newLineStr;
            MyFile << newLineStr;
        }
        /*vector<string>().swap(d);*/
        d.clear();
        MyFile.close();
    }
}

