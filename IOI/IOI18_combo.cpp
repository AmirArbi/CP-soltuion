#include <bits/stdc++.h>
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
#define INF 1e9
#define eps 1e-7
#define eps1 1e-2
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 2e5+5
using namespace std;
const int MOD = 1e9+7;
const int nax = 1e6+5;
typedef complex<int> Point;
#define X real()
#define Y imag()
#include "combo.h"

char let[4] = {'A','B','X','Y'};
string guess_sequence(int n) {
    string s = "";
    int beg = 0;
    int a = press("AB");
    if(a >= 1){
        int b = press("A");
        if(b) beg = 0,s = "A";
        else beg = 1,s = "B";
    } else{
        int b= press("X");
        if(b) beg = 2,s = "X";
        else beg = 3,s = "Y";
    }
    for (int i = 2; i < n; ++i)
    {
        if(beg == 0){
            string cur = s+"X"+s+"YX"+s+"YY"+s+"YB";
            int a = press(cur);
            if(a == i-1) s+="B";
            else if(a == i) s+="X";
            else s += "Y";
        } else if(beg == 1){
            string cur = s+"X"+s+"YX"+s+"YY"+s+"YA";
            int a = press(cur);
            if(a == i-1) s+="A";
            else if(a == i) s+="X";
            else s += "Y";
        } else if(beg == 2){
            string cur = s+"A"+s+"YA"+s+"YY"+s+"YB";
            int a = press(cur);
            if(a == i-1) s+="B";
            else if(a == i) s+="A";
            else s += "Y";
        } else {
            string cur = s+"A"+s+"BA"+s+"BX"+s+"BB";
            int a = press(cur);
            if(a == i-1) s+="X";
            else if(a == i) s+="A";
            else s += "B";
        }
    }
    if(n!=1){
        int cnt = 0;
        for (int i = 0; i < 4; ++i)
        {
            if(beg == i) continue;
            if(cnt < 2 && press(s+let[i]) == n){
                s += let[i];
                break;
            } else if(cnt == 2){
                s += let[i];
                break;
            } else cnt++;
        }
    }
    return s;
}
