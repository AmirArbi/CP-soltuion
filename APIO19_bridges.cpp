#include <bits/stdc++.h>
#define vi vector<int>
#define gi greater<int>
#define gr greater
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
const int MOD = 1e9+7;
const int nax = 1e5+5;
const int nax2 = 5e4+5;
typedef complex<int> Point;
#define X real()
#define Y imag()
const int batch = 1000;
int x[nax], y[nax], w[nax], t[nax], b[nax], r[nax];
int sz[nax], par[nax], ans[nax];
vi un[batch];
stack<int> st;
bool changed[nax];
int findpar(int u){
    if(par[u] == u) return u;
    return u = findpar(par[u]);
}
bool isSameSet(int u, int v){
    return (findpar(u) == findpar(v));
}
void unionSet(int u, int v){
    u = findpar(u), v = findpar(v);
    if(u == v) return;
    if(sz[u] > sz[v]) swap(u,v);
    st.push(u);
    sz[v] += sz[u];
    par[u] = v; 
}
void rollback(int steps){
    while(st.size() > steps){
        int cur = st.top();
        sz[par[cur]] -= sz[cur];
        par[cur] = cur;
        st.pop();
    }
}
bool cmp(int a, int b){
    return r[a] > r[b];
}
bool cmp2(int a, int b){
    return w[a] > w[b];
}
int main(){
    optimise;
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) cin >> x[i] >> y[i] >> w[i];
    int q; cin >> q;
    for(int i = 0; i < q; i++) cin >> t[i] >> b[i] >> r[i];
    for(int l = 0; l < q; l += batch){
        int rg = min(q, l+batch);
        memset(changed, 0, sizeof changed);
        for(int i = 0; i < nax2; i++) sz[i] = 1, par[i] = i;
        vi ask, update, unchanged;
        for (int i = l; i < rg; ++i)
        {
            if(t[i] == 1){
                changed[b[i]] = 1;
                update.pb(i);
            } else ask.pb(i);
        }
        for(int i = 1; i <= m; i++) if(!changed[i]) unchanged.pb(i);
        sort(ask.begin(), ask.end(), cmp);
        sort(unchanged.begin(), unchanged.end(), cmp2);
        for (int i = l; i < rg; ++i)
        {
            if(t[i] == 1) {
                w[b[i]] = r[i];
            } else {
                un[i-l].clear();
                for(auto j : update) if(w[b[j]] >= r[i]) un[i-l].pb(b[j]);
            }
        }
        int cnt = 0;
        for(auto j : ask){
            while(cnt < unchanged.size() && r[j] <= w[unchanged[cnt]]) 
            {
                unionSet(x[unchanged[cnt]], y[unchanged[cnt]]);
                cnt++;
            }
            int prv = st.size();
            for(auto i : un[j-l]) unionSet(x[i], y[i]);
            ans[j] = sz[findpar(b[j])];
            rollback(prv);
        }
    }
    for(int i = 0; i <q ; i++) if(t[i] == 2) cout << ans[i] << endl;
}
