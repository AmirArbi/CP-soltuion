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
#define MAX_A 1e5+5
using namespace std;
const int MOD = 1e4+7;
const int nax = 2e5+5;

typedef complex<int> Point;
#define X real()
#define Y imag()
int a[105][2],k;
string s[2];
int dp[105][nax][2], pref[2][nax], out[nax];
bool srch(int i, int j, int feel){
    if(j <= 0 && i==0) return 1;
    else if(j == 0) return 0;
    return dp[i][j][feel];
}
int main()
{
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    cin >> s[0];
    cin >> k;
    s[1] = s[0];
    string aff = s[0];
    int n = s[0].size();
    reverse(s[1].begin(), s[1].end());
    int p = -1;
    for (int i = 0; i < k; ++i)
    {
        cin >> a[i][0];
        a[k-i-1][1] = a[i][0];
    }
    for (int i = 0; i < n; ++i)
    {

        pref[0][i] = (s[0][i] != '_');
        pref[1][i] = (s[1][i] != '_');
        if(i > 0){
            pref[0][i] += pref[0][i-1];       
            pref[1][i] += pref[1][i-1];       
        }
    }
    //memset(dp,-1,sizeof dp);
    dp[0][0][0] = dp[0][0][1] = 1;
    for (int i = 0; i <= k; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            for (int feel = 0; feel < 2; ++feel)
            {
                if(s[feel][j-1] == '_' || s[feel][j-1] == '.') dp[i][j][feel] = dp[i][j-1][feel];
                if ((s[feel][j-1] == 'X' || s[feel][j-1] == '.') && i != 0){
                    if(j-a[i-1][feel] > 0) {
                        bool p = (s[feel][j-a[i-1][feel]-1] == '_' || s[feel][j-a[i-1][feel]-1] == '.');
                        int res = 0;
                        p &= (a[i-1][feel] == pref[feel][j-1] - pref[feel][j-a[i-1][feel]-1]);
                        if(p) dp[i][j][feel] |= dp[i-1][j-a[i-1][feel]-1][feel];
                    } else if(j-a[i-1][feel] == 0 && i == 1){
                        bool p = (a[i-1][feel] == pref[feel][j-1]);
                        if(p) dp[i][j][feel] = 1;
                    }
                }
                //cout << i << " " << j << " " << dp[i][j][feel] << endl;
            }
        }
    }
    for (int j = 1; j <= n; ++j)
    {
        if(s[0][j-1] == '.'){
            for (int i = 0; i <= k; ++i)
            {
                if(srch(i,j-1,0)==1 && srch(k-i,n-j,1)==1)
                {
                    aff[j-1] = '?';
                    break;
                }
            }
        }
    }
    dp[0][0][0] = dp[0][0][1] = 1;
    for (int j = 1; j <= n; ++j)
    {
        if(aff[j-1] != '_'){
            for (int i = k-1; i >= 0; --i)
            {
                if(j+a[i][0]-1 > n) continue;
                bool p = true;
                if(j > 1) p &= (aff[j-2] != 'X');
                if(j+a[i][0]-1 < n) p &=  (aff[j+a[i][0]-1] != 'X');
                p &= (pref[0][j+a[i][0]-2] - pref[0][j-2] == a[i][0]); 
                if(srch(i,j-2,0) == 1 && srch(k-i-1, n-j-a[i][0], 1) == 1 && p)
                {
                    out[j-1] = max(out[j-1], a[i][0]);
                }
            }
        }
    }
    int curmx = 0;
    for (int i = 0; i < n; ++i)
    {
        for(int k = max(i, curmx); k < i+out[i]; k++){
            if(aff[k] == '.') aff[k] = 'X';
            else if(aff[k] == '?') aff[k] = '#';
        }
        curmx = i+out[i]-1;
    }
    for(int i = 0; i < n; i++) {
        if(aff[i] == '#') aff[i] = '?';
        else if(aff[i] == '?') aff[i] = '_';  
        cout << aff[i]; 
    }
}