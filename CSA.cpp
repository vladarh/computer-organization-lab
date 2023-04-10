#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>

template <typename T>
class Bin {
	union {
		T m_number = 0;
		char m_cnumber[sizeof(m_number)];
	};
	int m_numsys;
	int m_color;
	int m_low;
	int m_high;
	int m_speed;
public:
	Bin() {
		m_color = -1;
		m_low = -1;
		m_high = -1;
	}
	void Bit();
	void Sys();
	void Set();
	void Bits();
	int Inp(int a, int b);
	void Color();
	void GraphIn();
	void GraphOut();
};
enum {
	Char = 49,
	Int,
	Float,
	Double,
	Short_int
};
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
void SetColor(int text, int background) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

bool contwork(char a) {
	if (a == 27)
		return 0;
	std::cout << "\nContinue?\n";
	return (_getch() == 13);
}
void Menu() {
	char a;
	do {
		system("cls");
		std::cout << "1.Char\n2.Int\n3.Float\n4.Double\n5.Short int";
		do {
			a = _getch();
		} while ((a < '1') && (a > '5'));
		Bin <char> bin;
		Bin <int> bin1;
		Bin <float> bin2;
		Bin <double> bin3;
		Bin <short int> bin4;
		switch (a) {
		case Char:
			bin.Set();
			break;
		case Int:
			bin1.Set();
			break;
		case Float:
			bin2.Set();
			break;
		case Double:
			bin3.Set();
			break;
		case Short_int:
			bin4.Set();
			break;
		}
	} while (contwork(a));
}
int todec(int numsys, char num, int* n) {
	bool a = false;
	if (numsys <= 10) {
		if ((num >= '0') && (num <= numsys + 48)) {
			*n = num - '0';
			a = 1;
		}
	}
	if ((numsys >= 11) && (numsys <= 36)) {
		if ((num >= '0') && (num <= '9')) {
			*n = num - '0';
			a = 1;
		}
		if ((num >= 'A') && (num <= numsys - 10 + 'A')) {
			*n = num + 10 - 'A';
			a = 1;
		}
	}
	if ((numsys >= 37) && (numsys <= 62)) {
		if ((num >= '0') && (num <= '9')) {
			*n = num - '0';
			a = 1;
		}
		if ((num >= 'A') && (num <= 'Z')) {
			*n = num + 10 - 'A';
			a = 1;
		}
		if ((num >= 'a') && (num <= numsys - 36 + 'a')) {
			*n = num + 36 - 'a';
			a = 1;
		}
	}
	return *n;
}
bool diap(int numsys, char num) {
	bool a = false;
	if (numsys <= 10) {
		if ((num >= '0') && (num <= numsys + 48)) {
			a = 1;
		}
	}
	if ((numsys >= 11) && (numsys <= 36)) {
		if ((num >= '0') && (num <= '9')) {
			a = 1;
		}
		if ((num >= 'A') && (num <= numsys - 10 + 'A')) {
			a = 1;
		}
	}
	if ((numsys >= 37) && (numsys <= 62)) {
		if ((num >= '0') && (num <= '9')) {
			a = 1;
		}
		if ((num >= 'A') && (num <= 'Z')) {
			a = 1;
		}
		if ((num >= 'a') && (num <= numsys - 36 + 'a')) {
			a = 1;
		}
	}
	return a;
}
template<typename T>
void Bin<T>::Bit()
{
	std::cout << "Binary: ";
	for (int i = sizeof(m_number) * 8 - 1; i >= 0; i--) {
		SetColor(White, Black);
		if ((i != sizeof(m_number) * 8 - 1) && ((i + 1) % 4 == 0)) {
			std::cout << ' ';
		}
		if ((i >= m_low) && (i <= m_high) && (m_color != -1))
			SetColor(m_color, Black);
		if ((i != (sizeof(m_number) * 8 - 1)) && (!((i + 1) % 8)))
			std::cout << ' ';
		std::cout << ((m_cnumber[i / 8] >> (i % 8)) & 1);
	}
	SetColor(White, Black);
	std::cout << '\n';
}

