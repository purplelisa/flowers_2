#include "Flower.h"

char buf[256] = " ";
char buf1[256] = " ";

Flower::Flower()
{
    name = new char[1];
    name[0] = '\0';
    price = 0;
    day = 0;
    month = 0;
    year = 0;
    type[0] = '\0';
}

Flower::Flower(const Flower*& data)
{
    //strcpy_s(buf, sizeof buf, data->type);
    name = new char[strlen(data->name) + 1];
    strcpy_s(name, strlen(data->name) + 1, data->name);
    strcpy_s(type, strlen(data->type) + 1, data->type);
    day = data->day;
    month = data->month;
    year = data->year;
    price = data->price;

}

void Flower::Input()
{
    //  gets_s(buf);
    //  strcpy_s(buf,256, buf);
      //SetConsoleOutputCP(1251);
      //SetConsoleCP(1251);
     //rewind(stdin);
    cout << "������� ��������:" << endl;
    rewind(stdin);
    gets_s(buf);
    name = new char[strlen(buf) + 1];
    strcpy_s(name, strlen(buf) + 1, buf);

    cout << "���:" << endl;
    rewind(stdin);
    gets_s(buf);
    strcpy_s(type, strlen(buf) + 1, buf);

    rewind(stdin);
    int res = 0;
    while (!res) {
        cout << "������� ���������: ";
        gets_s(buf);
        res = Correct(buf, 0);
    }
    double value = 0;
    sscanf_s(buf, "%lf", &value);
    price = value;

    res = 0;
    char bufRes[20];
    while (!res) {
        cout << "������� ���� �������� (��.��.����): ";
        gets_s(buf);
        strcpy_s(bufRes, strlen(buf) + 1, buf);
        res = Correct(buf, 1);
    }
    char* pTm1 = NULL;
    int count1 = 0;
    int day1 = 0, month1 = 0, year1 = 0;

    char* pc = strtok_s(bufRes, " ", &pTm1);
    while (pc != NULL) {
        if (count1 == 0) { int temp = stoi(pc); day1 = temp; count1++; }
        else if (count1 == 1) { int temp = stoi(pc); month1 = temp; count1++; }
        else if (count1 == 2) { int temp = stoi(pc); year1 = temp; count1++; }
        pc = strtok_s(NULL, " \n", &pTm1);
    }
    day = day1;
    month = month1;
    year = year1;


    system("cls");
}

bool Flower::IsEmpty()
{
    int count{};
    return  count == 0;
}

void Flower::Dispose()
{
    delete[] name;
}

void Flower::Print(Flower*& data, int count)
{
    //    cout << buf;
    if (count != 0)
        for (int i = 0; i < count; i++)
        {
            cout << "������: " << i + 1 << endl;
            cout << "�������� : " << data[i].name << endl;
            cout << "���: " << data[i].type << endl;
            cout << "����: " << data[i].price << endl;
            cout << "����: " << data[i].day << " " << data[i].month << " " << data[i].year << endl;
        }
    else
        cout << "������� ���." << endl;
}

void  Flower::Save(Flower*& data, int count)
{

    // if (IsEmpty()) {
     //    cout << "������ �����!" << endl;
      //   return;
    // }

    char fname[256];
    cout << "������� �������� �����: ";
    cin >> fname;
    strcat_s(fname, ".txt");//���������� ���������� �����
    ofstream fout(fname);

    system("cls");
    if (!fout.is_open())
    {
        cout << "���! �� ������� ������� ����: " << fname << endl;
        return;
    }
    else
    {
        cout << "\n���� ��������!" << endl;
    }

    if (count > 0)
    {

        // ������� ����� ��� ���������� �����
      //  ofstream fout(fname, ios::out);
        Flower flow;

        // fout << count << endl;
        for (int i = 0; i < count; i++) {
            fout << data[i].name << " ";
            fout << data[i].type << " ";
            fout << data[i].price << " ";
            fout << data[i].day << " ";
            fout << data[i].month << " ";
            fout << data[i].year << endl;
        }
    }
    else
    {
        cout << "��� ������� ��� ����������!" << endl;
        fout.close();
        return;
    }
    fout.close();
}

