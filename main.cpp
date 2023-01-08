#define _CRT_SECURE_NO_WARNINGS
#include <iostream>  
#include <io.h>  //对系统文件进行操作的头文件
#include <string>  
#include <sstream>
#include<vector>
#include <string.h>

using namespace std;

const int N = 3;   //整型格式化输出为字符串后的长度，例如，N=6，则整型转为长度为6的字符串，12转为为000012

const string FileType = ".jpg";    // 需要查找的文件类型

/* 函数说明 整型转固定格式的字符串
输入：
n 需要输出的字符串长度
i 需要结构化的整型
输出：
返回转化后的字符串
*/

string int2string(int n, int i)
{
	char s[BUFSIZ];
	sprintf(s, "%d", i);
	int l = strlen(s);  // 整型的位数	

	if (l > n)
	{
		cout << "整型的长度大于需要格式化的字符串长度！";
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
	_finddata_t c_file;   // 查找文件的类

	string File_Directory = "";   //文件夹目录
	printf("请输入要批量重命名文件夹目录\n");
	scanf_s("&s", &File_Directory);

	string buffer = File_Directory + "\\*" + FileType;

	//long hFile;  //win7系统，_findnext()返回类型可以是long型
	intptr_t hFile;   //win10系统 ，_findnext()返回类型为intptr_t ，不能是long型

	hFile = _findfirst(buffer.c_str(), &c_file);   //找第一个文件

	if (hFile == -1L)   // 检查文件夹目录下存在需要查找的文件
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
			str_name = int2string(N, i);    //整型转字符串
			newfullFilePath = File_Directory + "\\" + str_name + FileType;

			/*重命名函数rename（const char* _OldFileName,const char* _NewFileName）
			  第一个参数为旧文件路径，第二个参数为新文件路径*/



			int c = rename(oldfullFilePath.c_str(), newfullFilePath.c_str());

			if (c == 0)
				puts("File successfully renamed");
			else
				perror("Error renaming file");

		} while (_findnext(hFile, &c_file) == 0);  //如果找到下个文件的名字成功的话就返回0,否则返回-1  
		_findclose(hFile);
		while (113);
	}

	return 0;
}




