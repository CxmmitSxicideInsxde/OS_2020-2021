#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

bool IsExit(char message[])
{
    if(!strcmp(message,"Quit")){ /***Если обнаружен quit, то выходим из цикла***/
        printf("Quit to programm\n");
        return true;
    }
    return false;
}

int main(){
    int fd_one[2],fd_two[2], result;
    size_t size;

    if (pipe(fd_one) < 0 || pipe(fd_two) < 0) { /***Если создать pipe не удалось, печатаем об этом сообщение и прекращаем работу***/
        printf("Can\'t create pipe\n");
        exit(-1);
    }
    result = fork();
    if(result < 0){ /***Если создать процесс не удалось, сообщаем об этом и завершаем работу***/
        printf("Can\t fork child\n");
        exit(-1);
    } else if (result > 0) { /***Родитель процесс***/
    
        close(fd_one[0]); /***Закрываем поток вывода для первого pipe***/
        close(fd_two[1]); /***Закрываем поток ввода для второго pipe***/
        char message[60];
        while(true)
        {
            message[0] = 0; 
            cin.clear(); /***Очищает флаг ошибки***/
            printf("Введите сообщение для потомка: \n");
            cin >> message;
            if(IsExit(message))break; // 
            size = write(fd_one[1], message, strlen(message)+1); /*** 1 символ это /0 ***/
            message[0] = 0; /***Очищаем массив для того, чтобы считать информацию с потомка**/
            size = read(fd_two[0], message, 60);
            printf("От потомка, родитель получил сообщение: %s\n",message); /***Выводим то, что нам передал потомок***/
            if(IsExit(message))break; // 
        }
        close(fd_one[1]); /***Закрываем поток ввода для первого pipe***/
        close(fd_two[0]); /***Закрываем поток вывода для второго pipe***/
    }
    else
    {
        close(fd_one[1]); /***Закрываем поток ввода для первого pipe***/
        close(fd_two[0]); /***Закрываем поток вывода для второго pipe***/
        char message[60];
        while(true)
        {
            message[0] = 0;
            size = read(fd_one[0], message, 60);
            printf("Потомок получил от родителя сообщение: %s\n",message);
            if(IsExit(message))break;
            message[0] = 0;
            cin.clear(); /***Очищает флаг ошибки***/
            printf("Введите сообщение для родителя: \n");
            cin >> message;
            if(IsExit(message))break;
            size = write(fd_two[1], message, strlen(message)+1); /*** 1 символ это /0 ***/
        }
        close(fd_one[0]); /***Закрываем поток вывода для первого pipe***/
        close(fd_two[1]); /***Закрываем поток ввода для второго pipe***/
    }
    return 0;
}