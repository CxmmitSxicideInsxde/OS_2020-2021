#include "pch.h"
#include <iostream>
#include <atlstr.h>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[]) {
	SetFileAttributes(CString(argv[1]), FILE_ATTRIBUTE_NORMAL); // Устанавливаем аттрибут обычный файл, который не имеет других атрибутов; 
	DeleteFile(CString(argv[1])); // Удаление файла
}