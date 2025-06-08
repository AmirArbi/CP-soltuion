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
const int nax = 2e5+5;
const int kax = 25+5;
const int MOD = 1e9+7;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
int main() {
    int n,q;
    ll s,t;
    cin >> n >> q >> s >> t;
    ve<ll> st(n+1), cur(n+1);
    ll ans = 0;
    for (int i = 0; i <= n; ++i)
    {
        cin >> cur[i];
        st[i] = cur[i];
        if(i) st[i] -= cur[i-1];
        if(st[i]<0) ans += -st[i]*t;
        else ans += -st[i]*s;
    }
    while(q--){
        int l,r;
        ll x;
        cin >> l >> r >> x;
        if(st[l] < 0) ans += st[l]*1ll*t;
        else ans += st[l]*1ll*s;
        st[l] += x;
        if(st[l] < 0) ans -= st[l]*1ll*t;
        else ans -= st[l]*1ll*s;
        if(r != n){
            if(st[r+1] < 0) ans += st[r+1]*1ll*t;
            else ans += st[r+1]*1ll*s;
            st[r+1] -= x;
            if(st[r+1] < 0) ans -= st[r+1]*1ll*t;
            else ans -= st[r+1]*1ll*s;
        }
        cout << ans << endl;
    }
}
