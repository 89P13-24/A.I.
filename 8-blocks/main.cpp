#include<bits/stdc++.h>
using namespace std;

struct state{
public :
    vector<int> s;
    int heuristics;
    int depth;
    int pindex;
    bool operator>(const state& other) const{
        return heuristics > other.heuristics;
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
map<int,pair<int,int>> create_goalp(vector<int> &g,int n);
int linear_Conflict(int n,vector<int> &s,vector<int> &g);
void printl(state st,vector<state> &soln,int step);
void A_using_manhattan(int n,vector<int> &v,vector<int> &g);
void A_using_hamming(int n,vector<int> &v,vector<int> &g);
void A_using_Linear_Conflict(int n,vector<int> &v,vector<int> &g);
void A_star(string x,vector<int> &v,vector<int> &g,int n);
string stv(vector<int> &v){
    int s =v.size();
    string ans ="";
    for(int i=0;i<s;i++){
        ans+=to_string(v[i]);
    }
    return ans;
}

int main()
{
	vector<int> v{7,2,4,5,0,6,8,3,1};
    vector<int> g{0,1,2,3,4,5,6,7,8};

	cout << "Enter 1 to input an initial state and a goal state and get it solved if solvable:\n";
    cout << "Enter 2 to randomly generate some solvable examples and their solutions\n";
    int x;
    cin>>x;
    if(x==1){
        cout << "Enter the start state:\n";
        for(int i=0;i<9;i++){
            cin>>v[i];
        }
        cout << "Enter the goal state:\n";
        for(int i=0;i<9;i++){
            cin>>g[i];
        }
        if(!solvable_odd(v,g)){
            cout<<"NOT SOLVABLE"<<endl;
            return 0;
        }
        else{
            cout<<"SOLVABLE"<<endl;
        }
        string choice;
        cout << "Enter Manhattan to try Manhattan distance as the heuristic\n";
        cout << "Enter Misplaced_Tile to try Misplaced Tile heuristic\n";
        cout << "Enter Linear_Conflict to try Linear Conflict heuristic\n";
        cin>>choice;
        cout<<"\nUsing "<<choice<<" Heuristics"<<endl;

        A_star(choice,v,g,3);
    }
    else if(x==2){
        int cc = 0,t;
        cout << "How many examples do you want to see?\n";
        cin>>t;
        vector<vector<int>> start_states(t,vector<int>(9)) ;
        while(cc<t){
            shuffle(v.begin(),v.end(),default_random_engine(time(0)));
            if(solvable_odd(v,g)){
                start_states[cc] = v;
                cc++;
            }
        }
        string choice;
        cout << "Enter Manhattan to try Manhattan distance as the heuristic\n";
        cout << "Enter Misplaced_Tile to try Misplaced Tile heuristic\n";
        cout << "Enter Linear_Conflict to try Linear Conflict heuristic\n";
        cin>>choice;
        cout<<"\nUsing "<<choice<<" Heuristics"<<endl;
        while(t--){
            A_star(choice,start_states[t],g,3);
        }
	}



}

                                        /* ......Definitions of different functions......*/



int manhattan(int n,vector<int> &s,vector<int> &g){
    vector<vector<int>> st(n,vector<int>(n)),tar(n,vector<int>(n));
    map<int,pair<int,int>> m ;
    m = create_goalp(g,n);
    pair<int,int> p;
    int dist = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            st[i][j] = s[i*n+j];
            //tar[i][j] = g[i*n+j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(st[i][j] == 0) continue;
            //p = find_index(n,st[i][j],tar);
            p = m[st[i][j]];
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
        if(r-1 >=0){
            swap(temp[r][c],temp[r-1][c]);
            res = transform_(n,temp);
            temp = mat;
            if(!(res == s)) ng.push_back(res);
        }
        if(r+1 < n && c < n){
            swap(temp[r][c],temp[r+1][c]);
            res = transform_(n,temp);
            temp = mat;
            if(!(res == s)) ng.push_back(res);
        }
        if(c-1 >=0){
            swap(temp[r][c],temp[r][c-1]);
            res = transform_(n,temp);
            temp = mat;
            if(!(res == s)) ng.push_back(res);
        }
        if(c+1 <n){
            swap(temp[r][c],temp[r][c+1]);
            res = transform_(n,temp);
            temp = mat;
            if(!(res == s)) ng.push_back(res);
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
    int flag = 1;
    for(auto i : soln){
        if(i == v){
            flag = 0;
            break;
        }
    }
    return flag;
}

map<int,pair<int,int>> create_goalp(vector<int> &g,int n){
    map<int,pair<int,int>> m;
    pair<int,int> p;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            p = make_pair(i,j);
            m[g[i*n+j]] = p;
        }
    }
    return m ;
}

int count_conflicts(vector<int> &v){
    int c=0;
    for(int i=0;i<int(v.size());i++){
        for(int j=i+1;j<int(v.size());j++){
            if(v[j] < v[i] ){
                c++;
            }
        }
    }
    return c;
}

int linear_Conflict(int n,vector<int> &s,vector<int> &g){
    vector<vector<int>> st(n,vector<int>(n)),tar(n,vector<int>(n));
    map<int,pair<int,int>> m ;
    m = create_goalp(g,n);
    pair<int,int> p;
    int dist = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            st[i][j] = s[i*n+j];
            //tar[i][j] = g[i*n+j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(st[i][j] == 0) continue;
            //p = find_index(n,st[i][j],tar);
            p = m[st[i][j]];
            dist+=(abs(i-p.first)+abs(j-p.second));
        }
    }

    for(int i=0;i<n;i++){
        vector<int> row;
        for(int j=0;j<n;j++){
            if(i == m[st[i][j]].first){
                row.push_back(m[st[i][j]].second);
            }
        }
        dist+=count_conflicts(row);
    }
    for(int i=0;i<n;i++){
        vector<int> col;
        for(int j=0;j<n;j++){
            if(i == m[st[j][i]].second){
                col.push_back(m[st[j][i]].first);
            }
        }
        dist+=count_conflicts(col);
    }
    return dist;
}

