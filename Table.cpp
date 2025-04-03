#include "Table.h"

Table::Table()
{
	data = nullptr;
	count = 0;
}

Table::~Table()
{
	if (data == nullptr)
		return;

	delete[] data;
}

void Table::Actions()
{
	int act = 0;
	do {
		Menu(act);

		switch (act)
		{
		case 0:
			break;

		case 1:
			Print();
			break;

		case 2:
			Add();
			break;

		case 3:
			Edit();
			break;

		case 4:
			Delete();
			break;

		case 5:
			Search();
			break;

		case 6:
			Sort();
			break;

		case 7:
			Load();
			break;

		case 8:
			Save();
			break;

		default:
			cout << "Неверный выбор!" << endl;
			break;
		}

		system("pause"); // задержка консоли
		system("cls");	 // очистка консоли
	} while (act != 0);
}

void Table::Copy(int n, Flower* org, Flower* res, int excl)
{
	int q = 0;
	for (int i = 0; i < n; i++) {
		if (i != excl)
			res[q++] = org[i];
	}
}

void Table::Add()
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

	cout << "Данные добавлены!" << endl;
}

void Table::Edit()
{
	if (IsEmpty()) {
		cout << "Данные пусты!" << endl;
		return;
	}

	int index;
	cout << "Введите индекс (от 1 до " << count << "): ";
	cin >> index;
	index--;

	system("cls");

	// Проверка индекса
	if (index < 0 || index >= count) {
		cout << "Индекс вне диапазона!" << endl;
		return;
	}

	data[index].Input();
	system("cls");

	cout << "Данные изменены!" << endl;
}

void Table::Delete()
{
	if (IsEmpty()) {
		cout << "Данные пусты!" << endl;
		return;
	}

	int index;
	cout << "Введите индекс (от 1 до " << count << "): ";
	cin >> index;
	index--;

	system("cls");

	// Проверка индекса
	if (index < 0 || index >= count) {
		cout << "Индекс вне диапазона!" << endl;
		return;
	}

	// Переносим данные во временный массив
	Flower* buf = new Flower[count];
	Copy(count, data, buf, -1);

	// Выделяем новую память
	delete[] data;
	count--;
	data = new Flower[count];

	// Возвращаем данные, кроме удаляемого
	Copy(count + 1, buf, data, index);
	delete[] buf;

	cout << "Данные удалены!" << endl;
}

void Table::Print()
{
	if (IsEmpty()) {
		cout << "Данные пусты!" << endl;
		return;
	}

	for (int i = 0; i < count; i++) {
		data[i].Print();
		cout << endl;
	}
}

void Table::Search()
{
	if (IsEmpty()) {
		cout << "Данные пусты!" << endl;
		return;
	}

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
			if (strcmp(buf, data[i].GetName()) == 0)
			{
				cout << "\n Информация,которую искали: " << endl;
				cout << endl;
				cout << "Номер записи: " << i + 1 << endl;
				data[i].Print();

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
			if (strcmp(buf, data[i].GetType()) == 0)
			{
				cout << "\nВаша искомая запись: " << endl;
				cout << endl;
				cout << "Номер записи: " << i + 1 << endl;
				data[i].Print();

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
			if (is_equal(x, data[i].GetPrice()))
			{
				cout << "\nВаша искомая запись: " << endl;
				cout << endl;
				cout << "Номер записи: " << i + 1 << endl;
				data[i].Print();

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
			if (data[i].GetDay() == x && data[i].GetMonth() == y && data[i].GetYear() == z)
			{
				cout << "\nВаша искомая запись: " << endl;
				cout << endl;
				cout << "Номер записи: " << i + 1 << endl;
				data[i].Print();

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

void Table::Sort()
{
	if (IsEmpty()) {
		cout << "Данные пусты!" << endl;
		return;
	}

	int n = 0;//счетчик для считывание сколько раз мы делали сортировку

	//сортировка методом пузырька
	for (int i = 0; i < count; i++) {//первый цикл ходит по текущему второй по последующему//т.е второй начинается от текущего плюс 1 до последующего
		for (int j = i + 1; j < count; j++) {
			//условия сортировки
			if (data[i].GetPrice() > data[j].GetPrice()) {//элементы класса у нас закрытые поэтому мы выхываем метод который выводит информацию данного объекта
				swap(data[i], data[j]);
				n++;
			}
		}
	}
	cout << "Данные отсортированны " << n << endl;
}

void Table::Save()
{
	if (IsEmpty()) {
		cout << "Данные пусты!" << endl;
		return;
	}

	string fname;
	cout << "Введите название файла: ";
	cin >> fname;

	system("cls");

	// Создаем поток для перезаписи файла
	ofstream fout(fname, ios::out);

	fout << count << endl;
	for (int i = 0; i < count; i++) {
		data[i].WriteStream(fout);

		if (i < count - 1)
			fout << endl;
	}

	fout.close();
	cout << "Данные сохранены!" << endl;
}

void Table::Load()
{
	string fname;
	cout << "Введите название файла: ";
	cin >> fname;

	system("cls");

	// Создаем поток для чтения
	ifstream fin(fname);

	if (!fin) {
		cout << "Ошибка отрытия файла!" << endl;
		return;
	}

	fin >> count;
	Init(count);

	for (int i = 0; i < count; i++) {
		data[i].ReadStream(fin);
	}

	fin.close();
	cout << "Данные загружены!" << endl;
}

bool Table::IsEmpty()
{
	return count == 0;
}

void Table::Menu(int& act)
{
	cout << "Выберите действие: " << endl
		<< "0: Выход" << endl
		<< "1: Просмотр" << endl
		<< "2: Добавить" << endl
		<< "3: Изменить" << endl
		<< "4: Удалить" << endl
		<< "5: Поиск" << endl
		<< "6: Сортировка" << endl
		<< "7: Загрузить" << endl
		<< "8: Сохранить" << endl;

	while (true)
	{
		cout << "Ваш выбор: ";
		cin >> act;

		if (!cin)
		{
			cout << "\nНеверный ввод, попробуйте снова!\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else
			break;
	}

	system("cls");
}

void Table::Init(int count)
{
	this->count = count;

	if (data != nullptr)
		delete[] data;

	data = new Flower[count];
}
