#include "Table.h"
#include <Windows.h>

int main() {
	// Локализация консоли
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Table db;
	db.Actions();
}