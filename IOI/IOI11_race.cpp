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
#define INF 2e9+5
#define INF2 1e9+5
#define eps 1e-7
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
#define V 450
#define MAX_N 500000
using namespace std;
const int MOD = 1e9+7;
#include "race.h"
const int nax = 2e5+5;
const int nax2 = 1e6+5;
vii adj[nax];
bool vis[nax];
int K;
int sb[nax], cnt[nax2], ans = INF;
int dfs(int u, int p){
    sb[u] = 1;
    for(auto x : adj[u]){
        if(x.fi == p || vis[x.fi]) continue;
        sb[u] += dfs(x.fi,u);
    }
    return sb[u];
}
int getc(int u, int p, int ms){
    for(auto x : adj[u]){
        if(x.fi == p || vis[x.fi]) continue;
        if(sb[x.fi]*2 > ms)
            return getc(x.fi,u,ms);
    }
    return u;
}
void update(int u, int p, bool feel, int dep, int dist){
    if(dist > K) return;
    if(feel) cnt[dist] = min(cnt[dist],dep);
    else ans = min(ans, dep+cnt[K-dist]);
    for(auto x : adj[u]){
        if(x.fi == p || vis[x.fi]) continue;
        update(x.fi,u,feel,dep+1,dist+x.se);
    }
}
void del(int u, int p, int dist){
    if(dist > K) return;
    cnt[dist] = INF;
    for(auto x : adj[u]){
        if(x.fi == p || vis[x.fi]) continue;
        del(x.fi,u,dist+x.se);
    }
}
void centdec(int u){
    int c = getc(u,u,dfs(u,u));
    vis[c] = 1,cnt[0] = 0;
    for(auto x : adj[c]){
        if(vis[x.fi]) continue;
        update(x.fi,c,0,1,x.se);
        update(x.fi,c,1,1,x.se);
    }
    for(auto x : adj[c]){
        if(vis[x.fi]) continue;
        del(x.fi,c,x.se);
    }
    for(auto x : adj[c]){
        if(vis[x.fi]) continue;
        centdec(x.fi);
    }
}
int best_path(int n, int k, int h[][2], int s[])
{
    K = k;
    for (int i = 0; i < n-1; ++i)
    {
        adj[h[i][0]].pb({h[i][1],s[i]});
        adj[h[i][1]].pb({h[i][0],s[i]});
    }
    for (int i = 0; i <= k; ++i)
    {
        cnt[i] = INF;
    }
    centdec(0);
    if(ans >= INF2) return -1;
    else return ans;
}