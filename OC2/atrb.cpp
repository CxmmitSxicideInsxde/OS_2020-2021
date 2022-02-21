#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

const char* g_uid(uid_t uid)
{
    static char result[16];
    struct passwd* pwd;
 
    if ((pwd = getpwuid(uid)) != NULL) // если структура найдена, возвращаем имя пользователя
        return pwd->pw_name;
 
    sprintf(result, "%d", uid); // если не найдена, то возвращаем пользователя-владельца 
    return result;
}
 
const char* g_gid(gid_t gid)
{
    static char result[16];
    struct group* grp;
 
    if ((grp = getgrgid(gid)) != NULL) // если структура найдена, возвращаем имя группы
        return grp->gr_name;
 
    sprintf(result, "%d", gid); // если не найдена, то возвращаем группы-владельца
    return result;
}
 
const char* displayFileType(mode_t mode)
{  
    static char result[10] = { 0 };
    memset(result, '-', 10); // заполняем массив -
    switch((mode & S_IFMT)) // накладываем битовую маску для полей типа файл
    {
        case S_IFSOCK:result[0] = 's'; break; //  сокет
        case S_IFLNK:result[0] = 'l'; break; //  символьная ссылка
        case S_IFREG:result[0] = '-'; break; //  обычный файл
        case S_IFBLK:result[0] = 'b'; break; //  блочное устройство
        case S_IFDIR:result[0] = 'd'; break; //  каталог
        case S_IFCHR:result[0] = 'c'; break; //  символьное устройство
        case S_IFIFO:result[0] = 'p'; break; //  канал FIFO
    }

    if (mode & S_IRUSR)result[1] = 'r'; // User read
    if (mode & S_IWUSR)result[2] = 'w'; // User write
    if (mode & S_IXUSR)result[3] = 'x'; // User право выполнять

    if (mode & S_IRGRP)result[4] = 'r'; // Group read
    if (mode & S_IWGRP)result[5] = 'w'; // Group write
    if (mode & S_IXGRP)result[6] = 'x'; // Group право выполнять

    if (mode & S_IROTH)result[7] = 'r'; // All read
    if (mode & S_IWOTH)result[8] = 'w'; // All read
    if (mode & S_IXOTH)result[9] = 'x'; // All read
 
    return result;
}
 
int main(int argc, char *argv[])
{
    const char* curDir = ".";
    DIR* dp;
    struct dirent* p;
 
    if (argc > 1) // если кол-во аргументов больше 1
       curDir = argv[1];
 
    if (!(dp = opendir(curDir))) // если не удаётся открыть каталог,  то есть он не существует, выходим из программы
    {
        std::cout << "Ошибка открытия";
        exit(1);      
    }
    size_t path_len = strlen(curDir);
    char *buf;
    size_t len;
    while ((p = readdir(dp)) != NULL) // читаем директорию
    {
        len = path_len + strlen(p->d_name) + 2;  // длина пути каталога + длина имени каталога + 2 символа (/ and /0)
        buf = (char*)malloc(len); // выделяем память
        if (buf) // если память выделилась, то продолжаем
        {
            struct stat r;
            snprintf(buf, len, "%s/%s", curDir, p->d_name); 
            lstat(buf, &r) ; // читаем информацию о файле
            char* times = ctime(&r.st_mtime);
            times[strlen(times)-1] = times[strlen(times)-2] = 0; // удаляем /n
            std::cout << displayFileType(r.st_mode) << " " << (unsigned long)r.st_nlink << " " << g_uid(r.st_uid) << 
            " " <<  g_gid(r.st_gid) <<  " " <<  r.st_size << " " << times << " " <<  p->d_name << std::endl;
            free(buf); // очищаем память
        }
    }
 
    closedir(dp);
 
    return 0;
}