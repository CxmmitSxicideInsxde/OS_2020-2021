#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid, ppid;
    pid = getpid();// индефикатор процесса
    ppid = getppid();// индефикатор родительского процесса
    printf("pid = %d, ppid = %d\n",pid,ppid);
    (void)execl("./fork1", "./fork1", "0.2","0.1",NULL); 
    // Вызываем системный вызов, первый параметр путь до файла, второй параметр, так же путь(arg0), 
    // далее параметры которые передаются в программу
    exit(-1);// ошибка, не удалось вызвать системный вызов
    return 0;
}