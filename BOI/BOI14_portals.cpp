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
#define fi first
#define se second
#define INF 1e7
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
char grid[1005][1005];
int mov[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
int main(){
    optimise;
    int r,c;
    cin >> r >> c;
    ii start, end;
    ll dis[r][c];
    set<int> wallsc[r], wallsr[c];
    for (int i = 0; i < c; ++i)
    {
        wallsr[i].insert(-1);
        wallsr[i].insert(r);
    }
    for (int i = 0; i < r; ++i)
    {
        wallsc[i].insert(-1);
        wallsc[i].insert(c);
    }
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cin >> grid[i][j];
            dis[i][j] = INF;
            if(grid[i][j] == 'S'){
                start.fi = i,start.se = j;
            } else if(grid[i][j] == 'C'){
                end.fi = i,end.se = j;
            } else if(grid[i][j] == '#'){
                wallsc[i].insert(j);
                wallsr[j].insert(i);
            }
        }
    }
    dis[start.fi][start.se] = 0;
    queue<ii> q;
    q.push(start);
    while(!q.empty()){
        ii cur = q.front(); q.pop();
        bool ses = false;
        auto ux = wallsr[cur.se].upper_bound(cur.fi),uy = wallsc[cur.fi].upper_bound(cur.se),lx = wallsr[cur.se].lower_bound(cur.fi), ly = wallsc[cur.fi].lower_bound(cur.se);
        lx--;ly--;
        for (int i = 0; i < 4; ++i)
        {
            int nx =  cur.fi +  mov[i][0], ny = cur.se + mov[i][1];
            if(nx < 0 || ny < 0 || nx >= r || ny >= c || grid[nx][ny] == '#') {
                ses = true;
                continue;
            }
            if(dis[nx][ny] > dis[cur.fi][cur.se] +1 ){
                dis[nx][ny] = dis[cur.fi][cur.se] +1 ;
                q.push({nx,ny});
            }
        }
        int near = min(cur.fi-*lx, cur.se-*ly);
        near = min(near, *uy-cur.se);
        near = min(near, *ux-cur.fi);
        int nx =  *ux-1, ny = cur.se;
        if(nx < 0 || ny < 0 || nx >= r || ny >= c || grid[nx][ny] == '#') 
            continue;
        if(dis[nx][ny] > dis[cur.fi][cur.se] +near ){
            dis[nx][ny] = dis[cur.fi][cur.se] +near ;
            q.push({nx,ny});
        }
        nx =  *lx+1, ny = cur.se;
        if(nx < 0 || ny < 0 || nx >= r || ny >= c || grid[nx][ny] == '#') 
            continue;
        if(dis[nx][ny] > dis[cur.fi][cur.se] +near ){
            dis[nx][ny] = dis[cur.fi][cur.se] +near ;
            q.push({nx,ny});
        }
        nx = cur.fi, ny = *ly+1;
        if(nx < 0 || ny < 0 || nx >= r || ny >= c || grid[nx][ny] == '#') 
            continue;
        if(dis[nx][ny] > dis[cur.fi][cur.se] +near ){
            dis[nx][ny] = dis[cur.fi][cur.se] +near ;
            q.push({nx,ny});
        }
        nx = cur.fi, ny = *uy-1;
        if(nx < 0 || ny < 0 || nx >= r || ny >= c || grid[nx][ny] == '#') 
            continue;
        if(dis[nx][ny] > dis[cur.fi][cur.se] +near ){
            dis[nx][ny] = dis[cur.fi][cur.se] +near ;
            q.push({nx,ny});
        }
    }
    cout << dis[end.fi][end.se];
}