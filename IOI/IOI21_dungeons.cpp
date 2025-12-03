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
#define INF 2e9+5
#define eps 1e-7
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
#define V 450
using namespace std;
const int MOD = 1e9;
const int nax = 4e5+5;
const int lg = 20;
//#include "dungeons.h"
int nxt[8][nax][lg], n;
vi s,p,w,l;
ll sm[8][nax][lg], mn[8][nax][lg];
void init(int N, vi S, vi P, vi W, vi L) {
    n = N; 
    s = S, p = P, w = W, l = L;
    s.pb(0), p.pb(0);
    for (int i = 0; i < lg; ++i)
    {
        for(int j =0; j < 8; j++) nxt[j][n][i] = n, sm[j][n][i] = 0, mn[j][n][i] = 1e9;
    }
    int cur = 1;
    for(int ind = 0; ind < 8; ind++){
        for (int i = 0; i < n; ++i)
        {
            if(cur >= s[i]) nxt[ind][i][0] = w[i], sm[ind][i][0] = s[i], mn[ind][i][0] = 1e9;
            else nxt[ind][i][0] = l[i], sm[ind][i][0] = p[i], mn[ind][i][0] =s[i];     
        }
        for (int j = 1; j < lg; ++j){
            for (int i = n-1; i >= 0; --i)
            {
                nxt[ind][i][j] = nxt[ind][nxt[ind][i][j-1]][j-1];
                sm[ind][i][j] = sm[ind][i][j-1] + sm[ind][nxt[ind][i][j-1]][j-1];
                if(mn[ind][nxt[ind][i][j-1]][j-1] == 1e9) mn[ind][i][j] = mn[ind][i][j-1];
                else mn[ind][i][j] = min(mn[ind][i][j-1], max(mn[ind][nxt[ind][i][j-1]][j-1] - sm[ind][i][j-1],0ll));
            }
        } 
        cur *= 10;
    }
}

long long simulate(int x, int z) {
    ll ind = 0, cur = 1, val = z;
    while(x != n){
        while(ind < 7 && 10*cur <= val) ind++, cur *= 10;
        for (int i = 0; i < lg; ++i)
        {
            if(min(val,(ll)(1e7)) < mn[ind][x][i]){
                val += sm[ind][x][i];
                x = nxt[ind][x][i];
            }
        }
        if(x == n) break;
        if(val >= s[x]) val += s[x], x = w[x];
        else val += p[x], x = l[x];   
    }
    return val;
}