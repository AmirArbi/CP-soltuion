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
using namespace std;
const int MOD = 1e4+7;
const int nax = 1e5+5;

typedef complex<int> Point;
#define X real()
#define Y imag()
int pnts[nax], ns[nax];
vi solved[nax];
ve<pair<ii,int>> sb;
int main()
{
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    int n,t,p;
    cin >> n >> t >> p;
    p--;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            int a;
            cin >> a;
            if(a == 0) pnts[j]++;
            else ns[i]++, solved[i].pb(j); 
        }
    }
    for (int i = 0; i < n; ++i)
    {
        int sc = 0;
        for(auto x : solved[i]){
            sc += pnts[x];
        }
        sb.pb({{sc,ns[i]},-i});
    }
    sort(sb.begin(), sb.end(), greater<pair<ii,int>>());
    for (int i = 0; i < n; ++i)
    {
        if(sb[i].se == -p)
            cout << sb[i].fi.fi << " " << i+1 << endl; 
    }
}