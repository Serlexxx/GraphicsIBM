#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <cmath>
#include <Windows.h>
class Figure //to do шифратор и дешифратор, мультикомлплексор
{
public:
	Figure();
	virtual ~Figure();
	int getX(); // получить x - центра фигуры
	int getY();  // получить y - центра фигуры
	void setX(int x);// установка x - центра фигуры
	void setY(int y);// установка y - центра фигуры

	int getIn(); //получить кол-во входов
	int getOut(); //получить кол-во выходов
	void setIn(int in); //установить кол-во входов
	void setOut(int out); //установить кол-во выходов

	void setCoordIn(int x, int y, int ind); //установить координаты X Y входа с индексом ind
	void setCoordOut(int x, int y, int ind); //установть координаты X Y выхода с индексом ind

	int getCoordXIn(int ind); //получить координату Х входа с индексом ind 
	int getCoordYIn(int ind); //получить координату Y входа с индексом ind

	int* getCoordXOut(int ind); //получить координату X выхода с индексом ind
	int* getCoordYOut(int ind); //получить координату Y выхода с индексом ind

 	bool getStatusOut(int ind); 
	bool getStatusIn(int ind);
	void setStatusIn(int ind, bool connect);
	void setStatusOut(int ind, bool connect);

	void setName(std::string name);
	std::string getName();

	void ConnectIn(int* x, int* y, int ind); // x и y - координаты выхода другой фигуры, которые хранятся под индексу входа нашей фигуры

	int* getXCoordOutOther(int ind);
	int* getYCoordOutOther(int ind);

	COLORREF getColor();
	void setColor(COLORREF colors);

	virtual int getYmax() = 0;
	virtual int getXmax() = 0;
	virtual bool* getOutBool() = 0; //получить выходное значение с фигуры
	virtual bool* getInBool() = 0; //получить входное значение фигуры
	virtual void setInBool(int ind, bool out) = 0;
	virtual void Function() = 0; //функция фигуры
	
private:
	std::string name;
	Figure* all;
	COLORREF colorFig;
	int x, y; //центр логической операции или фигуры
	int cnt_in, cnt_out; //кол-во входов и выходов в фигуре
	struct Сontact_status
	{
		int** xOutOtherFigure, **yOutOtherFigure;
		int* xIn, *xOut;
		int* yIn, *yOut;
		bool* In; //статус подключения 1 - подключен/0 - не подключен
		bool* Out; // статус подключения 1 - подключен / 0 - не подключен
	}сontact_status;
};

