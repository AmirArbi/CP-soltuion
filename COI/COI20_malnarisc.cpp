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
vii ans[nax];
int merge(int l, int r, bool sens, int lvl){
    if(r-l+1 == 1) return 0;
    int sz = 1;
    while(sz*2 < r-l+1) sz *= 2;
    for (int i = l; i+sz <= r; ++i)
    {
        if(!sens){
            ans[lvl].pb({i,i+sz});
        } else {
            ans[lvl].pb({i+sz,i});
        }
    }
    return 1 + max(merge(l+sz,r,sens,lvl+1),merge(l,l+sz-1,sens,lvl+1));
}
int bitonicSort(int l, int r,bool sens, int lvl){
    //cout << l << " " << r << endl;
    if(r-l+1 == 1) return 0;
    int md = (l+r+1)/2;
    lvl = max(bitonicSort(l,md-1, !sens, lvl), bitonicSort(md,r, sens, lvl));
    lvl += merge(l,r,sens, lvl);
    return lvl;
}
int main()
{
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    int n;
    cin >> n;
    int aff =  bitonicSort(1,n,0,0);
    cout << aff << endl;
    for (int i = 0; i < aff; ++i)
    {
        for(auto x : ans[i])
            cout << "CMPSWP R" << x.fi << " R" << x.se << " ";
        cout << endl;
    }
}