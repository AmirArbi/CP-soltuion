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
#define INF 1e8
#define eps 1e-7
#define eps1 1e-2
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
using namespace std;
const int MOD = 1e9+7;
const int nax = 2e5+5;
typedef complex<int> Point;
#define X real()
#define Y imag()
ii st[nax*4][2];
int s[nax], ind[nax];
void update(int v, int l, int r, int pos, int val, int type){
    if(r < pos || l > pos) return;
    if(l == r){
        st[v][type] = {val,val};
        return ;
    }
    int md = (l+r)/2;
    update(v*2,l,md,pos,val, type);
    update(v*2+1,md+1,r,pos,val, type);
    st[v][type].fi = min(st[v*2][type].fi, st[v*2+1][type].fi);
    st[v][type].se = max(st[v*2][type].se, st[v*2+1][type].se);
}
ii get(int v, int l, int r, int i, int j, int type){
    if(r < i || l > j) return {INF,0};
    if(i <= l && r <= j) return st[v][type];
    int md = (l+r)/2;
    ii a =get(v*2,l,md,i,j, type), b= get(v*2+1, md+1, r, i, j, type);
    return {min(a.fi, b.fi), max(a.se, b.se)};
}
int main()
{
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    int n,m;
    cin >> n >>m;
    for (int i = 0; i < n; ++i)
    {
        cin >> s[i];
        ind[s[i]] = i;
        update(1,0,n-1,i,s[i], 0);
        update(1,0,n-1,s[i],i, 1);
    }
    while(m--){
        int type,a,b;
        cin >> type >> a >> b;
        if(type == 1){
            a--,b--;
            update(1,0,n-1,a,s[b],0);
            update(1,0,n-1,b,s[a],0);
            update(1,0,n-1,s[b],a,1);
            update(1,0,n-1,s[a],b,1);
            swap(s[a],s[b]);
        } else {
            ii rg = get(1,0,n-1,a,b,1);
            ii ml = get(1,0,n-1,rg.fi,rg.se,0);
            if(ml.fi >= a && ml.se <= b){
                cout << "YES" << endl;
            } else{
                cout << "NO" << endl;
            }
        }
    }
}