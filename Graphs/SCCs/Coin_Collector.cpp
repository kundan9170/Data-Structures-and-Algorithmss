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

//using tarjan's algo to make find SCCs
class makeSCC{
    public:
    int N;
    int id = 1;
    int scc_cnt = 0;
    vector<vector<int>>adj;
    stack<int>s;
    vector<int>on_stack;
    vector<int>ids;
    vector<int>low;
    makeSCC(vector<vector<int>>adj , int n){
        this->adj = adj;
        N = n;
        on_stack.resize(n+1 , 0);
        ids.resize(n+1 , 0);
        low.resize(n+1 , 0);
    }
    void dfs(int node){
        on_stack[node] = 1;
        ids[node] = low[node] = id++;
        s.pp(node);

        for(auto child : adj[node]){
            if(ids[child] == 0)dfs(child);
            if(on_stack[child])low[node] = min(low[node] , low[child]);
        }

        if(ids[node] == low[node]){
            scc_cnt++;
            int new_node = s.top();
            while(new_node != node){
                on_stack[new_node] = 0;
                low[new_node] = scc_cnt;
                s.pop();
                new_node = s.top();
            }
            low[node] = scc_cnt;
            on_stack[node] = 0;
            s.pop();
        }
    }

    void find_all_scc(){
        for(int i = 1 ; i<=N ; ++i){
            if(ids[i] == 0){
                dfs(i);
            }
        }
    }

    vector<vector<int>> make_DAG(){
        vector<vector<int>>dag_adj;
        dag_adj.resize(scc_cnt + 1);
        set<pr<int,int>>m;
        for(int i = 1; i<=N ; ++i){
            for(auto node : adj[i]){
                if(low[i]!=low[node] && m.find({low[i] , low[node]}) == m.end()){
                    m.insert({low[i] , low[node]});
                    dag_adj[low[i]].pb(low[node]);
                }
            }
        }
        return dag_adj;
    }

    vector<int> return_low(){
        return low;
    }

    int return_no_scc(){
        return scc_cnt;
    }

};

// lol topological sort is not required
class topo_sort{
    public:
    vector<vector<int>>adj;
    int N;

    topo_sort(vector<vector<int>>adj , int n){
        this->adj = adj;
        this->N = n;
    }

    vector<int> sort_node(){
        queue<int>q;
        vector<int>sorted_node;
        vector<int>degree;
        degree.resize(N+1 , 0);
        for(int i = 1 ; i<=N ; ++i){
            for(auto child : adj[i]){
                degree[child]++;
            }
        }
        for(int i = 1 ; i<=N ; ++i){
            if(degree[i] == 0){
                q.pp(i);
            }
        }
        while(!q.empty()){
            int node = q.front();
            sorted_node.pb(node);
            q.pop();
            for(auto x : adj[node]){
                degree[x]--;
                if(degree[x] == 0){
                    q.pp(x);
                }
            }
        }
        return sorted_node;
    }
};

// works without topological sort
class DP{
    public:
    vector<vector<int>>adj;
    int N;
    vector<int>visited;
    vector<int>coin;
    vector<int>max_coin;
    vector<int>sorted_node;
    DP(vector<vector<int>>adj , int N , vector<int>coin , vector<int>sorted_node){
        this->adj = adj;
        this->N = N;
        visited.resize(N+1 , 0);
        this->coin = coin;
        max_coin.resize(N+1, 0);
        this->sorted_node = sorted_node;
    }

    void dfs(int node){
        if(adj[node].empty() == true){
            max_coin[node] = coin[node];
            return;
        }
        for(auto child : adj[node]){
            if(visited[child] == 1){
                max_coin[node] = max(max_coin[node] , coin[node]+max_coin[child]);
            }
            else{
                visited[child] = 1;
                dfs(child);
                max_coin[node] = max(max_coin[node] , coin[node]+max_coin[child]);
            }
        }
    }

    void all_dfs(){
        for(auto node : sorted_node){
            if(visited[node] == 0){
                dfs(node);
            }
        }
    }

    vector<int>return_max_coin(){
        return max_coin;
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
        vector<vector<int>>adj;
        vector<int>coin;
        adj.resize(n+1);
        coin.resize(n+1 , 0);
        for(int i = 1 ; i<=n ; ++i){
            cin >> coin[i];
        }
        for(int i = 1;i<=m;++i){
            int u , v;
            cin >> u >> v;
            adj[u].pb(v);
        }
        makeSCC new_graph(adj , n);
        new_graph.find_all_scc();
        int scc_cnt = new_graph.return_no_scc();
        vector<vector<int>>DAG;
        DAG = new_graph.make_DAG();
        vector<int> low = new_graph.return_low();
        vector<int>sort_node;
        topo_sort top_sort(DAG , scc_cnt);
        sort_node = top_sort.sort_node();
        vector<int>scc_coin;
        scc_coin.resize(scc_cnt+1 , 0);
        for(int i = 1 ; i<=n ; ++i){
            scc_coin[low[i]]+= coin[i];
        }
        DP dp(DAG , scc_cnt , scc_coin , sort_node);
        dp.all_dfs();
        vector<int>max_coin = dp.return_max_coin();
        int max_ = -1;
        for(int i = 1 ; i<=scc_cnt ; ++i){
            max_ = max(max_ , max_coin[i]);
        }
        cout << max_ << endl;
    }
    return 0;
}