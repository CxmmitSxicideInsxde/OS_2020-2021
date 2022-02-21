#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

using namespace std;
int getIdMenu();
int getInt();
int getIntRage(int form, int before);

struct base
{
    int key;
    int appraisal;
    char surname[32];
    char name[32];
    char patronymic[32];
    char subject[32];
} *ptr, *tmpptr;

void output(struct base* ppt) // определяем функцию для вывода данных
{
    cout << to_string(ppt->key) + " " + ppt->surname + " " + ppt->name + " " + ppt->surname + 
    " " + ppt->subject + " " + to_string(ppt->appraisal) << endl;
}

int main() {
    int fd;
    size_t lengths;
    int validEntry = 0;
    fd = open("BD.dat", O_RDWR | O_CREAT, 0666); // открываем файл
    if( fd == -1) {
        printf("File open failed!\n");
        return 1;
    }
    struct stat buff;
    fstat(fd,&buff); 
    lengths = buff.st_size; // узнаём размер файла 
    validEntry = lengths/sizeof(struct base); // знаяя структура и размер функции, можем узнать кол-во записей в базе
    ptr = (base*)mmap(NULL, lengths, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0); // выгружаем файл в память 
    close(fd); // закрываем файл
    if ( ptr == MAP_FAILED ){
        printf("Mapping failed!\n");
        return 2;
    }

    int idMenu = getIdMenu(); // узнаём ID  меню
    while(idMenu != 0)
    {
        switch(idMenu)
        {
            case 1: 
            {
                cout << "Введите Ключ:" << endl;
                int inputKey = getInt();
                for(int i = 0; i < validEntry; i ++)
                {
                    tmpptr = ptr + i;  
                    if(tmpptr->key == inputKey)output(tmpptr); // пробегаемся и сравниваем ключи
                }
                break;
            }
            case 2:
            {
                char inputSubject[32];
                cout << "Введите Предмет:" << endl;
                cin >> inputSubject;
                for(int i = 0; i < validEntry; i ++)
                {
                    tmpptr = ptr + i;  
                    if(!strcmp(tmpptr->subject,inputSubject))output(tmpptr); // пробегаемся и сравниваем предмет 
                }
                break;
            }
            case 3:
            {
                int inputAppraisal = 0;
                cout << "Введите оценку за год:" << endl;
                inputAppraisal = getIntRage(2,5);
                for(int i = 0; i < validEntry; i ++)
                {
                    tmpptr = ptr + i;  
                    if(tmpptr->appraisal == inputAppraisal)output(tmpptr); // пробегаемся и сравниваем оценки
                }
            }
        }
        idMenu = getIdMenu();
    }
    return 0;
}


int getIdMenu()
{
    int idMenu = 0;
    do
    {
        cout << "0) Exit" << endl;
        cout << "1) вывод записей с заданным значением ключа" << endl;
        cout << "2) вывод всех записей с одинаковым значением полей «Предмет»" << endl;
        cout << "3) вывод всех записей с одинаковым значением полей «Оценка за год»" << endl;
        idMenu = getInt();
    } while (idMenu > 3 || idMenu < 0);
    
    return idMenu;
}

int getInt()
{
    int a = 0;
    while (!(cin >> a))
    {
        cout << "Ввёдено не целочисленное число" << endl;
        cin.clear();
        cin.ignore(8000,'\n');
        cout << "Введите повторно значения:" << endl;
    }
    return a;
}

int getIntRage(int form, int before)
{
    int a = getInt();
    while (a < form || a > before)
    {
        cout << "число может лежать в диапазоне[" << to_string(form) << ',' << to_string(before) << ']' << endl;
        cout << "Введите повторно значения:" << endl;
        a = getInt();
    }
    return a;
}