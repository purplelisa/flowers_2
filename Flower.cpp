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
    cout << "Введите название:" << endl;
    rewind(stdin);
    gets_s(buf);
    name = new char[strlen(buf) + 1];
    strcpy_s(name, strlen(buf) + 1, buf);

    cout << "Тип:" << endl;
    rewind(stdin);
    gets_s(buf);
    strcpy_s(type, strlen(buf) + 1, buf);

    rewind(stdin);
    int res = 0;
    while (!res) {
        cout << "Введите стоимость: ";
        gets_s(buf);
        res = Correct(buf, 0);
    }
    double value = 0;
    sscanf_s(buf, "%lf", &value);
    price = value;

    res = 0;
    char bufRes[20];
    while (!res) {
        cout << "Введите дату поставки (дд.мм.гггг): ";
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
            cout << "Запись: " << i + 1 << endl;
            cout << "Название : " << data[i].name << endl;
            cout << "Тип: " << data[i].type << endl;
            cout << "Цена: " << data[i].price << endl;
            cout << "Дата: " << data[i].day << " " << data[i].month << " " << data[i].year << endl;
        }
    else
        cout << "Записей нет." << endl;
}

void  Flower::Save(Flower*& data, int count)
{

    // if (IsEmpty()) {
     //    cout << "Данные пусты!" << endl;
      //   return;
    // }

    char fname[256];
    cout << "Введите название файла: ";
    cin >> fname;
    strcat_s(fname, ".txt");//добавление расширение файла
    ofstream fout(fname);

    system("cls");
    if (!fout.is_open())
    {
        cout << "Упс! Не удалось открыть файл: " << fname << endl;
        return;
    }
    else
    {
        cout << "\nФайл сохранен!" << endl;
    }

    if (count > 0)
    {

        // Создаем поток для перезаписи файла
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
        cout << "Нет записей для сохранения!" << endl;
        fout.close();
        return;
    }
    fout.close();
}

