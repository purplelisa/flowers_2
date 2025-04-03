#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <istream>
#include <cmath>


using namespace std;
#define Size 256

class Flower
{
private:
	char* name;
	char type[15];
	double price;
	int day, month, year;

	int  Correct(char* str, int mode);
public:
	Flower();
	Flower(const Flower*& data);

	void Copy(Flower* (&d_n), Flower* (&d_o), int count);
	bool IsEmpty();
	void Copy(int n, Flower* org, Flower* res, int excl);
	void Input();
	void Add(Flower*& data, int& count);
	void Delete(Flower*& data, int& count);
	void Edit(Flower*& data, int count);
	void Sort(Flower*& data, int count);
	void Search(Flower*& data, int count);
	void Save(Flower*& data, int count);
	void Load(Flower*& data, int& count);
	void Print(Flower*& data, int count);
	void FlowerEntry(char* name, char* type, double price, int day, int month, int year);
	void Dispose();

	// ================================================================================ //

	int GetDay() { return price; }
	int GetMonth() { return price; }
	int GetYear() { return price; }
	int GetPrice() { return price; }
	char* GetName() { return name; }
	char* GetType() { return type; }

	void ReadStream(istream& in);
	void WriteStream(ostream& out);

	void SetName(char* name);
	void Print();

	friend bool Equal(const Flower& a, const Flower& b);
	friend bool More(const Flower& a, const Flower& b);
};

bool is_equal(double x, double y);


