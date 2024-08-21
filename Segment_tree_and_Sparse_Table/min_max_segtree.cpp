struct seg_tree{
    int N;
    int pow_two;
    vector<pii>tree_max;
    vector<pii>tree_min;
    seg_tree(int n , vector<int>&v){
        N = n;
        pow_two = ceil(log2(n));
        pow_two = (1<<pow_two);
        tree_max.resize(4*pow_two+1);
        tree_min.resize(4*pow_two+1);
        int cnt = 0;
        for(int i = pow_two ; i<=2*pow_two-1 ; ++i){
            if(cnt <n){
                tree_max[i] = {v[cnt+1],i-pow_two+1};
                tree_min[i] = {v[cnt+1],i-pow_two+1};
                cnt++;
            }
            else{
                tree_max[i] = {n_INF,i-pow_two+1};
                tree_min[i] = {INF,i-pow_two+1};
            }
        }
        for(int i = 2*pow_two-2 ; i>1 ; i-=2){
            tree_max[i/2] = tree_max[i].ff >= tree_max[i+1].ff ? tree_max[i] : tree_max[i+1];
            tree_min[i/2] = tree_min[i].ff <= tree_min[i+1].ff ? tree_min[i] : tree_min[i+1];
        }
    }
    void update_max(int l){
        int L = pow_two+l-1;
        tree_max[L] = {n_INF , l};
        while(L>1){
            L = L/2;
            tree_max[L] = tree_max[2*L].ff >= tree_max[2*L+1].ff ? tree_max[2*L] : tree_max[2*L+1];
        }
    }
    void update_min(int l){
        int L = pow_two+l-1;
        tree_min[L] = {INF , l};
        while(L>1){
            L = L/2;
            tree_min[L] = tree_min[2*L].ff <= tree_min[2*L+1].ff ? tree_min[2*L] : tree_min[2*L+1];
        }
    }
    pii query_max(int l , int r){
        int L = l + pow_two-1;
        int R = r + pow_two-1;
        if(L == R) return tree_max[L];
        else{
            pii max_ = {n_INF , -1};
            max_ = tree_max[L].ff >= tree_max[R].ff ? tree_max[L] : tree_max[R];
            while(L/2 != R/2){
                if(!(L&1)){
                    if(tree_max[L+1].ff > max_.ff) max_ = tree_max[L+1];
                    else if(tree_max[L+1].ff == max_.ff)max_.ss = min(max_.ss , tree_max[L+1].ss);
                }
                if(R&1){
                    if(tree_max[R-1].ff > max_.ff)max_ = tree_max[R-1];
                    else if(tree_max[R-1].ff == max_.ff)max_.ss = min(max_.ss , tree_max[R-1].ss);
                }
                L = L/2;
                R = R/2;
            }
            return max_;
        }
    }
    pii query_min(int l , int r){
        int L = l + pow_two-1;
        int R = r + pow_two-1;
        if(L == R) return tree_min[L];
        else{
            pii min_ = {INF , -1};
            min_ = tree_min[L].ff <= tree_min[R].ff ? tree_min[L] : tree_min[R];
            while(L/2 != R/2){
                if(!(L&1)){
                    if(tree_min[L+1].ff < min_.ff) min_ = tree_min[L+1];
                    else if(tree_min[L+1].ff == min_.ff)min_.ss = min(min_.ss , tree_min[L+1].ss);
                }
                if(R&1){
                    if(tree_min[R-1].ff < min_.ff)min_ = tree_min[R-1];
                    else if(tree_min[R-1].ff == min_.ff)min_.ss = min(min_.ss , tree_min[R-1].ss);
                }
                L = L/2;
                R = R/2;
            }
            return min_;
        }
    }
    
};
