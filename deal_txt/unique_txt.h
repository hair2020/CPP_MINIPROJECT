#include <map>
#include <iostream>
#include <iomanip>
#include <fstream> // �����ļ�
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;


void unique_txt() {

    vector<string> dirVec;
    const char* rdirName = "txtFile"; // ��ȡ���ļ���
    const char* udirName = "utxtFile"; // unique dir

    dirVec = list_dir(rdirName);

    string dirStr, fileStr, fpStr; // ƴ��·��
    dirStr = rdirName;

    fstream file; // �����ļ�
    vector<string> d; // save data
    for (int i = 2; i < dirVec.size(); i++) { // �����ļ�,����ǰ������. ..��
        
        fileStr = dirVec[i].data();
        fpStr = dirStr + "/" + fileStr;
        // cout << fpStr << endl;

        file.open(fpStr, ios::in); // ���ļ�

        string tempStr;
        int _count = 0;
        while (getline(file, tempStr)) {
            if (_count < 2) { // ����ǰ����
                _count += 1;
                continue;
            }
            d.push_back(tempStr);
        }
        file.close();

        cout << fileStr << "ȥ��ǰ��������" << d.size();
        auto new_end = unique(d.begin(), d.end());
        d.erase(new_end, d.end());
        cout << "-->ȥ�غ���������" << d.size() << endl;
        
        char newLineStr[100]; // ���ɵ�����
        ofstream MyFile; // ����д�ļ�����
        MyFile.open(fpStr.replace(0, 7, udirName), ios::app); // ׷��д�ļ�
        
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

