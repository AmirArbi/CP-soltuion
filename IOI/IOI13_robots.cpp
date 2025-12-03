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
const int nax = 3e5+5;
typedef complex<int> Point;
//#define X real()
//#define Y imag()
#include "robots.h"
 
int putaway(int a, int b, int t, int X[], int Y[], int w[], int s[]){
    vi x,y;
    priority_queue<int> pq;
    vii vals;
    for (int i = 0; i < a; ++i)
    {
        x.pb(X[i]);
    }
    for (int i = 0; i < b; ++i)
    {
        y.pb(Y[i]);
    }
    for (int i = 0; i < t; ++i)
    {
        vals.pb({w[i], s[i]});
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    sort(vals.begin(), vals.end());
    for (int i = 0; i < t; ++i)
    {
        if((a == 0 || w[i] >= x[a-1]) && (b == 0 || s[i] >= y[b-1]))
            return -1;
    }
    int l = 0, r = t;
    while(l < r){
        int md = (l+r)/2;
        while(!pq.empty()) pq.pop();
        int j = 0;
        for (int i = 0; i < t; ++i)
        {
            while(j < a && vals[i].fi >= x[j]){
                for (int i = 0; i < md && !pq.empty(); ++i)
                {
                    pq.pop();
                }
                j++;
            }
            pq.push(vals[i].se);
        }
        while(j < a && !pq.empty()){
            for (int i = 0; i < md && !pq.empty(); ++i)
            {
                pq.pop();
            }
            j++;
        } 
        j = 0;
        vi bg;
        while(!pq.empty()){
            int ft = pq.top();
            pq.pop();
            bg.pb(ft);
        }
        sort(bg.begin(), bg.end());
        j = 0;
        int res = 0, cnt = 0;
        for(auto cur : bg){
            while(j < b && cur >= y[j]){
                res += min(md,cnt);
                cnt = max(0,cnt-md);
                j++;
            }
            cnt++;
        }
        while(j < b && cnt > 0){
            res += min(md,cnt);
            cnt = max(0,cnt-md);
            j++;
        }
        if(res == bg.size()) r = md;
        else l = md + 1;
    }
    return r;
}
/*int main(){
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int a,b,t;
    cin >> a >> b >> t;
    int x[a],y[b],w[t],s[t];
    for (int i = 0; i < a; ++i)
    {
        cin >> x[i];
    }
    for (int i = 0; i < b; ++i)
    {
        cin >> y[i];
    }
    for (int i = 0; i < t; ++i)
    {
        cin >> w[i] >> s[i];
    }
    cout << putaway(a,b,t,x,y,w,s) << endl;
}*/