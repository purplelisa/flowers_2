#pragma once
#pragma once
#include "Flower.h"
#include <string>

// База данных всех цветов
class Table
{
	// Поля класса
private: // закрытая часть
	Flower* data;
	int count;

	// Методы класса
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

public: // открытая часть
	Table();
	~Table();

	void Actions();
};