template<typename T>
void Bin<T>::Sys()
{
	std::cout << " 2 to 62: ";
	m_numsys = 0;
	char sym;
	int count = 0;
	do {
		sym = _getch();
		if ((count < 2) && (sym >= '0') && (sym <= '9')) {
			std::cout << sym;
			m_numsys = m_numsys * 10 + sym - '0';
			count += 1;
		}
		if ((sym == 8) && (count)) {
			std::cout << "\b \b";
			m_numsys /= 10;
			count -= 1;
		}
	} while ((sym != 13) || ((m_numsys < 2) || (m_numsys > 62)));
	std::cout << '\n';
}

template<typename T>
void Bin<T>::Bits()
{
	std::cout << "Enter high bit: ";
	int high = Inp(1, sizeof(m_number) * 8 - 1);
	std::cout << "Enter amount: ";
	int group = Inp(1, high + 1);
	uint64_t temp = 0;
	int temp1 = high - group + 1;
	m_low = temp1, m_high = high;
	for (int i = high; i >= high - group + 1; i--, temp1++)
		temp |= (uint64_t)(((m_cnumber[i / 8] >> (i % 8)) & 1)) << temp1;
	temp1 = high - group + 1;
	for (int i = sizeof(m_number) * 8 - 1; i >= 0; i--) {
		if ((i != sizeof(m_number) * 8 - 1) && ((i + 1) % 4 == 0)) {
			std::cout << ' ';
		}
		if ((i >= temp1) && (i <= high))
			if ((temp >> i) & 1)
				m_cnumber[i / 8] |= ((1 << (i % 8)));
			else
				m_cnumber[i / 8] &= (~(1 << (i % 8)));
	}
	std::cout << "Set color of changed bits?";
	char a;
	do {
		a = _getch();
	} while ((a != 13) && (a != 27));
	if (a == 13)
		Color();
	Bit();
	std::cout << '\n' << "Number after: " << std::fixed << m_number;
	GraphIn();
	//GraphOut();
}

template<typename T>
int Bin<T>::Inp(int a, int b)
{
	int num = 0, count = 0;
	char sym;
	do {
		sym = _getch();
		if ((count < 3) && (sym >= '0') && (sym <= '9')) {
			std::cout << sym;
			num = num * 10 + sym - '0';
			count += 1;
		}
		if ((sym == 8) && (count)) {
			std::cout << "\b \b";
			num /= 10;
			count -= 1;
		}
	} while ((sym != 13) || ((num < a) || (num > b)));
	std::cout << '\n';
	return num;
}

