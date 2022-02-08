#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <vector>
#include <thread>
#include <mutex>

#include "Figure.h"
#include "Binary_Operations.h"
#define MAX_LOADSTRING	100
#define MY_KEYDOWN		600
#define IDC_MY			109
#define UPP				601
#define DOWNN			602
#define LEFTT			603
#define RIGHTT			604
typedef struct tagMYREC
{
	int  ind;
	char  key;
} MYREC;
COPYDATASTRUCT MyCDS;
PCOPYDATASTRUCT pMyCDS;
MYREC MyRec;
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING] = L"IBM";;                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING] = L"IBM";            // имя класса главного окна

std::vector<Figure*> allFigure;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE);
/**
 * \brief Оконная процедура (объявление)
 * \param hWnd Хендл окна
 * \param message Идентификатор сообщения
 * \param wParam Параметр сообщения
 * \param lParam Парамтер сообщения
 * \return Код выполнения
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}


	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	return TRUE;
}


int processing(HINSTANCE hInst) {
	MyRegisterClass(hInst);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInst))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_MY));

	MSG msg;


	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{

			SendMessage(msg.hwnd, WM_PAINT, NULL, NULL);
			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

void EnterNewFigure() {
	std::cout << "Пермещаем с помощью WASD, устанавливаем по нажатии Enter.\nОтмена установления N.\n";
	bool exitMovement = 1;
	int cancellation = 1;
	while (exitMovement) {
		switch (char c = _getch())
		{
		case 'A':
		case 'ф':
		case 'Ф':
		case 'a': //Движение влево
		{
			SendMessageW(hWnd, MY_KEYDOWN, VK_LEFT, NULL);
			break;
		}
		case 'd':
		case 'D':
		case 'в':
		case 'В': //Движение вправо
		{
			SendMessageW(hWnd, MY_KEYDOWN, VK_RIGHT, NULL);
			break;
		}
		case 'w':
		case 'W':
		case 'ц':
		case 'Ц': //Движение вверх
		{
			SendMessageW(hWnd, MY_KEYDOWN, VK_UP, NULL);
			break;
		}
		case 'ы':
		case 'Ы':
		case 'S':
		case 's': //Движение внииз
		{
			SendMessageW(hWnd, MY_KEYDOWN, VK_DOWN, NULL);
			break;
		}
		case 'n':
		case 'N':
		case 'т':
		case 'Т':
		{
			allFigure.erase(allFigure.begin()+ allFigure.size() - 1);
			cancellation = -1;
			exitMovement = 0;
			break;
		}
		case 13:
			exitMovement = 0;
			break;
		}
	}
	if (cancellation != -1) {
		if (allFigure.size() > 1) {
			bool exitConnetinos = 1;
			if (allFigure[allFigure.size() - 1]->getIn() - 1 >= 0)	{
				while (exitConnetinos) {
					std::cout << "Соединяем входы 0.." << allFigure[allFigure.size() - 1]->getIn() - 1 << "? (Y/N)\n";
					switch (char c = _getch())
					{
					case 'y':
					case 'Y':
					case 'н':
					case 'Н':
					{
						int counterConncetIn = 0;
						for (int j = 0; j < allFigure[allFigure.size() - 1]->getIn(); j++) {
							if (allFigure[allFigure.size() - 1]->getStatusIn(j)) counterConncetIn++;
						}
						if (counterConncetIn != allFigure[allFigure.size() - 1]->getIn()) { //проверка на заполняемость всех выходов
							int indInNewFigure; //индекс входа
							bool exitFromConnet = 1;
							int exit = 1;
							//выбор индекса входа нашей новой фигуры
							while (exitFromConnet) {
								std::cout << "Выберите входы 0.." << allFigure[allFigure.size() - 1]->getIn() - 1 << std::endl;
								std::cout << "-1 для отмены\n";
								std::cin >> indInNewFigure;
								if (indInNewFigure != -1) {
									if (indInNewFigure < 0 || indInNewFigure > allFigure[allFigure.size() - 1]->getIn() - 1) {
										std::cout << "Некоректное значение!\n";
									}
									else {
										if (allFigure[allFigure.size() - 1]->getStatusIn(indInNewFigure)) {
											std::cout << "Вход " << indInNewFigure << " занят, выберите другой\n";
										}
										else {
											exitFromConnet = 0;
										}
									}
								}
								else {
									exitFromConnet = 0;
								}
							}
							//выбор выхода другой фигуры
							if (indInNewFigure != -1) {
								exitFromConnet = 1;
								int ind = 0; //индекс выбранной фигуры
								int ind_prev = allFigure.size() - 2;
								std::cout << "Выберите фигуру с выходом которой соединить\t(W/D, Enter - выбрать, N - отмена)\nВыбираемая фигура подсвечивается другим цветом\n";
								while (exitFromConnet) {
									switch (char c = _getch())
									{
									case 'A':
									case 'ф':
									case 'Ф':
									case 'a': //Движение влево
									{
										ind_prev = ind;
										ind--;
										if (ind < 0) { ind = allFigure.size() - 2; ind_prev = 0; }
										else if (ind > allFigure.size() - 2) { ind = 0; ind_prev = allFigure.size() - 2; }
										allFigure[ind_prev]->setColor(RGB(0, 0, 0));
										allFigure[ind]->setColor(RGB(0, 255, 0));
										SendMessageW(hWnd, WM_PAINT, NULL, NULL);
										break;
									}
									case 'd':
									case 'D':
									case 'в':
									case 'В': //Движение вправо
									{
										ind_prev = ind;
										ind++;
										if (ind < 0) { ind = allFigure.size() - 2; ind_prev = 0; }
										else if (ind > allFigure.size() - 2) { ind = 0; ind_prev = allFigure.size() - 2; }
										allFigure[ind_prev]->setColor(RGB(0, 0, 0));
										allFigure[ind]->setColor(RGB(0, 255, 0));
										SendMessageW(hWnd, WM_PAINT, NULL, NULL);
										break;
									}
									case 13:
									{ //клавиша Enter
										int counterConncetIn = 0;
										for (int j = 0; j < allFigure[ind]->getOut() - 1; j++) {
											if (allFigure[allFigure.size() - 1]->getStatusOut(j)) counterConncetIn++;
										}
										if (counterConncetIn != allFigure[ind]->getOut()) {
											exitFromConnet = 0;
										}
										else {
											std::cout << "Все входы заняты.\nВыберите другую фигуру или отмените.\n";
										}
										break;
									}
									case 'n':
									case 'N':
									case 'т':
									case 'Т': //клавиша N
										allFigure[ind]->setColor(RGB(0, 0, 0));
										exitFromConnet = 0;
										exit = -1;
										break;
									}
								}
								if (exit != -1) {
									exitFromConnet = 1;
									int indOutFigure; //индекс выхода другой фигуры
									while (exitFromConnet) {
										std::cout << "Выберите выходы выбранной фигуры 0.." << allFigure[ind]->getOut() - 1 << std::endl;
										std::cout << "-1 для отмены\n";
										std::cin >> indOutFigure;
										if (indOutFigure != -1) {
											if (indOutFigure < 0 || indOutFigure > allFigure[ind]->getOut() - 1) {
												std::cout << "Некоректное значение!\n";
											}
											else {
												if (allFigure[ind]->getStatusOut(indOutFigure)) {
													//std::cout << "Выход " << indOutFigure << " занят, выберите другой\n";
													exitFromConnet = 0; // если надо чтобы выход был занят только одним входов, расскоментировать выше и закомментировать эту
												}
												else {
													exitFromConnet = 0;
												}
											}
										}
										else {
											exit = -1;
											exitFromConnet = 0;
										}
									}
									if (exit != -1) {
										allFigure[allFigure.size() - 1]->ConnectIn(allFigure[ind]->getCoordXOut(indOutFigure), allFigure[ind]->getCoordYOut(indOutFigure), indInNewFigure);
										allFigure[allFigure.size() - 1]->setStatusIn(indInNewFigure, 1);
										allFigure[allFigure.size() - 1]->setInBool(indInNewFigure, allFigure[ind]->getOutBool()[indOutFigure]);
										allFigure[ind]->setStatusOut(indOutFigure, 1);
										allFigure[ind]->setColor(RGB(0, 0, 0));
										SendMessageW(hWnd, WM_PAINT, NULL, NULL);
									}
									else {
										allFigure[ind]->setColor(RGB(0, 0, 0));
									}
								}
								else {
									allFigure[ind]->setColor(RGB(0, 0, 0));
								}

							}
						}
						else {
							std::cout << "Все входы заняты.\n";
						}
						break;
					}
					case 'n':
					case 'N':
					case 'т':
					case 'Т':
					{
						exitConnetinos = 0;
						break;
					}
					}
				}
		}
		}
	}
	SendMessageW(hWnd, WM_PAINT, NULL, NULL);
}

void EditAllFigure() {
	bool exitFromChoose = 1;
	int cancellation = 1;
	int ind = 0; //индекс выбранной фигуры
	int ind_prev = allFigure.size() -1;
	std::cout << "Выберите фигуру которую хотите редактировать\t(W/D, Enter - выбрать, N - отмена)\nВыбираемая фигура подсвечивается другим цветом\n";
	while (exitFromChoose) {
		switch (char c = _getch())
		{
		case 'A':
		case 'ф':
		case 'Ф':
		case 'a': //Движение влево
		{
			ind_prev = ind;
			ind--;
			if (ind < 0) { ind = allFigure.size() -1; ind_prev = 0; }
			else if (ind > allFigure.size() - 1 ) { ind = 0; ind_prev = allFigure.size() - 1; }
			allFigure[ind_prev]->setColor(RGB(0, 0, 0));
			allFigure[ind]->setColor(RGB(0, 255, 0));
			SendMessageW(hWnd, WM_PAINT, NULL, NULL);
			break;
		}
		case 'd':
		case 'D':
		case 'в':
		case 'В': //Движение вправо
		{
			ind_prev = ind;
			ind++;
			if (ind < 0) { ind = allFigure.size() - 1; ind_prev = 0; }
			else if (ind > allFigure.size() - 1) { ind = 0; ind_prev = allFigure.size() - 1; }
			allFigure[ind_prev]->setColor(RGB(0, 0, 0));
			allFigure[ind]->setColor(RGB(0, 255, 0));
			SendMessageW(hWnd, WM_PAINT, NULL, NULL);
			break;
		}
		case 13:
		{ //клавиша Enter
			exitFromChoose = 0;
			break;
		}
		case 'n':
		case 'N':
		case 'т':
		case 'Т': //клавиша N
			allFigure[ind]->setColor(RGB(0, 0, 0));
			exitFromChoose = 0;
			cancellation = -1;
			break;
		}
	}
	if (cancellation != -1) {
		exitFromChoose = 1;
		while (exitFromChoose) {
			std::cout << "Что сделать с этой фигурой?\n";
			std::cout << "1. Переместить\n2. Удалить\n3. Пересоединить входы\n4. Пересоеденить выходы\n0. Назад\n";
			switch (char choose = _getch()) {
			case '1': {
				bool exitMovement = 1;
				std::cout << "Пермещаем с помощью WASD, устанавливаем по нажатии Enter.\nОтмена - N.\n";
				while (exitMovement) {
					switch (char c = _getch())
					{
					case 'A':
					case 'ф':
					case 'Ф':
					case 'a': //Движение влево
					{
						MyRec.ind = ind;
						MyRec.key = c;
						MyCDS.cbData = sizeof(MyRec);  // size of data
						MyCDS.lpData = &MyRec;
						SendMessage(hWnd,
							WM_COPYDATA,
							(WPARAM)(HWND)hWnd,
							(LPARAM)(LPVOID)&MyCDS);
						SendMessageW(hWnd, WM_PAINT, NULL, NULL);
						
						break;
					}
					case 'd':
					case 'D':
					case 'в':
					case 'В': //Движение вправо
					{
						MyRec.ind = ind;
						MyRec.key = c;
						MyCDS.cbData = sizeof(MyRec);  // size of data
						MyCDS.lpData = &MyRec;
						SendMessage(hWnd,
							WM_COPYDATA,
							(WPARAM)(HWND)hWnd,
							(LPARAM)(LPVOID)&MyCDS);
						SendMessageW(hWnd, WM_PAINT, NULL, NULL);
						
						break;
					}
					case 'w':
					case 'W':
					case 'ц':
					case 'Ц': //Движение вверх
					{
						MyRec.ind = ind;
						MyRec.key = c;
						MyCDS.cbData = sizeof(MyRec);  // size of data
						MyCDS.lpData = &MyRec;
						SendMessage(hWnd,
							WM_COPYDATA,
							(WPARAM)(HWND)hWnd,
							(LPARAM)(LPVOID)&MyCDS);
						SendMessageW(hWnd, WM_PAINT, NULL, NULL);
						
						break;
					}
					case 'ы':
					case 'Ы':
					case 'S':
					case 's': //Движение внииз
					{
						MyRec.ind = ind;
						MyRec.key = c;
						MyCDS.cbData = sizeof(MyRec);  // size of data
						MyCDS.lpData = &MyRec;
						SendMessage(hWnd,
							WM_COPYDATA,
							(WPARAM)(HWND)hWnd,
							(LPARAM)(LPVOID)&MyCDS);
						SendMessageW(hWnd, WM_PAINT, NULL, NULL);
						
						break;
					}
					case 'n':
					case 'N':
					case 'т':
					case 'Т':
					{
						cancellation = -1;
						exitMovement = 0;
						break;
					}
					case 13:
						exitMovement = 0;
						break;
					}
				}
				break;
			}
			case '2': {
				for (int i = 0; i < allFigure[ind]->getIn(); i++) {
					if (allFigure[ind]->getStatusIn(i)) {
						for (int j = 0; j < allFigure.size(); j++) {
							for (int k = 0; k < allFigure[j]->getOut(); k++) {
								if (allFigure[ind]->getXCoordOutOther(i) != NULL && allFigure[ind]->getYCoordOutOther(i) != NULL) {
									if (*allFigure[ind]->getXCoordOutOther(i) == *allFigure[j]->getCoordXOut(k) &&
										*allFigure[ind]->getYCoordOutOther(i) == *allFigure[j]->getCoordYOut(k)) {
										allFigure[j]->setStatusOut(k, 0);
									}
								}
							}
						}
					}
				}
				for (int i = 0; i < allFigure[ind]->getOut(); i++) {
					if (allFigure[ind]->getStatusOut(i)) {
						for (int j = 0; j < allFigure.size(); j++) {
							for (int k = 0; k < allFigure[j]->getIn(); k++) {
								if (allFigure[j]->getXCoordOutOther(k) != NULL && allFigure[j]->getYCoordOutOther(k) != NULL) {
									if (*allFigure[ind]->getCoordXOut(i) == *allFigure[j]->getXCoordOutOther(k) &&
										*allFigure[ind]->getCoordYOut(i) == *allFigure[j]->getYCoordOutOther(k))
									{
										allFigure[j]->setInBool(k, 0);
										allFigure[j]->ConnectIn(NULL, NULL, k);
										allFigure[j]->setStatusIn(k, 0);
									}
								}
							}
						}
					}
				}
				allFigure.erase(allFigure.begin() + ind);
				cancellation = -1;
				exitFromChoose = 0;
				break;
			}
			case '3': {
				//to do пересоединение входов
				break;
			}
			case '4': {
				//to do пересоединение выходов
				break;
			}
			case '0': {
				allFigure[ind]->setColor(RGB(0, 0, 0));
				exitFromChoose = 0;
				break;
			}
			}
		}
	}
	SendMessageW(hWnd, WM_PAINT, NULL, NULL);
}


/**
 * \brief Точка входа
 * \param argc Кол-во аргументов на входе
 * \param argv Агрументы (массив C-строк)
 * \return Код выполнения
 */

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	try
	{

		// Получение хендла исполняемого модуля
		HINSTANCE hInst = GetModuleHandle(nullptr);

		std::thread* t = new std::thread(processing, hInst);
		


		bool mainexit = 1;
		while (mainexit) {
			char mainswitch;
			std::cout << "1. Добавить фигуру\n2. Переместиться\n3. Редактировать фигуру\n0. Выход\n";
			std::cin >> mainswitch;
			switch (mainswitch)
			{
			case '1': {
				bool enterExit = 1;
				while (enterExit) {
					std::cout << "1. Конъюнкция\n2. Дизъюнкция\n3. Входная переменная\n4. Отрицание\n5. Эквивалентность\n6. Искл.ИЛИ\n7. Импликация\n0. Назад\n";
					char enterSwitch;
					std::cin >> enterSwitch;
					switch (enterSwitch)
					{
					case '1': {
						allFigure.push_back(new Conjunction(320,480));
						EnterNewFigure();
						break;
					}
					case '2': {
						allFigure.push_back(new Disjunction(320, 480));
						EnterNewFigure();
						break;
					}
					case '3': {
						std::string name;
						std::cout << "Введите имя входной переменной\t";
						std::cin >> name;
						allFigure.push_back(new Constant(320, 480, name));
						EnterNewFigure();
						break;
					}
					case '4': {
						allFigure.push_back(new Denial(320, 480));
						EnterNewFigure();
						break;
					}
					case '5': {
						allFigure.push_back(new Equivalence(320, 480));
						EnterNewFigure();
						break;
					}
					case '6': {
						allFigure.push_back(new Nonequivalence(320, 480));
						EnterNewFigure();
						break;
					}
					case '7': {
						allFigure.push_back(new Implication(320, 480));
						EnterNewFigure();
						break;
					}
					case '0': {
						
						enterExit = 0;
						break;
					}
					default:
						break;
					}
				}
				break;
			}
			case '2': {
				std::cout << "Пермещаем с помощью WASD, устанавливаем по нажатии Enter\n";
				bool exitMovement = 1;
				while (exitMovement) {
					switch (char c = _getch())
					{
					case 'A':
					case 'ф':
					case 'Ф':
					case 'a': //Движение влево
					{
						SendMessageW(hWnd, MY_KEYDOWN, LEFTT, NULL);
						break;
					}
					case 'd':
					case 'D':
					case 'в':
					case 'В': //Движение вправо
					{
						SendMessageW(hWnd, MY_KEYDOWN, RIGHTT, NULL);
						break;
					}
					case 'w':
					case 'W':
					case 'ц':
					case 'Ц': //Движение вверх
					{
						SendMessageW(hWnd, MY_KEYDOWN, UPP, NULL);
						break;
					}
					case 'ы':
					case 'Ы':
					case 'S':
					case 's': //Движение внииз
					{
						SendMessageW(hWnd, MY_KEYDOWN, DOWNN, NULL);
						break;
					}
					case 13:
						exitMovement = 0;
						break;
					}
				}
				break;
			}
			case '3':{
				EditAllFigure();
				break;
			}
			case '0':
			{
				//to do выход
				t->detach();
				mainexit = 0;
				break;
			}
			default:
				break;
			}
		}

	}
	catch (std::exception const& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}


