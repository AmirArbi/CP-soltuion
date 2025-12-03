#include <bits/stdc++.h>
 
    #define ii pair<int,int>
    #define ve sector
    #define vi vector<int>
    #define vii vector<ii>
    #define pb push_back
    #define fi first
    #define se second
    #define ll long long
    #define MAX_R  1000000
    #define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    using namespace std;

    int R, L;
    long long B;
    int X[MAX_R];
    int solution;
    int besthub(int r, int l, int s[], long long b){
        ll cur = b, i = s[0];
        ll u = 0, v = 0;
        while(v < r-1 && cur-(s[v+1]-i) >= 0){
            v++;
            cur -= s[v]-i;
        }
        ll mx = v-u+1;
        for (int k = 1; k < r; ++k)
        {
            i = s[k];      
            cur += (v-k+1)*(s[k]-s[k-1]) - (k-u)*(s[k]-s[k-1]);  
            assert(cur <= 1e18); 
            assert(cur >= -1e18); 
            while(v < r-1 && i-s[u] >= s[v+1]-i ){
                cur += i-s[u] - (s[v+1]-i);
                u++;
                v++;
            }
            while(cur < 0 && u <= k && k <= v){
                if(i-s[u] < s[v]-i){
                    cur += s[v]-i;
                    v--;
                } else {
                    cur += i-s[u];
                    u++;
                }
            }
            while(v < r-1 && i-s[u] > s[v+1]-i ){
                cur += i-s[u] - (s[v+1]-i);
                u++;
                v++;
            }
            while(cur >= 0 && (u > 0 || v < r-1)){
                if(v >= r-1){
                    if(cur - (i-s[u-1]) < 0) break;
                    u--;
                    cur -= i-s[u];
                } else if(u <= 0){
                    if(cur - (s[v+1]-i) < 0) break;
                    v++;
                    cur -= s[v]-i;
                } else if(i-s[u-1] > s[v+1]-i){
                    if(cur - (s[v+1]-i) < 0) break;
                    v++;
                    cur -= s[v]-i;
                } else {
                    if(cur - (i-s[u-1]) < 0) break;
                    u--;
                    cur -= i-s[u];
                }
            }
            mx = max(mx,v-u+1);
        }
        return mx;
    }

void read_input()
{
  int i;
  scanf("%d %d %lld",&R,&L,&B);
  for(i=0; i<R; i++)
    scanf("%d",&X[i]);
    scanf("%d",&solution);
}

int main()
{

    freopen("input.txt","r",stdin); 
    freopen("output.txt","w",stdout); 
    int ans;
    read_input();

    ans = besthub(R,L,X,B);
    if(ans==solution)
        printf("Correct.\n");
    else{
        assert(ans < solution);
        printf("Incorrect.  Returned %d instead of %d.\n",ans,solution);
    }

    return 0;
}