#include "pch.h"
#include <iostream>
#include <atlstr.h>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[]) { // Копирование файла
	SetFileAttributes(CString(argv[1]), FILE_ATTRIBUTE_NORMAL); // Копирование файла
	CopyFile(CString(argv[1]), CString(argv[2]), false);// Копирование файла
}

int main(int argc, char* argv[]) { // Удаление файла
	SetFileAttributes(CString(argv[1]), FILE_ATTRIBUTE_NORMAL); // Удаление файла
	DeleteFile(CString(argv[1])); // Удаление файла
}


int main(int argc, char* argv[]) { // Запись в конец файла
	HANDLE a = CreateFile(CString(argv[2]), GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // Запись в конец файла
	SetFilePointer(a, NULL, NULL, FILE_END); // Запись в конец файла
	WriteFile(a, argv[1], strlen(argv[1]), 0, 0); // Запись в конец файла
}