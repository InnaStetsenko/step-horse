#include <iostream>
#include <windows.h>
using namespace std;
const int k = 5; // chess board size
int ar[k][k];
const int shift_count = 8;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD shift[]
{
	{ 1, -2 }, { 2, -1 }, { 2, 1 }, { 1, 2 },
	{ -1, 2 }, { -2, 1 }, { -2, -1 }, { -1, -2 }
};

int rollbacks = 0;
void show_state()
{
	COORD info{ 0, 1 };
	
	SetConsoleCursorPosition(h, info);
	SetConsoleTextAttribute(h, 10);
	for (int y = 0; y < k; y++)
	{
		for (int x = 0; x < k; x++)
		{
			cout << "\t" << ar[y][x];
		}
		cout << "\n\n";
	}
}
void message()
{
	COORD mg{ 42,1 };
	SetConsoleCursorPosition(h, mg);
	SetConsoleTextAttribute(h, 3);
	cout << " Message:";
}
void back()
{
	COORD back{ 42,3 };
	SetConsoleCursorPosition(h, back);
	SetConsoleTextAttribute(h, 3);
	cout << " Returns:";
}
bool pony(int x, int y, int step)
{
	show_state();
	Sleep(2000);

	ar[y][x] = step;
	if (step >= k * k)
		return true;
	for (int i = 0; i < shift_count; i++)
	{
		if ((x + shift[i].X >= 0) && (x + shift[i].X < k) &&
			(y + shift[i].Y >= 0) && (y + shift[i].Y < k) &&
			(ar[y + shift[i].Y][x + shift[i].X] == 0))
		{
			if (pony(x + shift[i].X, y + shift[i].Y, step + 1))
				return true;
		}
		else
		{
			rollbacks++;
			show_state();
			COORD mg{ 55,1 };
			SetConsoleCursorPosition(h, mg);
			SetConsoleTextAttribute(h, 3);
			cout << " Lock ";
			Sleep(1000);
			SetConsoleCursorPosition(h, mg);
			cout << "      ";
			COORD retn{ 59,3 };
			SetConsoleCursorPosition(h, retn);
			SetConsoleTextAttribute(h, 3);
			cout << rollbacks;

		}
	}

	ar[y][x] = 0;
	show_state();
	Sleep(2000);
	
	return false;
}

int main()
{
	system("title Horse Move");
	int x, y;
	cout << "Put position, two numbers from 0 to " << k - 1 << ":\n";
	cin >> x >> y;
	if (x < 0 || x > k - 1) x = 0;
	if (y < 0 || y > k - 1) y = 0;
	system("cls");

	message();
	back();
	pony(x, y, 1);

	// results
	show_state();

	system("pause");
}
