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
#define fi first
#define se second
#define INF 1e9
#define eps 1e-7
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);
#define MAX_A 1e5+5
#define V 450
using namespace std;
const int MOD = 1e9+7;
const int nax = 2000005;
ll add(ll x, ll y)
{
    x += y;
    while(x >= MOD)
        x -= MOD;
    while(x < 0)
        x += MOD;
    return x;                         
}
ll sub(ll x, ll y)
{
    return add(x, MOD - y);
}
ll mul(ll x, ll y)
{
    return (x *  y) % MOD;
}
ll binpow(ll x, ll y)
{
    int z = 1;
    while(y > 0)
    {
        if(y % 2 == 1)
            z = mul(z, x);
        x = mul(x, x);
        y /= 2;
    }
    return z;
}
ll inv(ll x)
{
    return binpow(x, MOD - 2);   
}
ll s[nax];
void solve(int l, int r){
    if(l+1==r){
        s[l] = binpow(2,s[l]);
        return ;
    }
    int mid = (l+r)/2;
    for (int i = l; i < mid; ++i)
    {
        s[mid+i-l]+=s[i];
    }
    solve(l,mid);
    solve(mid,r);

    for (int i = l; i < mid; ++i)
    {
        s[mid+i-l]=sub(s[mid+i-l],s[i]);
    }
}
int main() { 
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        int a;
        cin >> a;
        int mask = 0;
        for (int i = 0; i < a; ++i)
        {
            int b;
            cin >> b;
            b--;
            mask |= (int) pow(2,b);
        }
        s[mask]++;
    }
    solve(0,pow(2,m));
    cout << s[(int)(pow(2,m)-1)] << endl;
}