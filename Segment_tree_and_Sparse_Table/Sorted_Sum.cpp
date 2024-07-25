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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count()); // call rnd() to get random 64bit int
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

bool compare(pii a , pii b){
    if(a.ff != b.ff) return a.ff < b.ff;
    else{
        return a.ss < b.ss;
    }
}


struct seg_tree{
    int N;
    int pow_two;
    vector<int>tree;
    seg_tree(int n){
        N = n;
        pow_two = ceil(log2(n));
        pow_two = (1<<pow_two);
        tree.resize(4*pow_two+1 , 0);
    }
    void update(int l , int val){
        int L = l+pow_two-1;
        tree[L]+=val;
        while(L>1){
            if(L&1)
            tree[L/2] = tree[L] + tree[L-1];
            else{
                tree[L/2] = tree[L] + tree[L+1];
            }
            L = L/2;
        }
    }
   

    int query(int l , int r){
        if(l>r) return 0;
        int L = l + pow_two -1;
        int R = r + pow_two -1;
        if(L == R) return tree[L];
        else{
            int sum_ = 0;
            sum_+= tree[L]; sum_ += tree[R];
            while(L/2 != R/2){
                if(!(L&1)){
                    sum_+= tree[L+1];
                }
                if(R&1){
                    sum_+= tree[R-1];
                }
                L = L/2;
                R = R/2;
            }
            return sum_;
        }
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
        int n;cin >> n ;vector<int>num(n+1 , 0);for(int i =1 ; i<=n ; ++i){cin >> num[i];}
        vector<pii>v(n , {0 , 0}); for(int i = 0 ; i<n ; ++i){v[i].ff = num[i+1] ; v[i].ss = i+1;}
        sort(v.begin() , v.end() , compare);
        vector<int>idx_mp(n+1 , 0); for(int i = 0 ; i<n ; ++i){ idx_mp[v[i].ss] = i+1;}
        ordered_set idx;
        seg_tree st(n);
        st.update(idx_mp[1] , num[1]);
        int last = num[1];
        int sum_ = last;
        int max_ = idx_mp[1];
        idx.insert(max_);
        for(int i = 2 ; i<=n ; ++i){
            int j = idx_mp[i];
            int mul = idx.order_of_key(j);
            idx.insert(j);
            last+= num[i]*(mul+1);
            st.update(j , num[i]);
            last+= st.query(j+1 , n);
            last%=mod;
            //max_ = max(max_ , j);
            sum_+= last;
            sum_%=mod;
        }
        cout << sum_%mod << endl;
    }
    return 0;
}
