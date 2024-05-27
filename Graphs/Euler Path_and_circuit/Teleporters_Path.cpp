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

int in_deg[100000+1] = {0};
int out_deg[100000+1] = {0};
vector<int>edge;

void dfs(int node, int parent , set<int>adj[] , int*p){
    if(adj[node].empty() == true){
        edge.pb(node);
        return;
    }
    while(!adj[node].empty()){
        int child = *adj[node].begin();
        adj[node].erase(adj[node].begin());
        //adj[child].erase(adj[child].find(node));
        (*p)++;
        dfs(child, node , adj , p);
    }
    edge.pb(node);
}

int32_t main()
    {
    fastio
    int t;
    //cin >> t;
    t = 1;
    vector<int>ans;
    for(int i = 0 ; i<t; ++i){
        int n , m;
        cin >> n >> m;
        set<int>adj[n+1];
        for(int i = 1 ; i<=m ; ++i){
            int u , v;
            cin >> u >> v;
            adj[u].insert(v);
            out_deg[u]++;
            in_deg[v]++;
        }
        int flag = 0;
        for(int i =2 ; i<n ; ++i){
            if(in_deg[i] != out_deg[i]){
                flag = 1;
                break;
            }
        }
        if(out_deg[1]-in_deg[1] == 1 && in_deg[n]-out_deg[n]== 1 && !flag){
            int edge_cnt = 0;
            int *p = &edge_cnt;
            dfs(1 , -1 , adj , p);
            //cout << edge_cnt << endl;
            if(edge_cnt == m){
                reverse(edge.begin() , edge.end());
                for(auto x : edge){
                    cout << x << " ";
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