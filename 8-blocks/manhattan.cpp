#include<bits/stdc++.h>
using namespace std;

struct state{
public :
    vector<int> s;
    int distance;
    bool operator>(const state& other) const{
        return distance > other.distance;
    }
};

vector<int> transform_(int n,vector<vector<int>> v);
pair<int,int> find_index(int n,int index,vector<vector<int>> &s);
int manhattan(int n,vector<int> &s,vector<int> &g);
int solvable_odd(vector<int> &v,vector<int> &g);
void print_state(vector<int> &v);
int No_misplaced_tile(vector<int> &h,vector<int> &g);
vector<vector<int>> neighbors(int n,vector<int> &s);
void print_2D(int n,vector<int> &v);
void print_solution(vector<vector<int>> &v,int n);
int closed(vector<int> &v,vector<vector<int>> &soln);


int main()
{
    clock_t start,endt;
	vector<int> v{4,6,5,2,7,8,1,0,3};
    vector<int> g{1,2,3,4,5,6,7,8,0};
    //vector<int> v{0,1,2,3,4,5,6,7,8};
	int cc = 0;
	vector<vector<int>> start_states(10,vector<int>(9)) ;
	while(cc<10){
        //shuffle(g.begin(),g.end(),default_random_engine(time(0)));
        shuffle(v.begin(),v.end(),default_random_engine(time(0)));
        start_states[cc] = v;
        cc++;
	}

    //shuffle(v.begin(),v.end(),default_random_engine(time(0)));

    print_state(start_states[0]);
    print_state(g);
    if(!solvable_odd(start_states[0],g)){
        cout<<"NOT SOLVABLE"<<endl;
        return 0;
    }
    else{
        cout<<"SOLVABLE"<<endl;
   }
    start = clock();
    priority_queue<state,vector<state>,greater<state>> q;
    int c =0;
    state st,temp;
    st.s = start_states[0];
    st.distance = manhattan(3,v,g);
    q.push(st);

	vector<vector<int>> soln;
	vector<vector<int>> done;


	while(!q.empty() && c<100000){
        temp = q.top();
        q.pop();
        soln.push_back(temp.s);

        if(!No_misplaced_tile(temp.s,g)){
            break;
        }
        if(closed(temp.s,done) == 0){
            continue;
        }
        done.push_back(temp.s);
        vector<vector<int>> ngh = neighbors(3,temp.s);
        for(auto i : ngh){
            if(closed(i,done) == 0)
               continue;

            state z;
            z.s = i;
            z.distance = manhattan(3,i,g);
            q.push(z);
        }
        c++;
	}
	endt = clock();
	double time_taken = double(endt - start) / double(CLOCKS_PER_SEC);

    print_solution(soln,3);
    cout<<"No. of states visited : "<<c<<endl;
    cout<<"No. of nodes removed from the Frontier : "<<q.size()-c<<endl;
     cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}

                                        /* ......Definitions of different functions......*/

int manhattan(int n,vector<int> &s,vector<int> &g){
    vector<vector<int>> st(n,vector<int>(n)),tar(n,vector<int>(n));
    pair<int,int> p;
    int dist = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            st[i][j] = s[i*n+j];
            tar[i][j] = g[i*n+j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(st[i][j] == 0) continue;
            p = find_index(n,st[i][j],tar);
            dist+=(abs(i-p.first)+abs(j-p.second));
        }
    }
    return dist;
}

pair<int,int> find_index(int n,int index,vector<vector<int>> &s){
    pair<int,int> p;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(s[i][j] == index){
                p.first = i;
                p.second =j;
            }
        }
    }
    return p;
}






int solvable_odd(vector<int> &v,vector<int> &g){
    int inv1=0,inv2=0;
	for(int i=0;i<9;i++){
	    for(int j=i+1;j<9;j++){
	       if(v[j] == 0) continue;
	       if(v[j]<v[i]) inv1++;
	    }
	}
	for(int i=0;i<9;i++){
	        for(int j=i+1;j<9;j++){
	            if(g[j] == 0) continue;
	            if(g[j]<g[i]) inv2++;
	    }
	}
	if(inv1%2 == inv2%2) return 1;
	return 0;
}


void print_state(vector<int> &v){
    int l =v.size();
    for(int i=0;i<l;i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

int No_misplaced_tile(vector<int> &h,vector<int> &g){
    int s = h.size();
    int ans = 0;
    for(int i=0;i<s;i++){
        if(h[i] != g[i])
            ans++;
    }
    return ans;
}
vector<vector<int>> neighbors(int n,vector<int> &s){
        vector<vector<int>> ng,mat(3,vector<int>(3,-1)),temp(3,vector<int>(3,-1));
        vector<int> res;
        int r,c;

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                mat[i][j] = s[i*n+j];
                if(mat[i][j] == 0){
                    r=i;
                    c =j;
                }
            }
        }
        temp = mat;
        if(r+1 < n && c < n){
            swap(temp[r][c],temp[r+1][c]);
            res = transform_(n,temp);
            temp = mat;
            if(No_misplaced_tile(res,s)) ng.push_back(res);
        }
        if(r-1 >=0){
            swap(temp[r][c],temp[r-1][c]);
            res = transform_(n,temp);
            temp = mat;
            if(No_misplaced_tile(res,s)) ng.push_back(res);
        }
        if(c-1 >=0){
            swap(temp[r][c],temp[r][c-1]);
            res = transform_(n,temp);
            temp = mat;
            if(No_misplaced_tile(res,s)) ng.push_back(res);
        }
        if(c+1 <n){
            swap(temp[r][c],temp[r][c+1]);
            res = transform_(n,temp);
            temp = mat;
            if(No_misplaced_tile(res,s)) ng.push_back(res);
        }
        return ng;
}

void print_2D(int n,vector<int> &v){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<v[j+i*n]<<" ";
        cout<<endl;
    }
    cout<<endl;
}
void print_solution(vector<vector<int>> &v,int n){
    for(auto i:v){
        print_2D(n,i);
    }
}


vector<int> transform_(int n,vector<vector<int>> v){
    vector<int> res(n*n);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res[i*n+j] = v[i][j];
        }
    }
    return res;
}
int closed(vector<int> &v,vector<vector<int>> &soln){
    int flag = 10;
    for(auto i : soln){
        flag = min(flag,No_misplaced_tile(v,i));
    }
    return flag;
}