template<typename T>
void Bin<T>::Color()
{
	SetColor(Black, Black);
	std::cout << "\n1.Black\n";
	SetColor(Blue, Black);
	std::cout << "2.Blue\n";
	SetColor(Green, Black);
	std::cout << "3.Green\n";
	SetColor(Cyan, Black);
	std::cout << "4.Cyan\n";
	SetColor(Red, Black);
	std::cout << "5.Red\n";
	SetColor(Magenta, Black);
	std::cout << "6.Magenta\n";
	SetColor(Brown, Black);
	std::cout << "7.Brown\n";
	SetColor(LightGray, Black);
	std::cout << "8.LightGray\n";
	SetColor(DarkGray, Black);
	std::cout << "9.DarkGray\n";
	SetColor(LightBlue, Black);
	std::cout << "10.LightBlue\n";
	SetColor(LightGreen, Black);
	std::cout << "11.LightGreen\n";
	SetColor(LightRed, Black);
	std::cout << "12.LightRed\n";
	SetColor(LightMagenta, Black);
	std::cout << "13.LightMagenta\n";
	SetColor(Yellow, Black);
	std::cout << "14.Yellow\n";
	SetColor(White, Black);
	std::cout << "15.White\n";
	m_color = Inp(1, 15) - 1;
	std::cout << '\n';
}
BOOL Line(HDC hdc, int x1, int y1, int x2, int y2) {
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
}
template<typename T>
void Bin<T>::GraphIn()
{
	std::cout << "\nGraph of singnal\n";
	std::cout << "Set speed of graph animation: \n";
	m_speed = Inp(0, 1000000);
	int y = 620;
	HWND hWnd = GetConsoleWindow();
	HDC hDc = GetDC(hWnd);
	int  r = 100, b = 255, g = 255;
	COLORREF color = RGB(r, g, b);
	HPEN pen = CreatePen(PS_SOLID, 5, color);
	SelectObject(hDc, pen);
	double period = 13;
	int size = 0;
	int e = 0, c = 0, h = 0, f = 0;
	Line(hDc, 0, y, 2000, y);
	int mas[sizeof(m_number) * 2];
	for (int i = 0; i < sizeof(m_number); i++)
		mas[i] = 0;
	for (int i = sizeof(m_number) * 2 - 1; i >= 0; i--) {
		if (i % 2)
			mas[i] = (m_cnumber[i / 2] & (15 << 4)) >> 4;
		else
			mas[i] = m_cnumber[i / 2] & 15;
		mas[i] *= 10;
	}
	double y1 = 0;

	color = RGB(255, 100, 100);
	for (int i = sizeof(m_number) * 2 - 1; i >= 0; i--) {
		//if(i != sizeof(m_number))
		//y1 = mas[i];
		for (double x1 = 0; x1 < period; x1 += 0.01) {
			SetPixel(hDc, x1 * 2 + size * 25, y - y1, color);
			Sleep(m_speed);
		}
		if (i) {
			if (mas[i] != mas[i - 1]) {
				bool max = (mas[i] > mas[i - 1] ? true : false);
				if (max) {
					double min = y1 - 20;
					for (; y1 > min; y1 -= 0.01) {
						SetPixel(hDc, (size + 1) * 25, y - y1, color);
						Sleep(m_speed);
					}
				}
				else {
					double high = y1 + 20;
					for (; y1 < high; y1 += 0.01) {
						SetPixel(hDc, (size + 1) * 25, y - y1, color);
						Sleep(m_speed);
					}
				}
			}
		}
		size++;
	}


	/*for (int i = sizeof(m_number) * 8 - 1; i >= 0; i--) {
		if (((m_cnumber[i / 8] >> (i % 8)) & 1) == 0) {
			color = RGB(255, 100, 100);
			pen = CreatePen(PS_SOLID, 1, color);
			if (i == sizeof(m_number) * 8 - 1) {
				double y1 = ;
				for (; y1 < 0; y1 += 0.01) {
					SetPixel(hDc, size * 25, y - y1, color);
					Sleep(m_speed);
				}
				for (double x1 = 0; x1 < period; x1 += 0.01) {
					++e;
					SetPixel(hDc, x1 * 2 + size * 25, y - y1, color);
					Sleep(m_speed);
				}
			}
			else {
				double y1 = -50;
				if (((m_cnumber[(i + 1) / 8] >> ((i + 1) % 8)) & 1)) {
					for (; y1 < 0; y1 += 0.01) {
						SetPixel(hDc, size * 25, y - y1, color);
						Sleep(m_speed);
					}
					for (double x1 = 0; x1 < period; x1 += 0.01) {
						SetPixel(hDc, x1 * 2 + size * 25, y - y1, color);
						Sleep(m_speed);
					}
				}
				else {
					y1 = 0;
					for (double x1 = 0; x1 < period; x1 += 0.01) {
						SetPixel(hDc, x1 * 2 + size * 25, y - y1, color);
						Sleep(m_speed);
					}
				}
			}
		}
		else {
			color = RGB(100, 255, 255);
			pen = CreatePen(PS_SOLID, 1, color);
			double y1 = 0;
			if (i == sizeof(m_number) * 8 - 1) {
				for (; y1 > -50; y1 -= 0.01) {
					SetPixel(hDc, size * 25, y - y1, color);
					Sleep(m_speed);
				}
				for (double x1 = 0; x1 < period; x1 += 0.01) {
					Sleep(m_speed);
					SetPixel(hDc, x1 * 2 + size * 25, y - y1, color);
				}
			}
			else {
				if (((m_cnumber[(i + 1) / 8] >> ((i + 1) % 8)) & 1) == 0) {
					for (; y1 > -50; y1 -= 0.01) {
						SetPixel(hDc,  size * 25, y - y1, color);
						Sleep(m_speed);
					}
					for (double x1 = 0; x1 < period; x1 += 0.01) {
						Sleep(m_speed);
						SetPixel(hDc, x1 * 2 + size * 25, y - y1, color);
					}
				}
				else {
					y1 = -50;
					for (double x1 = 0; x1 < period; x1 += 0.01) {
						SetPixel(hDc, x1 * 2 + size * 25, y - y1, color);
						Sleep(m_speed);
					}
				}
			}
		}
		++size;
	}*/
}

