#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define INF 1e9
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
const int kax = 25+5;
#include<bits/stdc++.h>
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
int par[nax];
int findpar(int u){
    if(par[u] == u) return u;
    return par[u] = findpar(par[u]);
}
bool isSameSet(int u, int v){
    return (findpar(u) == findpar(v));
}
void unionSet(int u, int v){
    u = findpar(u), v = findpar(v);
    if(u == v) return;
    par[u] = v;
}
ll cross(ii a, ii b, ii c){
    return (b.fi-a.fi)*(c.se-b.se) - (c.fi-b.fi) * (b.se-a.se);
}   
vii cur;
ll curval;
int n,m, x[nax], y[nax], c[nax], t[nax];
ii MST(ve<ii> &edge){
    for (int i = 0; i < n; ++i)
    {
        par[i] = i;
    }
    sort(edge.begin(), edge.end());
    cur.clear();
    int smt = 0, smc = 0;
    for(auto v : edge){
        if(!isSameSet(x[v.se], y[v.se])){
            unionSet(x[v.se], y[v.se]);
            cur.pb({x[v.se], y[v.se]});
            smt += t[v.se], smc += c[v.se];
        }
    }
    curval = smt*1ll*smc;
    return {smt, smc};
}
int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> x[i] >> y[i] >> t[i] >> c[i];
    }
    ve<ii> edge;
    for(int i = 0; i < m; i++) edge.pb({t[i], i});
    ii a = MST(edge);
    vii ans = cur;
    ii aff = a;
    ll ansval = curval;
    edge.clear(); 
    for(int i = 0; i < m; i++) edge.pb({c[i], i});
    ii b = MST(edge);
    if(ansval > curval){
        ansval = curval;
        ans = cur;
        aff = b;
    }
    queue<pair<ii,ii>> bfs;
    bfs.push({a,b});
    while(!bfs.empty()){
        ii a = bfs.front().fi, b = bfs.front().se;
        bfs.pop();
        edge.clear(); 
        for(int i = 0; i < m; i++) edge.pb({c[i]*(b.fi-a.fi)-t[i]*(b.se-a.se), i});
        ii p = MST(edge);
        if(ansval > curval){
            ansval = curval;
            ans = cur;
            aff = p;
        }
        if(cross(a,b,p) >= 0) continue;
        bfs.push({a,p});
        bfs.push({p,b});
    }
    cout << aff.fi << " " << aff.se << endl;
    for(auto x : ans){
        cout << x.fi << " " << x.se << endl;
    }

}