#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream> // �����ļ�
#include <vector>
#include <string>
#include <numeric> // ���ֵ
using namespace std;

#include "get_file_name.h" // ��ȡ�ļ���
#include "split_str.h" // �ָ��ַ���
#include "save.h"
#include "unique_txt.h"

bool filter(float& x) {
    if (x < 0 || x > 70) {
        return false;
    }
    return true;
}

int main() {
    unique_txt();// ����ȥ������

    dataVec d; // ��������
    
    const char* wdirName = "avDir"; // д���ļ���
    vector<string> dirVec;
    const char* rdirName = "utxtFile"; // ��ȡ���ļ���
    dirVec = list_dir(rdirName);
    
    string dirStr, fileStr, fpStr; // ƴ��·��
    dirStr = rdirName;

    fstream file; // �����ļ�

    for (int i = 2; i < dirVec.size(); i++) { // �����ļ�,����ǰ������. ..��
        
        fileStr = dirVec[i].data();
        cout << "�����ļ�������" << i - 1 << " ���ƣ�" << fileStr << '\n';

        fpStr = dirStr + "/" + fileStr; // ���ƴ��
        //cout << fpStr << endl;

        file.open(fpStr, ios::in); // ���ļ�
        
        string tempStr;
        int _count = 0;
        while (getline(file, tempStr)) {

            // cout << tempStr << endl;

            vector<string> tokens;
            string delim = "/   \n"; // �ָ��
            tokens = split(tempStr, delim);

            string dateDay = tokens[0]; // 20190101
            string valueStr = tokens[2]; // ֵ
            string dateMon = dateDay.substr(0, 6); // 201901

            float value = atof(valueStr.c_str()); // תfloat

            if (filter(value)) {
                d.dataMap[dateDay].push_back(value); // ���ֵ
                d.dataMap[dateMon].push_back(value);
            }

        }
        file.close();
        char newLineStr[100]; // ���ɵ�����
        ofstream MyFile; // ����д�ļ�����
        MyFile.open(fpStr.replace(0, 8, wdirName), ios::app); // ׷��д�ļ�

        for (auto i = d.dataMap.begin(); i != d.dataMap.end(); ++i) { // ����map
            // cout << i->first << "��"<< i->second.size() << endl;
            float avFloat = accumulate(i->second.begin(), i->second.end(), 0.0) / i->second.size(); // accumulate�ۼӣ����ֵ
            // cout << i->first << "��"<< avFloat << '\n';

            sprintf_s(newLineStr, sizeof(newLineStr), "%s:%f\n", i->first.c_str(), avFloat); // ������
            // cout << newLineStr << '\n';

            MyFile << newLineStr;
        }
        d.dataMap.clear();
        // �ر��ļ�
        MyFile.close();
        // break;
    }

    return 1;
}

