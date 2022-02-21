#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

int main()
{
    int fd;
    size_t size;
    umask(0);
    /***Пытаемся открыть файл с именем myfile в текущей директории
    только для вывода. Если файла не существует, попробуем его создать с правами
    доступа 0666, т. е. read-write для всех категорий пользователей***/
    if ((fd = open("First", O_RDONLY, 0666)) < 0) { /***Если файл открыть не удалось, печатаем об этом сообщение и прекращаем работу***/
        printf("Can\'t open file\n");
        _exit(-1) ;
    }
    char *buf;
    struct stat buff;
    fstat(fd,&buff); /***Узнаём размер файла,чтобы выделить память***/
    buf = (char*)malloc(buff.st_size); /***Выделяем память***/

    size = read(fd, buf, buff.st_size); /***Считываем данные из файла и записываем в buf***/
    if (size < 0){ /***Если записалось меньшее количество байт,сообщаем об ошибке***/
        printf("Can\'t read string\n"); 
        _exit(-1);
    }

    printf("%s\n",buf); /***Выводим, что считали***/
    free(buf); /***Отчитска памяти***/
    if (close (fd) < 0) { /***Закрываем файл***/
        printf("Can\'t close file\n");
    }
    return 0 ;
}