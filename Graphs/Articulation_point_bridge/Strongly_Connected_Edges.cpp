#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define pi 3.14285714285
#define pb push_back
#define ppb pop_back
#define mpr make_pair
#define int long long
#define ld long double
#define pr pair
#define INF INT64_MAX - INT32_MAX
#define mod 1000000007
#define endll endl
#define ff first
#define ss second
#define fo(i,a,n) for ( int i = a; i < n; i++ )
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
using namespace __gnu_pbds;
using namespace std;


//vector<pr<int,int>>edge;
vector<pr<int,int>>bridge;
int visited[100000+1] = {0};
int DFN[100000+1];
int High_pt[100000+1];
int TIME = 0;
//int AP[100+1] = {0};
//int parent[100000+1];
set<pr<int,int>>edge_set;
void dfs(int node , int parent , vector<int>adj[]){
    visited[node] = 1;
    DFN[node] = ++TIME;
    High_pt[node] = INF;
    for(auto child : adj[node]){
        if(edge_set.find({child , node}) == edge_set.end()){
            edge_set.insert({node , child});
        }
        if(visited[child]==0){
            dfs(child , node , adj);
            High_pt[node] = min(High_pt[child] , High_pt[node]);
            if(High_pt[child] > DFN[node]){
                bridge.pb({node , child});
            }
        }else{
            if(child != parent){
                High_pt[node] = min(DFN[child] , High_pt[node]);
            }
        }
    }
}



int scc(vector<int>adj[] , int n){
    int cc = 0;
    for(int i =1 ; i<=n ; ++i){
        if(!visited[i]){
            dfs(i , -1 , adj);
            cc++;
        }
    }
    return cc;
}


int32_t main()
    {
    fastio
    int t;
    //cin >> t;
    t = 1;
    vector<int>ans;
    for(int i = 0 ; i<t; ++i){
        int n , m ;
        cin >> n >> m;
        vector<int>adj[n+1];
        for(int i =1 ; i<=m ; ++i){
            int u , v;
            cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        if(scc(adj , n) == 1 && bridge.empty()==true){
            for(auto it = edge_set.begin() ; it != edge_set.end() ; ++it){
                cout << (*it).ff << " "  << (*it).ss << endl;
            }
        }
        else{
            cout << "IMPOSSIBLE" << endl;
        }
    }
    return 0;
}