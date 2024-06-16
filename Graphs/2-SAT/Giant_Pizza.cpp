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

int ceil_(int a , int b){
if(a%b == 0) return a/b;
else{
return a/b + 1;
    }
}

int log_(int n){
    return 31 - __builtin_clz(n);
}
int binpow(int a, int b) {
int res = 1;
while (b > 0) {
if (b & 1)
res = res * a;
a = a * a;
b >>= 1;
}
return res;
}


struct two_sat{
    int n;
    vector<vector<int>>adj;
    vector<vector<int>>t_adj;
    vector<int>visit;
    vector<int>top_sort;
    vector<int>comp;
    vector<int>value;

    two_sat(int n){
        this->n = n;
        adj.resize(2*n+1);
        t_adj.resize(2*n+1);
        visit.resize(2*n+1 , 0);
        comp.resize(2*n+1 , 0);
        value.resize(n+1 , 0);
    }

    void add_edge(int u , int v){
        adj[u].pb(v);
        t_adj[v].pb(u);
    }

    void imp_edge(int u , bool u_b , int v , int v_b){
        add_edge(u+(u_b ? n : 0) , v + (v_b ? 0 : n));
        add_edge(v+(v_b ? n : 0) , u + (u_b ? 0 : n));
    }

    void dfs(int v){
        visit[v] = 1;
        for(auto child : adj[v]){
            if(visit[child] == 0){
                dfs(child);
            }
        }
        top_sort.pb(v);
    }
    void all_dfs(){
        for(int i=1 ; i<=2*n ; ++i){
            if(visit[i] == 0){
                dfs(i);
            }
        }
    }

    void scc(int u , int id){
        comp[u] = id;
        for(auto child : t_adj[u]){
            if(comp[child] == 0){
                scc(child , id);
            }
        }
    }
    void make_scc(){
        int idx = 1;
        reverse(top_sort.begin() , top_sort.end());
        for(auto node : top_sort){
            if(comp[node] == 0){
                scc(node , idx);
                idx++;
            }
        }
    }
    bool is_satisfy(){
        for(int i = 1 ; i<=n ; ++i){
            if(comp[i] == comp[i+n] && comp[i]!= 0) return false;
            value[i] = comp[i]<comp[i+n] ? 0 : 1;
        }
        return true;
    }
    vector<int>return_val(){
        return value;
    }

};

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
        two_sat t_s(m);
        for(int i = 1 ; i<=n ; ++i){
            char u_b , v_b ;
            int u , v;
            cin >> u_b >> u >> v_b >> v;
            t_s.imp_edge(u , u_b == '+' , v , v_b == '+');
        }
        t_s.all_dfs();
        t_s.make_scc();
        bool ans_ = t_s.is_satisfy();
        if(ans_ == false){
            cout << "IMPOSSIBLE" << endl;
        }
        else{
            vector<int>val = t_s.return_val();
            for(auto i = 1 ; i<=m ; ++i){
                if(val[i] == 1){
                    cout << '+' << " ";
                }
                else{
                    cout << '-' << " ";
                }
            }
            cout << endl;
        }
    }
    return 0;
}