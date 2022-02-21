#include <iostream>
#include <Windows.h>
#include <atlstr.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

using namespace std;

bool compare(char attribs[], char n) {
	if (attribs[1] == n) return true;
	else return false;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	for (int j = 2; j < argc; j++) {
		CString DataBuffer(argv[j]);
		char attrib[50] = "";
		strcpy_s(attrib, argv[j]);
		if (compare(attrib, 'h')) {
			cout << endl << "[-h] - Показать справку по утилите" << endl; // Справка по утилите
			cout << "[-s] - Показать размер файла в байтах" << endl; // Размер файла
			cout << "[-i] – Вывести информацию о файле" << endl; // Информация о файле
			cout << "[-b_n] – Заблокировать n% содержимого файла в начале файла" << endl; // Блокировка содержимого файла в начале
			cout << "[-e_n] – Заблокировать n% содержимого файла в конце файла" << endl; // Блокировка содержимого файла в конце
		}
		if (compare(attrib, 's')) {
			CString path(argv[1]);
			unsigned long FileSize = 0; // Переменная для размера файла
			HANDLE hFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL); // Открываем файловый дескриптор
			FileSize = GetFileSize(hFile, NULL); // Делаем системный вызов GetFileSize
			CloseHandle(hFile);
			cout << "Размер файла в байтах: " << FileSize << endl;
		}
		if (compare(attrib, 'i')) {
			CString path(argv[1]);
			HANDLE hFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // Открываем файловый дескриптор

			BY_HANDLE_FILE_INFORMATION FileInfo;
			GetFileInformationByHandle(hFile, &FileInfo); //Записываем в нашу структуру FileInfo, информацию о файле hFile
			cout << "Атрибуты для файла: " << endl;
			if (FileInfo.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
				cout << "Файл готов для архивирования" << endl;
			}
			if (FileInfo.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED) {
				cout << "Сжатый файл" << endl;
			}
			if (FileInfo.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED) {
				cout << "Зашифрованный файл" << endl;
			}
			if (FileInfo.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {
				cout << "Скрытый файл" << endl;
			}
			if (FileInfo.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
				cout << "Только для чтения" << endl;
			}
			cout << endl << "Cерийный номер тома: " << FileInfo.dwVolumeSerialNumber << endl;
			cout << "Младшая часть размера файла: " << FileInfo.nFileSizeLow << endl;
			cout << "Старшая часть размера файла: " << FileInfo.nFileSizeHigh << endl;
			cout << "Количество ссылок на файл: " << FileInfo.nNumberOfLinks << endl;
			cout << "Старшая часть индекса файла: " << FileInfo.nFileIndexHigh << endl;
			cout << "Младшая часть индекса файла: " << FileInfo.nFileIndexLow << endl;

			FILETIME FileTimeCreate, FileTimeAccess, FileTimeWrite; // Создаём структуры внутри структуры типа _FILETIME
			SYSTEMTIME stUTC, stLocal; // Создаём две структуры для времени
			// Структура SYSTEMTIME представляет дату и время, используя отдельные члены для месяца, дня, года, дня недели, часа, минут, секунд и миллисекунд

			GetFileTime(hFile, &FileTimeCreate, &FileTimeAccess, &FileTimeWrite);
			// Записываем время Создания, Доступа и когда файл в последний раз был записан в наши структуры

			FileTimeToSystemTime(&FileTimeWrite, &stUTC); // Преобразовываем время в нормальный вид.
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
			//Преобразовываем время в формате UTC в соответствующее местному времени заданного часового пояса.
			cout << endl << "Дата и время последней записи в файл: " << stLocal.wMonth << "." << stLocal.wDay << "."
																		<< stLocal.wYear << " " << stLocal.wHour << ":" 
																			<< stLocal.wMinute << endl;

			FileTimeToSystemTime(&FileTimeAccess, &stUTC); // Преобразовываем время в нормальный вид.
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
			//Преобразовываем время в формате UTC в соответствующее местному времени заданного часового пояса.
			cout << "Дата и время последнего доступа к файлу: " << stLocal.wMonth << "." << stLocal.wDay << "."
																	<< stLocal.wYear << " " << stLocal.wHour << ":"
																		<< stLocal.wMinute << endl;

			FileTimeToSystemTime(&FileTimeCreate, &stUTC); // Преобразовываем время в нормальный вид.
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
			//Преобразовываем время в формате UTC в соответствующее местному времени заданного часового пояса.
			cout << "Дата и время создания файла: " << stLocal.wMonth << "." << stLocal.wDay << "."
														<< stLocal.wYear << " " << stLocal.wHour << ":"
															<< stLocal.wMinute << endl;
			CloseHandle(hFile);
		}
		if (compare(attrib, 'b')) {
			CString path(argv[1]);
			HANDLE hFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL); // Открываем файловый дескриптор
			int n = 0;
			n = atoi (argv[j + 1]);

			unsigned long FileSize = 0; // Переменная для размера файла
			FileSize = GetFileSize(hFile, NULL); // Делаем системный вызов GetFileSize
			int size = FileSize * n / 100; // Находим сколько байт нужно заблокировать

			BOOL Locking = LockFile(hFile, 0, 0, size, 0);
			if (Locking == false) {
			    cout << endl << "Не заблокированы байты";
			}
			else cout << endl << "Заблокировано " << n << "% содержимого файла в начале файла" << endl;
			CloseHandle(hFile); // Закрываем файловый дескриптор
		}
		if (compare(attrib, 'e')) {
			CString path(argv[1]);
			HANDLE hFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL); // Открываем файловый дескриптор
			int n = 0;
			n = atoi(argv[j + 1]);

			unsigned long FileSize = 0; // Переменная для размера файла
			FileSize = GetFileSize(hFile, NULL); // Делаем системный вызов GetFileSize 
			int size = FileSize * n / 100; // Находим сколько байт нужно заблокировать

			int pp = FileSize - size;
			BOOL Locking = LockFile(hFile, pp, 0, size, 0);
			if (Locking == false) {
				cout << endl << "Не заблокированы байты";
			}
			else cout << endl << "Заблокировано " << n << "% содержимого файла в конце файла" << endl;
			CloseHandle(hFile); // Закрываем файловый дескриптор
		}
	}  
	return 0;
}