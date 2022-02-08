#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <cmath>
#include <Windows.h>
class Figure //to do �������� � ����������, �����������������
{
public:
	Figure();
	virtual ~Figure();
	int getX(); // �������� x - ������ ������
	int getY();  // �������� y - ������ ������
	void setX(int x);// ��������� x - ������ ������
	void setY(int y);// ��������� y - ������ ������

	int getIn(); //�������� ���-�� ������
	int getOut(); //�������� ���-�� �������
	void setIn(int in); //���������� ���-�� ������
	void setOut(int out); //���������� ���-�� �������

	void setCoordIn(int x, int y, int ind); //���������� ���������� X Y ����� � �������� ind
	void setCoordOut(int x, int y, int ind); //��������� ���������� X Y ������ � �������� ind

	int getCoordXIn(int ind); //�������� ���������� � ����� � �������� ind 
	int getCoordYIn(int ind); //�������� ���������� Y ����� � �������� ind

	int* getCoordXOut(int ind); //�������� ���������� X ������ � �������� ind
	int* getCoordYOut(int ind); //�������� ���������� Y ������ � �������� ind

 	bool getStatusOut(int ind); 
	bool getStatusIn(int ind);
	void setStatusIn(int ind, bool connect);
	void setStatusOut(int ind, bool connect);

	void setName(std::string name);
	std::string getName();

	void ConnectIn(int* x, int* y, int ind); // x � y - ���������� ������ ������ ������, ������� �������� ��� ������� ����� ����� ������

	int* getXCoordOutOther(int ind);
	int* getYCoordOutOther(int ind);

	COLORREF getColor();
	void setColor(COLORREF colors);

	virtual int getYmax() = 0;
	virtual int getXmax() = 0;
	virtual bool* getOutBool() = 0; //�������� �������� �������� � ������
	virtual bool* getInBool() = 0; //�������� ������� �������� ������
	virtual void setInBool(int ind, bool out) = 0;
	virtual void Function() = 0; //������� ������
	
private:
	std::string name;
	Figure* all;
	COLORREF colorFig;
	int x, y; //����� ���������� �������� ��� ������
	int cnt_in, cnt_out; //���-�� ������ � ������� � ������
	struct �ontact_status
	{
		int** xOutOtherFigure, **yOutOtherFigure;
		int* xIn, *xOut;
		int* yIn, *yOut;
		bool* In; //������ ����������� 1 - ���������/0 - �� ���������
		bool* Out; // ������ ����������� 1 - ��������� / 0 - �� ���������
	}�ontact_status;
};

