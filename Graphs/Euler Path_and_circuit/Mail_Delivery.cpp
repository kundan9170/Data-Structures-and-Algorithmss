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

int degree[100000+1] = {0};
vector<int>euler;
void dfs(int node , int parent , set<int>adj[] , int*p){
    if(degree[node] == 0){
        euler.pb(node);
        return;
    }
    while(!adj[node].empty()){
        if(1){
            int child = *adj[node].begin();
            adj[node].erase(adj[node].begin());
            adj[child].erase(adj[child].find(node));
            (*p)++;
            degree[node]--;
            degree[child]--;
            dfs(child , node , adj , p);
        }
        else{
            continue;
        }
    } 
    euler.pb(node);
}



int32_t main()
    {
    fastio
    int t;
    //cin >> t;
    t = 1;
    //vector<int>ans;
    for(int i = 0 ; i<t; ++i){
        int  n , m;
        cin >> n >> m;
        set<int>adj[n+1];
        for(int i = 1 ; i<=m ; ++i){
            int u , v;
            cin >> u >> v;
            adj[u].insert(v);
            adj[v].insert(u);
            degree[u]++;
            degree[v]++;
        }
        int cnt = 0;
        int start = 1;
        for(int i = 1 ; i<=n ; ++i){
            if(degree[i]&1){
                cnt++;
                }
        }
        if(cnt == 0){
            int edge_cnt = 0;
            int *p = &edge_cnt;
            dfs(start , -1 , adj, p);
            if(edge_cnt == m){
                reverse(euler.begin() , euler.end());
                for(auto x : euler){
                    cout << x << " " ;
                }
                cout << endl;
            }
            else{
                cout << "IMPOSSIBLE" << endl;
            }
        }
        else{
            cout << "IMPOSSIBLE" << endl;
        }
    }
    return 0;
}