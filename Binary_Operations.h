#pragma once
#include "Figure.h"

/*****************Conjunction**************************/
class Conjunction: public Figure
{
public:
	Conjunction(int x, int y);
	~Conjunction();
	int getYmax() override;
	int getXmax() override;
	bool* getOutBool() override;
	bool* getInBool() override;
	void setInBool(int ind, bool out) override;
	void Function() override;
private:
	std::string name =  "&";
	bool In[2] = {0, 0};
	bool Out[1] = { 0 };
	int y_max = 100;
	int x_max = 60;
};

/******************Denial*************************/
class Denial : public Figure
{
public:
	Denial(int x, int y);
	~Denial();
	int getYmax() override;
	int getXmax() override;
	bool* getOutBool() override;
	bool* getInBool() override;
	void setInBool(int ind, bool out) override;
	void Function() override;
private:
	std::string name = "~";
	int rad = 20;
	int in = 1;
	int out = 1;
	bool In[1] = { 0 };
	bool Out[1] = { 0 };
};

/****************Constant*****************************/
class Constant : public Figure
{
public:
	Constant(int x, int y, std::string name);
	~Constant();
	int getYmax() override;
	int getXmax() override;
	bool* getOutBool() override;
	bool* getInBool() override;
	void setInBool(int ind, bool out) override;
	void Function() override;
private:
	int y_max = 30;
	int x_max = 30;
	int in = 0;
	int out = 1;
	bool Out[1] = { 1 };
};

/****************Disjunction*****************************/
class Disjunction : public Figure
{
public:
	Disjunction(int x, int y);
	~Disjunction();
	int getYmax() override;
	int getXmax() override;
	bool* getOutBool() override;
	bool* getInBool() override;
	void setInBool(int ind, bool out) override;
	void Function() override;
private:
	std::string name = "|";
	bool In[2] = { 0, 0 };
	bool Out[1] = { 0 };
	int y_max = 100;
	int x_max = 60;
};


/****************Equivalence*****************************/
class Equivalence : public Figure
{
public:
	Equivalence(int x, int y);
	~Equivalence();
	int getYmax() override;
	int getXmax() override;
	bool* getOutBool() override;
	bool* getInBool() override;
	void setInBool(int ind, bool out) override;
	void Function() override;
private:
	std::string name = "=";
	bool In[2] = { 0, 0 };
	bool Out[1] = { 0 };
	int y_max = 100;
	int x_max = 60;
};

/****************Nonequivalence*****************************/
class Nonequivalence : public Figure
{
public:
	Nonequivalence(int x, int y);
	~Nonequivalence();
	int getYmax() override;
	int getXmax() override;
	bool* getOutBool() override;
	bool* getInBool() override;
	void setInBool(int ind, bool out) override;
	void Function() override;
private:
	std::string name = "^";
	bool In[4] = { 0, 0 };
	bool Out[1] = { 0 };
	int y_max = 100;
	int x_max = 60;
};

/****************Implication*****************************/
class Implication : public Figure
{
public:
	Implication(int x, int y);
	~Implication();
	int getYmax() override;
	int getXmax() override;
	bool* getOutBool() override;
	bool* getInBool() override;
	void setInBool(int ind, bool out) override;
	void Function() override;
private:
	std::string name = "->";
	bool In[2] = { 0, 0 };
	bool Out[1] = { 0 };
	int y_max = 100;
	int x_max = 60;
};
