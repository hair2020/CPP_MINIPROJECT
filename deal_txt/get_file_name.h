// 读取文件夹内的文件
#include <stdio.h>
#include <vector> // 类模板
#include <string>
#include "dirent.h" // 获取文件夹文件
using namespace std;

vector<string> list_dir(const char* path) {

    vector<string> dirVec;
    struct dirent* entry; // 声明结构体指针
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