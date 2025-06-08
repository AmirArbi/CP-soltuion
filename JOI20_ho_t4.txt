#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define INF 1e15
#define ve vector
#define vi ve<int>
#define ii pair<int,int>
#define vii ve<ii>
#define pb push_back
#define fi first
#define se second
#define ll long long
using namespace __gnu_pbds;
using namespace std;
const int nax = 1e4+5;
const int kax = 1e5+5;
const int MOD = 1e9+7;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
int x[kax], y[kax];
ll c[kax], d[kax]; 
int n,m;
vi adj[2][nax];
set<int> way1, way2;
ve<ll> dijkstra(int st, bool type, int del){
    ve<ll> dist(n+1, INF);
    ve<bool> vis(n+1,0);
    dist[st] = 0;
    vi par(n+1,-1);
    for(int k = 0; k < n; k++){
        int u = -1;
        for (int i = 1; i <= n; ++i)
        {
            if(!vis[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        if(dist[u] == INF) break;
        vis[u] = 1;
        for(auto j : adj[type][u]){
            if(j == del) continue;
            int to = y[j];
            if(type) to = x[j];
            if(dist[to] > (c[j] + dist[u])){
                dist[to] = c[j] + dist[u];
                par[to] = j;
            }
        }
        if(del != -1 && u == y[del] && dist[x[del]] > (c[del] + dist[u])){
            dist[x[del]] = c[del] + dist[u];
        }
    }
    if(way1.size() == 0){
        if(dist[n] == INF) way1.insert(-1);
        int u = n;
        while(par[u] != -1){
            way1.insert(par[u]);
            u = x[par[u]];
        }
    } else if(way2.size() == 0){
        if(dist[1] == INF) way2.insert(-1);
        int u = 1;
        while(par[u] != -1){
            way2.insert(par[u]);
            u = x[par[u]];
        }
    }
    return dist;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> x[i] >> y[i] >> c[i] >> d[i];
        adj[0][x[i]].pb(i);
        adj[1][y[i]].pb(i);
    }
    ve<ll>  dist1 = dijkstra(1, 0, -1), distn = dijkstra(n, 0, -1), distrev1 = dijkstra(1, 1, -1) , distrevn = dijkstra(n, 1, -1);
    ll aff = min(dist1[n] + distn[1], (ll)INF);
    for (int i = 0; i < m; ++i)
    {
        if(!way1.count(i) && !way2.count(i)){
            aff = min(aff, dist1[y[i]] + distrevn[x[i]] + distn[y[i]] + distrev1[x[i]] + 2*c[i] + d[i]);
            aff = min(aff, dist1[n] + distn[y[i]] + distrev1[x[i]] + c[i] + d[i]);
            aff = min(aff, dist1[y[i]] + distrevn[x[i]] + distn[1] + c[i] + d[i]);
        } else {
            ve<ll>  cur1 = dijkstra(1, 0, i), curn = dijkstra(n, 0, i);
            aff = min(aff, cur1[n] + curn[1] + d[i]);
        }
    }
    if(aff >= INF) cout << -1 << endl;
    else cout << aff << endl;
}