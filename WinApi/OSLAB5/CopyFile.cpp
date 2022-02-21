#include "pch.h"
#include <iostream>
#include <atlstr.h>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[]) {
	//SetFileAttributes(CString(argv[1]), FILE_ATTRIBUTE_NORMAL); // Устанавливаем 
	CopyFile(CString(argv[1]), CString(argv[2]), false); // Копируем файл
}