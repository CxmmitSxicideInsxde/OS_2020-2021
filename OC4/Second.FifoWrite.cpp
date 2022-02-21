#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

int main(){
    int fd;
    size_t size;
    char name[]="Second.fifо";
    umask(0) ;/***Обнуляем маску создания файлов текущего процесса для того, 
			чтобы права доступа у создаваемого FIFO точно соответствовали параметру вызова mknod()***/
    /***Попытаемся создать FIFO с именем aaa.fifo в текущей директории***/
    if (mknod(name, S_IFIFO | 0666, 0) < 0){ /***Если создать FIFO не удалось, печатаем об этом сообщение и прекращаем работу***/
        printf("Can\'t create FIFO\n");
        _exit(-1);
    }
    if ((fd = open(name, O_WRONLY)) < 0){ /***Открываем Second.fifo***/
        /***Если открыть FIFO не удалось, печатаем об этом сообщение и рекращаем работу***/
        printf("Can\'t open FIFO for writing\n");
        _exit(-1);
    }
    char message[60];
    while(true){
        message[0] = 0;
        cin.clear();
        cin >> message;/***Читаем сообщения из консоли***/
        if(!strcmp(message,"quit")) /***Если обнаружен quit, то выходим из цикла***/
        {
            printf("Quit to programm\n");
            break;
        }
        size = write(fd, message, 60); 
        if (size < strlen(message)) { /***Если записалось меньшее количество байт, то сообщаем об ошибке и завершаем работу***/
            printf("Can\'t write all string to FIFO\n");
            _exit(-1);
        }
    }
    close(fd);/***Закрываем поток***/
    return 0;
}