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
#define mp make_pair
#define fi first
#define se second
#define INF 1e9
#define eps 1e-7
#define eps1 1e-2
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
using namespace std;
const int MOD = 1e4+7;
const int nax = 1e5+5;
#include <ext/pb_ds/assoc_container.hpp>
#define ook order_of_key
#define fbo find_by_order

using namespace __gnu_pbds;

typedef tree<pair<ll,int> ,null_type,less<pair<ll,int>>,rb_tree_tag,
tree_order_statistics_node_update> indexed_set;

typedef complex<int> Point;
#define X real()
#define Y imag()
int res = 0, a[nax], sb[nax], n;
vii adj[nax];
ll  st[4*nax];
bool vis[nax];
indexed_set cnt, cur[nax];
void up(int v, int tl, int tr, int l, int r, ll add) {
    if (l > r)
        return;
    if (l == tl && r == tr) {
        st[v] += add;
    } else {
        int tm = (tl + tr) / 2;
        up(v*2, tl, tm, l, min(r, tm), add);
        up(v*2+1, tm+1, tr, max(l, tm+1), r, add);
        st[v] = min(st[v*2], st[v*2+1]);
    }
}
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
void update(int u, int p, bool feel, ll fuel, ll mnfuel, int dep, int sbn){
    if(!feel){
        fuel += a[u];
        if(st[1]>=0){
            cnt.insert({fuel,u});
            res++;
            cur[sbn].insert({fuel,u});
        }
        fuel -= a[u];
    }
    else{
        if(mnfuel >= 0)
            res += cnt.size()-cur[sbn].size()+1;
        else{
            res+= cnt.size() - cnt.ook({-mnfuel,0});
            res-= cur[sbn].size() - cur[sbn].ook({-mnfuel,0});
        }
    }
    for(auto x : adj[u]){
        if(x.fi == p || vis[x.fi]) continue;
        if(!feel)
            up(1,0,n-1,0,dep,a[x.fi]-x.se);
        update(x.fi,u,feel, fuel-x.se+a[u] , min(fuel-x.se+a[u], mnfuel), dep+1, sbn);
        if(!feel)
            up(1,0,n-1,0,dep,-(a[x.fi]-x.se));
    }
}
void centdec(int u){
    int c = getc(u,u,dfs(u,u));
    vis[c] = 1;
    cnt.clear();
    int cc = 0;
    for(auto x : adj[c]){
        if(vis[x.fi]) continue;
        cur[cc].clear();
        up(1,0,n-1,0,0,a[x.fi]-x.se);
        update(x.fi,c,0,-x.se,-x.se,1, cc);
        up(1,0,n-1,0,0,-(a[x.fi]-x.se));
        cc++;
    }
    cc = 0;
    for(auto x : adj[c]){
        if(vis[x.fi]) continue;
        update(x.fi,c,1,a[c]-x.se,a[c]-x.se,1, cc);
        cc++;
    }
    for(auto x : adj[c]){
        if(vis[x.fi]) continue;
        centdec(x.fi);
    }
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n-1; ++i)
    {
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].pb({b,c});
        adj[b].pb({a,c});
    }
    centdec(1);
    cout << res << endl;
}