void Flower::Load(Flower*& data, int& count)
{
    cout << "Введите название файла:";
    char file1[256];
    char buf[100]{ '\0' };

    cin >> file1;
    cin.clear();
    FILE* file = NULL;
    errno_t err = fopen_s(&file, file1, "r");

    if (err != 0) {
        cout << "Не удалось открыть файл:(" << endl;
        return;
    }
    else {
        cout << "Файл успешно открыт!" << endl;
    }

    if (fscanf_s(file, "%c", buf) == EOF) {
        cout << "Файл пуст!" << endl;
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


    // Проверяем наличие данных
    if (count == 0) {
        count++;
        data = new Flower[1];
    }
    else {
        // Переносим данные во временный массив
        Flower* buf = new Flower[count];
        Copy(count, data, buf, -1);

        // Выделяем новую память
        delete[] data;
        count++;
        data = new Flower[count];

        // Возвращаем данные
        Copy(count - 1, buf, data, -1);
        delete[] buf;
    }
    data[count - 1] = temp;

    std::cout << "Данные добавлены!" << endl;

}

void Flower::Copy(Flower* (&d_n), Flower* (&d_o), int count) //приходит массив данных который ыбл пустой и массив сданными 
{
    for (int i = 0; i < count; i++)
    {
        d_n[i] = d_o[i]; //все поля котрые были в старом присвоем значением массиве
    }
}

void Flower::Delete(Flower*& data, int& count)
{
    int k;
    //временный массив
    Flower* buf = new Flower[count];
    cout << "Введите номер элемента ( от 1 до" << count << "):";
    cin >> k;
    k--;
    system("cls");
    if (k >= 0 && k < count) {

        Copy(buf, data, count);//из нашего массива в временный баф
        //выделяем новую часть
        count--;
        //delete []b;
        data = new Flower[count];//выделяем новую память
        int  q = 0;
        for (int i = 0; i <= count; i++) {//перезаписываеи из баф в наш  текущий массив
            if (i != k) {//проверка ходим по циклу если не тот который нужен для удаление мы сохраняем 
                //Copy(b[q] , buf[i]);
                data[q] = buf[i];
                ++q;
            }
        }
        delete[]buf;
        //b[n].Copy(InfRab infR, DateZav dateZ, DateTrud dateT, InfaFirm infaF);
        cout << "Данные удалены" << endl;
    }
    else
        cout << "Номер введен неверно!!!" << endl;
    /**int k = 0;
     cout << "Введите номер записи, которую хотите удалить " << endl;
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

     cout << "\nЗапись успешно удалена!" << endl;*/
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

    // Проверяем наличие данных
    if (count == 0) {
        count++;
        data = new Flower[1];
    }
    else {
        // Переносим данные во временный массив
        Flower* buf = new Flower[count];
        Copy(count, data, buf, -1);

        // Выделяем новую память
        delete[] data;
        count++;
        data = new Flower[count];

        // Возвращаем данные
        Copy(count - 1, buf, data, -1);
        delete[] buf;
    }
    data[count - 1] = d;

    std::cout << "Данные добавлены!" << endl;
}

void Flower::Edit(Flower*& data, int count)
{
    //if (IsEmpty()) {
    //    cout << "Данные пусты!" << endl;
     //   return;
    //}

    int k;
    cout << "Введите индекс (от 1 до " << count << "): ";
    cin >> k;
    k--;

    system("cls");

    // Проверка индекса
    if (k < 0 || k >= count) {
        cout << "Индекс вне диапазона!" << endl;
        return;
    }

    data[k].Input();
    system("cls");

    cout << "Данные изменены!" << endl;
}

void Flower::Search(Flower*& data, int count)
{

    int c;
    cout << "Что вы хотите найти?" << endl;
    cout << "1. Название " << endl;
    cout << "2. Вид" << endl;
    cout << "3. Цена" << endl;
    cout << "4. Дата поставки" << endl;


    cin >> c; // для switch

    int k = 0; // для проверки, есть записи или нет
    int* m = &k;
    switch (c)
    {
    case 1:
    {
        cout << "Введите имя для поиска: " << endl;

        char buf[256] = " ";
        cin.ignore();
        gets_s(buf);
        for (int i = 0; i < count; i++)
        {
            if (strcmp(buf, data[i].name) == 0)
            {
                cout << "\n Информация,которую искали: " << endl;
                cout << endl;
                cout << "Номер записи: " << i + 1 << endl;
                cout << "Название: " << data[i].name << endl;
                cout << "Вид: " << data[i].type << endl;
                cout << "Цена: " << data[i].price << endl;
                cout << "Дата: " << data[i].day << " " << data[i].month << " " << data[i].year << endl;

                (*m)++;//запись найдена, увеличиваем счетчик
            }
        }
        break;
    }
    case 2:
    {
        cout << "Введитие вид для поиска: " << endl;

        char buf[256] = "";
        cin.ignore();
        gets_s(buf);
        for (int i = 0; i < count; i++)
        {
            if (strcmp(buf, data[i].type) == 0)
            {
                cout << "\nВаша искомая запись: " << endl;
                cout << endl;
                cout << "Номер записи: " << i + 1 << endl;
                cout << "Название: " << data[i].name << endl;
                cout << "Вид: " << data[i].type << endl;
                cout << "Цена: " << data[i].price << endl;
                cout << "Дата: " << data[i].day << " " << data[i].month << " " << data[i].year << endl;

                (*m)++;//запись найдена, увеличиваем счетчик

            }
        }
        break;
    }
    case 3:
    {
        cout << "Введитие price для поиска: " << endl;

        int x = 0;
        cin >> x;


        for (int i = 0; i < count; i++)
        {
            if (is_equal(x, data[i].price))
            {
                cout << "\nВаша искомая запись: " << endl;
                cout << endl;
                cout << "Номер записи: " << i + 1 << endl;
                cout << "Название: " << data[i].name << endl;
                cout << "Вид: " << data[i].type << endl;
                cout << "Цена: " << data[i].price << endl;
                cout << "Дата: " << data[i].day << " " << data[i].month << " " << data[i].year << endl;

                (*m)++;//запись найдена, увеличиваем счетчик
            }
        }
        break;
    }
    case 4:
    {
        cout << "Введитие date для поиска: " << endl;

        int x, y, z;
        cin >> x >> y >> z;


        for (int i = 0; i < count; i++)
        {
            if (data[i].day == x && data[i].month == y && data[i].year == z)
            {
                cout << "\nВаша искомая запись: " << endl;
                cout << endl;
                cout << "Номер записи: " << i + 1 << endl;
                cout << "Вид: " << data[i].name << endl;
                cout << "Вид: " << data[i].type << endl;
                cout << "Цена: " << data[i].price << endl;
                cout << "Дата: " << data[i].day << " " << data[i].month << " " << data[i].year << endl;

                (*m)++;//запись найдена, увеличиваем счетчик
            }
        }
        break;
    }

    }
    if (k == 0)
    {
        cout << "Такой записи нет!" << endl;
    }
}

void Flower::Sort(Flower*& data, int count)
{
    int n = 0;//счетчик для считывание сколько раз мы делали сортировку
    //сортировка методом пузырька
    for (int i = 0; i < count; i++) {//первый цикл ходит по текущему второй по последующему//т.е второй начинается от текущего плюс 1 до последующего
        for (int j = i + 1; j < count; j++) {
            //условия сортировки
            if (data[i].price > data[j].price) {//элементы класса у нас закрытые поэтому мы выхываем метод который выводит информацию данного объекта
                swap(data[i], data[j]);
                n++;
            }
        }
    }
    cout << "Данные отсортированны " << n << endl;
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
            cout << "Ошибка ввода даты в записи!" << endl;
            return 0;
        }

        if ((month == 2 && day > 28) || (month == 4 && day > 30) || (month == 6 && day > 30) || (month == 9 && day > 30) || (month == 11 && day > 30))
        {
            cout << "Ошибка ввода даты  в записи! " << endl;
            return 0;
        }

        if (((year % 100 == 0 && year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)) && ((day <= 29 && month == 2)))
        {
            cout << "Ошибка ввода даты  в записи!" << endl;
            return 0;
        }

        return 1;

    }

    else {
        int price = 0;
        price = stof(str);
        if (price < 0)
        {
            cout << "Ошибка ввода зарплаты в  записи!  " << endl;
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
    cout << "Название: " << name << endl;
    cout << "Вид: " << type << endl;
    cout << "Стоимость: " << price << endl;
    cout << "Дата поставки (дд.мм.гггг): " << day << "." << month << "." << year << endl;
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