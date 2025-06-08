#include <bits/stdc++.h>
#include "gift.h"
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
#define INF 1e10
#define unsigned u
#define eps 1e-18
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);
#define MAX_A 100005
#define V 450
#define re register
#define maxi(a,b) ((a) > (b) ? (a) : (b))
ll MOD = 998244353;
using namespace std;
vi p;
int findSet(int x){return (p[x] == x ? x : p[x] = findSet(p[x]));}
bool isSameSet(int x, int y){return findSet(x) == findSet(y);}
void unionSet(int x, int y){
    if(isSameSet(x,y))
        return;
    int i = findSet(x), j = findSet(y);
    p[min(i,j)] = max(i,j);
}
int construct(int n, int r, vector<int> a, vector<int> b, vector<int> x)
{
    p.resize(n);
    set<int> st;
    string s;
    for(int i = 0 ; i < n; i++){
        p[i] = i;
        st.insert(i);
    }
    for (int i = 0; i < r; ++i)
    {
        if(x[i] == 1){
            auto lb = st.lower_bound(a[i]), ub = st.lower_bound(b[i]);
            if(*ub != b[i])
                ub--;
            for (int j = (*lb)+1; j <= *ub; ++j)
            {
                if(j != b[i])
                    st.erase(j);
                unionSet(j,j-1);
            }
        } 
    }
    for (int i = 0; i < r; ++i)
    {
        bool p = false;
        if(x[i] == 2){
            if(findSet(a[i]) >= b[i])
                return 0;
        } 
    }
    char p = 'R';
    s += p;
    for (int i = 1; i < n; ++i)
    {
        if(isSameSet(i,i-1)){
            s += p;
        } else {
            if(p == 'R')
                p = 'B';
            else
                p = 'R';
            s += p;
        }
    }
    craft(s);
    return 1;
}