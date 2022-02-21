#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

using namespace std;
int getIdMenu(); // объяявляем функции
int getInt();
int getIntRage(int form, int before);

struct base // заводим структуру
{
    int key;
    int appraisal;
    char surname[32];
    char name[32];
    char patronymic[32];
    char subject[32];
} *ptr, *tmpptr;

int main() {
    int fd;
    size_t lengths;
    int validEntry = 0; // хранит кол-во записей
    fd = open("BD.dat", O_RDWR | O_CREAT, 0666); // открываем файл 
    if( fd == -1) {
        printf("File open failed!\n");
        return 1;
    }
    lengths = 100*sizeof(struct base); // 100 записей можем сделать
    ftruncate(fd,lengths); // меняем размер файла
    ptr = (base*)mmap(NULL, lengths, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0); // отображаем файл в памяти
    close(fd); // закрываем файл
    if ( ptr == MAP_FAILED ){ 
        printf("Mapping failed!\n");
        return 2;
    }

    int idMenu = getIdMenu(); // узнаём какой пункт нажали 
    while(idMenu != 0)
    {
        switch(idMenu)
        {
            case 1: 
            {
                tmpptr = ptr + validEntry; // формируем структуру
                cout << "Введите Ключ:" << endl;
                tmpptr->key = getInt();
                cout << "Введите Фамилию:" << endl;
                cin >> tmpptr->surname;
                cout << "Введите Имя:" << endl;
                cin >> tmpptr->name ;
                cout << "Введите отчество:" << endl;
                cin >> tmpptr->patronymic;
                cout << "Введите название предмета:" << endl; 
                cin >> tmpptr->subject;
                cout << "Введите оценку:" << endl;
                tmpptr->appraisal = getIntRage(2,5);
                validEntry++;
                break;
            }
            case 2:
            {
                int inputKey = 0;
                cout << "Введите значение поля,которое хотите изменить ( от 0 до " + to_string(validEntry-1) + " )";
                inputKey = getIntRage(0,validEntry-1); // просим ввести значения для изменения 
                tmpptr = ptr + inputKey;
                cout << "Выберите что хотите изменить:";
                cout << "0) Exit" << endl;
                cout << "1) Ключ" << endl;
                cout << "2) Фамилию" << endl;
                cout << "3) Имя" << endl;
                cout << "4) Отчество" << endl;
                cout << "5) Предмет" << endl;
                cout << "6) Оценка" << endl;
                int idChange = getIntRage(0,6);
                switch(idChange)
                {
                    case 0: break;
                    case 1:
                    {
                        cout << "Введите Ключ:" << endl;
                        tmpptr->key = getInt();
                        break;
                    }
                    case 2:
                    {
                        cout << "Введите Фамилию:" << endl;
                        cin >> tmpptr->surname;
                        break;
                    }
                    case 3:
                    {
                        cout << "Введите Имя:" << endl;
                        cin >> tmpptr->name;
                        break;
                    }
                    case 4:
                    {
                        cout << "Введите Отчество:" << endl;
                        cin >> tmpptr->patronymic;
                        break;
                    }
                    case 5:
                    {
                        cout << "Введите Предмет:" << endl;
                        cin >> tmpptr->subject;
                        break;
                    }
                    case 6:
                    {
                        cout << "Введите Оценка:" << endl;
                        tmpptr->appraisal = getIntRage(2,5);
                        break;
                    }
                }
                break;
            }
            case 3:
            {
                for(int i = 0; i < validEntry; i ++) // выводим данные из памяти в консоль
                {
                    tmpptr = ptr + i;  
                    cout << to_string(tmpptr->key) + " " + tmpptr->surname + " " + tmpptr->name + " " + tmpptr->surname + 
                    " " + tmpptr->subject + " " + to_string(tmpptr->appraisal) << endl;
                }
            }
        }
        idMenu = getIdMenu();
    }
    lengths = validEntry*sizeof(struct base); // узнаём размер данных,которые были внесены
    fd = open("BD.dat", O_RDWR | O_CREAT, 0666); // открываем файл
    if( fd == -1) {
        printf("File open failed!\n");
        return 1;
    }
    ftruncate(fd,lengths); // меняем размер 
    close(fd); // закрываем
    munmap((void *)ptr, lengths); // выгружаем память в файл
    return 0;
}


int getIdMenu()
{
    int idMenu = 0;
    do
    {
        cout << "0) Exit" << endl;
        cout << "1) Add" << endl;
        cout << "2) Change" << endl;
        cout << "3) Show" << endl;
        idMenu = getInt();
    } while (idMenu > 3 || idMenu < 0); // пока не ввели из трёх пунктов, работаем бесконечно
    
    return idMenu;
}

int getInt()
{
    int a = 0;
    while (!(cin >> a))
    {
        cout << "Ввёдено не целочисленное число" << endl;
        cin.clear();
        cin.ignore(8000,'\n'); // пропускаем 8000 элементов, необходимо, чтобы не ушли в бесконечный цикл
        cout << "Введите повторно значения:" << endl;
    }
    return a;
}

int getIntRage(int form, int before) // диапозон целочисленной переменной
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