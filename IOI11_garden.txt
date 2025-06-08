#include <bits/stdc++.h>
#include "gardenlib.h"
#define ii pair<int,int>
#define ve vector
#define vi vector<int>
#define vii vector<ii>
#define pb push_back
#define fi first
#define MAX_N 500000
#define se second
#define eps 1e-7
#define INF 1e9
#define ll long long
#include "garden.h"
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int nax = 3e5+5;
using namespace std;
int n,m,p,q, aff = 0, cur,res,c1 = INF, c2 = INF;
vi rev[nax];
bool vis[nax];
int adj[nax], f1[nax], f2[nax];
void dfs(int u, int d){
    if(vis[u] && u == p){
        c1 = d;
        return;
    } else if(vis[u])
        return;
    f1[u] = d;
    vis[u] = 1;
    for(auto x : rev[u])
        dfs(x,d+1);
}
void dfs2(int u, int d){
    if(vis[u] && u == p+n){
        c2 = d;
        return;
    } else if(vis[u])
        return;
    f2[u] = d, vis[u] = 1;
    for(auto x : rev[u])
        dfs2(x,d+1);
}
void count_routes(int N, int M, int P, int R[][2], int Q, int G[]){
    n = N,m = M, p = P;
    memset(adj,-1,sizeof adj);
    for(int i = 0; i < m; i++){
        int a,b;
        a = R[i][0], b = R[i][1];
        if(adj[a] == -1) {
            if(adj[b] != -1){
                adj[a] = b;
                if(adj[b+n] == -1) adj[b+n] = a+n;
            } else {
                adj[a] = b+n, adj[b] = a+n;
            }
        } else if(adj[a+n] == -1){
            if(adj[b] != -1){
                adj[a+n] = b;
                if(adj[b+n] == -1) adj[b+n] = a;
            } else {
                adj[a+n] = b+n, adj[b] = a;
            }
        } else {
            if(adj[b] != -1){
                if(adj[b+n] == -1)
                    adj[b+n] = a;
            } else {
                adj[b] = a;
            }
        }
    }
    for (int i = 0; i < 2*n; ++i)
    {
        if(i < n && adj[i+n] == -1) adj[i+n] = adj[i];
        f1[i] = INF, f2[i] = INF;
        rev[adj[i]].pb(i);
    }
    dfs(p,0);
    memset(vis,0,sizeof vis);
    dfs2(p+n,0);
    q = Q;
    for(int i = 0; i < q; i++){
        aff = 0;
        cur = G[i];
        for (int j = 0; j < n; ++j)
        {
            if(c1 != INF && cur >= f1[j] && (cur-f1[j])%c1 == 0) aff++;
            else if(c2 != INF && cur >= f2[j]  && (cur-f2[j])%c2 == 0) aff++;
            else if(cur == f1[j]) aff++;
            else if(cur == f2[j]) aff++;
        }
        answer(aff);
    }
}