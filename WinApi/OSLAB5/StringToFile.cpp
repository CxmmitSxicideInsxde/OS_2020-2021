#include "pch.h"
#include <iostream>
#include <atlstr.h>
#include <Windows.h>
using namespace std;

int main(int argc, char* argv[]) {
	HANDLE a = CreateFile(CString(argv[2]), GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // Создаем если файл не существует
																												//Открываем если файл существует
	SetFilePointer(a, NULL, NULL, FILE_END); // Ставим указатель на конец файла
	WriteFile(a, argv[1], strlen(argv[1]), 0, 0); // Записываем строку
}