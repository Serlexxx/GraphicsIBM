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
// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING] = L"IBM";;                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING] = L"IBM";            // ��� ������ �������� ����

std::vector<Figure*> allFigure;

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE);
/**
 * \brief ������� ��������� (����������)
 * \param hWnd ����� ����
 * \param message ������������� ���������
 * \param wParam �������� ���������
 * \param lParam �������� ���������
 * \return ��� ����������
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//
//  �������: MyRegisterClass()
//
//  ����: ������������ ����� ����.
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
//   �������: InitInstance(HINSTANCE, int)
//
//   ����: ��������� ������ ���������� � ������� ������� ����
//
//   �����������:
//
//        � ���� ������� ������ ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance)
{
	hInst = hInstance; // ��������� ������ ���������� � ���������� ����������

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

	// ��������� ������������� ����������:
	if (!InitInstance(hInst))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_MY));

	MSG msg;


	// ���� ��������� ���������:
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
	std::cout << "��������� � ������� WASD, ������������� �� ������� Enter.\n������ ������������ N.\n";
	bool exitMovement = 1;
	int cancellation = 1;
	while (exitMovement) {
		switch (char c = _getch())
		{
		case 'A':
		case '�':
		case '�':
		case 'a': //�������� �����
		{
			SendMessageW(hWnd, MY_KEYDOWN, VK_LEFT, NULL);
			break;
		}
		case 'd':
		case 'D':
		case '�':
		case '�': //�������� ������
		{
			SendMessageW(hWnd, MY_KEYDOWN, VK_RIGHT, NULL);
			break;
		}
		case 'w':
		case 'W':
		case '�':
		case '�': //�������� �����
		{
			SendMessageW(hWnd, MY_KEYDOWN, VK_UP, NULL);
			break;
		}
		case '�':
		case '�':
		case 'S':
		case 's': //�������� �����
		{
			SendMessageW(hWnd, MY_KEYDOWN, VK_DOWN, NULL);
			break;
		}
		case 'n':
		case 'N':
		case '�':
		case '�':
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
					std::cout << "��������� ����� 0.." << allFigure[allFigure.size() - 1]->getIn() - 1 << "? (Y/N)\n";
					switch (char c = _getch())
					{
					case 'y':
					case 'Y':
					case '�':
					case '�':
					{
						int counterConncetIn = 0;
						for (int j = 0; j < allFigure[allFigure.size() - 1]->getIn(); j++) {
							if (allFigure[allFigure.size() - 1]->getStatusIn(j)) counterConncetIn++;
						}
						if (counterConncetIn != allFigure[allFigure.size() - 1]->getIn()) { //�������� �� ������������� ���� �������
							int indInNewFigure; //������ �����
							bool exitFromConnet = 1;
							int exit = 1;
							//����� ������� ����� ����� ����� ������
							while (exitFromConnet) {
								std::cout << "�������� ����� 0.." << allFigure[allFigure.size() - 1]->getIn() - 1 << std::endl;
								std::cout << "-1 ��� ������\n";
								std::cin >> indInNewFigure;
								if (indInNewFigure != -1) {
									if (indInNewFigure < 0 || indInNewFigure > allFigure[allFigure.size() - 1]->getIn() - 1) {
										std::cout << "����������� ��������!\n";
									}
									else {
										if (allFigure[allFigure.size() - 1]->getStatusIn(indInNewFigure)) {
											std::cout << "���� " << indInNewFigure << " �����, �������� ������\n";
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
							//����� ������ ������ ������
							if (indInNewFigure != -1) {
								exitFromConnet = 1;
								int ind = 0; //������ ��������� ������
								int ind_prev = allFigure.size() - 2;
								std::cout << "�������� ������ � ������� ������� ���������\t(W/D, Enter - �������, N - ������)\n���������� ������ �������������� ������ ������\n";
								while (exitFromConnet) {
									switch (char c = _getch())
									{
									case 'A':
									case '�':
									case '�':
									case 'a': //�������� �����
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
									case '�':
									case '�': //�������� ������
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
									{ //������� Enter
										int counterConncetIn = 0;
										for (int j = 0; j < allFigure[ind]->getOut() - 1; j++) {
											if (allFigure[allFigure.size() - 1]->getStatusOut(j)) counterConncetIn++;
										}
										if (counterConncetIn != allFigure[ind]->getOut()) {
											exitFromConnet = 0;
										}
										else {
											std::cout << "��� ����� ������.\n�������� ������ ������ ��� ��������.\n";
										}
										break;
									}
									case 'n':
									case 'N':
									case '�':
									case '�': //������� N
										allFigure[ind]->setColor(RGB(0, 0, 0));
										exitFromConnet = 0;
										exit = -1;
										break;
									}
								}
								if (exit != -1) {
									exitFromConnet = 1;
									int indOutFigure; //������ ������ ������ ������
									while (exitFromConnet) {
										std::cout << "�������� ������ ��������� ������ 0.." << allFigure[ind]->getOut() - 1 << std::endl;
										std::cout << "-1 ��� ������\n";
										std::cin >> indOutFigure;
										if (indOutFigure != -1) {
											if (indOutFigure < 0 || indOutFigure > allFigure[ind]->getOut() - 1) {
												std::cout << "����������� ��������!\n";
											}
											else {
												if (allFigure[ind]->getStatusOut(indOutFigure)) {
													//std::cout << "����� " << indOutFigure << " �����, �������� ������\n";
													exitFromConnet = 0; // ���� ���� ����� ����� ��� ����� ������ ����� ������, ����������������� ���� � ���������������� ���
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
							std::cout << "��� ����� ������.\n";
						}
						break;
					}
					case 'n':
					case 'N':
					case '�':
					case '�':
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
	int ind = 0; //������ ��������� ������
	int ind_prev = allFigure.size() -1;
	std::cout << "�������� ������ ������� ������ �������������\t(W/D, Enter - �������, N - ������)\n���������� ������ �������������� ������ ������\n";
	while (exitFromChoose) {
		switch (char c = _getch())
		{
		case 'A':
		case '�':
		case '�':
		case 'a': //�������� �����
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
		case '�':
		case '�': //�������� ������
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
		{ //������� Enter
			exitFromChoose = 0;
			break;
		}
		case 'n':
		case 'N':
		case '�':
		case '�': //������� N
			allFigure[ind]->setColor(RGB(0, 0, 0));
			exitFromChoose = 0;
			cancellation = -1;
			break;
		}
	}
	if (cancellation != -1) {
		exitFromChoose = 1;
		while (exitFromChoose) {
			std::cout << "��� ������� � ���� �������?\n";
			std::cout << "1. �����������\n2. �������\n3. ������������� �����\n4. ������������� ������\n0. �����\n";
			switch (char choose = _getch()) {
			case '1': {
				bool exitMovement = 1;
				std::cout << "��������� � ������� WASD, ������������� �� ������� Enter.\n������ - N.\n";
				while (exitMovement) {
					switch (char c = _getch())
					{
					case 'A':
					case '�':
					case '�':
					case 'a': //�������� �����
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
					case '�':
					case '�': //�������� ������
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
					case '�':
					case '�': //�������� �����
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
					case '�':
					case '�':
					case 'S':
					case 's': //�������� �����
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
					case '�':
					case '�':
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
				//to do �������������� ������
				break;
			}
			case '4': {
				//to do �������������� �������
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
 * \brief ����� �����
 * \param argc ���-�� ���������� �� �����
 * \param argv ��������� (������ C-�����)
 * \return ��� ����������
 */

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	try
	{

		// ��������� ������ ������������ ������
		HINSTANCE hInst = GetModuleHandle(nullptr);

		std::thread* t = new std::thread(processing, hInst);
		


		bool mainexit = 1;
		while (mainexit) {
			char mainswitch;
			std::cout << "1. �������� ������\n2. �������������\n3. ������������� ������\n0. �����\n";
			std::cin >> mainswitch;
			switch (mainswitch)
			{
			case '1': {
				bool enterExit = 1;
				while (enterExit) {
					std::cout << "1. ����������\n2. ����������\n3. ������� ����������\n4. ���������\n5. ���������������\n6. ����.���\n7. ����������\n0. �����\n";
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
						std::cout << "������� ��� ������� ����������\t";
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
				std::cout << "��������� � ������� WASD, ������������� �� ������� Enter\n";
				bool exitMovement = 1;
				while (exitMovement) {
					switch (char c = _getch())
					{
					case 'A':
					case '�':
					case '�':
					case 'a': //�������� �����
					{
						SendMessageW(hWnd, MY_KEYDOWN, LEFTT, NULL);
						break;
					}
					case 'd':
					case 'D':
					case '�':
					case '�': //�������� ������
					{
						SendMessageW(hWnd, MY_KEYDOWN, RIGHTT, NULL);
						break;
					}
					case 'w':
					case 'W':
					case '�':
					case '�': //�������� �����
					{
						SendMessageW(hWnd, MY_KEYDOWN, UPP, NULL);
						break;
					}
					case '�':
					case '�':
					case 'S':
					case 's': //�������� �����
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
				//to do �����
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
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: ������������ ��������� � ������� ����.
//
//  WM_COMMAND  - ���������� ���� ����������
//  WM_PAINT    - ��������� �������� ����
//  WM_DESTROY  - ��������� ��������� � ������ � ���������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
	case MY_KEYDOWN: {
		switch (wParam) {
		case VK_LEFT: {  /* ������������ ������� LEFT ARROW (������� �����). */
			allFigure[allFigure.size() - 1]->setX(allFigure[allFigure.size() - 1]->getX() - 5);
			break;
		}
		case VK_RIGHT: {/* ������������ ������� RIGHT ARROW (������� ������). */
			allFigure[allFigure.size() - 1]->setX(allFigure[allFigure.size() - 1]->getX() + 5);
			break;
		}
		case VK_UP: {/* ������������ ������� UP ARROW (������� �����). */
			allFigure[allFigure.size() - 1]->setY(allFigure[allFigure.size() - 1]->getY() - 5);
			break;
		}
		case VK_DOWN: {/* ������������ ������� DOWN ARROW (������� ����). */
			allFigure[allFigure.size() - 1]->setY(allFigure[allFigure.size() - 1]->getY() + 5);
			break;
		}
		case LEFTT: {  /* ������������ ������� LEFT ARROW (������� �����). */
			for (int i = 0; i < allFigure.size(); i++) {
				allFigure[i]->setX(allFigure[i]->getX() - 15);
			}

			break;
		}
		case RIGHTT: {  /* ������������ ������� LEFT ARROW (������� �����). */
			for (int i = 0; i < allFigure.size(); i++) {
				allFigure[i]->setX(allFigure[i]->getX() + 15);
			}

			break;
		}
		case UPP: {  /* ������������ ������� LEFT ARROW (������� �����). */
			for (int i = 0; i < allFigure.size(); i++) {
				allFigure[i]->setY(allFigure[i]->getY() - 15);
			}

			break;
		}
		case DOWNN: {  /* ������������ ������� LEFT ARROW (������� �����). */
			for (int i = 0; i < allFigure.size(); i++) {
				allFigure[i]->setY(allFigure[i]->getY() + 15);
			}

			break;
		}
		default:
			break; /* ������������ ������ �� ���������� ������� ������. */
		}
	}
    case WM_PAINT:
    {
		//to do ������ ������ � �������
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
				//������� ��������� ������ � �������
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
				//����� ������� �������� � ������ � �������
				//������� ��������� ����������
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
		case '�':
		case '�':
		case 'a': //�������� �����
		{
			allFigure[((MYREC*)(pMyCDS->lpData))->ind]->setX(allFigure[((MYREC*)(pMyCDS->lpData))->ind]->getX() - 5);
			break;
		}
		case 'd':
		case 'D':
		case '�':
		case '�': //�������� ������
		{
			allFigure[((MYREC*)(pMyCDS->lpData))->ind]->setX(allFigure[((MYREC*)(pMyCDS->lpData))->ind]->getX() + 5);
			break;
		}
		case 'w':
		case 'W':
		case '�':
		case '�': //�������� �����
		{
			allFigure[((MYREC*)(pMyCDS->lpData))->ind]->setY(allFigure[((MYREC*)(pMyCDS->lpData))->ind]->getY() - 5);
			break;
		}
		case '�':
		case '�':
		case 'S':
		case 's': //�������� �����
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