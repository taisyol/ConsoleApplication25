#include "unchi.h"

using namespace std;



//フィールド描画
void drawfield(int width,int depth,int** field){
	
	for(int i = 0; i < depth+2; i++){
		for(int j = 0; j < width+2; j++){
			switch(field[j][i]){
			case 0://スペース
				cout<<" ";break;
			case 1://壁
				cout<<"#";break;
			case 2://草
				cout<<"w";break;
			case 3://馬
				cout<<"U";break;
			case 4://草馬
				cout<<"U";break;
			case 5://虎
				cout<<"T";break;
			case 6://草虎
				cout<<"T";break;
			}
		}
		cout<<endl;
	}

};

//カーソル移動
void setCursorPos(int x, int y){
	HANDLE hCons = GetStdHandle( STD_OUTPUT_HANDLE );
	COORD pos;
	pos.X = x;
	pos.Y = y;
    SetConsoleCursorPosition(hCons, pos);
}

//ベクトル削除
void d_vector::d_kusa(vector<kusa>& p_kusa, int i){

	p_kusa.erase(p_kusa.begin()+i);

}

//生き物初期選択
void begin_life::s_kind(int width, int depth, int& n_kusa, int& n_uma, int& n_tora){
	random_device rnd;

	cout<<"kusa ";
	cin>>kusa;
	cout<<"uma ";
	cin>>uma;
	cout<<"tora ";
	cin>>tora;

	for(int i = 0; i < width*depth; i++){
		if(rnd()%10000 < kusa*100){
			n_kusa++;
		}
	}
	for(int i = 0; i < width*depth; i++){
		if(rnd()%10000 < uma*100){
			n_uma++;
		}
	}
	for(int i = 0; i < width*depth; i++){
		if(rnd()%10000 < tora*100){
			n_tora++;
		}
	}
}

//草の初期位置決定
void kusa::set_p(int width, int depth, int** field){
	int x,y;
	random_device rnd;

	unko:
	x = rnd()%(width)+1;
	y = rnd()%(depth)+1;
	if(field[x][y] == 0){
		field[x][y] = 2;
	}
	else{
		goto unko;
	}

	position_x=x;
	position_y=y;
}

//草の年
void kusa::life_info(){
	random_device rnd;

	life=rnd()%210;

}

//草の命
void kusa::life_m(int& i, int** field, int& n_kusa, vector<kusa>& p_kusa){
	d_vector del;

	life++;
	

	if(life >= 210){
		
		if(field[position_x][position_y] == 2){
			field[position_x][position_y] = 0;
		}
		else if(field[position_x][position_y] == 4){
			field[position_x][position_y] = 3;
		}
		else if(field[position_x][position_y] == 6){
			field[position_x][position_y] = 5;
		}

		n_kusa--;
		del.d_kusa(p_kusa, i);
		i--;
	}

}

//馬の初期位置決定
void uma::set_p(int width, int depth, int** field){
	int x,y;
	random_device rnd;
	
	unko:
	x = rnd()%width+1;
	y = rnd()%depth+1;
	if(field[x][y] == 0){
		field[x][y] = 3;
	}

	else if(field[x][y] == 2){
		field[x][y] = 4;
	}

	else{
		goto unko;
	}

	position_x=x;
	position_y=y;
}

//虎の初期値決定
void tora::set_p(int width, int depth, int** field){
	int x,y;
	random_device rnd;
	
	unko:
	x = rnd()%width+1;
	y = rnd()%depth+1;
	if(field[x][y] == 0){
		field[x][y] = 5;
	}

	else if(field[x][y] == 2){
		field[x][y] = 6;
	}

	else{
		goto unko;
	}

	position_x=x;
	position_y=y;
}

//馬移動
void uma::uma_move(int** field){
	int roop=1;
	random_device rnd;

	int m_x,m_y;
	int direction;

	while(roop){

	direction = rnd()%5;
	m_x = 0;
	m_y = 0;
	switch(direction){
	case 0://上
		m_y = -1;break;
	case 1://下
		m_y = 1;break;
	case 2://左
		m_x = -1;break;
	case 3://右
		m_x = 1;break;
	case 4://止
		break;
	}

	if(field[position_x+m_x][position_y+m_y] == 0){
		if(field[position_x][position_y] == 3){
			field[position_x][position_y] = 0;
			field[position_x+m_x][position_y+m_y] = 3;
		}
		else if(field[position_x][position_y] == 4){
			field[position_x][position_y] = 2;
			field[position_x+m_x][position_y+m_y] = 3;
		}
		roop = 0;
	}
	else if(field[position_x+m_x][position_y+m_y] == 2){
		if(field[position_x][position_y] == 3){
			field[position_x][position_y] = 0;
			field[position_x+m_x][position_y+m_y] = 4;
		}
		else if(field[position_x][position_y] == 4){
			field[position_x][position_y] = 2;
			field[position_x+m_x][position_y+m_y] = 4;
		}
		roop = 0;
	}
	else if(direction == 4){
		roop = 0;
	}

	}

	position_x = position_x+m_x;
	position_y = position_y+m_y;

}

//虎移動
void tora::tora_move(int** field){
	int roop=1;

	int m_x,m_y;
	int direction;

	while(roop){

	direction = rand()%5;
	m_x = 0;
	m_y = 0;
	switch(direction){
	case 0://上
		m_y = -1;break;
	case 1://下
		m_y = 1;break;
	case 2://左
		m_x = -1;break;
	case 3://右
		m_x = 1;break;
	case 4://止
		break;
	}

	if(field[position_x+m_x][position_y+m_y] == 0){
		if(field[position_x][position_y] == 5){
			field[position_x][position_y] = 0;
			field[position_x+m_x][position_y+m_y] = 5;
		}
		else if(field[position_x][position_y] == 6){
			field[position_x][position_y] = 2;
			field[position_x+m_x][position_y+m_y] = 5;
		}
		roop = 0;
	}
	else if(field[position_x+m_x][position_y+m_y] == 2){
		if(field[position_x][position_y] == 5){
			field[position_x][position_y] = 0;
			field[position_x+m_x][position_y+m_y] = 6;
		}
		else if(field[position_x][position_y] == 6){
			field[position_x][position_y] = 2;
			field[position_x+m_x][position_y+m_y] = 6;
		}
		roop = 0;
	}
	else if(direction == 4){
		roop = 0;
	}

	}

	position_x = position_x+m_x;
	position_y = position_y+m_y;

}

