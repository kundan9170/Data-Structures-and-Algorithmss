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

int id = 1;
int scc_cnt = 0;
int ids[100000+1] = {0};
int low[100000+1];
int on_stack[100000+1] = {0};
stack<int>s;
vector<int>path; //path which will not be possible 

void dfs(int node , vector<int>adj[]){
    s.pp(node);
    on_stack[node] = 1;
    ids[node] = low[node] = id++;

    //visit all neighbours & min low-link on callback
    for(auto child : adj[node]){
        if(ids[child] == 0)dfs(child , adj);
        if(on_stack[child]){
            low[node] = min(low[node] , low[child]);
        }
    }
    // After having visited all the neighbour of node, if we're at the start of a SCC, empty the seen 
    // stack untill we're back to the start of the SCC.
    if(ids[node] == low[node]){
        int new_node = s.top();
        while(new_node!=node){
            low[new_node] = low[node];
            on_stack[new_node] = 0;
            s.pop();
            new_node = s.top();
        }
        path.pb(node);
        on_stack[node] = 0;
        s.pop();
        scc_cnt++;
    }
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
        vector<int>adj[n+1];
        for(int i = 1 ; i<=m ; ++i){
            int u , v;
            cin >> u >> v;
            adj[u].pb(v);
        }
        for(int i = 1 ; i<=n  ; ++i){
            if(ids[i]==0){
                dfs(i , adj);
            }
        }
        if(scc_cnt == 1){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
            cout << path[0] << " " << path[1] << endl;
        }
    }
    return 0;
}