void Flower::Load(Flower*& data, int& count)
{
    cout << "������� �������� �����:";
    char file1[256];
    char buf[100]{ '\0' };

    cin >> file1;
    cin.clear();
    FILE* file = NULL;
    errno_t err = fopen_s(&file, file1, "r");

    if (err != 0) {
        cout << "�� ������� ������� ����:(" << endl;
        return;
    }
    else {
        cout << "���� ������� ������!" << endl;
    }

    if (fscanf_s(file, "%c", buf) == EOF) {
        cout << "���� ����!" << endl;
        fclose(file);
        return;
    }
    buf[0] = '\0';
    fseek(file, 0, SEEK_SET);

    char* pTm = NULL;
    int count2 = 0;

    while (fgets(buf, 50, file) != NULL)
    {
        char* pc = strtok_s(buf, " \n", &pTm);
        while (pc != NULL) {
            if (count2 == 0) { data->name = pc; count2++; }
            else if (count2 == 1) { strcpy_s(data->type, sizeof(data->type), pc); count2++; }
            else if (count2 == 2) { int temp = stof(pc); data->price = temp; count2++; }
            else if (count2 == 3) { int temp = stoi(pc); data->day = temp; count2++; }
            else if (count2 == 4) { int temp = stoi(pc); data->month = temp; count2++; }
            else if (count2 == 5) { int temp = stoi(pc); data->year = temp; count2++; }
            pc = strtok_s(NULL, " \n", &pTm);
        }
    }
    fclose(file);



    Flower temp;
    temp.name = new char[strlen(data->name) + 1];
    strcpy_s(temp.name, strlen(data->name) + 1, data->name);
    strcpy_s(temp.type, strlen(data->type) + 1, data->type);
    temp.price = data->price;
    temp.day = data->day;
    temp.month = data->month;
    temp.year = data->year;


    // ��������� ������� ������
    if (count == 0) {
        count++;
        data = new Flower[1];
    }
    else {
        // ��������� ������ �� ��������� ������
        Flower* buf = new Flower[count];
        Copy(count, data, buf, -1);

        // �������� ����� ������
        delete[] data;
        count++;
        data = new Flower[count];

        // ���������� ������
        Copy(count - 1, buf, data, -1);
        delete[] buf;
    }
    data[count - 1] = temp;

    std::cout << "������ ���������!" << endl;

}

void Flower::Copy(Flower* (&d_n), Flower* (&d_o), int count) //�������� ������ ������ ������� ��� ������ � ������ �������� 
{
    for (int i = 0; i < count; i++)
    {
        d_n[i] = d_o[i]; //��� ���� ������ ���� � ������ �������� ��������� �������
    }
}

void Flower::Delete(Flower*& data, int& count)
{
    int k;
    //��������� ������
    Flower* buf = new Flower[count];
    cout << "������� ����� �������� ( �� 1 ��" << count << "):";
    cin >> k;
    k--;
    system("cls");
    if (k >= 0 && k < count) {

        Copy(buf, data, count);//�� ������ ������� � ��������� ���
        //�������� ����� �����
        count--;
        //delete []b;
        data = new Flower[count];//�������� ����� ������
        int  q = 0;
        for (int i = 0; i <= count; i++) {//�������������� �� ��� � ���  ������� ������
            if (i != k) {//�������� ����� �� ����� ���� �� ��� ������� ����� ��� �������� �� ��������� 
                //Copy(b[q] , buf[i]);
                data[q] = buf[i];
                ++q;
            }
        }
        delete[]buf;
        //b[n].Copy(InfRab infR, DateZav dateZ, DateTrud dateT, InfaFirm infaF);
        cout << "������ �������" << endl;
    }
    else
        cout << "����� ������ �������!!!" << endl;
    /**int k = 0;
     cout << "������� ����� ������, ������� ������ ������� " << endl;
     cin >> k;
     k--;
     Flower temp;
     count--;

     for (int i = k; i < count; i++)
     {
         temp = data[i];
         data[i] = data[i + 1];
         data[i + 1] = temp;
     }

     cout << "\n������ ������� �������!" << endl;*/
}

