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


int xor_node[2*100000+1] = {0};
int height[2*100000+1] = {0};

void dfs(int node , int parent , vector<pii>adj[]){
    for(auto child : adj[node]){
        if(child.ff != parent){
            height[child.ff] = height[node]+1;
            xor_node[child.ff] = xor_node[node]^child.ss;
            dfs(child.ff , node , adj);
        }
    }
}


struct tr{
    struct node {
        node* left;
        node* right;
        int value;
        node(){
            this->left = NULL;
            this->right = NULL;
            value = 0;
        }
    };

    node* mk_node(){
        return new node();
    }

    void insert(node* root , int x){
        node* curr  = root;
        for(int i = 30 ; i>=0 ; --i){
            int val = (((1<<i)&(x)) == (1<<i));
            if(val == 0){
                if(curr->left == NULL){
                    curr->left = new node();
                }
                curr = curr->left;
            }
            else{
                if(curr->right == NULL){
                    curr->right = new node();
                }
                curr = curr->right;
            }
            curr->value +=1;
        }
    }

    void del(node* root , int x){
       node* curr = root;
        for(int i = 30 ; i>=0 ; --i){
            int val = (((1<<i)&(x)) == (1<<i));
            if(val == 0){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
            curr->value -=1;

        }
    }

    int max_xor(node* root , int x){
        node* curr = root;
        int ans = 0;
        for(int i = 30 ; i>=0 ; --i){
            int val = (((1<<i)&(x)) == (1<<i));
            if(val == 0){
                if(curr->right != NULL && curr->right->value>0){
                    curr = curr->right;
                    ans+= (1<<i);
                }
                else{
                    if(curr->left != NULL && curr->left->value>0){
                        curr = curr->left;
                    }
                    else{
                        return -1;
                    }
                }
            }
            else{
                if(curr->left != NULL && curr->left->value>0){
                    curr = curr->left;
                    ans+= (1<<i);
                }
                else{
                    if(curr->right != NULL && curr->right->value>0){
                        curr = curr->right;
                    }
                    else{
                        return -1;
                    }
                }
            }

        }
        return ans;
    }

};


int32_t main()
    {
    fastio
    int t;
    cin >> t;
    vector<int>ans;
    for(int i = 0 ; i<t; ++i){
        int n , m;
        cin >> n >> m;
        vector<pii>adj[n+1];
        for(int i = 1 ; i<=n-1 ; ++i){
            int u , v , w;
            cin >> u >> v >> w;
            adj[u].pb({v , w});
            adj[v].pb({u , w});
        }
        xor_node[1] = 0;
        height[1] = 0;
        dfs(1 , -1 , adj);
        int xor_ = 0;
        tr t1;
        tr t2;
        auto tree1 = t1.mk_node();
        auto tree2 = t2.mk_node();
        for(int i =1 ; i<=n ; ++i){
            if(height[i]&1){
                t1.insert(tree1 , xor_node[i]);
            }
            else{
                t2.insert(tree2 , xor_node[i]);
            }
        }
        for(int i = 1 ; i<=m ; ++i){
            char c;
            cin >> c;
            if(c == '^'){
                int x;
                cin >> x;
                xor_^= x;
            }
            else{
                int v , x;
                cin >> v >> x;
                int max_ = -1;
                if(height[v]&1){
                    t1.del(tree1 , xor_node[v]);
                    max_ = max(max_ , t1.max_xor(tree1 , (x)^xor_node[v]));
                    t1.insert(tree1 , xor_node[v]);
                    max_ = max(max_ , t2.max_xor(tree2 , x^xor_node[v]^xor_));
                }
                else{
                    t2.del(tree2 , xor_node[v]);
                    max_ = max(max_ , t2.max_xor(tree2 , (x)^xor_node[v]));
                    t2.insert(tree2 , xor_node[v]);
                    max_ = max(max_ , t1.max_xor(tree1 , (x^xor_node[v])^xor_));
                }
                cout << max_ << " ";
            }
        }
        cout << endl; 
    }
    return 0;
}