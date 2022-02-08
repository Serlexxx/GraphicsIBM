#include "Figure.h"


Figure::Figure()
{
	x = 0;
	y = 0;
	colorFig = (0, 0, 0);
}

Figure::~Figure()
{
	delete ñontact_status.In;
	delete ñontact_status.Out;
	delete ñontact_status.xIn;
	delete ñontact_status.yIn;
	delete ñontact_status.yOut;
	delete ñontact_status.xOut;
	delete ñontact_status.xOutOtherFigure;
	delete ñontact_status.yOutOtherFigure;
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
	ñontact_status.In = new bool [in];
	ñontact_status.xOutOtherFigure = new int*[in];
	ñontact_status.yOutOtherFigure = new int*[in];
	ñontact_status.xIn = new int[in];
	ñontact_status.yIn = new int[in];
	for (int i = 0; i < in; i++) {
		ñontact_status.In[i] = 0;
	}
	cnt_in = in;
}

void Figure::setOut(int out) {
	ñontact_status.Out = new bool[out];
	ñontact_status.xOut = new int[out];
	ñontact_status.yOut = new int[out];
	for (int i = 0; i < out; i++) {
		ñontact_status.Out[i] = 0;
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
	ñontact_status.xIn[ind] = x;
	ñontact_status.yIn[ind] = y;
}
void Figure::setCoordOut(int x, int y, int ind) {
	ñontact_status.xOut[ind] = x;
	ñontact_status.yOut[ind] = y;
}
int Figure::getCoordXIn(int ind) {
	return ñontact_status.xIn[ind];
}
int* Figure::getCoordXOut(int ind) {
	return &ñontact_status.xOut[ind];
}
int Figure::getCoordYIn(int ind) {
	return ñontact_status.yIn[ind];
}
int* Figure::getCoordYOut(int ind) {
	return &ñontact_status.yOut[ind];
}

bool Figure::getStatusOut(int ind) {
	return ñontact_status.Out[ind];
}
bool Figure::getStatusIn(int ind) {
	return ñontact_status.In[ind];
}

void Figure::setStatusIn(int ind, bool connect) {
	ñontact_status.In[ind] = connect;
}
void Figure::setStatusOut(int ind, bool connect) {
	ñontact_status.Out[ind] = connect;
}
void Figure::ConnectIn(int* x, int* y, int ind) {
	ñontact_status.xOutOtherFigure[ind] = x;
	ñontact_status.yOutOtherFigure[ind] = y;
}

int* Figure::getXCoordOutOther(int ind) {
	return ñontact_status.xOutOtherFigure[ind];
}
int* Figure::getYCoordOutOther(int ind) {
	return ñontact_status.yOutOtherFigure[ind];
}

void Figure::setName(std::string name) {
	this->name = name;
}

std::string Figure::getName() {
	return name;
}