#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("Вы не передали строку! Попробуйте еще раз с введенной строкой!\n");
        _exit(-1) ;
    }
    int fd;
    size_t size;
    umask(0);
    /***Пытаемся открыть файл с именем myfile в текущей директории
    только для ввода. Если файла не существует, попробуем его создать с правами
    доступа 0666, т. е. read-write для всех категорий пользователей***/
    if ((fd = open("First", O_WRONLY | O_CREAT, 0666)) < 0) { /***Если файл открыть не удалось, печатаем об этом сообщение и прекращаем работу***/ 
        printf("Can\'t open file\n");
        _exit(-1) ;
    }
    size = write(fd, argv[1], strlen(argv[1]));/***Пробуем записать в файл всю строку которую мы ввели***/ 
    if (size != strlen(argv[1])){ /***Если записалось меньшее количество байт,сообщаем об ошибке***/
        printf("Can\'t write all string\n");
        _exit(-1);
    }
    if (close (fd) < 0) { /***Закрываем файл***/
        printf("Can\'t close file\n");
    }
    return 0 ;
}