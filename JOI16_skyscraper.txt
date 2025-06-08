#include <bits/stdc++.h>
#include <random>
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
const int MAXK = 1e9;
const int lg = 20;
const int N = 105;
const int L = 1005;
const string SUBTASK = "6";


int sol1(int n, int l){
    vi a;
    for(int i = 1; i <= n; i++) a.pb(i);
    int res = 0;    
    sort(a.begin(),  a.end());
    do{
        int sm = 0;
        for(int i = 0; i < n-1; i++){
            sm += abs(a[i] - a[i+1]);
        }
        if(sm <= l) res++; 
    } while(next_permutation(a.begin(), a.end()));
    return res; 
}

const int mod = 1e9+7;
/*int dp[(1 << N)][N][L];

int sol2(int n, int l){
    // initialiser les cas de bases
    for(int i = 0; i < n; i++)
        dp[1 << i][i][0] = 1;
    for(int i = 0; i < 1<<n; i++){
        // i représente les éléments déjà utilisés
        for(int lst = 0; lst < n; lst++){
            // lst est le dernier élément qu'on a choisi pour le moment
            // vérifier que l'élément séléctionné est present dans le bitmask 
            if(i & (1 << lst))
                for(int cur = 0; cur < n; cur++){
                    // cur est l'élément qu'on va choisir pour la position suivante
                    // vérifier qu'il n'existe pas déjà dans le bitmask 
                    if(!(i & (1 << cur))){
                        int cout_act = abs(cur-lst); 
                        for(int cst = 0; cst <= l; cst++)
                            // cst est la somme des différences consécutifs des éléments déja présents
                            if(cst+cout_act <= l)
                                dp[i|(1 << cur)][cur][cst+cout_act] = (dp[i|(1 << cur)][cur][cst+cout_act]  + dp[i][lst][cst])%mod;
                    }
                }
        }
    }
    long long rep = 0;
    // la réponse finale est la somme des états qui ont une somme inférieur à l tels que tous les éléments sont utilisés
    // On ne s'intéresse pas donc au dernier élément choisi -> on somme tout les cas possibles
    for(int cst = 0; cst <= l; cst++) 
        for(int lst = 0; lst < n; lst ++){
            rep += dp[(1 << n)-1][lst][cst];
            rep %= mod;
        }
    return rep;
}
*/
long long dp2[N][N][L][3];

int sol3(vi A, int n, int l){
    // initialiser les cas de bases
    dp2[0][0][0][0] = 1;
    sort(A.begin(), A.end());
     for(int i = 1; i <= n; i++){
        for(int c = 1; c <= i; c++){
            //Vérifier que la nouvelle somme vérifie la condition
            for(int bouts = 0; bouts <= 2; bouts++){
                int mn_cst = 0;
                if(i < n) mn_cst = (A[i]-A[i-1]) * (2 * c - bouts);
                for(int cst = mn_cst; cst <= l; cst++){
                    int new_cst = cst ; 
                    if(i < n) new_cst -= (A[i]-A[i-1]) * (2 * c - bouts);
                    // Joindre deux composantes connexes
                    if(c+1 <= i-1) dp2[i][c][cst][bouts] += (c) * dp2[i-1][c+1][new_cst][bouts]; 
                    dp2[i][c][cst][bouts] %= mod;
                    // Ajouter a une composante existante sans créer un bout
                    dp2[i][c][cst][bouts] += (2*c-bouts) * dp2[i-1][c][new_cst][bouts];
                    dp2[i][c][cst][bouts] %= mod;
                    // Créer une nouvelle composante 
                    dp2[i][c][cst][bouts] += (c - bouts) * dp2[i-1][c-1][new_cst][bouts];
                    dp2[i][c][cst][bouts] %= mod;
                    // Créer un nouveau bout
                    if(bouts >= 1) dp2[i][c][cst][bouts] += (3-bouts) * dp2[i-1][c-1][new_cst][bouts-1];
                    dp2[i][c][cst][bouts] %= mod;
                    // Ajouter a une composante existante en créant un bout    
                    if(bouts >= 1) dp2[i][c][cst][bouts] += (3-bouts) * dp2[i-1][c][new_cst][bouts-1];
                    dp2[i][c][cst][bouts] %= mod;
                    cout << i << " " << c << " " << cst << " " << bouts << " " << dp2[i][c][cst][bouts] << endl;
                }
            }
        }
    }
    long long rep = 0;
    // la réponse finale est la somme des états qui ont une somme inférieur à l tels que :
    // on a utilisé tous les éléments 
    // 2 fermeture
    // une seule composante connexe
    for(int cst = 0; cst <= l; cst++) {
        rep += dp2[n][1][cst][2];
        cout << dp2[n][1][cst][2] << endl;
        rep %= mod;
    }
    return rep;
}

long long dp3[N][L][3];
long long lst_dp3[N][L][3];

int sol4(vi A, int n, int l){
    // initialiser les cas de bases
    lst_dp3[0][0][0] = 1;
    sort(A.begin(), A.end());
    for(int i = 1; i <= n; i++){
        for(int c = 1; c <= i; c++){
            //Vérifier que la nouvelle somme vérifie la condition
            for(int bouts = 0; bouts <= 2; bouts++){
                for(int cst = 0; cst <= l; cst++){
                    int new_cst = cst ; 
                    if(i < n) new_cst -= (A[i]-A[i-1]) * (2 * c - bouts);
                    // remettre dp3 à 0
                    dp3[c][cst][bouts] = 0;
                    if(new_cst < 0) continue;
                    // Joindre deux composantes connexes
                    if(c+1 <= i-1) dp3[c][cst][bouts] += (c) * lst_dp3[c+1][new_cst][bouts]; 
                    dp3[c][cst][bouts] %= mod;
                    // Ajouter a une composante existante sans créer un bout
                    dp3[c][cst][bouts] += (2*c-bouts) * lst_dp3[c][new_cst][bouts];
                    dp3[c][cst][bouts] %= mod;
                    // Créer une nouvelle composante 
                    dp3[c][cst][bouts] += (c - bouts) * lst_dp3[c-1][new_cst][bouts];
                    dp3[c][cst][bouts] %= mod;
                    // Créer un nouveau bout
                    if(bouts >= 1) dp3[c][cst][bouts] += (3-bouts) * lst_dp3[c-1][new_cst][bouts-1];
                    dp3[c][cst][bouts] %= mod;
                    // Ajouter a une composante existante en créant un bout    
                    if(bouts >= 1) dp3[c][cst][bouts] += (3-bouts) * lst_dp3[c][new_cst][bouts-1];
                    dp3[c][cst][bouts] %= mod;
                }
            }
        }
        for(int c = 0; c <= i; c++)
            for(int bouts = 0; bouts <= 2; bouts++)
                for(int cst = 0; cst <= l; cst++)
                    lst_dp3[c][cst][bouts] = dp3[c][cst][bouts];
    }
    long long rep = 0;
    // la réponse finale est la somme des états qui ont une somme inférieur à l tels que :
    // on a utilisé tous les éléments 
    // 2 fermeture
    // une seule composante connexe
    for(int cst = 0; cst <= l; cst++) {
        rep += lst_dp3[1][cst][2];
        rep %= mod;
    }
    return rep;
}

int main() {
    int N,L;
    cin >> N >> L;
    vi A;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        A.pb(a);
    } 
    if(N == 1) cout << 1 << endl;
    else cout << sol4(A,N,L) << endl;
}