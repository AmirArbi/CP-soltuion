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
#define V 450
using namespace std;
const int MOD = 998244353;
const int nax = 2e5+5;
void solve(int x, int y, int i, int j, int cx, int cy){
    if(x == i && y == j) return;
    int mdx = (x+i)/2, mdy = (y+j)/2;
    if(cx <= mdx && cy <= mdy){
        cout << mdx+1 << " "  << mdy+1 << " " << mdx << " " << mdy+1 << " " << mdx+1 << " " << mdy << endl;
        solve(x,y,mdx,mdy,cx,cy);
    } else {
        solve(x,y,mdx,mdy,mdx,mdy);
    }
    if(cx <= mdx && cy > mdy){
        cout << mdx+1 << " "  << mdy+1 << " " << mdx+1 << " " << mdy << " " << mdx << " " << mdy << endl;
        solve(x,mdy+1,mdx,j,cx,cy);
    } else {
        solve(x,mdy+1,mdx,j,mdx,mdy+1);
    }
    if(cx > mdx && cy <= mdy){
        cout << mdx+1 << " "  << mdy+1 << " " << mdx << " " << mdy+1 << " " << mdx << " " << mdy << endl;
        solve(mdx+1,y,i,mdy,cx,cy);
    } else {
        solve(mdx+1,y,i,mdy,mdx+1,mdy);
    }
    if(cx > mdx && cy > mdy){
        cout << mdx+1 << " "  << mdy << " " << mdx << " " << mdy+1 << " " << mdx << " " << mdy << endl;
        solve(mdx+1,mdy+1,i,j,cx,cy);
    } else {
        solve(mdx+1,mdy+1,i,j,mdx+1,mdy+1);
    }
}
int main(){ 
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int n,x,y;
    cin >> n >> x >> y;
    solve(0,0,(int)(pow(2,n)-1),(int)(pow(2,n)-1),x,y);
}