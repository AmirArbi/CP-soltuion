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
#define INF 1e9+5
#define eps 1e-4
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
using namespace std;
const int MOD = 1e9+7;
const int nax = 200005;
vi s[nax],g[nax];
int st[nax*4],l[nax],r[nax];
ii qu[nax];
void update(int v, int l, int r, int i){
    if(r < i || l > i) return;
    if(l == r) {
        st[v]++;
        return;
    }
    int md = (l+r)/2;
    update(v*2,l,md,i);
    update(v*2+1,md+1,r,i);
    st[v] = st[v*2]+st[v*2+1];
}
int query(int v, int l, int r, int i, int j){
    //cout << l << " " << r << endl;
    if(r < i || l > j) return 0;
    if(i <= l && r <= j) return st[v];
    int md = (l+r)/2;
    return query(v*2,l,md,i,j) + query(v*2+1,md+1,r,i,j);
}
int main(){
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int n,q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
    {
        int a;
        cin >> a;
        s[a].pb(i);
    }
    for (int i = 0; i < q; ++i)
    {
        cin >> qu[i].fi >> qu[i].se;
        qu[i].fi--, qu[i].se--;
        l[i] = 1, r[i] = n;
    }
    while(1){
        memset(st,0,sizeof st);
        bool flag = 0;
        for (int i = 0; i < q; ++i)
        {
            if(l[i] <= r[i]){
                flag = 1;
                int md = (l[i]+r[i])/2;
                g[md].pb(i);
            } 
        }  
        if(!flag) break;
        for (int i = nax-1; i >= 1; i--)
        {
            for(auto x : s[i]) update(1,0,n-1,x);
            for(auto x : g[i]){
                if(query(1,0,n-1,qu[x].fi,qu[x].se) >= i) l[x] = i+1;
                else r[x] = i-1; 
            }
            g[i].clear();
        }
    }
    for (int i = 0; i < q; ++i)
    {
        cout << r[i] << endl;
    }
}