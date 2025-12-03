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
#define unsigned u
#define eps 1e-18
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);
#define MAX_A 1e5+5
#define V 450
using namespace std;
const int MOD = 1e9+7;
const int N = 1030;
int t[800005];
int sum(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return sum(v*2, tl, tm, l, min(r, tm))
           + sum(v*2+1, tm+1, tr, max(l, tm+1), r);
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] += new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = t[v*2] + t[v*2+1];
    }
}
bool vis[200005];
long long count_swaps(std::vector<int> S){
    int n = S.size();
    stack<int> l[n+1][2];
    for (int i = 0; i < n; ++i)
    {
        l[abs(S[i])][S[i]<0].push(i);
        update(1,0,n-1,i,1);
    }
    long long res = 0;
    for(int i = n-1; i >= 0; i--){
        if(vis[i]) continue;
        int u=l[abs(S[i])][S[i]>0].top();        
        l[abs(S[i])][S[i]>0].pop();
        l[abs(S[i])][S[i]<0].pop();
        int j = sum(1,0,n-1,0,u);
        //cout << j << " " << sum(1,0,n-1,0,i) << endl;
        vis[u] = 1;
        res += sum(1,0,n-1,0,i)-j-1;
        if(S[i]<0)
            res++;
        update(1,0,n-1, u,-1);
    }
    return res;
}
int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    vi s;
    for (int i = 0; i < n; ++i)
    {
        int a;
        cin >> a;
        s.pb(a);
    }
    cout << count_swaps(s) << endl;
}