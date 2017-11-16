#include"CryptoFuntion.h"
#include"FileFunction.h"

bool EnCryptoFile(char * file_name, unsigned char * key)
{
	unsigned char Buff[16];//�洢����������
	unsigned char xorBlock[AES::BLOCKSIZE];
	unsigned char outBlock[AES::BLOCKSIZE];//������ݿ�

	//���ܺ��ļ�������
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


	ofstream ofile(newFileName,ios::binary);//������ܺ���ļ�

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

	memset(xorBlock, 0, AES::BLOCKSIZE);//����
	AESEncryption aesEncryptor;//����ʵ��
	aesEncryptor.SetKey(key, AES::DEFAULT_KEYLENGTH);//���ü�����Կ

	//��ǰround�����ݼ���
	for (long i = 0; i<Round; i++)
	{
		ReadBuffFromFile(Buff, infile);//��������
		aesEncryptor.ProcessAndXorBlock(Buff, xorBlock, outBlock);//����
		WriteDataFromBuff(outBlock, ofile);//������ܺ������

		ofile.flush();

	}
	//���һ�����ݴ�������
	if (rest != 0)
	{
		unsigned char restBuff[16];
		memset(restBuff, rest, 16);
		infile.read((char*)restBuff, rest);
		aesEncryptor.ProcessAndXorBlock(restBuff, xorBlock, outBlock);
		WriteDataFromBuff(outBlock, ofile);//������ܺ������

	}

	infile.close();
	ofile.close();

	return true;
}

bool DeCryptoFile(char * file_name, unsigned char * key)
{
	unsigned char Buff[16];//�洢����������
	unsigned char xorBlock[AES::BLOCKSIZE];
	unsigned char outBlock[AES::BLOCKSIZE];//������ݿ�

   //���ܺ��ļ�������
	string newFileName(file_name);
	int dot_pos;
	for (dot_pos = newFileName.size() - 1; dot_pos >= 0; dot_pos--)
	{
		if (newFileName[dot_pos] == '.')
			break;
	}
	newFileName.insert(dot_pos, "_Decryped");

	ofstream ofile(newFileName,ios::binary);//������ܺ���ļ�

	fstream infile(file_name,ios::binary|ios::in);

	if (!infile)
	{
		throw "file open erro";
		return false;
	}


	long fileSize = SizeOfFile(file_name);

	//int rest = fileSize - Round*BUFFKSIZE;
	long Round = fileSize / BUFFKSIZE;
	memset(xorBlock, 0, AES::BLOCKSIZE);//����
	AESDecryption aesDecryptor;//����ʵ��
	aesDecryptor.SetKey(key, AES::DEFAULT_KEYLENGTH);//���ý�����Կ

													 //��ǰround�����ݽ���
	for (long i = 0; i<(Round-1); i++)
	{
		ReadBuffFromFile(Buff, infile);//��������
		aesDecryptor.ProcessAndXorBlock(Buff, xorBlock, outBlock);//����
		WriteDataFromBuff(outBlock, ofile);//������ܺ������
										   //cout.write((char*)outBlock, BUFFKSIZE);
	}
	//���һ�����ݴ���
	ReadBuffFromFile(Buff, infile);//��������
	aesDecryptor.ProcessAndXorBlock(Buff, xorBlock, outBlock);//����

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
	//	WriteDataFromBuff(outBlock, ofile);//������ܺ������
	//}


	infile.close();
	ofile.close();

	return true;
}