#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int removeDirectory(const char *path) //  определяем функцию
{
   DIR *d = opendir(path); // открываем папку
   size_t path_len = strlen(path); // узнаём её размер
   int r = -1; 

   if (d) // если удалось открыть продолжаем
   {
      struct dirent *p; 

      r = 0; 

      while (!r && (p=readdir(d))) // читаем каталог
      {
          int r2 = -1; 
          char *buf;
          size_t len;

          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))continue; // если имя каталог . или .., то пропускаем

          len = path_len + strlen(p->d_name) + 2;  // длина пути каталога + длина имени каталога + 2 символа (/ and /0)
          buf = (char*)malloc(len); // выделяем память

          if (buf) // если память выделилась, то продолжаем
          {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", path, p->d_name);

             if (!stat(buf, &statbuf)) // если успешно считался атрибут
             {
               r2 = S_ISDIR(statbuf.st_mode) ? removeDirectory(buf) : unlink(buf); 
               // проверяем, если тип файла директория, то рекурсивно вызываем нашу функцию
               // если нет, то удаляем файл/связь
             }

             free(buf); // очищаем память
          }

          r = r2;
      }

      closedir(d); // закрываем директорию
   }

   if (!r) 
   {
      r = rmdir(path); // удаляем директорию
   }

   return r;
}

int main(int argc, char *argv[]) {
    const char* curDir = ".";
    DIR* dp;
    struct dirent* dirp;
    if (argc > 1) // если кол-во аргументов больше 1
       curDir = argv[1];
       else exit(1);

    if (!(dp = opendir(curDir))) // если не удаётся открыть каталог,  то есть он не существует, выходим из программы
    {
      std::cout << "Ошибка открытия";
      exit(1);      
    }
    removeDirectory(curDir);
    return 0;
}