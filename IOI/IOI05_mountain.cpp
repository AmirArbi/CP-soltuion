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
#define INF 2e9
#define eps 1e-7
#define eps1 1e-2
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
#define V 450
using namespace std;
const int MOD = 1e9+7;
const int nax = 2e6+5;
const int nax2 = 105;

typedef complex<int> Point;
#define X real()
#define Y imag()
int n;

struct Node{
    ii st;
    int lx,rx,lazy = INF;
    Node *l = 0, *r = 0; 
    Node(int lx, int rx) : lx(lx), rx(rx) {}

    void mod(int v){
        if(v == INF) return;
        st.fi = (rx-lx+1)*v;
        st.se = max(0,st.fi);
        lazy = v;
    }

    void push(){
        int md = (lx+rx)/2;
        if(!l) l = new Node(lx,md);
        if(!r) r = new Node(md+1,rx);
        l->mod(lazy);r->mod(lazy);
        lazy = INF;
    }

    int get(int h){
        if(rx == lx) 
            if(st.se > h) return lx-1;
            else return lx;
        push();
        if(l->st.se > h) return l->get(h);
        else return r->get(h - l->st.fi);
    }

    void update(int i, int j, int val){ 
        if(j < lx || i > rx) return;
        if(i <= lx && rx <= j){
            mod(val);
            return;
        } 
        push();
        int md = (lx+rx)/2;
        l->update(i, j,val); r->update(i, j,val);
        st.fi = l->st.fi + r->st.fi ;
        st.se = max(l->st.se, l->st.fi + r->st.se);
    }
};


int main()
{
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    cin >> n;
    char c;
    cin >> c;
    Node root(0,n);
    while(c != 'E'){
        if(c == 'Q'){
            int h;
            cin >> h;
            cout << root.get(h) << '\n';
        } else {
            int l,r,val;
            cin >> l >> r >> val;
            root.update(l,r,val);
        }
        cin >> c;
    }
}