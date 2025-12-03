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
#define INF 1e7
#define eps 1e-18
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);
#define MAX_A 1e5+5
#define V 450
using namespace std;
const int MOD = 1e9+7;
const int nax = 40005;
vii pnt;
bool vis[2][100005];
short dp[2][2][100005];
int n;
bool srch(int x, bool eq, bool turn){
    //cout << x << " " << eq << " " << turn << endl;
    bool p;
    if(dp[eq][turn][x] != -1)
        return dp[eq][turn][x];
    if(turn == 1){
        p = true;
        for (int i = 0; i < n; ++i)
        {
            if(!p) break;
            if(eq == 0){
                if(x == pnt[i].fi && !vis[1][pnt[i].se]){
                    vis[1][pnt[i].se] = 1;
                    //cout << "aze" << endl;
                    p &=  srch(pnt[i].se, 1, turn^1);
                    vis[1][pnt[i].se] = 0;
                }
            }else {
                if(x == pnt[i].se && !vis[0][pnt[i].fi]){
                    vis[0][pnt[i].fi] = 1;
                    p &= srch(pnt[i].fi, 0, turn^1);
                    vis[0][pnt[i].fi] = 0;
                }
            }
        }
    }
    if(turn == 0){
        p = false;
        for (int i = 0; i < n; ++i)
        {
            if(p) break;
            if(eq == 0){
                if(x == pnt[i].fi && !vis[1][pnt[i].se]){
                    vis[1][pnt[i].se] = 1;
                    p |= srch(pnt[i].se, 1, turn^1);
                    vis[1][pnt[i].se] = 0;
                }
            }else {
                if(x == pnt[i].se && !vis[0][pnt[i].fi]){
                    vis[0][pnt[i].fi] = 1;
                    p |= srch(pnt[i].fi, 0, turn^1);
                    vis[0][pnt[i].fi] = 0;
                }
            }
        }
    }
    return dp[eq][turn][x] = p;
}
bool srch2(int x, bool eq, bool turn){
    //cout << x << " " << eq << " " << turn << endl;
    bool p;
    if(turn == 1){
        p = true;
        for (int i = 0; i < n; ++i)
        {
            if(!p) break;
            if(eq == 0){
                if(x == pnt[i].fi && !vis[1][pnt[i].se]){
                    vis[1][pnt[i].se] = 1;
                    //cout << "aze" << endl;
                    p &= srch2(pnt[i].se, 1, turn^1);
                    vis[1][pnt[i].se] = 0;
                }
            }else {
                if(x == pnt[i].se && !vis[0][pnt[i].fi]){
                    vis[0][pnt[i].fi] = 1;
                    p &= srch2(pnt[i].fi, 0, turn^1);
                    vis[0][pnt[i].fi] = 0;
                }
            }
        }
    }
    if(turn == 0){
        p = false;
        for (int i = 0; i < n; ++i)
        {
            if(p) break;
            if(eq == 0){
                if(x == pnt[i].fi && !vis[1][pnt[i].se]){
                    vis[1][pnt[i].se] = 1;
                    p |= srch2(pnt[i].se, 1, turn^1);
                    vis[1][pnt[i].se] = 0;
                }
            }else {
                if(x == pnt[i].se && !vis[0][pnt[i].fi]){
                    vis[0][pnt[i].fi] = 1;
                    p |= srch2(pnt[i].fi, 0, turn^1);
                    vis[0][pnt[i].fi] = 0;
                }
            }
        }
    }
    return p;
}
int main() { 
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    memset(dp, -1, sizeof dp);
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int a,b;
        cin >> a >> b;
        pnt.pb({a,b});
    }
    bool p =false;
    for (int i = 0; i < n; ++i)
    {   
        vis[0][pnt[i].fi] = 1;
        if(n<12)
            p |=  srch2(pnt[i].fi,0,1) ;
        else
            p |=  srch(pnt[i].fi,0,1) ;
        vis[0][pnt[i].fi] = 0;
    }
    for (int i = 0; i < n; ++i)
    {   
        vis[1][pnt[i].se] = 1;
        if(n<12)
            p |=  srch2(pnt[i].se,1,1); 
        else
            p |=  srch(pnt[i].se,1,1); 
        vis[1][pnt[i].se] = 0;
    }
    if(p)
        cout << "Mirko" << endl;
    else cout << "Slavko" << endl;
}