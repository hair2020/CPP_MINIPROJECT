// 分割字符串
#include <vector>
#include <string>
#include <cstring> // 含strcpy strtok
#include <iostream>
using namespace std;

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if ("" == str) return res;

	//先将要切割的字符串从string类型转换为char*类型
	char* strs = new char[str.length() + 1]; // 加一个'\0'长度
	strcpy_s(strs, str.length() + 1, str.c_str()); // copy

	char* d = new char[delim.length() + 1];
	strcpy_s(d, delim.length() + 1, delim.c_str());
	char* ptr = NULL;
	char* p = strtok_s(strs, d, &ptr); // 拆分字符串
	while (p) {
		string s = p; //分割得到的字符串转换为string类型
		// cout << s << '\n';
		res.push_back(s); //存入结果数组
		p = strtok_s(NULL, d, &ptr); // 确保扫描位置正确
	}

	return res;
}
