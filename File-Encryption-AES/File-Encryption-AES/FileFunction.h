#pragma once

#define BUFFKSIZE 16
#define BuffRows 64
#include<fstream>
using namespace std;


long long SizeOfFile(char * file_loc);
void ReadBuffFromFile(unsigned char * buff, fstream &infile);
void WriteDataFromBuff(unsigned char * buff, ofstream &ofile);
void ClearBuff(char * Buff);