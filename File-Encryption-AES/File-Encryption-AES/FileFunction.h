#pragma once

#define BUFFKSIZE 16

#include<fstream>
using namespace std;
long SizeOfFile(char * file_loc);
void ReadBuffFromFile(unsigned char * buff, fstream &infile);
void WriteDataFromBuff(unsigned char * buff, ofstream &ofile);
