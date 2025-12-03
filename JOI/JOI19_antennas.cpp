#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
const int nax= 2e5 + 5;
int n, q, k = 1;
vector<int> A, B, H, L1, R1, L2, R2;
vector<pair<int,pair<int,int>>> events;
int ans[nax], lquery[nax], rquery[nax];
 
const int MOD = 1e9 + 7;
struct node
{
    int maxi = -MOD, mini = MOD, umax = -MOD, umin = MOD, ans = -1;
 
};
vector<node> st;
vector<int> lazymx, lazymn;
node BASE;
void propagate(int p)
{
    if(lazymx[p] != -MOD)
    {
        if(p < k)
        {
            lazymx[2 * p] = max(lazymx[p], lazymx[2 * p]);
            lazymx[2 * p + 1] = max(lazymx[p], lazymx[2 * p + 1]);
        }
        st[p].ans = max(st[p].ans, lazymx[p] - st[p].mini);
        lazymx[p] = -MOD;
    }
    if(lazymn[p] != MOD)
    {
        if(p < k)
        {
            lazymn[2 * p] = min(lazymn[p], lazymn[2 * p]);
            lazymn[2 * p + 1] = min(lazymn[p], lazymn[2 * p + 1]);
        }
        st[p].ans = max(st[p].ans, st[p].maxi -  lazymn[p] );
        lazymn[p] = MOD;
    }
    //if(p < k)
        //st[p].ans = max(st[2 * p].ans, st[2 * p + 1].ans);
    //cout << st[p].ans << endl;
}
void pupd(int p, int l, int r, int pos, int v)
{
    propagate(p);
    if(l > r || r < pos || l > pos)
        return ;
    if(l == r){
        //st[p] = BASE;
        if(v == 0)
            st[p].maxi = -MOD, st[p].mini = MOD;
        else
            st[p].maxi = H[pos], st[p].mini = H[pos];
        return ;
    }
    int md = (l+r)/2;
    pupd(p*2,l,md,pos,v);
    pupd(p*2+1,md+1,r,pos,v);
    st[p].maxi = max(st[2 * p].maxi, st[2 * p + 1].maxi);
    st[p].mini = min(st[2 * p].mini, st[2 * p + 1].mini);
    //st[p].ans = max(st[2 * p].ans, st[2 * p + 1].ans);
}
void update(int p, int l, int r, int i, int j, int val)
{
    propagate(p);
    if(i > j)
        return ;
    if(l >= i && r <= j)
    {
        lazymx[p] = val;
        lazymn[p] = val;
        propagate(p);
        //cout << l << " " << r << " " <<  st[p].mini << " " << st[p].umax << ' ' << st[2*p+1].ans << endl;
        return ;
    }
    int m = (l + r)/2;
    update(2 * p, l, m, i, min(j, m), val);
    update(2 * p + 1, m + 1, r, max(i, m + 1), j, val);
//  st[p].umin = min(st[2*p].umin, st[2*p+1].umin);
//  st[p].umax = min(st[2*p].umax, st[2*p+1].umax);
    st[p].ans = max(st[p*2].ans, st[p*2+1].ans);
    //cout << l << " " << r << " " << st[p].mini << " " << st[p].maxi << " " << st[p].umin << " " << st[p].umax << " " << st[p].ans << endl;
}
int query(int v,int l, int r, int i, int j){
    propagate(v);
    if(i > j)
        return -1;
    if(l >= i && r <= j) return st[v].ans;
    int m = (l + r)/2;
    return max(query(2 * v, l, m, i, min(j, m)),
                query(2 * v + 1, m + 1, r, max(i,m +1 ), j));
}
void solve()
{
    cin >> n;
    A.resize(n + 1); B.resize(n + 1); H.resize(n + 1);
    L1.resize(n + 1); R1.resize(n + 1); L2.resize(n + 1); R2.resize(n + 1);
    while(k < n + 1)
        k = (k << 1);
    
    BASE.umax = -1, BASE.umin = MOD, BASE.maxi = -1, BASE.mini = MOD, BASE.ans = -1;
    st.assign(2 * k + 1, BASE);
    lazymn.assign(2 * k + 1, MOD);
    lazymx.assign(2 * k + 1, -1);
 
    for(int i= 1; i <= n; i++)
    {
        cin >> H[i] >> A[i] >> B[i];
        L1[i] = max(0, i - B[i]), R1[i] = max(0, i - A[i]);
        L2[i] = min(n + 1, i + A[i]), R2[i] = min(n + 1, i + B[i]);
 
        events.pb({i, {1, i}});
        events.pb({L2[i], {0, i}});
        events.pb({R2[i], {3, i}});
        /// Computing L1, R1, L2, R2 and pushing in the sweep line
    }
    cin >> q;
    for(int i =1;i  <= q; i++)
    {
        int l, r;
        cin >> l >> r;
        lquery[i] = l, rquery[i] = r;
        events.pb({r, {2, i}});
    }
    sort(all(events));
    int curmax = 0;
    for(auto e: events)
    {
        int tim = e.ff;
        int typ = e.ss.ff;
        int idx = e.ss.ss;
        //cout << '\t' << tim << ' ' << typ << ' ' << idx << endl;
        if(typ == 0)
        {
            //curmax = max(curmax, idx);
            pupd(1,0,k-1,idx, 1);
        }
        else if(typ == 1)
        {
            update(1, 0, k - 1, L1[idx], R1[idx], H[idx]);
            //cout << idx<< ' ' <<  L1[idx] << " " << R1[idx] << " " << H[idx] << endl;
        }
        else if(typ ==3)
        {
            
            pupd(1,0,k-1,idx, 0);
        }
        if(typ == 2)
        {
            ans[idx]= max(-1, query(1, 0, k - 1, lquery[idx], rquery[idx]));
        }
        //cout << tim << " " << query(1,0,k-1,1,1) << endl;
    }
    for(int i = 1; i <= q; i++)
        cout << ans[i] << '\n';
    //cout << endl;
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int tt = 1; // cin >> tt;
    while(tt--)
        solve();
 
}