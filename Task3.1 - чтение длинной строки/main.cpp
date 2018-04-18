#include <cstdio>
#include <cstring>
#include <clocale>


/// Читает строку любой длины из потока, пока не встретит перевод строки \n.
/// Возвращает строку в динамической памяти с прочитанными данными (\n в конце строки есть).
char* ReadLongString(FILE* str)
{
    /// Начальный размер буфера. Будет увеличиваться в 2 раза на каждой итерации
    /// В целях отладки надо сначала делать маленьким, а потом можно сделать побольше
    int size = 3;
    /// Буфер
    char* buf = new char[size];

    /// Место в буфере, начиная с которого пишем новые данные. Изначально начало буфера
    char* readStart = buf;


    /// Метка конца буфера. Если её перетёрли в 0, то буфер был заполнен полностью.
    buf[size-1] = 1;

    while(true)
    {
        /// Читаем символы в буфер - не более, чем осталось байт от readStart до конца буфера
        fgets(readStart, size-(readStart - buf), str);
        /// Разбираемся, всё ли прочитано или надо будет ещё прочитать.
        if((buf[size-1]==1)||(buf[size-2]=='\n'))
        {

            /// Если метку не тронули, то строка короткая и уже прочитана.
            /// Если перетёрли, но предпоследний символ - перевод строки, то строка вместилась в тютельку
            return buf;
        /// Иначе выделяем буфер в 2 раза больше
        /// Переносим в него данные
        /// И удаляем старый буфер!!!

        } else{
        char* newBuf = buf;
        buf = new char[size * 2];
        strcpy(buf, newBuf);
        delete[] newBuf;
        /// записываем данные с середины буфера
        readStart = buf + size - 1;
        size *= 2;
        buf[size-1] =1;
        }



        /// Теперь писать будем в середину нового буфера (начиная с нулевого байта), т.к. первая половина занята старыми данными.

        /// Не забываем в конце нового буфера проставить метку конца

    }

    return buf;
}



int main()
{
    //setlocale(LC_ALL, "Russian"); // только ломает
    printf("Input long string\n");

    // Читаем строчку с консоли
    char* s = ReadLongString(stdin);

    // Выводим. Длинна будет всегда на единицу больше визуальной, т.к. в строке будет перевод строки \n
    printf("Readed: %s\nLength=%d\n", s, strlen(s));

    // Сохраняем в файл - можно даже кириллицу набирать
    // но смотреть такой файло надо будет в Notepad++ --> Кодировки --> Кириллица --> OEM866
    printf("Saving it to file file.txt (encoding OEM866)\n");
    FILE* out = fopen("file.txt", "w");
    // в функцию передаётся void* указатель, поэтому вторым параметром (1) мы говорим, сколько байт занимает один элемент массива
    fwrite(s, 1, strlen(s), out);
    // Не забываем закрыть файл!
    fclose(out);

    // Удаляем строку из кучи
    delete[] s;

    printf("Load it from file.txt\n");

    // Читаем файл
    FILE* in = fopen("file.txt", "r");
    char* s2 = ReadLongString(in);
    fclose(in);

    printf("Read from file: %s", s2);
    printf("Length=%d\n",strlen(s2));

    // Не забываем освободить память
    delete[] s2;

    return 0;
}
