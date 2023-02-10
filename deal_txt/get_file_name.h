// ��ȡ�ļ����ڵ��ļ�
#include <stdio.h>
#include <vector> // ��ģ��
#include <string>
#include "dirent.h" // ��ȡ�ļ����ļ�
using namespace std;

vector<string> list_dir(const char* path) {

    vector<string> dirVec;
    struct dirent* entry; // �����ṹ��ָ��
    DIR* dir = opendir(path);
    if (dir == NULL) {
        cout << "opendir failed" << endl;
        return dirVec;
    }

    while ((entry = readdir(dir)) != NULL) {
        // printf("%s\n",entry->d_name);
        dirVec.push_back(entry->d_name); // add
    }

    closedir(dir);
    return dirVec;
}