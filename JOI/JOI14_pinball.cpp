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
const int nax = 3e5+5;
const int nax2 = 200+5;
typedef complex<int> Point;
using cd = complex<double>;
const double PI = acos(-1);
ll m,n;
ll a[nax], b[nax], c[nax], d[nax], dp[nax], dp2[nax], st[nax*4];
ll query(int v, int l, int r, int i, int j){
    if(r < i || j < l) return INF;
    if(i <= l && r <= j) return st[v];
    int md = (l+r)/2;
    return min(query(v*2, l, md, i, j), query(v*2+1, md+1, r, i, j)); 
}
void update(int v, int l, int r, int pos, ll val){
    if(pos < l || r < pos) return;
    if(l == r) {
        st[v] = min(val, st[v]);
        return;
    }
    int md = (l+r)/2;
    update(v*2, l, md, pos, val);
    update(v*2+1, md+1, r, pos, val);
    st[v] = min(st[v*2], st[v*2+1]);
}
vi cc;
int gt(int x){
    return lower_bound(cc.begin(), cc.end(), x)-cc.begin();
}
int main(){ 
    optimise;
    cin >> m >> n;
    for (int i = 0; i < m; ++i)
    {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        cc.pb(a[i]);
        cc.pb(b[i]);
        cc.pb(c[i]);
    }
    sort(cc.begin(), cc.end());
    cc.resize(distance(cc.begin(), unique(cc.begin(), cc.end())));
    int sz = cc.size();
    c[m] = 1;
    memset(dp,-1, sizeof dp);
    memset(dp2,-1, sizeof dp2);
    for (int i = 0; i < sz*4; ++i)
    {
        st[i] = INF;
    }
    ll cur = INF;
    dp[m] = INF;
    for (int j = 0; j < m; ++j)
    {
        dp2[j] = INF;
        if(b[j] == n) dp2[j] = d[j]; 
        dp2[j] = min(dp2[j], query(1, 0, sz-1, 0, gt(b[j]))+d[j]);
        update(1, 0, sz-1, gt(c[j]), dp2[j]);
    }
    for (int i = 0; i < sz*4; ++i)
    {
        st[i] = INF;
    }
    for (int j = m-1; j >= 0; --j)
    {
        dp[j] = INF;
        if(b[j] == n) dp[j] = d[j]; 
        dp[j] = min(dp[j], dp2[j]);
        dp[j] = min(dp[j], query(1, 0, sz-1, 0, gt(c[j]))+d[j]);
        update(1, 0, sz-1, gt(a[j]), dp[j]);
        if(a[j] == 1){
            cur = min(cur,dp[j]);
        }
    }
    if(cur == INF) cout << -1 << endl;
    else cout << cur << endl;
}