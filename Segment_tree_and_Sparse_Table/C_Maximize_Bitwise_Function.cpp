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


// int N;
// int segment_tree_or[2*400000];
// int segment_tree_sum[2*400000];
// int pow_two;

// int query_or(int L , int R){
//     int ans = 0;
//     if(L == R)return segment_tree_or[L];
//     else{
//         ans|= segment_tree_or[L];
//         ans|= segment_tree_or[R];
//         while(L/2 != R/2){
//             if(!(L&1)){
//                 ans|= segment_tree_or[L+1];
//             }
//             if(R&1){
//                 ans|= segment_tree_or[R-1];
//             }
//             L = L/2;
//             R = R/2;
//         }
//     }
//     return ans;
// }

// int segment_tree_a[2*400000];

// int query_and(int L , int R){
//     int ans;
//     if(L == R) return segment_tree_a[L];
//     else{
//         ans= segment_tree_a[L];
//         ans&= segment_tree_a[R];
//         while(L/2 != R/2){
//             if(!(L&1)){
//                 ans&= segment_tree_a[L+1];
//             }
//             if(R&1){
//                 ans&= segment_tree_a[R-1];
//             }
//             L = L/2;
//             R = R/2;
//         }
//     }
//     return ans;
// }

// int query_sum(int L , int R){
//     int ans = 0;
//     if(L == R)return segment_tree_sum[L];
//     else{
//         ans+= segment_tree_sum[L];
//         ans+= segment_tree_sum[R];
//         while(L/2 != R/2){
//             if(!(L&1)){
//                 ans+= segment_tree_sum[L+1];
//                 //ans = ans%mod;
//             }
//             if(R&1){
//                 ans+= segment_tree_sum[R-1];
//                 //ans = ans%mod;
//             }
//             L = L/2;
//             R = R/2;
//         }
//     }
//     return ans;
// }

int log_(int x) {
    return 32 - __builtin_clz((int)x) - 1;
}


int sparse_table_or[4*100000][20];

int query_or(int L , int R){
    int len = R-L+1;
    int log = log_(len);
    int ans1 = sparse_table_or[L][log];
    int ans2 = sparse_table_or[R-(1<<log)+1][log];
    return ans1|ans2;
}

int sparse_table_a[4*100000][20];

int query_and(int L , int R){
    int len = R-L+1;
    int log = log_(len);
    int ans1 = sparse_table_a[L][log];
    int ans2 = sparse_table_a[R-(1<<log)+1][log];
    return ans1&ans2;
}

int32_t main()
    {
    fastio
    int t;
    cin >> t;
    for(int i = 0 ; i<t; ++i){
        int n , k;
        cin >> n;
        int a[n+1];
        int prefix_sum[n+1] = {0};
        for(int i = 1 ; i<=n ; ++i){
            cin >> a[i];
            prefix_sum[i] = a[i]+prefix_sum[i-1];
        }
        cin >> k;
        

        // int cnt = 0;
        // pow_two = ceil(log2(n));
        // pow_two = 1<<pow_two;
        // for(int i = pow_two ; i<=2*pow_two-1 ; ++i){
        //     if(cnt<n){
        //         segment_tree_or[i] = a[cnt+1];
        //         segment_tree_a[i] = a[cnt+1];
        //         //segment_tree_sum[i] = a[cnt+1];
        //         cnt++;
        //     }
        //     else{
        //         segment_tree_or[i] = 0;
        //         segment_tree_a[i] = ((((int)1)<<50)-1);
        //         //segment_tree_sum[i] = 0;
        //     }
        // }
        // for(int i = 2*pow_two-2 ; i>=2 ; i-=2){
        //     segment_tree_or[i/2] = segment_tree_or[i]|segment_tree_or[i+1];
        //     segment_tree_a[i/2] = segment_tree_a[i]&segment_tree_a[i+1];
        //     //segment_tree_sum[i/2] = (segment_tree_sum[i]+segment_tree_sum[i+1]);
        // }
        int log = log_(n);
        for(int i = 1 ; i<=n ; ++i){
            sparse_table_or[i][0] = a[i];
            sparse_table_a[i][0] = a[i];
        }

        for(int j = 1 ; j<=log ; ++j){
            for(int i = 1 ; i + (1<<j)-1 <=n ; ++i){
                sparse_table_or[i][j] = sparse_table_or[i][j-1]|sparse_table_or[i + (1<<(j-1))][j-1];
                sparse_table_a[i][j] = sparse_table_a[i][j-1]&sparse_table_a[i + (1<<(j-1))][j-1];
            }
        }

        int max_ = 0;
        for(int i = 1 ; i<=n ; ++i){
            if(a[i]<k){
                continue;
            }
            int L = i;
            int R = n+1;
            while(R>L+1){
                int mid = (L+R)/2;
                if(query_and(i , mid)>=k){
                    L = mid;
                }
                else{
                    R = mid;
                }
            }
            int ans_or = query_or(i , L);
            int ans_sum = prefix_sum[L]-prefix_sum[i-1];
            max_ = max(max_ , ans_or+ans_sum);
        }
        cout << (max_%mod) << endl;
    }
    return 0;
}