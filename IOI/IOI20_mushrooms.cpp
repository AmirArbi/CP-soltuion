#include "mushrooms.h"
 
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
#define eps 1e-18
#define eps1 1e-25
#define optimise ios_base::sync_with_stdio(false);cin.tie(NULL);
#define MAX_A 1e5+5
#define V 450
using namespace std;
const int MOD = 1e9+7;
const int nax = 2000005;

int count_mushrooms(int n) {
    int X = 200;
    vi typ[2];
    typ[0].pb(0);
    if(n < 300){
        int cnt = 1;
        for(int i = 1;i<n;i++){
            vector<int> a;
            a.push_back(0);
            a.push_back(i);
            int x = use_machine(a);
            if(x == 0)cnt++;
        }
        return cnt;
    }
    for(int i = 1; i <= 2; i++){
        typ[use_machine({0,i})].pb(i);
    }
    bool B = false;
    if(typ[1].size() == 2)
        B = true;
    int res = 0;
    res = use_machine({typ[B][0],3,typ[B][1], 4});
    if(res == 0){
        typ[B].pb(3);
        typ[B].pb(4);
    } else if(res == 1){
        typ[B].pb(3);
        typ[B^1].pb(4);
    } else if(res == 2){
        typ[B^1].pb(3);
        typ[B].pb(4);
    } else {
        typ[B^1].pb(3);
        typ[B^1].pb(4);
    }
    B = false;
    if(typ[1].size() >= 3)
        B = true;
    for (int i = 5; i < X; i+=5)
    {
        int res = use_machine({typ[B][0], i, typ[B][1],i+1, typ[B][2], i+2});
        if(res%2==1)
            typ[1-B].pb(i+2);
        else typ[B].pb(i+2);
        res -= res%2;
        if(res%4==0){
            if(res == 4){
                typ[B^1].pb(i);
                typ[B^1].pb(i+1);
            } else if(res == 0){
                typ[B].pb(i);
                typ[B].pb(i+1);
            }
            res = use_machine({typ[B][0], i+3, typ[B][1],i+4});
            if(res == 0){
                typ[B].pb(i+3);
                typ[B].pb(i+4);
            } else if(res == 1){
                typ[B].pb(i+3);
                typ[B^1].pb(i+4);
            } else if(res == 2){
                typ[B^1].pb(i+3);
                typ[B].pb(i+4);
            } else {
                typ[B^1].pb(i+3);
                typ[B^1].pb(i+4);
            }
        } else {
            if(min(typ[0].size(), typ[1].size())>=2){
                res = use_machine({typ[B^1][0], i, typ[B^1][1], typ[B][0],i+1, typ[B][1], i+3 ,typ[B][2], i+4});
                if(res%2==0){
                    typ[1-B].pb(i+4);
                    res--;
                }
                else typ[B].pb(i+4);
                if(res>=4){
                    typ[B].pb(i);
                    typ[1-B].pb(i+1);
                    if(res == 5) typ[B].pb(i+3);
                    else typ[1-B].pb(i+3);
                } else {
                    typ[1-B].pb(i);
                    typ[B].pb(i+1);
                    if(res == 1) typ[B].pb(i+3);
                    else typ[1-B].pb(i+3);
                }
            } else {
                res = use_machine({0,i});
                typ[res].pb(i);
                typ[1-res].pb(i+1);
                res = use_machine({typ[B][0], i+3, typ[B][1],i+4});
                if(res == 0){
                    typ[B].pb(i+3);
                    typ[B].pb(i+4);
                } else if(res == 1){
                    typ[B].pb(i+3);
                    typ[B^1].pb(i+4);
                } else if(res == 2){
                    typ[B^1].pb(i+3);
                    typ[B].pb(i+4);
                } else {
                    typ[B^1].pb(i+3);
                    typ[B^1].pb(i+4);
                }
            }
        }
    }
    int cnt = typ[0].size();
    #define sz(x) (int)x.size()
    {
        int i = X;
        while(i<n){
             if(sz(typ[0]) >= sz(typ[1])){
            vector<int> a;
            for(int j : typ[0]){
                a.pb(j);
                a.pb(i);
                i++;
                if(i == n)break;
            }
            int x = use_machine(a);
            cnt += (int)(a.size()/2) - (x+1)/2;
            if(x%2){
                typ[1].pb(a.back());
            }
            else typ[0].pb(a.back());
            }
             else {
                vector<int> b;
            for(int j : typ[1]){
                b.pb(j);
                b.pb(i);
                i++;
                if(i == n)break;
            }
            int x = use_machine(b);
            cnt += (x+1)/2;
             if(x%2){
                typ[0].pb(b.back());
            }
            else typ[1].pb(b.back());
             }
 
        }
    }
    return cnt;
 
}