void Flower::FlowerEntry(char* name, char* type, double price, int day, int month, int year)
{
    // strcpy_s(name, name);


   //  strcpy_s(type, type);
    name = new char[strlen(name) + 1];
    strcpy_s(name, strlen(name), name);
    strcpy_s(type, sizeof type, type);
    price = price;

    day = day;
    month = month;
    year = year;


}

void Flower::Copy(int n, Flower* org, Flower* res, int excl)
{
    int q = 0;
    for (int i = 0; i < n; i++) {
        if (i != excl)
            res[q++] = org[i];
    }
}

void Flower::Add(Flower*& data, int& count)
{
    Flower d;
    d.Input();

    // ��������� ������� ������
    if (count == 0) {
        count++;
        data = new Flower[1];
    }
    else {
        // ��������� ������ �� ��������� ������
        Flower* buf = new Flower[count];
        Copy(count, data, buf, -1);

        // �������� ����� ������
        delete[] data;
        count++;
        data = new Flower[count];

        // ���������� ������
        Copy(count - 1, buf, data, -1);
        delete[] buf;
    }
    data[count - 1] = d;

    std::cout << "������ ���������!" << endl;
}

void Flower::Edit(Flower*& data, int count)
{
    //if (IsEmpty()) {
    //    cout << "������ �����!" << endl;
     //   return;
    //}

    int k;
    cout << "������� ������ (�� 1 �� " << count << "): ";
    cin >> k;
    k--;

    system("cls");

    // �������� �������
    if (k < 0 || k >= count) {
        cout << "������ ��� ���������!" << endl;
        return;
    }

    data[k].Input();
    system("cls");

    cout << "������ ��������!" << endl;
}

void Flower::Search(Flower*& data, int count)
{

    int c;
    cout << "��� �� ������ �����?" << endl;
    cout << "1. �������� " << endl;
    cout << "2. ���" << endl;
    cout << "3. ����" << endl;
    cout << "4. ���� ��������" << endl;


    cin >> c; // ��� switch

    int k = 0; // ��� ��������, ���� ������ ��� ���
    int* m = &k;
    switch (c)
    {
    case 1:
    {
        cout << "������� ��� ��� ������: " << endl;

        char buf[256] = " ";
        cin.ignore();
        gets_s(buf);
        for (int i = 0; i < count; i++)
        {
            if (strcmp(buf, data[i].name) == 0)
            {
                cout << "\n ����������,������� ������: " << endl;
                cout << endl;
                cout << "����� ������: " << i + 1 << endl;
                cout << "��������: " << data[i].name << endl;
                cout << "���: " << data[i].type << endl;
                cout << "����: " << data[i].price << endl;
                cout << "����: " << data[i].day << " " << data[i].month << " " << data[i].year << endl;

                (*m)++;//������ �������, ����������� �������
            }
        }
        break;
    }
    case 2:
    {
        cout << "�������� ��� ��� ������: " << endl;

        char buf[256] = "";
        cin.ignore();
        gets_s(buf);
        for (int i = 0; i < count; i++)
        {
            if (strcmp(buf, data[i].type) == 0)
            {
                cout << "\n���� ������� ������: " << endl;
                cout << endl;
                cout << "����� ������: " << i + 1 << endl;
                cout << "��������: " << data[i].name << endl;
                cout << "���: " << data[i].type << endl;
                cout << "����: " << data[i].price << endl;
                cout << "����: " << data[i].day << " " << data[i].month << " " << data[i].year << endl;

                (*m)++;//������ �������, ����������� �������

            }
        }
        break;
    }
    case 3:
    {
        cout << "�������� price ��� ������: " << endl;

        int x = 0;
        cin >> x;


        for (int i = 0; i < count; i++)
        {
            if (is_equal(x, data[i].price))
            {
                cout << "\n���� ������� ������: " << endl;
                cout << endl;
                cout << "����� ������: " << i + 1 << endl;
                cout << "��������: " << data[i].name << endl;
                cout << "���: " << data[i].type << endl;
                cout << "����: " << data[i].price << endl;
                cout << "����: " << data[i].day << " " << data[i].month << " " << data[i].year << endl;

                (*m)++;//������ �������, ����������� �������
            }
        }
        break;
    }
    case 4:
    {
        cout << "�������� date ��� ������: " << endl;

        int x, y, z;
        cin >> x >> y >> z;


        for (int i = 0; i < count; i++)
        {
            if (data[i].day == x && data[i].month == y && data[i].year == z)
            {
                cout << "\n���� ������� ������: " << endl;
                cout << endl;
                cout << "����� ������: " << i + 1 << endl;
                cout << "���: " << data[i].name << endl;
                cout << "���: " << data[i].type << endl;
                cout << "����: " << data[i].price << endl;
                cout << "����: " << data[i].day << " " << data[i].month << " " << data[i].year << endl;

                (*m)++;//������ �������, ����������� �������
            }
        }
        break;
    }

    }
    if (k == 0)
    {
        cout << "����� ������ ���!" << endl;
    }
}

