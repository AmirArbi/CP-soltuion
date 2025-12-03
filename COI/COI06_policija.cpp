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
#define INF 1e8
#define eps 1e-7
#define eps1 1e-2
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
using namespace std;
const int MOD = 1e9+7;
const int nax = 1e5+5;
typedef complex<int> Point;
#define X real()
#define Y imag()
vi adj[nax];
bool vis[nax];
int tin[nax], tout[nax], par[nax], dep[nax], low[nax], cnt = 0, dp[nax][35];
void dfs(int u, int p){
    tin[u] = low[u] = cnt++;
    par[u] = p;
    vis[u] = 1;
    for(auto x : adj[u])
    {
        if(x == p) continue;
        if(vis[x]){
            low[u] = min(low[u], tin[x]);
        } else {
            dep[x] = dep[u]+1;
            dfs(x,u);
            low[u] = min(low[u], low[x]);
        }
    }
    tout[u] = cnt;
}
bool desc(int u, int v){
    return (tin[u] >= tin[v] && tout[u] <= tout[v]);
}
int find_par(int u, int d){
    int ps = 31;
    while(d){
        if(d - (1 << ps) >= 0){
            u = dp[u][ps];
            d-=(1 << ps);
        }
        ps--;
    }
    return u;
}
int main()
{
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    int n,e;
    cin >> n >> e;
    for (int i = 0; i < e; ++i)
    {
        int a,b;
        cin >> a >> b;
        a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dep[0] = 1;
    dfs(0,0);
    for (int i = 0; i < n; ++i)
    {
        dp[i][0] = par[i];
    }
    for (int i = 1; (1 << i) < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            dp[j][i] = dp[dp[j][i-1]][i-1]; 
        }
    }
    int q;
    cin >> q;
    while(q--){
        int type, a,b,c;
        cin >> type >> a >> b >> c;
        a--,b--,c--;
        if(type == 1){
            int d;
            cin >> d;
            d--;
            if(desc(d,c)) swap(d,c);
            if(desc(a,c) ==desc(b,c) || tin[d] >= low[c]) cout << "yes" << endl;
            else cout << "no" << endl; 
        } else {
            int p1 = find_par(a,dep[a]-dep[c]-1);
            int p2 = find_par(b,dep[b]-dep[c]-1);
            if(desc(a,c) && desc(b,c)){
                if(p1 == p2 || (tin[c] > low[p1] && tin[c] > low[p2]))
                    cout << "yes" << endl;
                else
                    cout << "no" << endl;
            } else if(!desc(a,c) && !desc(b,c)){
                cout << "yes" << endl;
            } else if((desc(a,c) && tin[c] > low[p1]) || (desc(b,c) && tin[c] > low[p2])) {
                cout << "yes" << endl;
            } else {
                cout << "no" << endl;
            }
        }
    }
}