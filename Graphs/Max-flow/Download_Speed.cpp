#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define pi 3.14285714285
#define pb push_back
#define ppb pop_back
#define mpr make_pair
#define pp push
#define pii pair<int,int>
#define int long long
#define ld long double
#define pr pair
#define INF INT64_MAX - INT32_MAX
#define n_INF INT64_MIN + INT32_MAX
#define mod 1000000007
#define endll endl
#define ff first
#define ss second
#define fo(i,a,n) for ( int i = a; i < n; i++ )
#define bit_cnt(n) __builtin_popcount(n)
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
using namespace __gnu_pbds;
using namespace std;

int gcd(int a, int b)
{
if (a == 0)
return b;
return gcd(b % a, a);
}

int n;
vector<vector<int>>capacity;
vector<vector<int>>adj;

int bfs(int s , int t , vector<int>&parent){
    fill(parent.begin() , parent.end() , -1);
    parent[s] = -2;
    queue<pii>q;
    q.pp({s , INF});
    while(!q.empty()){
        int cur = q.front().ff;
        //cout << cur << " ";
        int flow = q.front().ss;
        q.pop();
        for(auto next : adj[cur]){
            if(parent[next] == -1 && capacity[cur][next]){
                parent[next] = cur;
                int new_flow = min(flow , capacity[cur][next]);
                if(next == t){
                    return new_flow;
                }
                q.pp({next , new_flow});
            }
        }
    }
    return 0;
}



int max_flow(int s , int t){
    int flow = 0;
    vector<int>parent(n+1);
    int new_flow;

    while((new_flow = bfs(s,t,parent))){
        flow+= new_flow;
        int cur = t;
        while(cur!=s){
            int prev = parent[cur];
            capacity[prev][cur]-= new_flow;
            capacity[cur][prev]+= new_flow;
            cur = prev;
        }
    }
    return flow;
}


int32_t main()
    {
    fastio
    int t;
    //cin >> t;
    t = 1;
    vector<int>ans;
    for(int i = 0 ; i<t; ++i){
        int m;
        cin >> n >> m;
        adj.resize(n+1);
        capacity.resize(n+1);

        for(int i = 1 ; i <=n ; ++i){
            capacity[i].resize(n+1 , 0);
        }

        for(int i = 1 ; i<=m ; ++i){
            int u , v , c;
            cin >> u >> v >> c;
            adj[u].pb(v);
            adj[v].pb(u);
            capacity[u][v]+= c;
        }
       cout << max_flow(1,n) << endl;

    }
    return 0;
}