//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
	case MY_KEYDOWN: {
		switch (wParam) {
		case VK_LEFT: {  /* Обрабатывает клавишу LEFT ARROW (Стрелка влево). */
			allFigure[allFigure.size() - 1]->setX(allFigure[allFigure.size() - 1]->getX() - 5);
			break;
		}
		case VK_RIGHT: {/* Обрабатывает клавишу RIGHT ARROW (Стрелка вправо). */
			allFigure[allFigure.size() - 1]->setX(allFigure[allFigure.size() - 1]->getX() + 5);
			break;
		}
		case VK_UP: {/* Обрабатывает клавишу UP ARROW (Стрелка вверх). */
			allFigure[allFigure.size() - 1]->setY(allFigure[allFigure.size() - 1]->getY() - 5);
			break;
		}
		case VK_DOWN: {/* Обрабатывает клавишу DOWN ARROW (Стрелка вниз). */
			allFigure[allFigure.size() - 1]->setY(allFigure[allFigure.size() - 1]->getY() + 5);
			break;
		}
		case LEFTT: {  /* Обрабатывает клавишу LEFT ARROW (Стрелка влево). */
			for (int i = 0; i < allFigure.size(); i++) {
				allFigure[i]->setX(allFigure[i]->getX() - 15);
			}

			break;
		}
		case RIGHTT: {  /* Обрабатывает клавишу LEFT ARROW (Стрелка влево). */
			for (int i = 0; i < allFigure.size(); i++) {
				allFigure[i]->setX(allFigure[i]->getX() + 15);
			}

			break;
		}
		case UPP: {  /* Обрабатывает клавишу LEFT ARROW (Стрелка влево). */
			for (int i = 0; i < allFigure.size(); i++) {
				allFigure[i]->setY(allFigure[i]->getY() - 15);
			}

			break;
		}
		case DOWNN: {  /* Обрабатывает клавишу LEFT ARROW (Стрелка влево). */
			for (int i = 0; i < allFigure.size(); i++) {
				allFigure[i]->setY(allFigure[i]->getY() + 15);
			}

			break;
		}
		default:
			break; /* Обрабатывает другие не символьные нажатия клавиш. */
		}
	}
    case WM_PAINT:
    {
		//to do номера входов и вызодов
		InvalidateRect(hWnd, NULL, TRUE);
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
		if (allFigure.size() != 0) {
			for (int i = 0; i < allFigure.size(); i++) {
				if (allFigure[i]->getName() =="~") {
					SelectObject(hdc, CreateSolidBrush(allFigure[i]->getColor()));
					SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
					Ellipse(hdc, allFigure[i]->getX() - allFigure[i]->getXmax(),
						allFigure[i]->getY() - allFigure[i]->getYmax(),
						allFigure[i]->getX() + allFigure[i]->getXmax(),
						allFigure[i]->getY() + allFigure[i]->getYmax());
				}
				else {
					SelectObject(hdc, CreatePen(PS_SOLID, 1, allFigure[i]->getColor()));
					SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
					Rectangle(hdc, allFigure[i]->getX() - allFigure[i]->getXmax(),
						allFigure[i]->getY() - allFigure[i]->getYmax(),
						allFigure[i]->getX() + allFigure[i]->getXmax(),
						allFigure[i]->getY() + allFigure[i]->getYmax());
					
				}
				TextOutW(hdc, allFigure[i]->getX()-10, allFigure[i]->getY()-10,
					LPCWSTR(allFigure[i]->getName().c_str()), allFigure[i]->getName().length());
				//Участок отрисовки входов и выходов
				int deltY;
				if (allFigure[i]->getIn() != 0) {
					 deltY = allFigure[i]->getYmax() / allFigure[i]->getIn();
				}
				else {
					deltY = allFigure[i]->getYmax();
				}
				int prevY = deltY;
				int k = 1;
				int cnt = 0;
				k = allFigure[i]->getIn() % 2 == 0 ? 1 : 0;
				cnt = 0;
				for (int j = 0; j < allFigure[i]->getIn(); j++) {
					int x0 = allFigure[i]->getX() - allFigure[i]->getXmax();
					int y0 = allFigure[i]->getY() + k * prevY;
					int x = allFigure[i]->getX() - allFigure[i]->getXmax() - 30;
					int y = allFigure[i]->getY() + k * prevY;
					MoveToEx(hdc, x0, y0, NULL);
					allFigure[i]->setCoordIn(x, y, j);
					LineTo(hdc, x, y);
					TextOutW(hdc, 
						x+10, 
						y - 20,
						LPCWSTR(std::to_string(allFigure[i]->getInBool()[j]).c_str()),
						std::to_string(allFigure[i]->getInBool()[j]).length());
					k = k == 1 ? -1 : 1;
					cnt++;
					if (allFigure[i]->getIn() % 2 == 0 && cnt == 2) {
						cnt = 0;
						prevY += 1.5 * deltY;
					}

				}
				deltY= allFigure[i]->getYmax() / allFigure[i]->getOut();
				prevY = deltY;
				cnt = 0;
				k = allFigure[i]->getOut() % 2 == 0 ? 1 : 0;
				for (int j = 0; j < allFigure[i]->getOut(); j++) {
					int x0 = allFigure[i]->getX() + allFigure[i]->getXmax();
					int y0 = allFigure[i]->getY() + k * prevY;
					int x = allFigure[i]->getX() + allFigure[i]->getXmax() + 30;
					int y = allFigure[i]->getY() + k * prevY;
					MoveToEx(hdc, x0, y0, NULL);
					allFigure[i]->setCoordOut(x, y, j);
					LineTo(hdc, x, y);
					TextOutW(hdc, x-10, y - 20, 
								LPCWSTR(std::to_string(allFigure[i]->getOutBool()[j]).c_str()), std::to_string(allFigure[i]->getOutBool()[j]).length());
					k = k == 1 ? -1 : 1;
					cnt++;
					prevY = round(cnt / 2.0) * 1.5 * deltY;


				}
				//конец участка отрисовк и входов и выходов
				//участок отрисовки соединений
				for (int j = 0; j < allFigure[i]->getIn(); j++) {
					if (allFigure[i]->getStatusIn(j)) {
						int x = allFigure[i]->getCoordXIn(j);
						int y = allFigure[i]->getCoordYIn(j);
						int* x0 = allFigure[i]->getXCoordOutOther(j);
						int* y0 = allFigure[i]->getYCoordOutOther(j);
						if (*y0 != y) {
							int midleX = (x + *x0) / 2;
							
							MoveToEx(hdc, *x0, *y0, NULL);
							LineTo(hdc, midleX, *y0);
							MoveToEx(hdc, midleX, *y0, NULL);
							LineTo(hdc, midleX, y);
							MoveToEx(hdc, midleX, y, NULL);
							LineTo(hdc, x, y);
						}
						else {
							MoveToEx(hdc, *x0, *y0, NULL);
							LineTo(hdc, x, y);
						}
					}
				}
			}
		}
		
        EndPaint(hWnd, &ps);
		return 0;
		break;
		//InvalidateRect(hWnd, NULL, true);
    }
	case WM_COPYDATA: {
		pMyCDS = (PCOPYDATASTRUCT)lParam;
		switch (((MYREC*)(pMyCDS->lpData))->key)
		{
		case 'A':
		case 'ф':
		case 'Ф':
		case 'a': //Движение влево
		{
			allFigure[((MYREC*)(pMyCDS->lpData))->ind]->setX(allFigure[((MYREC*)(pMyCDS->lpData))->ind]->getX() - 5);
			break;
		}
		case 'd':
		case 'D':
		case 'в':
		case 'В': //Движение вправо
		{
			allFigure[((MYREC*)(pMyCDS->lpData))->ind]->setX(allFigure[((MYREC*)(pMyCDS->lpData))->ind]->getX() + 5);
			break;
		}
		case 'w':
		case 'W':
		case 'ц':
		case 'Ц': //Движение вверх
		{
			allFigure[((MYREC*)(pMyCDS->lpData))->ind]->setY(allFigure[((MYREC*)(pMyCDS->lpData))->ind]->getY() - 5);
			break;
		}
		case 'ы':
		case 'Ы':
		case 'S':
		case 's': //Движение внииз
		{
			allFigure[((MYREC*)(pMyCDS->lpData))->ind]->setY(allFigure[((MYREC*)(pMyCDS->lpData))->ind]->getY() + 5);
			break;
		}
		}
		break;
	}
    case WM_DESTROY:

        PostQuitMessage(0);

        break;
    default: {
        return DefWindowProc(hWnd, message, wParam, lParam);

    }
    }
    return 0;
}