void printl(state st,vector<state> &soln,int step){

    if(st.pindex == -1){
        cout<<"Step No. "<<step<<endl;
        print_2D(3,st.s);
        return;
    }
    printl(soln[st.pindex],soln,step-1);
    cout<<"Step No. "<<step<<endl;
    print_2D(3,st.s);

}

void A_using_manhattan(int n,vector<int> &v,vector<int> &g){
    clock_t start,endt;
    start = clock();
    priority_queue<state,vector<state>,greater<state>> q;
    int c =0;
    state st,temp;
    st.s = v;
    st.depth = 1;
    st.pindex = -1;
    st.heuristics = manhattan(3,v,g)+0;
    q.push(st);
    unordered_map<string,int> ms;
	vector<state> soln;
	vector<vector<int>> done;
    int f =1;

	while(!q.empty() && c<100000){
        temp = q.top();
        q.pop();
        soln.push_back(temp);
        if(temp.s == g)
            break;
        if(ms[stv(temp.s)]){
            continue;
        }
        ms[stv(temp.s)]++;
        vector<vector<int>> ngh = neighbors(3,temp.s);
        for(auto i : ngh){
            if(ms[stv(i)])
               continue;

            state z;
            z.s = i;
            z.heuristics = manhattan(3,i,g)+temp.depth;
            z.depth = temp.depth+1;
            z.pindex = soln.size() - 1;
            q.push(z);
            f++;
        }
        c++;
	}
	endt = clock();
	double time_taken = double(endt - start) / double(CLOCKS_PER_SEC);

    //print_solution(soln,3);
    printl(temp,soln,temp.depth);
    cout<<"No. of steps to reach the solution : "<<temp.depth<<endl;
    cout<<"No. of nodes removed from the Frontier : "<<f-c<<endl;
     cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}

void A_using_hamming(int n,vector<int> &v,vector<int> &g){
    clock_t start,endt;
    start = clock();
    priority_queue<state,vector<state>,greater<state>> q;
    int c =0;
    state st,temp;
    st.s = v;
    st.depth = 0;
    st.pindex = -1;
    st.heuristics = No_misplaced_tile(v,g)+1;
    q.push(st);

	vector<state> soln;
	unordered_map<string,int> done;
    int f =1;

	while(!q.empty()){
        temp = q.top();
        q.pop();
        soln.push_back(temp);
        if(temp.s == g)
            break;
        if(done[stv(temp.s)]){
            continue;
        }
        done[stv(temp.s)]++;
        vector<vector<int>> ngh = neighbors(3,temp.s);
        for(auto i : ngh){
            if(done[stv(i)])
               continue;

            state z;
            z.s = i;
            z.heuristics = No_misplaced_tile(i,g) + temp.depth;
            z.depth = temp.depth+1;
            z.pindex = soln.size()-1;
            q.push(z);
            f++;
        }
        c++;
	}
	endt = clock();
	double time_taken = double(endt - start) / double(CLOCKS_PER_SEC);

    //print_solution(soln,3);
    printl(temp,soln,temp.depth);
    cout<<"No. of steps to reach the solution : "<<temp.depth<<endl;
    cout<<"No. of nodes removed from the Frontier : "<<f-c<<endl;
     cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}


void A_using_Linear_Conflict(int n,vector<int> &v,vector<int> &g){
    clock_t start,endt;
    start = clock();
    priority_queue<state,vector<state>,greater<state>> q;
    int c =0;
    state st,temp;
    st.s = v;
    st.depth = 1;
    st.pindex = -1;
    st.heuristics = linear_Conflict(3,v,g)+1;
    q.push(st);

	vector<state> soln;
	map<string,int> done;
    int f =1;

	while(!q.empty() && c<100000){
        temp = q.top();
        q.pop();
        soln.push_back(temp);
        if(temp.s == g)
            break;
        if(done[stv(temp.s)]){
            continue;
        }
        done[stv(temp.s)]++;
        vector<vector<int>> ngh = neighbors(3,temp.s);
        for(auto i : ngh){
            if(done[stv(i)])
               continue;

            state z;
            z.s = i;
            z.heuristics = linear_Conflict(3,i,g)+temp.depth;
            z.depth = temp.depth+1;
            z.pindex = soln.size() - 1;
            q.push(z);
            f++;
        }
        c++;
	}
	endt = clock();
	double time_taken = double(endt - start) / double(CLOCKS_PER_SEC);

    //print_solution(soln,3);
    printl(temp,soln,temp.depth);
    cout<<"No. of steps to reach the solution : "<<temp.depth<<endl;
    cout<<"No. of nodes removed from the Frontier : "<<f-c<<endl;
     cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}

void A_star(string x,vector<int> &v,vector<int> &g,int n){
    if(x == "Manhattan")
        A_using_manhattan(n,v,g);
    else if(x == "Linear_Conflict")
        A_using_Linear_Conflict(n,v,g);
    else if(x == "Misplaced_Tile")
        A_using_hamming(n,v,g);
}
