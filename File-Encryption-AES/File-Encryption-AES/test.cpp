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
	cout << "待加密文件：" << endl;
	cin >> fileName;

	EnCryptoFile((char*)fileName.c_str(), key);

	cout << "带解密的文件" << endl;
	cin >> defilename;

	DeCryptoFile((char *)defilename.c_str(), key);

	return 0;


	
}