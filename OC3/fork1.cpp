#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
    double step[2];
    if (argc > 2) // если кол-во аргументов больше 2
    {
       step[0] = abs(atof(argv[1]));// считываем вещественное значение
       step[1] = abs(atof(argv[2]));
    }
    else step[0] = step[1] = 0.1;

    pid_t pid, ppid;
    int p = fork();// пораждаем новый процесс
    pid = getpid();// индефикатор процесса
    ppid = getppid();// индефикатор родительского процесса
    if(p < 0)// если значение отрицательное, то процесс не удалось создать
    {
        printf("создать новый процесс не удалось");
        exit(1);
    }
    else if(!p) // ребёнок
    {
        double f = -1.0;
        while(f <= 1.0){
            printf("pid = %d, ppid = %d, cosh(%f) = %f\n",(int) pid, (int) ppid,f, sinh(f));
            f = f + step[1];
            if( f >= 0.0)exit(1); // аргумент стал больше или равен 0
        }
    }
    else
    {    
        double f = -1.0;
        while(f <= 1.0){
            printf("pid = %d, ppid = %d, sinh(%f) = %f\n",(int) pid, (int) ppid,f, sinh(f));
            f = f + step[0];
            if( f >= 0.0)exit(1); // аргумент стал больше или равен 0
        }
    }
 
    

    return 0;
}