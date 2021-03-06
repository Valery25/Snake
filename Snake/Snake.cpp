#include <iostream> //Стандартная библиотека
#include <conio.h> //Библиотека работы с клавиатурой
#include <Windows.h> //Библиотека работы с консолью
#include <time.h> //Библиотека, подключающая время

using namespace std;

enum ConsoleColor //Цвета
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

bool gameOver;
const int width = 50; //Ширина поля
const int height = 20; //Высота поля
int x, y, l, fruitX, fruitY, score; //Голова, фрукт и счёт
int tailX[100], tailY[100]; //Отрисовка хвоста
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //Список возможных действий змеи
eDirection dir;

void Setup() {
	srand(time(NULL)); //Истинный рандом
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1; //В начале змейка стоит в центре
	y = height / 2 - 1; //В начале змейка стоит в центре
	fruitX = rand() % (width - 1); //Координаты фрукта по ширине
	fruitY = rand() % (height - 1);  //Координаты фрукта по высоте
	score = 0;
}

void Draw() {
	system("cls"); //Очистка экрана
	system("color F0"); //Установка цвета
	for (int i = 0; i < width + 1; i++)
		cout << "-"; //Прорисовка верхней грани рамки
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if ((j == 0) || (j == width - 1))
				cout << "|"; //Прорисовка левой и правой граней рамки
			if (i == y && j == x)
				cout << "0"; //Голова змеи
			else if (i == fruitY && j == fruitX)
				cout << "F"; //Фрукт
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) { //Прорисовка тела змеи
						print = true;
						cout << "o"; //Тело змеи
					}
				}
				if (!print)
					cout << " "; //Отрисовка поля
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)
		cout << "-"; //Прорисовка нижней грани рамки
	cout << endl;
	cout << "Счёт: " << score << endl; //Счёт
	setlocale(LC_ALL, "Russian");
	cout << "W S A D - управление, X - закрыть игру. Играть на английской раскладке" << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) //Функция ввода команд с клавиатуры
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break; //Закрытие приложения при нажатии на "x"
		}
	}
}

void Logic() {
	Sleep(150); //Скорость игры
	int prevX = tailX[0]; //Логика хвоста по иксу
	int prevY = tailY[0]; //Логика хвоста по игрику
	int prev2X, prev2Y; //Прошлое положение хвоста
	tailX[0] = x; // Путь за зеёй
	tailY[0] = y; //Путь за змеёй
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i]; //Начало движения хвоста за головой
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y; //Замена на повтор хвостового движения
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	//if (x > width || x < 0 || y > height || y < 0) //Конец игры при врезании в стену
	//	gameOver = true;

	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2; //Переход через стену

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1; //Переход через стену

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) //Если змея ест хвос - конец игры
			gameOver = true;
	}

	if (x == fruitX && y == fruitY) {
		score++; //Добавление очков
		fruitX = rand() % (width - 1);
		fruitY = rand() % (height - 1); //Следующий фрукт
		nTail++;
	}
}

int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
	}
	setlocale(LC_ALL, "Russian");
	cout << "Игра окончена. Ваш счёт: " << score << endl;
	system("PAUSE");
	return 0;
}