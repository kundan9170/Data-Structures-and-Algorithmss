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


struct seg_tree{
    int N;
    int pow_two;
    vector<pii>tree;
    seg_tree(int n){
        N = n;
        pow_two = ceil(log2(n));
        pow_two = (1<<pow_two);
        tree.resize(4*pow_two+1);
    }

    //build the tree
    void build(vector<int>v){
        int cnt = 0;
        //inserting value
        for(int i = pow_two ; i<=2*pow_two-1 ; ++i){
            if(cnt<N){
                tree[i].ff = v[cnt];
                tree[i].ss = 0;
                cnt++;
            }
            else{
                tree[i].ff= n_INF;
            }   
        }
        //building segment tree for max query
        for(int i = 2*pow_two-2 ; i>=2 ; i-=2){
            tree[i/2].ff = max(tree[i].ff , tree[i+1].ff);
            tree[i/2].ss = 0;
        }
    }

    void push(int v){
        int val = tree[v].ss;
        tree[v].ss = 0;
        tree[2*v].ss+= val;
        tree[2*v].ff+= val;
        tree[2*v+1].ss+= val;
        tree[2*v+1].ff+= val;
    }

    // range update
    void update(int value , int low , int high , int L , int R , int node){
        if(L<=low && high<=R){
            tree[node].ff+= value;
            tree[node].ss+= value;
            return;
        }
        else if(high<L || R<low){
            return;
        }
        else{
            push(node);
            int mid = (low+high)/2;
            update(value , low , mid , L , R , 2*node);
            update(value , mid+1 , high , L , R , 2*node+1);
            tree[node].ff = max(tree[2*node].ff , tree[2*node+1].ff);
        }
    }

    //query
    int query(int low , int high , int L , int R , int node){
        if(L<=low && high <=R){
            return tree[node].ff;
        }
        else if(R<low || high<L){
            return n_INF;
        }
        else{
            push(node);
            int mid = (low+high)/2;
            return max(query(low  , mid , L , R , 2*node) , query(mid+1 , high , L , R , 2*node+1));
        }
    }

    void print_(){
        for(int i = 1 ; i<=2*pow_two-1 ; ++i){
            cout << tree[i].ff << " ";
        }
        cout << endl;
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
        int n ,q;
        cin >> n >> q;
        int n_ =n;
        vector<int>array;
        vector<int>prefix_sum;
        for(int i = 0 ; i<n ; ++i){
            int tmp;
            cin >> tmp;
            array.pb(tmp);
            if(i==0){
                prefix_sum.pb(tmp);
            }
            else{
                tmp = tmp + prefix_sum[i-1];
                prefix_sum.pb(tmp);
            }
        }
        seg_tree st(n);
        st.build(prefix_sum);
        //st.print_();
        n = ceil(log2(n));
        n = (1<<n);
        for(int i = 0 ; i<q ; ++i){
            int a , b , c;
            cin >> a >> b >> c;
            if(a == 1){
                int num = st.query(1 , n , b , b , 1);
                if(b>1){
                    num-= st.query(1,n ,b-1,b-1,1);
                }
                int val = c-num;
                //cout << val << "hii" << endl;
                st.update(val , 1 , n , b , n_ , 1);
            }
            else{
                int ans_ = st.query(1 , n , b , c , 1);
                if(b>1){
                    ans_ -= st.query(1 , n , b-1 , b-1 , 1);
                }
                ans.pb(ans_>=0 ? ans_ : 0);
                //cout << ans_ << endl;
                //st.print_();
            }
        }
        for(auto x : ans){
            cout << x << endl;
        }

    }
    return 0;
}