#pragma once
#pragma once
#include "Flower.h"
#include <string>

// ���� ������ ���� ������
class Table
{
	// ���� ������
private: // �������� �����
	Flower* data;
	int count;

	// ������ ������
	void Copy(int n, Flower* org, Flower* res, int excl);
	void Add();
	void Edit();
	void Delete();
	void Print();
	void Search();
	void Sort();
	void Save();
	void Load();
	bool IsEmpty();

	void Menu(int& act);

	void Init(int count);

public: // �������� �����
	Table();
	~Table();

	void Actions();
};

