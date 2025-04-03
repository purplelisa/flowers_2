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
			cout << "�������� �����!" << endl;
			break;
		}

		system("pause"); // �������� �������
		system("cls");	 // ������� �������
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

	cout << "������ ���������!" << endl;
}

void Table::Edit()
{
	if (IsEmpty()) {
		cout << "������ �����!" << endl;
		return;
	}

	int index;
	cout << "������� ������ (�� 1 �� " << count << "): ";
	cin >> index;
	index--;

	system("cls");

	// �������� �������
	if (index < 0 || index >= count) {
		cout << "������ ��� ���������!" << endl;
		return;
	}

	data[index].Input();
	system("cls");

	cout << "������ ��������!" << endl;
}

void Table::Delete()
{
	if (IsEmpty()) {
		cout << "������ �����!" << endl;
		return;
	}

	int index;
	cout << "������� ������ (�� 1 �� " << count << "): ";
	cin >> index;
	index--;

	system("cls");

	// �������� �������
	if (index < 0 || index >= count) {
		cout << "������ ��� ���������!" << endl;
		return;
	}

	// ��������� ������ �� ��������� ������
	Flower* buf = new Flower[count];
	Copy(count, data, buf, -1);

	// �������� ����� ������
	delete[] data;
	count--;
	data = new Flower[count];

	// ���������� ������, ����� ����������
	Copy(count + 1, buf, data, index);
	delete[] buf;

	cout << "������ �������!" << endl;
}

void Table::Print()
{
	if (IsEmpty()) {
		cout << "������ �����!" << endl;
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
		cout << "������ �����!" << endl;
		return;
	}

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
			if (strcmp(buf, data[i].GetName()) == 0)
			{
				cout << "\n ����������,������� ������: " << endl;
				cout << endl;
				cout << "����� ������: " << i + 1 << endl;
				data[i].Print();

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
			if (strcmp(buf, data[i].GetType()) == 0)
			{
				cout << "\n���� ������� ������: " << endl;
				cout << endl;
				cout << "����� ������: " << i + 1 << endl;
				data[i].Print();

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
			if (is_equal(x, data[i].GetPrice()))
			{
				cout << "\n���� ������� ������: " << endl;
				cout << endl;
				cout << "����� ������: " << i + 1 << endl;
				data[i].Print();

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
			if (data[i].GetDay() == x && data[i].GetMonth() == y && data[i].GetYear() == z)
			{
				cout << "\n���� ������� ������: " << endl;
				cout << endl;
				cout << "����� ������: " << i + 1 << endl;
				data[i].Print();

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

void Table::Sort()
{
	if (IsEmpty()) {
		cout << "������ �����!" << endl;
		return;
	}

	int n = 0;//������� ��� ���������� ������� ��� �� ������ ����������

	//���������� ������� ��������
	for (int i = 0; i < count; i++) {//������ ���� ����� �� �������� ������ �� ������������//�.� ������ ���������� �� �������� ���� 1 �� ������������
		for (int j = i + 1; j < count; j++) {
			//������� ����������
			if (data[i].GetPrice() > data[j].GetPrice()) {//�������� ������ � ��� �������� ������� �� �������� ����� ������� ������� ���������� ������� �������
				swap(data[i], data[j]);
				n++;
			}
		}
	}
	cout << "������ �������������� " << n << endl;
}

void Table::Save()
{
	if (IsEmpty()) {
		cout << "������ �����!" << endl;
		return;
	}

	string fname;
	cout << "������� �������� �����: ";
	cin >> fname;

	system("cls");

	// ������� ����� ��� ���������� �����
	ofstream fout(fname, ios::out);

	fout << count << endl;
	for (int i = 0; i < count; i++) {
		data[i].WriteStream(fout);

		if (i < count - 1)
			fout << endl;
	}

	fout.close();
	cout << "������ ���������!" << endl;
}

void Table::Load()
{
	string fname;
	cout << "������� �������� �����: ";
	cin >> fname;

	system("cls");

	// ������� ����� ��� ������
	ifstream fin(fname);

	if (!fin) {
		cout << "������ ������� �����!" << endl;
		return;
	}

	fin >> count;
	Init(count);

	for (int i = 0; i < count; i++) {
		data[i].ReadStream(fin);
	}

	fin.close();
	cout << "������ ���������!" << endl;
}

bool Table::IsEmpty()
{
	return count == 0;
}

void Table::Menu(int& act)
{
	cout << "�������� ��������: " << endl
		<< "0: �����" << endl
		<< "1: ��������" << endl
		<< "2: ��������" << endl
		<< "3: ��������" << endl
		<< "4: �������" << endl
		<< "5: �����" << endl
		<< "6: ����������" << endl
		<< "7: ���������" << endl
		<< "8: ���������" << endl;

	while (true)
	{
		cout << "��� �����: ";
		cin >> act;

		if (!cin)
		{
			cout << "\n�������� ����, ���������� �����!\n";
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
