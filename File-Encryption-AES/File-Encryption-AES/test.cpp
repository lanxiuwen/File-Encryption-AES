#include<iostream>
#include<fstream>
#include"FileFunction.h"
#include"CryptoFuntion.h"

using namespace std;

int main(void)
{
	unsigned char key[AES::DEFAULT_KEYLENGTH];
	
	string fileName;
	string defilename;
	cout << "�������ļ���" << endl;
	cin >> fileName;

	EnCryptoFile((char*)fileName.c_str(), key);

	cout << "�����ܵ��ļ�" << endl;
	cin >> defilename;

	DeCryptoFile((char *)defilename.c_str(), key);

	return 0;


	
}