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
const int nax = 5e3+7;

typedef complex<int> Point;
#define X real()
#define Y imag()
int dp[nax][nax], s[nax], mx[nax];
int main()
{
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> s[i];
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            mx[j] = dp[j][i-1];
        }
        for (int j = 1; j < i; ++j)
        {
            mx[j] = max(mx[j], mx[j-1]);
        }
        int base1 = 0, base2 = 0, x = 0, pos = i-1, pntc = 0;
        for (int j = i; j < n; j++)
        {
            //cout <<pos << " " << i << " " << j << " " << x << " " << base1 << " " << base2<< endl;
            base2 += s[j];  
            while(pos > 0 && base1 < base2) base1 += s[pos],pos--;
            if(pos > 0 &&base1 == base2) pntc++, x = max(x, mx[pos] + pntc);
            dp[i][j+1] = x;
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        res = max(res, dp[i][n]);
    }
    cout << res << endl;
}