#include <bits/stdc++.h>
#include <ext/rope>
#define vi vector<int>
#define gi greater<int>
#define gr greater
#define ve vector
#define ll long long
#define vf vector<float>
#define vll vector<pair<ll,ll>>
#define ii pair<int,int>
#define pll pair<ll,ll>
#define vvi vector<vi>
#define vii vector<ii>
#define gii greater<ii>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF 1e18
#define eps 1e-7
#define eps1 1e-2
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 2e5+5
using namespace std;
using namespace __gnu_cxx;
const int MOD = 998244353;
const int nax = 1e6+5;
typedef complex<int> Point;
#define X real()
#define Y imag()
rope<char> s[nax];
int main(){
    optimise;
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int t;
    cin >> t;
    int cnt = 0;
    s[0] = "";
    while(t--){
        char type;
        cin >> type;
        if(type == 'T'){
            char l;
            cin >> l;
            s[cnt+1] = s[cnt];
            s[cnt+1] += l;
            cnt++;
        } else if(type == 'U'){
            int u;
            cin >> u;
            s[cnt+1] = s[cnt-u];
            cnt++;
        } else {
            int p;
            cin >> p;
            cout << s[cnt][p] << endl;
        }
    }
}