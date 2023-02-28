#include <iostream>
#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <direct.h>

using namespace std;

#define CHOICE 3

#if CHOICE == 1
// для вывода строки в консоль
void RussianMessage(const char* str) {
    char message[100];
    CharToOemA(str, message);
    cout << message;
}

// копирование файла
bool CopyFile(char* source, char* destination) {
    const int size = 65536;
    FILE* src, * dest;

    if (!fopen_s(&src, source, "rb")) {
        long handle = _fileno(src); // получение дескриптора файла
        char* data = new char[size]; // выделение памяти под буфер

        if (!fopen_s(&dest, destination, "wb")) {
            int realsize;
            while (!feof(src)) {
                realsize = fread(data, sizeof(char), size, src); // чтение из файла
                fwrite(data, sizeof(char), realsize, dest); // запись в файл
            }
        }
        else {
            delete[] data;
            return false;
        }

    }
    else return false;

    fclose(src);
    fclose(dest);
    return true;
}


void main()
{
    char source[_MAX_PATH];
    char destination[_MAX_PATH];
    char answer[20];

    RussianMessage("\nВведите путь и название копируемого файла\n");
    cin.getline(source, _MAX_PATH);
    if (_access(source, 00) == -1) {
        RussianMessage("\nУказан неверный путь к файлу или его название\n");
        return;
    }

    RussianMessage("\nВведите путь и название нового файла\n");
    cin.getline(destination, _MAX_PATH);
    if (_access(destination, 00) == 0) {
        RussianMessage("\nТакой файл уже создан. Перезаписать?(1 - Да/2 - Нет)\n");
        cin.getline(answer, 20);
        if (!strcmp(answer, "2")) {
            RussianMessage("\nОперация отменена\n");
            return;
        }
        else if (!strcmp(answer, "1")) {
            if (_access(destination, 02) == -1) {
                RussianMessage("\nНет доступа к записи\n");
                return;
            }            
        }
        else {
            RussianMessage("\nНеправильный ввод\n");
            return;
        }
    }
    if (!CopyFile(source, destination)) {
        RussianMessage("\nОшибка при работе с файлом\n");
        return;
    }
    return;
}


// FILE* fopen(char* path, char* mode) 
// fopen_s(FILE **f, char* path, char* mode) - открыть доступ к файлу

// fclose(FILE* f) - закрытие потока (доступа к файлу) 
// if(fclose(f) == EOF)

// fgets(char* string, int n, FILE* f) - построчное чтение
// fgetc() - посимвольное чтение
// fscanf() - чтение форматированной строки

// fputs(char* string, FILE* f) - построчное запись
// fputc() - посимвольная запись
// fprintf() - запись форматированной строки

// feof(FILE* f) - определение конца файла

// fread(void* buffer, size_t size, size_t count, FILE* f)
// чтение бинарного файла
// fwrite(const void* buffer, size_t size, size_t count, FILE* f)
// запись в бинарный файл

// fseek(FILE* f, int offset [, int origin])
// устанавливает смещение в файле

// include<io.h>
// int _access(const char* path, int mode)
// определяет разрешения файла или директории
    // 00 - проверка на существование
    // 02 - проверка на разрешения на запись
    // 04 - проверка на разрешения на чтение
    // 06 - проверка на разрешения на чтение и на запись

// long _filelength(int handle)
// возвращает размер файла в байтах

// int _locking(int handle, int mode, long nBytes) <sys/locking.h>
// блокирует или разблокирует байты файла начиная с текущей позиции
    // _LK_LOCK (_LK_RLCK) - блок (10 попыток)
    // _LK_NBLCK (_LK_NBRLCK) - блок (без попыток)
    // _LK_UNLCK - разблок

#elif CHOICE == 2

// переименование файла
void RenameFile(){
    char oldName[50], newName[50];
    cout << "Enter old name -> "; cin >> oldName;
    cout << "Enter new name -> "; cin >> newName;

    if (rename(oldName, newName) != 0)
        cout << "Error!\nCouldn't rename file.\n";
    else
        cout << "Ok...\n";
}

