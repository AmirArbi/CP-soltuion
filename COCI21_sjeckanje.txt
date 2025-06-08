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
#define INF 1e17
#define eps 1e-7
#define eps1 1e-2
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 2e5+5
using namespace std;
const int MOD = 1e9+7;
const int nax = 2e5+5;
const int nax2 = 200+5;
typedef complex<int> Point;
using cd = complex<double>;
ll st[nax*4][4], diff[nax], s[nax];
void combine(int v, int l, int r){
    int md = (l+r)/2;
    
    st[v][0] = st[v][1] = st[v][2] = st[v][3] = 0;

    if((diff[md] > 0 && diff[md+1] < 0) || (diff[md] < 0 && diff[md+1] > 0)){
        st[v][0] = max(abs(st[v*2][0]) + st[v*2+1][1], st[v][0]);  
        st[v][0] = max(st[v*2][2] + abs(st[v*2+1][0]), st[v][0]);

        st[v][1] = max(st[v*2][1] + st[v*2+1][1], st[v][1]);  
        st[v][1] = max(st[v*2][3] + abs(st[v*2+1][0]), st[v][1]); 

        st[v][2] = max(abs(st[v*2][0]) + st[v*2+1][3], st[v][2]);  
        st[v][2] = max(st[v*2][2] + st[v*2+1][2], st[v][2]);  

        st[v][3] = max(st[v*2][1] + st[v*2+1][3], st[v][3]);  
        st[v][3] = max(st[v*2][3] + st[v*2+1][2], st[v][3]); 
    } else {
        st[v][0] = max(abs(st[v*2][0]) + abs(st[v*2+1][0]), st[v][0]);

        st[v][1] = max(st[v*2][1] + abs(st[v*2+1][0]), st[v][1]); 

        st[v][2] = max(abs(st[v*2][0]) + st[v*2+1][2], st[v][2]); 

        st[v][3] = max(st[v*2][1] + st[v*2+1][2], st[v][3]);    
    }
}
void build(int v, int l, int r){
    if(l == r){
        st[v][0] = diff[l];
        st[v][1] = st[v][2] = st[v][3] = 0;
        return;
    }
    int md = (l+r)/2;
    build(v*2,l,md);
    build(v*2+1,md+1,r);
    combine(v, l, r);
}
void update(int v, int l, int r, int pos, ll val){
    if(pos < l || pos > r) return;
    if(l == r){
        st[v][0] += val;
        //cout << st[v][0] << " " << diff[l] << endl;
        return;
    }
    int md = (l+r)/2;
    update(v*2,l,md,pos,val);
    update(v*2+1,md+1,r,pos,val);
    combine(v, l, r);
}
int main(){ 
    optimise;
    int n,q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
    {
        cin >> s[i];
    }
    for (int i = 0; i < n; ++i)
    {
        if(i) diff[i] =  s[i]-s[i-1];
        else diff[i] = 0;
    }
    build(1,0,n-1);
    while(q--){
        int l,r;
        ll x;
        cin >> l >> r >> x;
        l--,r--;
        if(l > 0){ 
            diff[l] += x;
            update(1,0,n-1,l,x);
        }
        if(r < n-1){
            diff[r+1] -= x;  
            update(1,0,n-1,r+1,-x);
        }
        cout << st[1][0] << endl;
    }
}


