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
#define INF 1e9
#define eps 1e-7
#define eps1 1e-2
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 2e5+5
using namespace std;
int MOD = 1e9+7;
const int nax = 5e5+5;
const int nax2 = 200+5;
typedef complex<int> Point;
#define X real()
#define Y imag()
using cd = complex<double>;
const double PI = acos(-1);
pair<pll,ll> st[nax*4];
bool cmp(const pair<ii,int>& x, const pair<ii,int>& y) { return x > y; }
pair<pll,ll> combine(pair<pll,ll> a, pair<pll,ll> b){
    return {{max(a.fi.fi,b.fi.fi), max(a.fi.se, b.fi.se)} , max(a.se, max(b.se, a.fi.fi+b.fi.se) ) } ;
}
pair<pll,ll> qry(int v, int l, int r, int i, int j){
    if(r < i || l > j) return {{0,0},0};
    if(i <= l && r <= j) return st[v];
    int md = (l+r)/2;
    return combine(qry(v*2, l, md, i, j), qry(v*2+1, md+1, r, i, j));
}
void update(int v, int l, int r, int pos, ll val, bool type){
    if(pos < l || r < pos) return;
    if(l == r){
        if(type) st[v].fi.se = max(val, st[v].fi.se);
        else st[v].fi.fi = max(val, st[v].fi.fi);
        st[v].se = st[v].fi.fi+st[v].fi.se;
        return;
    }
    int md = (l+r)/2;
    update(v*2, l, md, pos, val, type);
    update(v*2+1, md+1, r, pos, val, type);
    st[v] = combine(st[v*2], st[v*2+1]);
}
int main(){ 
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    vi s(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> s[i];
    }
    stack<ii> st;
    vii rng;
    for (int i = 0; i < n; ++i)
    {
        while(!st.empty() && st.top().fi < s[i]) st.pop();
        if(!st.empty()) rng.pb({st.top().se, i});
        st.push({s[i],i});
    }
    while(!st.empty()) st.pop();
    for (int i = n-1; i >= 0; --i)
    {
        while(!st.empty() && st.top().fi < s[i]) st.pop();
        if(!st.empty()) rng.pb({i,st.top().se});
        st.push({s[i],i});
    }
    sort(rng.begin(), rng.end(), greater<ii>());
    int q;
    cin >> q;
    ve<pair<ii,int>> query;
    int cnt = 0;
    while(q--){
        int a,b;
        cin >> a >> b;
        a--,b--;
        query.pb({{a,b},cnt});
        cnt++;
    }
    sort(query.begin(), query.end(), cmp);
    for (int i = 0; i < n; ++i)
    {
        update(1,0,n-1,i,s[i],1);
    }
    ve<ll> ans(cnt);
    q = cnt;
    cnt = 0;
    for (int i = 0; i < q; ++i)
    {
        int x = query[i].fi.fi, y = query[i].fi.se, ind = query[i].se;
        while(cnt < rng.size() &&  rng[cnt].fi >= x){
            int a = rng[cnt].fi, b = rng[cnt].se;
            update(1,0,n-1, b+(b-a) , s[a]+s[b] ,0);
            cnt++;
        }
        ans[ind] = qry(1, 0, n-1, x, y).se;
    }
    for(auto x : ans) cout << x << endl;
}