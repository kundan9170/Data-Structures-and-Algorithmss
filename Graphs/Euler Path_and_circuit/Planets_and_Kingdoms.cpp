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
int on_stack[100000+1] = {0};
int low[100000+1];
stack<int>s;

void dfs(int node , vector<int>adj[]){
    on_stack[node] = 1;
    s.pp(node);
    low[node] = ids[node] = id++;

    for(auto child : adj[node]){
        if(ids[child] == 0)dfs(child , adj);
        if(on_stack[child]){
            low[node] = min(low[child] , low[node]);
        }
    }

    if(ids[node] == low[node]){
        //cout << node << "hii" << low[node] << endl;
        int new_node = s.top();
        while(new_node != node){
            low[new_node] = scc_cnt;
            on_stack[new_node] = 0;
            s.pop();
            new_node = s.top();
        }
        on_stack[node] = 0;
        low[node] = scc_cnt;
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
        int n , m ;
        cin >> n >> m;
        vector<int>adj[n+1];
        for(int i = 1 ; i<=m ; ++i){
            int u , v;
            cin >> u >> v;
            adj[u].pb(v);
        }
        for(int k = 1 ; k<=n ; ++k){
            if(ids[k]==0){
                dfs(k , adj);
            }
        }
        cout << scc_cnt << endl;
        for(int i = 1 ; i<=n ; ++i){
            cout << low[i]+1 << " ";
        }
        cout << endl;

    }
    return 0;
}