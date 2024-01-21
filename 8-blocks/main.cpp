#include<bits/stdc++.h>
using namespace std;

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

int main()
{
	//cout<<"Enter 0 for empty space"<<"\n";
	vector<int> g(9),v(9);
	//cout<<"Enter start state"<<"\n";
	//for(int i=0;i<9;i++) cin>>v[i];
	//cout<<"Enter goal state"<<"\n";
	int c = 0;

	for(int i=0;i<9;i++){
	    g[i] = 8-i;
	    v[i] = i;
	}
	vector<vector<int>> start_states(10,vector<int>(9)) ;
	vector<vector<int>> goal_states(10,vector<int>(9)) ;
	while(c<10){
        shuffle(g.begin(),g.end(),default_random_engine(time(0)));
        shuffle(v.begin(),v.end(),default_random_engine(time(0)));
        start_states[c] = v;
        goal_states[c] = g;
        c++;
	}
	int ans = 0;


	for(int i=0;i<10;i++){
        print_state(start_states[i]);
        print_state(goal_states[i]);
        cout<<endl;
        if(solvable_odd(start_states[i],goal_states[2]))
            ans++;
	}
	cout<<ans<<endl;
}
