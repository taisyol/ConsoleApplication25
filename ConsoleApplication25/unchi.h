#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<windows.h>
#include<conio.h>
#include<vector>
#include<random>
#include<iomanip>

using namespace std;

class begin_life{
	public:
	float kusa;
	float uma;
	float tora;

	void s_kind(int width, int depth, int& n_kusa, int& n_uma, int& n_tora);

};

class kusa{
public:
	int life;
	int position_x;
	int position_y;

	void set_p(int width, int depth, int** field);
	void life_info();
	void life_m(int& i, int** field, int& n_kusa, vector<kusa>& p_kusa);

};

class seed{
public:
	int position_x;
	int position_y;
	int life;

	
};

class uma{
private:
	int onaka;
public:
	int position_x;
	int position_y;

	void eat();
	void set_p(int width, int depth, int** field);
	void uma_move(int** field);
};

class tora{
private:
	int onaka;
public:
	int position_x;
	int position_y;

	void eat();
	void set_p(int width, int depth, int** field);
	void tora_move(int** field);
};

class d_vector{
public:
	void d_kusa(vector<kusa>& p_kusa, int i);
	void d_uma(vector<uma>& p_uma);
};

void drawfield(int width, int depth, int** field);
void setCursorPos(int x, int y);