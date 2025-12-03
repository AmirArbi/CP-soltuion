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
#define INF 1e18
#define eps 1e-7
#define eps1 1e-2
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
#define V 450
using namespace std;
const int MOD = 1e9+7;
const int nax = 2e5+5;
const int nax2 = 25;

typedef complex<int> Point;
#define X real()
#define Y imag()
int n,m,k;
vi adj[nax];
int d[nax], w[nax], sb[nax], pos[nax], cnt;
map<int,ll>  s[nax];
map<int,ll> ::iterator it,its,ite;
void dfs(int u){
    sb[u] = 1;
    for(auto x : adj[u]){
        dfs(x);
        sb[u] += sb[x];
        if(sb[x] > sb[pos[u]])
            pos[u] = x;
    }
    pos[u] = pos[pos[u]];
    if(adj[u].size() == 0) 
        pos[u] = ++cnt;
    for(auto y : adj[u]){
        int p = pos[y];
        if(p != pos[u]){
            for(auto x : s[p]){
                s[pos[u]][x.fi] += x.se;
            }
        }
    }
    if(d[u] != 0){
        s[pos[u]][d[u]] += w[u];
        ll sm = 0;
        it = s[pos[u]].upper_bound(d[u]);
        its = it;
        while(it != s[pos[u]].end() && sm + (it -> se) <= w[u]){
            sm += (it -> se);
            it++;
            ite = it;
        }
        if(it != s[pos[u]].end())
            it -> se += sm - w[u];
        if(it != its){
            s[pos[u]].erase(its,ite);
        }
    } 
}
int main()
{
    optimise; 
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    cin >> n >> m >> k;
    for (int i = 2; i <= n; ++i)
    {
        int a;
        cin >> a;
        adj[a].pb(i);        
    }
    for (int i = 0; i < m; ++i)
    {
        int a;
        cin >> a;
        cin >> d[a] >> w[a];
    }
    dfs(1);
    ll ans = 0;
    for(auto x : s[pos[1]])
        ans += x.se;
    cout << ans << endl;
}