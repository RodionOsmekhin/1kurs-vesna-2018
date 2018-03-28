#ifndef IntArray_h
#define IntArray_h

struct IntArray{
    int *data;
    int size;
};

///������� ������
IntArray CreateArray(int size);

///�������� � �������� index ������� array ������������� �������� value
///���������� false ��� ������ �� ������� �������
bool setItem(IntArray array, int index, int value);

///� ���������� result ������������ �������� �������� � �������� index ������� array
///���������� false ��� ������ �� ������� �������
bool getItem (IntArray array, int index, int& result);


///������� ������ �� �����
void write (IntArray array);

///����������
void sort (IntArray array);

///�������� �������
void remove (IntArray array);

///C������� ������ �������
IntArray newArray (IntArray array);

///�������� �������� �� �������
void put (IntArray array, int index, int value);


#endif
