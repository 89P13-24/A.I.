#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

// AI is 1 and Human is -1
void print_board(vector<vector<int>> v) {
	int k=0;
	cout<<"----++---++----"<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<"| ";
			if(v[i][j] == 0){
				cout<<k<<" |";
			}
			else{
				if(v[i][j]==-1){
					cout<<"X |";
				}
				else{
					cout<<"O |";
				}
			}
			k++;
		}
			cout<<"\n----++---++----"<<endl;
	}
}

void printt_board(vector<vector<int>> v);

int winner(vector<vector<int>> v){
    int x =0;

    for(int i=0;i<3;i++){
        if(v[i][0] == v[i][1] &&
           v[i][1] == v[i][2] &&
           v[i][1] != 0)
            return x = v[i][1];
    }
    for(int i=0;i<3;i++){
        if(v[0][i] == v[1][i] &&
           v[1][i] == v[2][i] &&
           v[1][i] != 0)
            return x = v[1][i];
    }
    if(v[0][0] == v[1][1] &&
           v[1][1] == v[2][2] &&
           v[1][1] != 0)
            return x = v[1][1];
    if(v[0][2] == v[1][1] &&
           v[1][1] == v[2][0] &&
           v[1][1] != 0)
            return x = v[1][1];

    return 0;

}

bool is_board_empty(vector<vector<int>> v){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(v[i][j] == 0)
                return true;
        }
    }
    return false;
}

int evaluation_func(vector<vector<int>> v, int c){
    int cx = 0,co=0,sx=0,so=0,Do=0,dx=0;
    for(int i=0;i<3;i++){
        sx = 0 ,so=0;
        for(int j=0;j<3;j++){
            if(v[i][j] == 1)
                sx++;
            else if(v[i][j] == 2)
                so++;
            if(i==j){
                if(v[i][j] == 1)
                    dx++;
                else if(v[i][j] == 2)
                    Do++;
            }
        }
        if(sx == 0 && so==0){
            co++;
            cx++;
            continue;
        }
        if(so == 0)
            cx++;
        else if(sx == 0)
            co++;
    }
    for(int i=0;i<3;i++){
        sx = 0 ,so=0;
        for(int j=0;j<3;j++){
            if(v[j][i] == 1)
                sx++;
            else if(v[j][i] == 2)
                so++;
        }
        if(sx == 0 && so==0){
            co++;
            cx++;
            continue;
        }
        if(so == 0)
            cx++;
        else if(sx == 0)
            co++;
    }
    if(Do == 0)
        cx++;
    if(dx == 0)
        co++;
    so=0,sx=0;
    if(v[0][2] == 1)
        sx++;
    if(v[1][1]== 1)
        sx++;
    if(v[2][0] == 1)
        sx++;

    if(v[0][2] == 2)
        so++;
    if(v[1][1]== 2)
        so++;
    if(v[2][0] == 2)
        so++;

    if(sx == 0)
        co++;
    if(so == 0)
        cx++;

    if(c==1) return (cx -co);
    else return (co-cx);
}



int minimax(vector<vector<int>> v,int depth,bool maximizing){
    int result = winner(v);
    if(result !=0){
        return result*100;
    }
    if(result == 0 && !is_board_empty(v))
        return 0;
    if(depth ==0){
        if(maximizing)return evaluation_func(v,1);
        else return evaluation_func(v,-1);
    }
    if(maximizing){
        int bestscore = INT_MIN;
        int score;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(v[i][j] == 0){
                    v[i][j] =1;
                    score = minimax(v,depth-1,false);

                    bestscore=max(score,bestscore);
                    v[i][j] = 0;
                }
            }
        }
        return bestscore;
    }else{
        int bestscore = INT_MAX;
        int score;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(v[i][j] == 0){
                    v[i][j] = -1;
                    score = minimax(v,depth-1,true);

                    bestscore = min(score,bestscore);
                    v[i][j] = 0;
                }
            }
        }
        return bestscore;
    }
}


void best_move(vector<vector<int>> &v,int depth){
    int bestscore = INT_MIN;
    int score;
    int x,y;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(v[i][j] == 0){
                v[i][j] = 1;
                score = minimax(v,depth-1,false);
                if(score > bestscore){
                    x=i;
                    y=j;
                    bestscore= score;
                }
                v[i][j] = 0;
            }
        }
    }
    v[x][y] = 1;
}


void printt_board(vector<vector<int>> v){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(v[i][j] == 0)
                cout<<"* ";
            else if(v[i][j] == 1)
                cout<<"X ";
            else
                cout<<"O ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main()
{
    clock_t start,endt;
    int ct=0;
    double total_time=0;
    cout<<"Initial Board :-"<<endl;

    int mv = 0;
    vector<vector<int>> v(3,vector<int>(3,0));
    print_board(v);
//    v[0][0] =-1;
//    v[1][1] =1;
//    v[2][2] = -1;
    cout<<"Do you want to play first :-\nEnter Yes or No"<<endl;
    string choice;
    cin>>choice;
    int x,y,p;
    int d =6;
    cout<<"What is the depth that you want to set.."<<endl;
    cin>>d;

    if(choice == "No"){
        start = clock();
        best_move(v,d);
        endt = clock();
        double time_taken = double(endt - start) / double(CLOCKS_PER_SEC);
        total_time+=time_taken;
        ct++;
        print_board(v);
        mv++;
    }
    int flag = 1;
    int result = 0;
    while(mv < 9){
        cout<<"Enter the Position where you want to play"<<endl;
        cin>>p;
        if(p<9){
            x = p/3;
            y = p%3;
            if(v[x][y] != 0){
                cout<<"Enter a valid move"<<endl;
                continue;
            }
            v[x][y] = -1;
            print_board(v);
        }else{
            cout<<"Enter a valid move"<<endl;
            continue;
        }
        result = winner(v);
        if(result == -1){
            cout<<"PLayer Has Won!!"<<endl;
            flag =0;
            break;
        }
        mv++;
        if(mv == 9) break;
        cout<<"Board after computer plays"<<endl;
        start = clock();
        best_move(v,d);
        endt = clock();
        double time_taken = double(endt - start) / double(CLOCKS_PER_SEC);
        total_time+=time_taken;
        ct++;
        mv++;
        print_board(v);
        result = winner(v);
        if(result == 1){
            cout<<"Computer Has Won!!"<<endl;
            flag = 0;
            break;
        }
    }
    if(flag) cout<<"Game is Tied"<<endl;
    cout << endl<<"Average time taken by program to make moves is : " << fixed
         << total_time/ct << setprecision(5);
    cout << " sec " << endl;
}
