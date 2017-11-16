#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>
#include<string>
#include<string.h>
#include<fstream>
#include"CryptoFuntion.h"
#include"FileFunction.h"

#define CMD_COLS 80
#define CMD_LINES 25

using namespace std;

void SetScreenGrid()
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "Mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}

void SetSysCaption()
{
	system("title Sample");
}

void ClearScreen()
{
	system("cls");
}

void SetSysCaption(const char * pText)
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}

void ShowWelcome()
{
	for (int i = 0; i < 7; i++)
		cout << endl;
	cout << setw(40);
	cout << "**************" << endl;
	cout << setw(40);
	cout << "*AES文件加密软件*" << endl;
	cout << setw(40);
	cout << "**************" << endl;
}
void ShowRootMenu()
{
	cout << endl;
	cout << setw(38);
	cout << "请选择功能" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1  加密文件" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2  解密文件" << endl;
	cout << endl;

}

void WaitUser()
{
	int iInputPage = 0;
	cout << "按任意键返回" << endl;
	char c[256];
	cin >> c;
	if (c[0] == 'q')
		system("exit");
}

int GetSelect()
{
	char buf[256];
	gets_s(buf);
	return atoi(buf);
}

