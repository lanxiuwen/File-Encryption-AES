#include"CryptoFuntion.h"
#include"FileFunction.h"

bool EnCryptoFile(char * file_name, unsigned char * key)
{
	unsigned char Buff[16];//存储待加密数据
	unsigned char xorBlock[AES::BLOCKSIZE];
	unsigned char outBlock[AES::BLOCKSIZE];//输出数据块

	//加密后文件的名字
	string newFileName(file_name);
	int dot_pos;
	for (dot_pos = newFileName.size() - 1; dot_pos >= 0; dot_pos--)
	{
		if (newFileName[dot_pos] == '.')
			break;
	}
	if (dot_pos > 0)
	{
		newFileName.insert(dot_pos, "_Encryped");
	}


	ofstream ofile(newFileName,ios::binary);//输出加密后的文件

	fstream infile(file_name,ios::binary|ios::in);
	try 
	{
		if (!infile)
		{
			throw "file open erro";
		}
	}
	catch (...)
	{
		return false;
	}



	long fileSize = SizeOfFile(file_name);
	long Round = fileSize / BUFFKSIZE;
	int rest = fileSize%BUFFKSIZE;

	memset(xorBlock, 0, AES::BLOCKSIZE);//置零
	AESEncryption aesEncryptor;//加密实体
	aesEncryptor.SetKey(key, AES::DEFAULT_KEYLENGTH);//设置加密密钥

	//对前round组数据加密
	for (long i = 0; i<Round; i++)
	{
		ReadBuffFromFile(Buff, infile);//读入数据
		aesEncryptor.ProcessAndXorBlock(Buff, xorBlock, outBlock);//加密
		WriteDataFromBuff(outBlock, ofile);//输出加密后的数据

		ofile.flush();

	}
	//最后一轮数据处理，补零
	if (rest != 0)
	{
		unsigned char restBuff[16];
		memset(restBuff, rest, 16);
		infile.read((char*)restBuff, rest);
		aesEncryptor.ProcessAndXorBlock(restBuff, xorBlock, outBlock);
		WriteDataFromBuff(outBlock, ofile);//输出加密后的数据

	}

	infile.close();
	ofile.close();

	return true;
}

bool DeCryptoFile(char * file_name, unsigned char * key)
{
	unsigned char Buff[16];//存储待解密数据
	unsigned char xorBlock[AES::BLOCKSIZE];
	unsigned char outBlock[AES::BLOCKSIZE];//输出数据块

   //解密后文件的名字
	string newFileName(file_name);
	int dot_pos;
	for (dot_pos = newFileName.size() - 1; dot_pos >= 0; dot_pos--)
	{
		if (newFileName[dot_pos] == '.')
			break;
	}
	newFileName.insert(dot_pos, "_Decryped");

	ofstream ofile(newFileName,ios::binary);//输出解密后的文件

	fstream infile(file_name,ios::binary|ios::in);

	if (!infile)
	{
		throw "file open erro";
		return false;
	}


	long fileSize = SizeOfFile(file_name);

	//int rest = fileSize - Round*BUFFKSIZE;
	long Round = fileSize / BUFFKSIZE;
	memset(xorBlock, 0, AES::BLOCKSIZE);//置零
	AESDecryption aesDecryptor;//加密实体
	aesDecryptor.SetKey(key, AES::DEFAULT_KEYLENGTH);//设置解密密钥

													 //对前round组数据解密
	for (long i = 0; i<(Round-1); i++)
	{
		ReadBuffFromFile(Buff, infile);//读入数据
		aesDecryptor.ProcessAndXorBlock(Buff, xorBlock, outBlock);//解密
		WriteDataFromBuff(outBlock, ofile);//输出加密后的数据
										   //cout.write((char*)outBlock, BUFFKSIZE);
	}
	//最后一轮数据处理
	ReadBuffFromFile(Buff, infile);//读入数据
	aesDecryptor.ProcessAndXorBlock(Buff, xorBlock, outBlock);//解密

	int bitrest = outBlock[15];
	ofile.write((char*)outBlock, bitrest);
	//for (int i = 0; i < bitrest; i++)
	//{
	//	ofile << outBlock[i];
	//	ofile.flush();

	//}


	//if (rest != 0)
	//{
	//	unsigned char restBuff[16] = { 0 };
	//	infile.read((char*)restBuff, rest);
	//	aesDecryptor.ProcessAndXorBlock(restBuff, xorBlock, outBlock);
	//	WriteDataFromBuff(outBlock, ofile);//输出解密后的数据
	//}


	infile.close();
	ofile.close();

	return true;
}