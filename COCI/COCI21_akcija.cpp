#include <bits/stdc++.h>
//#include "bubblesort2.h"
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
#define INF 1e17
#define eps 1e-4
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
using namespace std;
const int MOD = 1e9+7;
const int nax = 2005;
bool compareInterval(pair<int,ll> a, pair<int,ll> b)
{
     return (a.se < b.se);
}
struct node {
    int mn = 0, pos = 0, prop = 0;
    node () {}
    node (int _mn, int _pos, int _prop) {
        mn = _mn; pos = _pos; prop = _prop;
    }
};
struct sgtree{
	node st[4*nax];
	node merge(node x, node y){
		if(x.mn >= y.mn) return y; else return x;
	}
	void init(int v, int l, int r){
		if(l==r){
			st[v].mn = st[v].pos = l+1;
			st[v].prop = 0;
			return ;
		}
		int md = (l+r)/2;
		init(v*2,l,md);
		init(v*2+1,md+1,r);
		st[v] = merge(st[v*2],st[v*2+1]);
	}
	void propagate (int x, int l, int r) {
        if (st[x].prop == 0) return;

        if (l!=r) {
            st[2 * x].prop += st[x].prop;
            st[2 * x + 1].prop += st[x].prop;
        }

        st[x].mn += st[x].prop;
        st[x].prop = 0;
    }
    void update(int v,int l, int r, int i, int j, int val){
    	propagate(v,l,r);
    	if(r < i || l > j) return;
    	if(l >= i && r <= j){
    		st[v].prop += val;
    		propagate(v,l,r);
    		return;
    	}
    	int md = (l+r)/2;
    	update(v*2, l,md,i,j,val);
    	update(v*2+1,md+1,r,i,j,val);
    	st[v] = merge(st[v*2],st[v*2+1]);
    }

    node query(int v,int l, int r, int i, int j){
    	propagate(v,l,r);
    	if(r < i || l > j) {
    		node INF_N(nax*4,0,0);
    		return INF_N;
    	}
    	if(l >= i && r <= j){
    		return st[v];
    	}
    	int md = (l+r)/2;
    	return merge(query(v*2, l,md,i,j),query(v*2+1,md+1,r,i,j));
    }

} t;
 int n,k;
int cnt = 0;
ve<pair<int,ll>> s;
int opt[nax][nax], stat[nax][nax];
priority_queue<pair<pair<int,ll>, pair<int,int> >> pq;
pair<int,ll> cal(){
	int b = 0;
	ll sum = 0;
	t.init(1,0,n-1);
	for (int i = 0; i < n; ++i)
	{
		opt[cnt][i] = 0;
		if(stat[cnt][i] == 1 || (stat[cnt][i] == 0 && t.query(1,0,n-1,s[i].fi-1,n-1).mn>0)){
			opt[cnt][i] = 1;
			b++;
			sum+=s[i].se;
			t.update(1,0,n-1,s[i].fi-1,n-1,-1);
		}
	}
	return {b,sum};
}
void bfs(pair<int,ll> cur){
	ve<ll> bst(n+1,INF);
	for (int i = 0; i < n; ++i)
	{
		if(stat[cnt][i] == 0 && opt[cnt][i] == 0){
			bst[s[i].fi] = min(bst[s[i].fi] ,s[i].se);
			//cout << s[i].se << " " << bst[s[i].se] << endl;
		} 
	}
	for (int i = n-2; i >= 0; --i)
	{
		bst[i] = min(bst[i],bst[i+1]);
		//cout << i << " " << bst[i] << endl;

	}
	for (int i = 0; i < n; ++i)
	{
		if(stat[cnt][i] == 0 && opt[cnt][i] == 1){
			auto y = t.query(1,0,n-1,0,s[i].fi-2);
			int rmi;
			if(y.mn != 0) rmi = 0;
			else rmi = y.pos;
			int a = 0;
			ll b = 0;
			if(bst[rmi+1] == INF){
				a = cur.fi-1;
				b = cur.se-s[i].se;
			} else {
				a = cur.fi,
				b = cur.se-s[i].se+bst[rmi+1]; 
			}
			//cout << a << " a " << b << endl;
			pq.push({{a,-b},{cnt,i}});
		}
	}
}
void qpop(){
	pair<int,ll> a= pq.top().fi;
	pair<int,int> b = pq.top().se;
	pq.pop();
	//assert(pq.size() == 0);
	cout << a.fi << " " << -a.se << endl;
	if(b.fi == -1) return ;
	for (int i = 0; i < n; ++i)
	{
		stat[cnt][i] = stat[b.fi][i];
		if(stat[b.fi][i] == 0 && opt[b.fi][i] == 1){
			if(i<b.se)stat[cnt][i] = 1;
			else if(i == b.se) stat[cnt][i] = -1;
			else stat[cnt][i] = 0;
		}
	}
}
int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
    {
    	ll a,b;
    	cin >> a >> b;
    	s.pb({b,a});
    }
    sort(s.begin(), s.end(),compareInterval);
    pair<int,ll> best = cal();
    pq.push({{best.fi,-best.se},{-1,-1}});
    while(cnt < k){
    	qpop();
    	bfs(cal());
    	cnt++;
    }
}