#include <bits/stdc++.h>
#include "horses.h"
#define vi vector<int>
#define ve vector
#define ll unsigned long long
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
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
#define V 450
using namespace std;
const int MOD = 1e9+7;
ll x[500005],y[500005],memo[500005];
pair<long double,ll> lazy[2000005], st[2000005];
long double lg[500005];
int n;
ll add(ll x, ll y)
{
    x += y;
    while(x >= MOD)
        x -= MOD;
    while(x < 0)
        x += MOD;
    return x;                         
}
 
ll sub(ll x, ll y)
{
    return add(x, MOD - y);
}
ll mul(ll x, ll y)
{
    return (x *  y) % MOD;
}
ll binpow(ll x, ll y)
{
    int z = 1;
    while(y > 0)
    {
        if(y % 2 == 1)
            z = mul(z, x);
        x = mul(x, x);
        y /= 2;
    }
    return z;
}
ll inv(ll x)
{
    return binpow(x, MOD - 2);   
}
 
ll divide(ll x, ll y)
{
    return mul(x, inv(y));
}
pair<long double,ll> maxi(pair<double,ll> a, pair<double,ll> b){if(a.fi > b.fi) return a; else return b;}

pair<long double,ll> merge(pair<double,ll> a, pair<double,ll> b){
	if(a.fi > b.fi) return a; else return b;
}
void build(int v, int l, int r){
	if(l==r){
		st[v] = {lg[l]+log(y[l]) , (memo[l]*y[l])%MOD};
		return ;
	}
	int md = (l+r)/2;
	build(v*2,l,md);
	build(v*2+1,md+1,r);
	st[v] = merge(st[v*2],st[v*2+1]);
}
void push(int v, int l, int r){
	if(lazy[v].fi == 0) return;
	st[v].fi += lazy[v].fi;
	st[v].se = (st[v].se*lazy[v].se)%MOD;
	if(l<r){
		if(lazy[v*2].se == 0) lazy[v*2].se = 1;
		lazy[v*2].fi += lazy[v].fi;
		lazy[v*2].se = (lazy[v*2].se*lazy[v].se)%MOD;

		if(lazy[v*2+1].se == 0) lazy[v*2+1].se = 1;
		lazy[v*2+1].fi += lazy[v].fi;
		lazy[v*2+1].se = (lazy[v*2+1].se*lazy[v].se)%MOD;
	}
	lazy[v] = {0,1};
}
void update(int v, int l, int r,int i, int j, ll val, long double val2){
	push(v,l,r);
	if(r < i || l > j) return;
	if(i <= l && r <= j){
		lazy[v] = {val2,val};
		push(v,l,r);
		return;
	}
	int md = (l+r)/2;
	update(v*2,l,md,i,j,val,val2);
	update(v*2+1,md+1,r,i,j,val,val2);
	st[v] = merge(st[v*2],st[v*2+1]);
}
int init(int N, int X[], int Y[]) {
	n = N;
	for (int i = 0; i < n; ++i)
	{
		x[i] = X[i];
		y[i] = Y[i];
	}
	memo[0] = x[0],lg[0] = log(x[0]); 
	for (int i = 1; i < n; ++i)
	{
		memo[i] = (memo[i-1]*x[i])%MOD;
		lg[i] = lg[i-1]+log(x[i]);
	}
	build(1,0,n-1); 
	return st[1].se%MOD;
}

int updateX(int pos, int val) {	
	update(1,0,n-1,pos,n-1,divide(val,x[pos]), log(val)-log(x[pos]) );
	x[pos] = val;
	return st[1].se%MOD;
}

int updateY(int pos, int val) {
	update(1,0,n-1,pos,pos,divide(val,y[pos]), log(val)-log(y[pos]) );
	y[pos] = val;
	return st[1].se%MOD;
}