template<typename T>
void Bin<T>::GraphOut()
{
	int y = 700;
	HWND hWnd = GetConsoleWindow();
	HDC hDc = GetDC(hWnd);
	int  r = 100, b = 255, g = 255;
	COLORREF color = RGB(r, g, b);
	HPEN pen = CreatePen(PS_SOLID, 5, color);
	SelectObject(hDc, pen);
	int period = 13;
	int size = 0;
	int e = 0, c = 0, h = 0, f = 0;
	for (int i = sizeof(m_number) * 8 - 1; i >= 0; i--) {
		if (((m_cnumber[i / 8] >> (i % 8)) & 1) == 0) {
			color = RGB(255, 100, 100);
			for (double x1 = 0; x1 < period; x1 += 0.01) {
				double y1 = sin(x1 + 6.26) * (50);
				SetPixel(hDc, x1 * 2 + size * 25, y - y1, color);
				Sleep(m_speed);
			}
		}
		else {
			color = RGB(100, 255, 255);
			for (double x1 = 0; x1 < period; x1 += 0.01) {
				double y1 = cos(x1 + 1.055) * (50);
				SetPixel(hDc, x1 * 2 + size * 25, y - y1, color);
				Sleep(m_speed);
			}
		}
		++size;
	}
}

template<typename T>
void Bin<T>::Set()
{
	std::string type = typeid(m_number).name();
	std::cout << "\nEnter numeral system for type " << type;
	int e = 0;
	if ((type == "float") || (type == "double"))
		e = 1;
	if (type == "char")
		e = 2;
	Sys();
	char* num = (char*)malloc(sizeof(char));
	char sym;
	int count = 0;
	bool sign = false;
	bool point = 0;
	int b = 0;
	int c = 0;
	if (e == 2) {
		std::cout << "\nEnter symbol or value?(2\\0)\n";
		char a;
		do {
			a = _getch();
		} while ((a != '2') && (a != '0'));
		e = a - 48;
	}
	if (e == 2) {
		std::cout << "Enter symbol: ";
		m_number = _getch();
		std::cout << m_number << '\n';
		std::cout << "Symbol code:\n";
		std::cout << (int)m_number << '\n';
	}
	else {
		std::cout << "Enter value: ";
		do {
			sym = _getch();
			if ((sym == '-') && (!count) && (!sign)) {
				std::cout << '-';
				sign = 1;
			}
			if (((sym == '.') || (sym == ',')) && (count) && (!point) && (e == 1)) {
				std::cout << '.';
				point = 1;
			}
			if (F(m_numsys, sym)) {
				std::cout << sym;
				num[count + b] = sym;
				if (point)
					b += 1;
				else
					count += 1;
				num = (char*)realloc(num, sizeof(char) * (count + 1 + b));
				num[count + b] = '\0';
			}
			if (sym == 8) {
				if (count > 1) {
					num = (char*)realloc(num, sizeof(char) * (count - 1));
					if (point) {
						b -= 1;
						if (!b) {
							std::cout << "\b \b";
							point = 0;
						}
					}
					else
						count -= 1;
					std::cout << "\b \b";
				}
				else {
					if (count == 1) {
						if (sign) {
							sign = 0;
							std::cout << "\b \b";
						}
						num[0] = '\0';
						count = 0;
						std::cout << "\b \b";
					}
				}
			}
		} while (sym != 13);
		int numsys;
		if (point) {
			point = 0;
			int d = 0;
			for (int i = 0; i < count; i++)
				m_number = m_numsys * m_number + todec(m_numsys, num[i], &d);
			for (int i = count; i < count + b; i++)
				m_number = m_number + todec(m_numsys, num[i], &d) / pow(m_numsys, i - count + 1);
		}
		else {
			int d = 0;
			for (int i = 0; i < count; i++)
				m_number = m_numsys * m_number + todec(m_numsys, num[i], &d);
		}
		if (sign) {
			m_number *= (-1);
			sign = 0;
		}
		std::cout << '\n';
		std::cout << "Value in decimal numeral system: ";
		std::cout << std::fixed << m_number << '\n';
	}
	Bit();
	std::cout << "\nDo binary operatoins?\n";
	do {
		sym = _getch();
	} while ((sym != 13) && (sym != 27));
	if (sym == 13)
		Bits();
	_getch();
}

int main()
{
	Menu();
}



