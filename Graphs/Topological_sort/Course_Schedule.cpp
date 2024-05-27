#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define pi 3.14285714285
#define pb push_back
#define ppb pop_back
#define mpr make_pair
#define ll long long
#define ld long double
#define pr pair
#define endll endl
#define ff first
#define ss second
#define fo(i,a,n) for ( int i = a; i < n; i++ )
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
using namespace __gnu_pbds;
using namespace std;
ll max_idx(ll arr[] , int l , int r){
ll max_ = -1;
int max_idx = -1;
for(int i = l ; i<=r ; ++i){
if(arr[i] > max_){
max_ = arr[i];
max_idx = i;
}
}
return max_idx;
}
int main()
    {
    fastio
    int t;
    //cin >> t
    t = 1;
    for(int i = 0 ; i<t; ++i){
        int n , m;
        cin >> n >> m;
        vector<int> adj[n+1];
        int degree[n+1] = {0};
        for(int i = 0 ; i<m ; ++i){
            int u , v;
            cin >> u >> v;
            degree[v]++;
            adj[u].pb(v);
        }
        queue<int> q;
        vector<int>t_sort;
        for(int i = 1 ; i<= n ; ++i){
            if(degree[i] == 0){
                q.push(i);
            }
        }
        while(!q.empty()){
            int node = q.front();
            q.pop();
            t_sort.pb(node);
            for(auto child : adj[node]){
                degree[child]--;
                if(degree[child] == 0){
                    q.push(child);
                }
            }
        }
        if(t_sort.size() == n){
            for(auto x : t_sort){
                cout << x << " ";
            }
            cout << endl;
        }
        else{
            cout << "IMPOSSIBLE" << endl;
        }
    }
    return 0;
}