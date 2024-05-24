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

int matrix[101][101];
vector<int>coin_dist[16];
map<pair<int,int> , int>node;
int coin_cnt;

void bfs(int x , int y , int n , int m ){
    pr<int,int> s_node = {x,y};
    queue<pr<int,int>>q;
    int matrix_d[101][101];
    int visit[101][101];
    for(int i = 1 ; i<=100 ; ++i){
        for(int j = 1 ; j<=100 ; ++j){
            visit[i][j] = 0;
        }
    }
    matrix_d[x][y] = 0;
    q.push({x,y});
    visit[x][y] = 1;
    while(!q.empty()){
        auto pos = q.front();
        q.pop();
        int X , Y;
        X = pos.ff;
        Y = pos.ss;
        pr<int,int> direction[5];
        direction[1] = mpr(X-1 , Y); // left
        direction[2] = mpr(X+1 , Y); // right
        direction[3] = mpr(X, Y+1); // up
        direction[4] = mpr(X , Y-1); // down
        for(int i = 1 ; i<=4 ; ++i){
            auto l = direction[i];
            if(1<=l.ff && l.ff<=n && 1<=l.ss && l.ss<=m && matrix[l.ff][l.ss]!=1 && visit[l.ff][l.ss]==0){
                matrix_d[l.ff][l.ss] = matrix_d[X][Y]+1;
                visit[l.ff][l.ss] = 1;
                q.push(l);
                if(node.find(l)!=node.end()){
                    coin_dist[node[s_node]][node[l]] = matrix_d[l.ff][l.ss];
                }
            }
        }
    }
}

// return if ith is the part of the state
bool is_in(int state , int i){
    if(((1<<i) & (state)) != 0){
        return true;
    }
    else{
        return false;
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
        vector<pr<int,int>>coin;
        coin_cnt = 0;
        coin.pb({1,1});
        node[mpr(1,1)] = 0;
        for(int i = 1 ; i<=n ; ++i){
            for(int j = 1 ; j<=m ; ++j){
                cin >> matrix[i][j];
                // if coin is in bob place
                if(matrix[1][1] == 2){
                    matrix[1][1]=0;
                    continue;
                }
                if(matrix[i][j]==2){
                    coin_cnt++;
                    node[{i , j}] = coin_cnt;
                    coin.pb({i , j});
                }
            }
        }
        pr<int,int> alice;
        cin >> alice.ff >> alice.ss;
        alice.ff++;
        alice.ss++;
        // if coin is in alice place
        if(matrix[alice.ff][alice.ss] == 2){
            coin_cnt--;
            matrix[alice.ff][alice.ss] = 0;
            int idx = 0;
            vector<pr<int,int>>coin_;
            for(auto x : coin){
                if(x.ff == alice.ff && x.ss == alice.ss){
                    continue;
                }
                else{
                    node[x] = idx;
                    idx++;
                    coin_.pb(x);
                }
            }
            coin = coin_;
        }
        node[{alice}] = coin_cnt+1;
        for(int i = 0 ; i<=coin_cnt ; ++i){
            coin_dist[i].resize(coin_cnt+2);
        }
        for(int i = 0 ; i<=coin_cnt ; ++i){
            bfs(coin[i].ff , coin[i].ss , n , m);
        }
        int flag = 0;
        for(int i = 1 ; i<=coin_cnt+1 ; ++i){
            if(coin_dist[0][i] == 0){
                flag = 1;
            }
        }
        if(flag){
            cout << -1 << endl;
            continue;
        }
        //
        if(coin_cnt == 0){
            cout << coin_dist[0][1] << endl;
            continue;
        }
        // TSP
        vector<int>subset[coin_cnt+2];
        for(int i = 0 ;  i <((int)1 << (coin_cnt+1)) ; ++i){
            subset[__builtin_popcount(i)].pb(i);
        }

        int dp[coin_cnt+2][1<<(coin_cnt+2)];
        //intilization for r = 2 , where r is number of element in subset
        for(int i = 1 ; i<=coin_cnt ; ++i){
            dp[i][(1<<0)|(1<<i)] = coin_dist[0][i];
        }
        // filling dp table from r = 3 to r = coin_cnt+1
        for(int r = 3 ; r<=coin_cnt+1 ; ++r){
            for(auto state : subset[r]){
                if(is_in(state , 0)){ // source is in subset
                    for(int to = 1 ; to<=coin_cnt ; ++to){
                        if(is_in(state , to)){ // to is in subsett
                            int state_from = (state)^(1<<to); // state from where it came
                            dp[to][state] = INF;
                            for(int from  = 1 ; from<=coin_cnt ; ++from){
                                if(from == to || (!is_in(state_from , from))) continue;
                                else{
                                    dp[to][state] = min(dp[to][state] , dp[from][state_from]+coin_dist[from][to]);
                                }
                            }
                        }
                    }
                }
            }
        }
        //minimizing distance from all subset of  length coin_cnt to desitnation
        int f_state = (1<<(coin_cnt+1))-1;
        int min_dist = INF;
        for(int i = 1 ; i<=coin_cnt ; ++i ){
            min_dist = min(min_dist , dp[i][f_state] + coin_dist[i][coin_cnt+1]);
        }
        cout << min_dist << endl;

    }

    return 0;
}