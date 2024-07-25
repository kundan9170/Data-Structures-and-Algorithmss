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

int n_c_k(int n , int k){
    if(k>n) return 0;
    int sum_ = 1;
    for(int i = n-k+1 ; i<=n ; ++i){
        sum_*=i;
    }
    for(int i = 1 ; i<=k ; ++i){
        sum_/=i;
    }
    return sum_;
}

int digit_dp(int d , int cnt  ,string s){
    int n = s.size();
    vector<vector<vector<int>>>dp(n+1 , vector<vector<int>>(2 , vector<int>(cnt+1 , 0)));
    dp[n][0][0] = 1; dp[n][1][0] = 1;
    for(int i = n-1 ; i>=0 ; --i){
        for(int tight = 0 ; tight<2 ; ++tight){
            for(int c = 0 ; c<=cnt ; ++c){
                if(!tight){
                    dp[i][0][c]+= 9*dp[i+1][0][c];
                    if(c>0){
                        dp[i][0][c]+= dp[i+1][0][c-1];
                    }
                }
                else{
                    if(s[i]-'0'<d){
                        for(int digit = 0 ; digit<=s[i]-'0' ; ++digit){
                            dp[i][1][c]+= (digit == s[i]-'0') ? dp[i+1][1][c] : dp[i+1][0][c];
                        }
                    }
                    else{
                        for(int digit = 0 ; digit<=s[i]-'0' ; ++digit){
                            if(digit != d)
                                dp[i][1][c]+= (digit == s[i]-'0') ? dp[i+1][1][c] : dp[i+1][0][c];
                            else{
                                if(c>0)
                                dp[i][1][c]+= (digit == s[i]-'0') ? dp[i+1][1][c-1] : dp[i+1][0][c-1];
                            }
                        }
                    }
                }
            }
        }
    }
    return dp[0][1][cnt];
}

string i_to_s(int n){
    string s;
    while(n!=0){
        s+= n%10+'0';
        n/=10;
    }
    reverse(s.begin() , s.end());
    return s;
}

int s_to_i(string s){
    reverse(s.begin() , s.end());
    int ans_ = 0;
    for(int i = 0 ; i<s.size() ; ++i){
        int l = s[i]-'0';
        for(int j = 0 ; j<i ; ++j){
            l*=10;
        }
        ans_+= l;
    }
    return ans_;
}

int32_t main()
    {
    fastio
    int t;
    cin >> t;
    vector<int>ans;
    for(int i = 0 ; i<t; ++i){
        string low , high; int d , cnt ; cin >> low >> high >> d >> cnt;
        low = i_to_s(s_to_i(low)-1>0 ? s_to_i(low)-1 : 0);
        cout << digit_dp(d , cnt , high) - digit_dp(d , cnt , low) << endl;

    }
    return 0;
}
