// �ָ��ַ���
#include <vector>
#include <string>
#include <cstring> // ��strcpy strtok
#include <iostream>
using namespace std;

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if ("" == str) return res;

	//�Ƚ�Ҫ�и���ַ�����string����ת��Ϊchar*����
	char* strs = new char[str.length() + 1]; // ��һ��'\0'����
	strcpy_s(strs, str.length() + 1, str.c_str()); // copy

	char* d = new char[delim.length() + 1];
	strcpy_s(d, delim.length() + 1, delim.c_str());
	char* ptr = NULL;
	char* p = strtok_s(strs, d, &ptr); // ����ַ���
	while (p) {
		string s = p; //�ָ�õ����ַ���ת��Ϊstring����
		// cout << s << '\n';
		res.push_back(s); //����������
		p = strtok_s(NULL, d, &ptr); // ȷ��ɨ��λ����ȷ
	}

	return res;
}
