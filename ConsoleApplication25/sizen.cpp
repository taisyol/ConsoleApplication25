#include "unchi.h"

using namespace std;

void main(){
	
	int width;
	int depth;

	int days = 0;
	int month = 0;
	int year = 0;

	int n_kusa=0;
	int n_uma=0;
	int n_tora=0;

	cout<<"width ";
	cin>>width;
	cout<<"depth ";
	cin>>depth;

	
		
	//�񎟌��z��
	int** field = new int*[width+2];
	for(int i = 0; i < width+2; i++){
		field[i] = new int [depth+2];
	}

	//�z�񏉊���
	for(int i = 0; i < depth+2; i++){
			for(int j = 0; j < width+2; j++){
				field[j][i] = 0;
			}
	}

	//��
	for(int i = 0; i < width+2; i++){
		field[i][0] = 1;
		field[i][depth+1] = 1;
	}
	for(int i = 0; i < depth+2; i++){
		field[0][i] = 1;
		field[width+1][i] = 1;
	}

	//����������
	begin_life select;
	select.s_kind(width, depth, n_kusa, n_uma, n_tora);

	//�픭��
	vector<seed> p_seed(0);
	//��������
	vector<kusa> p_kusa(n_kusa);
	//���̈ʒu
	for(int i = 0; i < n_kusa; i++){
		p_kusa[i].set_p(width, depth, field);
		p_kusa[i].life_info();
	}
	//�n������
	vector<uma> p_uma(n_uma);
	//�n�̈ʒu
	for(int i = 0; i < n_uma; i++){
		p_uma[i].set_p(width, depth, field);
	}
	//�Ր�����
	vector<tora> p_tora(n_tora);
	//�Ղ̈ʒu
	for(int i = 0; i < n_tora; i++){
		p_tora[i].set_p(width, depth, field);
	}


	while(!_kbhit() || (_getch() != 0x1B)){

		days++;
		if(days >= 30){
			month++;
			days = 0;
		}
		if(month >= 12){
			year++;
			month = 0;
		}

		

		//��������
		for(int i = 0; i < n_kusa; i++){
			p_kusa[i].life_m(i,field,n_kusa, p_kusa);
		}
		for(int i = 0; i < n_uma; i++){
			p_uma[i].uma_move(field);
		}
		for(int j = 0; j < n_tora; j++){
			p_tora[j].tora_move(field);
		}

		
		cout<<year<<"�N"<<month<<"�J��"<<days<<"��"<<endl;
		cout<<"kusa "<<setw(3)<<n_kusa<<endl;
		cout<<"uma "<<setw(3)<<n_uma<<endl;
		cout<<"tora "<<setw(3)<<n_tora<<endl;

		drawfield(width,depth,field);
		//Sleep(2000);
		setCursorPos(0,5);
		
	}

	for(int i = 0; i < width+2; i++ ) {
        delete[] field[i];
    }
    delete[] field;

}