#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

int main(){
    int fd;
    size_t size;
    char name[]="Second.fifо"; // Название нашего файла.
    if ((fd = open(name, O_RDONLY)) < 0){ /***Если открыть FIFO не удалось, печатаем об этом сообщение и рекращаем работу***/
        printf("Can\'t open FIFO for reading\n");
        _exit(-1);
    }
    char message[60];
    while(true){
        message[0] = 0;
        size = read(fd, message, 60); /***Cчитываем сообщение***/
        if(!strcmp(message,"quit")){ /***Если обнаружен quit, то выходим из цикла***/
            printf("Quit to programm\n");
            break;
        }
        if (size < 0){ /***Если записалось меньшее количество байт,ообщаем об ошибке***/
            printf("Can\'t read string\n");
            _exit(-1);
        }
        printf("%s\n",message);/***Вывод сообщения***/
    }
    close(fd); /***Закрываем поток***/
    return 0;
}