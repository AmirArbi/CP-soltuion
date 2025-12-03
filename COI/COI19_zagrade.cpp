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
#define MAX_A 2e5+5
using namespace std;
int MOD = 1e9+7;
const int nax = 2000+5;
const int nax2 = 200+5;
typedef complex<int> Point;
#define X real()
#define Y imag()
using cd = complex<double>;
const double PI = acos(-1);
int main(){ 
    optimise;
    int n,q;
    cin >> n >> q;
    int r = 2;
    stack<int> cur;
    cur.push(1);
    string s;
    for (int i = 0; i < n; ++i)
    {
        s.pb(' ');
    }
    while(r!=(n+1)){
        if(cur.empty()){
            cur.push(r);
            r++;
            continue;
        }
        int l = cur.top();
        cout << "? " << l << " " << r << endl;
        int ans;
        cin >> ans;
        if(ans){
            cur.pop();
            s[l-1] = '(';
            s[r-1] = ')';
        } else cur.push(r);
        r++;
    }
    int b = cur.size()/2;
    while(cur.size() != b) {
        int l = cur.top();
        s[l-1] = '(';
        cur.pop();
    }
    while(!cur.empty()) {
        int l = cur.top();
        s[l-1] = ')';
        cur.pop();
    }
    cout << "! " << s << endl;
}