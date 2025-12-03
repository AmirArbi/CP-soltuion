#include <bits/stdc++.h>
#define vi vector<int>
#define ve vector
#define ll long long
#define vf vector<float>
#define vll vector<pair<ll,ll>>
#define ii pair<int,int>
#define vvi vector<vi>
#define vii vector<ii>
#define gii greater<ii>
#define pb push_back
#define fi first
#define se second
#define INF 1e9
#define eps 1e-7
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
#define V 450
using namespace std;
const int MOD = 1e9+7;
const int nax = 100005;
vi adj[nax];
ll dp[nax][2][2][2][2];
int rt,sn;
int p[nax], par[nax];
int getp(int x){
    if(p[x] == x) return x;
    else return p[x] = getp(p[x]);
}
void dfs(int u, int p){
    par[u] = p;
    for(auto x : adj[u]){
        if(x == p) continue;
        dfs(x,u);
    } 
}
ll srch(int u, bool cme, bool cp, bool crt, bool csn){
    if(dp[u][cme][cp][crt][csn] != -1) return dp[u][cme][cp][crt][csn] ;
    bool nvalid = false;
    if(u == sn && cp && crt) nvalid = true;
    if(u == sn && csn != cme) nvalid = true; 
    if(u== rt && crt != cme) nvalid = true;
    if(nvalid) return dp[u][cme][cp][crt][csn] = INF;
    ll res = INF;
    bool c = false;
    if(cp) c = true;
    if(u==sn && crt) c = true;
    if(u == rt && csn) c = true;
    ll sum = cme;    
    for(auto x : adj[u])
    {
        if(x == par[u]) continue;
        sum += srch(x,0,cme,crt,csn);
    }
    if(c){
        res = min(res,sum);
    } else {
        for(auto x : adj[u]){
            if(x == par[u]) continue;
            ll v = sum + srch(x,1,cme,crt,csn) - srch(x,0,cme,crt,csn);
            res = min(res,v);
        }
    }
    return dp[u][cme][cp][crt][csn] = res;
}
int main() {
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        p[i] = i;
    for (int i = 0; i < n; ++i)
    {
        int a,b;
        cin >> a >> b;
        a--,b--;
        int pa = getp(a),pb = getp(b);
        if(pa == pb){
            rt = a,sn = b;
        } else {
            p[pb] = pa;
            adj[a].pb(b);
            adj[b].pb(a);
        }
    }
    dfs(rt,-1);
    memset(dp, -1, sizeof dp);
    ll res = INF;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            res = min(res,srch(rt,i,0,i,j));
        }
    }
    if(res == INF) cout << -1  << endl;
    else cout << res << endl;
}