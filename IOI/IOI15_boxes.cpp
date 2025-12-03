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
const int MOD = 1e9+7;
const int nax = 1e7+5;
typedef complex<int> Point;
#define X real()
#define Y imag()
ll cw[nax], ccw[nax];
ll delivery(int n, int k, int l, int p[]){
    for (int i = 0; i < n; ++i)
    {
        cw[i+1] = p[i];
        if(i >= k-1){
            cw[i+1] += cw[i-k+1];
        }
    }
    for (int i = n-1; i >= 0; --i)
    {
        ccw[i+1] = l-p[i];
        if(i+k+1 <= n){
            ccw[i+1] += ccw[i+k+1];
        }
    }
    ll res = INF;
    for (int i = 0; i <= n; ++i) res = min(res,2ll*(cw[i]+ccw[i+1]));
    for (int i = 0; i <= n-k; ++i) res = min(res,2ll*(cw[i]+ccw[i+1+k])+l);
    return res;
}
int main()
{
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    int n,k,l;
    cin >> n >> k >> l;
    int positions[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> positions[i];
    }
    cout << delivery(n,k,l,positions);
}