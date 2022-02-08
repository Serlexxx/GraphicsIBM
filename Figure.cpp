#include "Figure.h"


Figure::Figure()
{
	x = 0;
	y = 0;
	colorFig = (0, 0, 0);
}

Figure::~Figure()
{
	delete �ontact_status.In;
	delete �ontact_status.Out;
	delete �ontact_status.xIn;
	delete �ontact_status.yIn;
	delete �ontact_status.yOut;
	delete �ontact_status.xOut;
	delete �ontact_status.xOutOtherFigure;
	delete �ontact_status.yOutOtherFigure;
}

int Figure::getX() {
	return x;
}

int Figure::getY() {
	return y;
}

void Figure::setX(int x) {
	this->x = x;
}

void Figure::setY(int y) {
	this->y = y;
}

int Figure::getIn() {
	return cnt_in;
}

int Figure::getOut() {
	return cnt_out;
}

void Figure::setIn(int in) {
	�ontact_status.In = new bool [in];
	�ontact_status.xOutOtherFigure = new int*[in];
	�ontact_status.yOutOtherFigure = new int*[in];
	�ontact_status.xIn = new int[in];
	�ontact_status.yIn = new int[in];
	for (int i = 0; i < in; i++) {
		�ontact_status.In[i] = 0;
	}
	cnt_in = in;
}

void Figure::setOut(int out) {
	�ontact_status.Out = new bool[out];
	�ontact_status.xOut = new int[out];
	�ontact_status.yOut = new int[out];
	for (int i = 0; i < out; i++) {
		�ontact_status.Out[i] = 0;
	}
	cnt_out = out;
}

void Figure::setColor(COLORREF colors) {
	this->colorFig = colors;
}

COLORREF Figure::getColor() {
	return this->colorFig;
}

void Figure::setCoordIn(int x, int y, int ind) {
	�ontact_status.xIn[ind] = x;
	�ontact_status.yIn[ind] = y;
}
void Figure::setCoordOut(int x, int y, int ind) {
	�ontact_status.xOut[ind] = x;
	�ontact_status.yOut[ind] = y;
}
int Figure::getCoordXIn(int ind) {
	return �ontact_status.xIn[ind];
}
int* Figure::getCoordXOut(int ind) {
	return &�ontact_status.xOut[ind];
}
int Figure::getCoordYIn(int ind) {
	return �ontact_status.yIn[ind];
}
int* Figure::getCoordYOut(int ind) {
	return &�ontact_status.yOut[ind];
}

bool Figure::getStatusOut(int ind) {
	return �ontact_status.Out[ind];
}
bool Figure::getStatusIn(int ind) {
	return �ontact_status.In[ind];
}

void Figure::setStatusIn(int ind, bool connect) {
	�ontact_status.In[ind] = connect;
}
void Figure::setStatusOut(int ind, bool connect) {
	�ontact_status.Out[ind] = connect;
}
void Figure::ConnectIn(int* x, int* y, int ind) {
	�ontact_status.xOutOtherFigure[ind] = x;
	�ontact_status.yOutOtherFigure[ind] = y;
}

int* Figure::getXCoordOutOther(int ind) {
	return �ontact_status.xOutOtherFigure[ind];
}
int* Figure::getYCoordOutOther(int ind) {
	return �ontact_status.yOutOtherFigure[ind];
}

void Figure::setName(std::string name) {
	this->name = name;
}

std::string Figure::getName() {
	return name;
}