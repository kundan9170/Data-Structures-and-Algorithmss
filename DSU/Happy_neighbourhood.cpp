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

struct dsu{
    vector<int>parent;
    vector<int>size;
    dsu(int n){
        parent.resize(n , 0);
        size.resize(n , 0);
        for(int i = 0 ; i<n ; ++i){
            parent[i] = i;
            size[i] = 1;
        }
    }
    int find_parent(int v){
        if(v == parent[v]){
            return v;
        }
        return parent[v] = find_parent(parent[v]);
    }
    void union_set(int a , int b){
        a = find_parent(a);
        b = find_parent(b);
        if(a!=b){
            if(size[a] < size[b]){
                swap(a , b);
            }
            parent[b] = a;
            size[a]+= size[b];
        }
    }
    int r_size(int a){
        return size[a];
    }
};

int32_t main()
    {
    fastio
    int t;
    t  = 1;
    vector<int>ans;
    for(int j = 0 ; j<t; ++j){
        int n;int f;cin >> n >> f;
        vector<int>v(n,0);for(int i = 0 ; i<n ; ++i){cin >> v[i];v[i]--;}
        vector<int>house(n,0);
        dsu ds(n);
        for(int i = 0 ; i<n ; ++i){
            house[v[i]] = 1;
            if(v[i]+1<n && house[v[i]+1] == 1){
                ds.union_set(v[i] , v[i]+1);
            }
            if(v[i]-1>=0 && house[v[i]-1] == 1){
                ds.union_set(v[i] , v[i]-1);
            }
            if(ds.r_size(ds.find_parent(v[i])) >= f){
                cout << i+1 << endl;
                break;
            }
        }
    }
    return 0;

}