// удаление файла
void RemoveFile() {
    char Name[50];
    cout << "Enter name -> "; cin >> Name;

    if (remove(Name) != 0)
        cout << "Error!\nCouldn't remove file.\n";
    else
        cout << "Ok...\n";
}

//поиск файлов в каталоге
void Dir() {
    char path[70];
    cout << "\nEnter full path -> "; cin >> path;

    char mask[15];
    cout << "\nEnter mask -> "; cin >> mask;

    strcat_s(path, mask);
    _finddata_t* fileinfo = new _finddata_t;

    //начало поиска
    intptr_t done = _findfirst(path, fileinfo);
    int count = 1;

    do {
        count++;
        cout << fileinfo->name << "\n";
    } while (_findnext(done, fileinfo) != -1);

    cout << "\nInformation: was found " << count;
    cout << " file(s) in folder .... " << path << endl;

    _findclose(done);
    delete fileinfo;
}

void main() {
    cout << "Please, select preffer number\n";
    char c;

    do {
        cout << "\n1 - Rename\n";
        cout << "\n2 - Remove\n";
        cout << "\n3 - View some folder\n";
        cout << "\n0 - Exit\n";
        cin >> c;
        switch (c)
        {
        case '1':
            RenameFile();
            break;
        case '2':
            RemoveFile();
            break;
        case '3':
            Dir();
            break;
        default:
            break;
        }
    } while (c != '0');
}
// <stdio.h>
// rename(char* oldname, char* newname) переименование файла
// remove(const char* filename) удаляет файл
// <io.h>
// _findfirst(char* path, _finddata_t* fileinfo)
// находит файлы по указанному пути
    // _finddata_t - записывает инф-я о найденном файле
        // unsigned attrib
            // _A_NORMAL
            // _A_RDONLY
            // _A_HIDDEN
            // _A_SYSTEM
            // _A_SUBDIR
            // _A_ARCH
        // time_t time_create
        // time_t time_access
        // time_t time_write
        // _fsize_t size
        // char name[260]

// _findnext(long done, _finddata_t* fileinfo)
// осуществляет переход на следующий файл в группе

// _findclose(long done) очищает память от группы файлов в памяти




#elif CHOICE == 3

// переименование директории
void RenameDirectory() {
    char oldName[50], newName[50];
    cout << "Enter old name -> "; cin >> oldName;
    cout << "Enter new name -> "; cin >> newName;

    if (rename(oldName, newName) != 0)
        cout << "Error!\nCouldn't rename file.\n";
    else
        cout << "Ok...\n";
}

// удаление каталога
void RemoveDirectory() {
    char Name[50];
    cout << "Enter name -> "; cin >> Name;

    if (_rmdir(Name) == -1)
        cout << "Error!\nCouldn't remove directory.\n";
    else
        cout << "Ok...\n";
}

// создание каталога
void CreateDirectory() {
    char Name[50];
    cout << "Enter name -> "; cin >> Name;

    if (_mkdir(Name) == -1)
        cout << "Error!\nCouldn't create directory.\n";
    else
        cout << "Ok...\n";
}

void main(){
    cout << "Please, select preffer number\n";
    char c;

    do {
        cout << "\n1 - Rename\n";
        cout << "\n2 - Remove\n";
        cout << "\n3 - Create\n";
        cout << "\n0 - Exit\n";
        cin >> c;
        switch (c)
        {
        case '1':
            RenameDirectory();
            break;
        case '2':
            RemoveDirectory();
            break;
        case '3':
            CreateDirectory();
            break;
        default:
            break;
        }
    } while (c != '0');
}

//<direct.h>
// 
//int _mkdir(const char* dirname)
// создает директорию по указанному пути

// int _rmdir(const char* dirname)
// удаляет директорию по указанному пути


#endif


