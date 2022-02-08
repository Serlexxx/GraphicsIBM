#include "Binary_Operations.h"

/******************Conjunction*****************************/
Conjunction::Conjunction(int x, int y) {
	this->setName(name);
	this->setX(x);
	this->setY(y);
	this->setOut(1);
	this->setIn(2);
}

Conjunction::~Conjunction() {

}

int Conjunction::getXmax() {
	return x_max;
}

int Conjunction::getYmax() {
	return y_max;
}

bool*Conjunction::getOutBool() {
	this->Function();
	return Out;
}

bool* Conjunction::getInBool() {
	return In;
}

void Conjunction::Function() {
	Out[0] = In[0] && In[1];
}

void Conjunction::setInBool(int ind, bool out) {
	In[ind] = out;
}

/********************Denial**************************/

Denial::Denial(int x, int y) {
	this->setName(name);
	this->setX(x);
	this->setY(y);
	this->setOut(out);
	this->setIn(in);
}

Denial::~Denial() {

}

int Denial::getXmax() {
	return rad;
}

int Denial::getYmax() {
	return rad;
}

bool* Denial::getOutBool() {
	this->Function();
	return Out;
}

bool* Denial::getInBool() {
	return In;
}

void Denial::Function() {
	Out[0] = !In[0];
}

void Denial::setInBool(int ind, bool out) {
	In[ind] = out;
}

/******************Constant**************************/

Constant::Constant(int x, int y, std::string name) {
	this->setName(name);
	this->setX(x);
	this->setY(y);
	this->setOut(out);
	this->setIn(in);
}

Constant::~Constant() {

}

int Constant::getXmax() {
	return x_max;
}

int Constant::getYmax() {
	return y_max;
}

bool* Constant::getOutBool() {
	return Out;
}

bool* Constant::getInBool() {
	return nullptr;
}

void Constant::Function() {
	
}

void Constant::setInBool(int ind, bool out) {

}

/*******************Disjunction***************************/

Disjunction::Disjunction(int x, int y) {
	this->setName(name);
	this->setX(x);
	this->setY(y);
	this->setOut(1);
	this->setIn(2);
}

Disjunction::~Disjunction() {

}

int Disjunction::getXmax() {
	return x_max;
}

int Disjunction::getYmax() {
	return y_max;
}

bool* Disjunction::getOutBool() {
	this->Function();
	return Out;
}

bool* Disjunction::getInBool() {
	return In;
}

void Disjunction::Function() {
	Out[0] = In[0] || In[1];
}

void Disjunction::setInBool(int ind, bool out) {
	In[ind] = out;
}


/*******************Equivalence***********************/

Equivalence::Equivalence(int x, int y) {
	this->setName(name);
	this->setX(x);
	this->setY(y);
	this->setOut(1);
	this->setIn(2);
}

Equivalence::~Equivalence() {

}

int Equivalence::getXmax() {
	return x_max;
}

int Equivalence::getYmax() {
	return y_max;
}

bool* Equivalence::getOutBool() {
	this->Function();
	return Out;
}

bool* Equivalence::getInBool() {
	return In;
}

void Equivalence::Function() {
	Out[0] = (In[0] == In[1]? 1:0);
}

void Equivalence::setInBool(int ind, bool out) {
	In[ind] = out;
}


/*******************Nonequivalence************************/
Nonequivalence::Nonequivalence(int x, int y) {
	this->setName(name);
	this->setX(x);
	this->setY(y);
	this->setOut(1);
	this->setIn(4);
}

Nonequivalence::~Nonequivalence() {

}

int Nonequivalence::getXmax() {
	return x_max;
}

int Nonequivalence::getYmax() {
	return y_max;
}

bool* Nonequivalence::getOutBool() {
	this->Function();
	return Out;
}

bool* Nonequivalence::getInBool() {
	return In;
}

void Nonequivalence::Function() {
	Out[0] = (In[0] != In[1] ? 1 : 0);
}

void Nonequivalence::setInBool(int ind, bool out) {
	In[ind] = out;
}


/*******************Implication************************/
Implication::Implication(int x, int y) {
	this->setName(name);
	this->setX(x);
	this->setY(y);
	this->setOut(1);
	this->setIn(2);
}

Implication::~Implication() {

}

int Implication::getXmax() {
	return x_max;
}

int Implication::getYmax() {
	return y_max;
}

bool* Implication::getOutBool() {
	this->Function();
	return Out;
}

bool* Implication::getInBool() {
	return In;
}

void Implication::Function() {
	Out[0] = (In[0] <= In[1] ? 1 : 0);
}

void Implication::setInBool(int ind, bool out) {
	In[ind] = out;
}
