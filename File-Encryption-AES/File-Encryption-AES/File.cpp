#pragma once
#include"FileFunction.h"

using namespace std;

long SizeOfFile(char * file_loc)
{
	long size;
	fstream file(file_loc);
	if (!file)
		return -1;
	file.seekg(0, ios::end);
	size = file.tellg();
	file.close();
	return size;
}

void ReadBuffFromFile(unsigned char * buff, fstream &infile)//��ȡһ��BUFF
{
	infile.read((char*)buff, BUFFKSIZE);
}

void WriteDataFromBuff(unsigned char * buff, ofstream & ofile)//дһ��buff
{
	ofile.write((char*)buff, BUFFKSIZE);
}

