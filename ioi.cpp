    /* 
     * let mx(i)  the farthest node from i in the tree , center of the tree is the node which has the smallest mx(node)
     * find the centers of the trees , put an edge between the centers and the center which has the maximum mx(node) 
     * return the diameter of the new tree
    */
    #define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
    #include <bits/stdc++.h>
    using namespace std;
    #define sqr 547
    #define mid (l+r)/2
    #define pb push_back
    #define ppb pop_back
    #define fi first
    #define se second
    #define lb lower_bound
    #define ub upper_bound
    #define ins insert
    #define era erase
    #define C continue
    #define mem(dp,i) memset(dp,i,sizeof(dp))
    #define mset multiset
    typedef long long ll;
    typedef short int si;
    typedef long double ld;
    typedef pair<int,int> pi;
    typedef pair<ll,ll> pll;
    typedef vector<int> vi;
    typedef vector<ll> vll;
    typedef vector<pi> vpi;
    typedef vector<pll> vpll;
    const ll inf=1e18;
    const ld pai=acos(-1);
    #include "dreaming.h"
    int n , m ;
    vpi v[100009] , trees;
    int done[100009];
    int dpdn[100009] , dpup[100009] ;
    vi nodes;
    void who ( int node , int p ) {
            done [ node ] = 1 ;
            nodes.pb ( node ) ;
            for ( auto u : v [ node ] ) {
                    if ( u.fi == p ) C ;
                    who ( u.fi , node ) ;
            }
    }
    void dfsdn ( int node , int p ) {
            for ( auto u : v[node] ) {
                    if ( u.fi == p ) C ;
                    dfsdn ( u.fi , node ) ;
                    dpdn[node] = max ( dpdn[node] , dpdn[u.fi] + u.se ) ;
            }
    }
    void dfsup ( int node , int p ) {
            pi mx1 , mx2 ;
            mx1 = mx2 = { -1 , -1 } ;
            for ( auto U : v[node] ) {
                    int u = U.fi ;
                    int x = U.se ;
                    if ( u == p ) C ;
                    pi ret = { dpdn[u] + x , u } ;
                    if ( ret.fi > mx1.fi ) {
                            swap ( mx1 , mx2 ) ;
                            mx1 = ret ;
                    }
                    else mx2 = max ( mx2 , ret ) ;
            }
            for ( auto U : v[node] ) {
                    int u = U.fi ;
                    int x = U.se ;
                    if ( u == p ) C ;
                    int MX= dpup[node];
                    if ( mx1.se != u ) MX = max ( MX , mx1.fi ) ;
                    else MX = max ( MX , mx2.fi ) ;
                    dpup[u] = MX + x ;
                    dfsup( u , node ) ;
            }
    }
    void fill ( int node ) {
            nodes.clear() ;
            who ( node , node ) ;
            for ( auto u : nodes ) dpdn[u] = dpup[u] = 0 ;
            dfsdn ( node , node ) ;
            dfsup ( node , node ) ;
    }
    int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
            n = N , m = M ;
            for ( int i = 0 ; i < m ; i ++ ) {
                    int a = A[i] ;
                    int b = B[i] ;
                    int c = T[i] ;
                    v[a].pb ( { b , c } ) ;
                    v[b].pb ( { a , c } ) ;
            }
            for ( int i = 0 ; i < n ; i ++ ) {
                    if ( done [i] ) C ;
                    fill ( i ) ;
                    pi mn = { 1e9 , 1e9 } ;
                    for ( auto u : nodes ) {
                            mn = min ( mn , { max ( dpdn[u] , dpup[u] ) , u } ) ;
                    }
                    trees .pb ( mn ) ;
            }
            sort ( trees.begin() , trees.end() ) ;
            for ( int i = 0 ; i < (int)trees.size() - 1 ; i ++ ) {
                    int a = trees[i].se;
                    int b = trees.back().se;
                    v[a] .pb ( { b , L } ) ;
                    v[b] .pb ( { a , L } ) ;
            }
            fill ( 0 ) ;
            int mx = 0 ;
            for ( auto u : nodes ) mx = max ( mx , dpdn[u] + dpup[u] ) ;
            return mx ;
    }
