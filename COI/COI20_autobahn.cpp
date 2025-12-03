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
#define MAX_A 2e5+5
using namespace std;
const int MOD = 1e4+7;
const int nax = 2e6+7;

typedef complex<int> Point;
#define X real()
#define Y imag()
ll n,x,ka;
ll  tot[nax], s[nax], e[nax], t[nax], cnt[nax],pref[nax];
ve<ll> ind;
void add(ll pos){
    ind.pb(pos);
    ind.pb(pos + x);
    ind.pb(pos - x);

}
int get(ll val){
    return lower_bound(ind.begin(), ind.end(), val) - ind.begin() + 1;
}
int main()
{
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    cin >> n >> ka >> x;
    ll res  = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> s[i] >> t[i] >> e[i];
        add(s[i]);
        add(e[i]+1);
        add(e[i]);
        add(s[i]+t[i]);
    }

    sort(ind.begin(), ind.end());
    ind.erase(unique(ind.begin(), ind.end()), ind.end());
    for (int i = 0; i < n; ++i)
    {
        int to = get(e[i] + 1);
        cnt[get(s[i])]++;
        cnt[to]--;
        tot[get(s[i]+t[i])]++;
        tot[to]--;
    }
    for (int i = 1; i < ind.size(); ++i)
    {
        cnt[i] += cnt[i-1];
        tot[i] += tot[i-1];
    }
    for (int i = 1; i < ind.size(); ++i)
    {
        pref[i] = pref[i-1];
        if(cnt[i-1] >= ka && i-2 >=0) pref[i] += (ind[i-1]-ind[i-2])*tot[i-1];
        //cout << i << " " << (ind[i-1]-ind[i-2]) << endl;
    }
    for (int i = 0; i < ind.size(); ++i)
    {
        int to = get(ind[i]+x);
        if(ind[to - 1] != ind[i] + x) continue;
        res = max(res, pref[to] - pref[i+1]);
    }
    cout << res << endl;
}