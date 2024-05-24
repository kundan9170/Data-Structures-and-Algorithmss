#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define pi 3.14285714285
#define pb push_back
#define ppb pop_back
#define mpr make_pair
#define pp push
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
int32_t main()
    {
    fastio
    int t;
    cin >> t;
    vector<int>ans;
    for(int i = 0 ; i<t; ++i){
        int n , m;
        cin >> n >> m;
        vector<pr<int,int>>adj[n+1];
        for(int i = 1 ; i<=m ; ++i){
            int u , v , w;
            cin >> u >> v >> w;
            adj[u].pb({v, w});
            adj[v].pb({u ,w});
        }
        int slow[n+1];
        for(int i = 1 ; i <= n ; ++i){
            cin >> slow[i];
        }
        priority_queue<tuple<int,int,int> , vector<tuple<int,int,int>> , greater<tuple<int,int,int>>>pq;
        pq.push({0,1,1});
        int dist[n+1][n+1];
        int visit[n+1][n+1];
        for(int i =1;i<=n; ++i){
            for(int j = 1 ; j<=n; ++j){
                visit[i][j] = 0;
                dist[i][j] = INF;
            }
        }
        dist[1][1] = 0;
        // graph modelling , made more node[i][j] as node i reached by cycle j
        while(!pq.empty()){
            int weight , node , bicycle;
            tie(weight , node , bicycle) = pq.top();
            pq.pop();
            if(visit[node][bicycle])continue;
            visit[node][bicycle] = 1;
            for(auto child : adj[node]){
                if(dist[child.ff][bicycle] > weight + child.ss*slow[bicycle]){
                   dist[child.ff][bicycle] = weight + child.ss*slow[bicycle];
                   // if you reached node , then either you take the older cycle or get new cycle and travel
                   pq.push({dist[child.ff][bicycle] , child.ff , bicycle});
                   pq.push({dist[child.ff][bicycle] , child.ff , child.ff});
                }
            }
        }
        int min_ = INF;
        for(int i = 1 ; i<=n-1 ; ++i){
            min_ = min(min_ , dist[n][i]);
        }
        ans.pb(min_);
    }
    for(auto x : ans){
        cout << x << endl;
    }
    return 0;
}