void Flower::Sort(Flower*& data, int count)
{
    int n = 0;//������� ��� ���������� ������� ��� �� ������ ����������
    //���������� ������� ��������
    for (int i = 0; i < count; i++) {//������ ���� ����� �� �������� ������ �� ������������//�.� ������ ���������� �� �������� ���� 1 �� ������������
        for (int j = i + 1; j < count; j++) {
            //������� ����������
            if (data[i].price > data[j].price) {//�������� ������ � ��� �������� ������� �� �������� ����� ������� ������� ���������� ������� �������
                swap(data[i], data[j]);
                n++;
            }
        }
    }
    cout << "������ �������������� " << n << endl;
}

int Flower::Correct(char* str, int mode)
{
    char* pTm = NULL;
    int count = 0;
    int day = 0, month = 0, year = 0;

    if (mode == 1) {
        char* pc = strtok_s(str, " ", &pTm);
        while (pc != NULL) {
            if (count == 0) { int temp = stoi(pc); day = temp; count++; }
            else if (count == 1) { int temp = stoi(pc); month = temp; count++; }
            else if (count == 2) { int temp = stoi(pc); year = temp; count++; }
            pc = strtok_s(NULL, " \n", &pTm);
        }

        if (day > 31 || day < 1 || month > 12 || month < 1)
        {
            cout << "������ ����� ���� � ������!" << endl;
            return 0;
        }

        if ((month == 2 && day > 28) || (month == 4 && day > 30) || (month == 6 && day > 30) || (month == 9 && day > 30) || (month == 11 && day > 30))
        {
            cout << "������ ����� ����  � ������! " << endl;
            return 0;
        }

        if (((year % 100 == 0 && year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)) && ((day <= 29 && month == 2)))
        {
            cout << "������ ����� ����  � ������!" << endl;
            return 0;
        }

        return 1;

    }

    else {
        int price = 0;
        price = stof(str);
        if (price < 0)
        {
            cout << "������ ����� �������� �  ������!  " << endl;
            return 0;
        }
        return 1;
    }



}

// ================================================================================ //

void Flower::ReadStream(istream& in)
{
    in >> price;
    in >> day;
    in >> month;
    in >> year;
    in >> type;
    in >> name;
}

void Flower::WriteStream(ostream& out)
{
    out << price << endl;
    out << day << endl;
    out << month << endl;
    out << year << endl;
    out << type << endl;
    out << name;
}

void Flower::SetName(char* name)
{
    strcpy(this->name, name);
}

void Flower::Print()
{
    cout << "��������: " << name << endl;
    cout << "���: " << type << endl;
    cout << "���������: " << price << endl;
    cout << "���� �������� (��.��.����): " << day << "." << month << "." << year << endl;
}

bool Equal(const Flower& a, const Flower& b)
{
    if (strcmp(a.name, b.name) == 0)
        return true;
    else
        return false;
}

bool More(const Flower& a, const Flower& b)
{
    if (strcmp(a.name, b.name) > 0)
        return true;
    else
        return false;
}

bool is_equal(double x, double y)
{
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}