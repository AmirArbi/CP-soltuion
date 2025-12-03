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
#define INF 1e12
#define unsigned u
#define eps 1e-18
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);
#define MAX_A 1e5+5
using namespace std;
const int MOD = 1e9+7;
const int nax = 100005;
vii w0;
int N;
int L,R;
int find_subset(int l, int u, int w[], int n, int result[]) { 
    L = l,R = u, N = n;
    for (int i = 0; i < n; ++i)
    {
        w0.pb({w[i],i});
    }
    sort(w0.begin(), w0.end());
    ll sum = 0;
    int imx = 0;
    int cn = 0;
    for (int i = 0; i < n; ++i)
    {
        if(sum + w0[i].fi <= R){
            sum += w0[i].fi;
            imx++;
            result[i] = w0[i].se;
            cn += w0[n-i-1].fi-w0[i].fi;
        }
        else {
            break;
        }
    }
    if(sum <= R && sum >= L) return imx;
    else {
        if(sum+cn >= L){
            for (int i = 0; i < imx && n-i-1 >= imx; ++i)
            {
                if(sum + w0[n-i-1].fi-w0[i].fi  <= R){
                    sum += w0[n-i-1].fi-w0[i].fi;
                    result[i] = w0[n-i-1].se;
                } else 
                    break;
            }
            return imx;
        } 
    }
    return 0;
}