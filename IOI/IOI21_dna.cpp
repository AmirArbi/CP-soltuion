#include <bits/stdc++.h>
#define vi vector<int>
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
#define INF 2e9+5
#define eps 1e-7
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MAX_A 1e5+5
#define V 450
using namespace std;
const int MOD = 1e9;
const int nax = 1e5+5;
//#include "dna.h"
int prefa[3][nax], prefb[3][nax], diff[3][3][nax];
map<char,int> cr;
void init(string a, string b) {
    int n = a.size();
    cr['A'] = 0, cr['T']= 1, cr['C'] = 2;
    for (int i = 0; i < n; ++i)
    {
        prefa[cr[a[i]]][i]++;
        prefb[cr[b[i]]][i]++;
        diff[cr[a[i]]][cr[b[i]]][i]++;
    }
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {  
            prefa[j][i] += prefa[j][i-1];
            prefb[j][i] += prefb[j][i-1];
        }
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                diff[j][k][i] += diff[j][k][i-1];
            }
        }
    }

}

int get_distance(int x, int y) {
    for (int i = 0; i < 3; ++i)
    {
        int n1 = prefa[i][y], n2 = prefb[i][y];
        if(x != 0){
            n1 -= prefa[i][x-1],n2 -= prefb[i][x-1];
        }
        if(n1 != n2) return -1;
    }
    int nb = y-x+1, res = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = i; j < 3; ++j)
        {   
            int n1 = diff[i][j][y], n2 = diff[j][i][y];
            if(x != 0){
                n1 -= diff[i][j][x-1], n2 -= diff[j][i][x-1];
            }
            if(i == j){
                nb -= n1;
                continue;
            }
            res += min(n1,n2);
            nb -= min(n1,n2)*2;
        }
    }
    res += (2*nb)/3;
    return res;
}
