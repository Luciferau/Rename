#define _CRT_SECURE_NO_WARNINGS
#include <iostream>  
#include <io.h>  //��ϵͳ�ļ����в�����ͷ�ļ�
#include <string>  
#include <sstream>
#include<vector>
#include <string.h>

using namespace std;

const int N = 3;   //���͸�ʽ�����Ϊ�ַ�����ĳ��ȣ����磬N=6��������תΪ����Ϊ6���ַ�����12תΪΪ000012

const string FileType = ".jpg";    // ��Ҫ���ҵ��ļ�����

/* ����˵�� ����ת�̶���ʽ���ַ���
���룺
n ��Ҫ������ַ�������
i ��Ҫ�ṹ��������
�����
����ת������ַ���
*/

string int2string(int n, int i)
{
	char s[BUFSIZ];
	sprintf(s, "%d", i);
	int l = strlen(s);  // ���͵�λ��	

	if (l > n)
	{
		cout << "���͵ĳ��ȴ�����Ҫ��ʽ�����ַ������ȣ�";
	}
	else
	{
		stringstream M_num;
		for (int i = 0; i < n - l; i++)
			M_num << "0";
		M_num << i;

		return M_num.str();
	}
}

 

int main()
{
	_finddata_t c_file;   // �����ļ�����

	string File_Directory = "";   //�ļ���Ŀ¼
	printf("������Ҫ�����������ļ���Ŀ¼\n");
	scanf_s("&s", &File_Directory);

	string buffer = File_Directory + "\\*" + FileType;

	//long hFile;  //win7ϵͳ��_findnext()�������Ϳ�����long��
	intptr_t hFile;   //win10ϵͳ ��_findnext()��������Ϊintptr_t ��������long��

	hFile = _findfirst(buffer.c_str(), &c_file);   //�ҵ�һ���ļ�

	if (hFile == -1L)   // ����ļ���Ŀ¼�´�����Ҫ���ҵ��ļ�
		printf("No %s files in current directory!\n", FileType);
	else
	{
		printf("Listing of files:\n");

		int i = 0;
		string newfullFilePath;
		string oldfullFilePath;
		string str_name;
		do
		{
			oldfullFilePath.clear();
			newfullFilePath.clear();
			str_name.clear();


			oldfullFilePath = File_Directory + "\\" + c_file.name;


			++i;
			str_name = int2string(N, i);    //����ת�ַ���
			newfullFilePath = File_Directory + "\\" + str_name + FileType;

			/*����������rename��const char* _OldFileName,const char* _NewFileName��
			  ��һ������Ϊ���ļ�·�����ڶ�������Ϊ���ļ�·��*/



			int c = rename(oldfullFilePath.c_str(), newfullFilePath.c_str());

			if (c == 0)
				puts("File successfully renamed");
			else
				perror("Error renaming file");

		} while (_findnext(hFile, &c_file) == 0);  //����ҵ��¸��ļ������ֳɹ��Ļ��ͷ���0,���򷵻�-1  
		_findclose(hFile);
		while (113);
	}

	return 0;
}




