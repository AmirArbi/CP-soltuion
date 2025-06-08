#include <bits/stdc++.h>
#define vi vector<int>
#define ve vector
#define ll long long
#define vf vector<float>
#define vll vector<pair<ll,ll>>
#define ii pair<int,int>
#define pll pair<ll,ll>
#define vvi vector<vi>
#define vii vector<ii>
#define gii greater<ii>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF 1e18
#define eps 1e-7
#define eps1 1e-2
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 2e5+5
using namespace std;
int MOD = 1e9+7;
const int nax = 5e5+5;
const int nax2 = 200+5;
typedef complex<int> Point;
using cd = complex<double>;
const double PI = acos(-1);
#include"factories.h"
vii adj[nax];
bool vis[nax];
int sb[nax], par[nax];
ve<ll> dst[nax];
int dfs(int u, int p, bool type, ll cur){
    if(type){
        dst[u].pb(cur);
    }
    sb[u] = 1;
    for(auto x : adj[u]){
        if(x.fi == p || vis[x.fi]) continue;
        sb[u] += dfs(x.fi,u, type, cur+x.se);
    }
    return sb[u];
}
int getcent(int u, int p, int ms){
    for(auto x : adj[u]){
        if(vis[x.fi] || x.fi == p) continue;
        if(sb[x.fi]*2 > ms) return getcent(x.fi,u,ms);
    }
    return u;
}
void centdec(int u, int p){
    int c = getcent(u,u,dfs(u,u,0,0));
    dfs(c,c,1,0);
    vis[c] = 1, par[c] = p;
    for(auto x : adj[c]){
        if(vis[x.fi] || x .fi == p) continue;
        centdec(x.fi, c);
    }
}   
ll ans[nax];
void Init(int n, int a[], int b[], int d[]){
    for (int i = 0; i < n; ++i)
    {
        ans[i] = INF;
    }
    for (int i = 0; i < n-1; ++i)
    {
        adj[a[i]].pb({b[i], d[i]});
        adj[b[i]].pb({a[i], d[i]});
    }
    centdec(0,-1);
    for (int i = 0; i < n; ++i)
    {
        reverse(dst[i].begin(), dst[i].end());
    }
}
long long Query(int s, int x[], int t, int y[]){
    ll aff = INF;
    for (int i = 0; i < s; ++i)
    {
        int cur = x[i], cnt = 0;
        while(cur != -1){
            ans[cur] = min(ans[cur], dst[x[i]][cnt]);
            cur = par[cur], cnt++;
        }
    }
    for (int i = 0; i < t; ++i)
    {
        int cur = y[i], cnt = 0;
        while(cur != -1){
            aff = min(aff , ans[cur] + dst[y[i]][cnt]);
            cur = par[cur], cnt++;
        }
    }
    for (int i = 0; i < s; ++i)
    {
        int cur = x[i];
        while(cur != -1){
            ans[cur] = INF;
            cur = par[cur];
        }
    }
    return aff;
}

