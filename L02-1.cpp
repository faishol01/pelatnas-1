#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9+7;

ll N, M, F[100005], G[100005];
ll matriks_proses[75][75], matriks_hasil[75][75], matriks_tmp[75][75];
ll fungsi[75], ans = 0, sz;

void subtask1(){
	F[0] = 1;
	G[0] = 1;
	for(int i=1;i<M;i++){
		F[i] = 1;
		G[i] = (F[i] + G[i-1])%MOD;
	}

	F[M] = 2;
	G[M] = (G[M-1] + F[M])%MOD;
	
	for(int i=M+1;i<=N;i++){
		F[i] = F[i-1] + G[i-M-1] + 1;
		G[i] = (G[i-1] + F[i])%MOD;
	}

	cout << F[N]%MOD << endl;
}

void modexp_matriks(ll e){
	while(e > 0){
		if(e&1){
			// Perkalian proses dengan hasil, simpan di tmp
			for(int i=0;i<sz;i++) for(int j=0;j<sz;j++){
				ll htg = 0;
				for(int k=0;k<sz;k++){
					htg = (htg + matriks_proses[i][k] * matriks_hasil[k][j] % MOD) % MOD;
				}

				matriks_tmp[i][j] = htg;
			}

			for(int i=0;i<sz;i++) for(int j=0;j<sz;j++)
				matriks_hasil[i][j] = matriks_tmp[i][j];
		}

		e >>= 1;

		// Perkalian proses dengan proses, simpan di tmp
		for(int i=0;i<sz;i++) for(int j=0;j<sz;j++){
			ll htg = 0;
			for(int k=0;k<sz;k++){
				htg = (htg + matriks_proses[i][k] * matriks_proses[k][j] % MOD) % MOD;
			}

			matriks_tmp[i][j] = htg;
		}

		for(int i=0;i<sz;i++) for(int j=0;j<sz;j++)
			matriks_proses[i][j] = matriks_tmp[i][j];
	}
}

int main(){
	// untuk setiap m, f(n) =
	// 1						untuk n < m
	// 2						untuk n = m
	// f(n-1) + g(n-m-1) + 1	untuk n > m
	//
	// dimana g(x) = f(0) + f(1) + f(2) + ... + f(x)
	
	cin >> N >> M;
	if(N < M) cout << 1 << endl;
	else{
		sz = M + 4;

		memset(matriks_proses, 0, sizeof matriks_proses);
		
		for(int i=1;i<sz-1;i++){
			matriks_proses[i][i+1] = 1;
		}

		matriks_proses[0][0] = 1;
		matriks_proses[2][0] = matriks_proses[2][2] = 1;
		matriks_proses[sz-1][0] = matriks_proses[sz-1][2] = matriks_proses[sz-1][3] = matriks_proses[sz-1][sz-1] = 1;

		for(int i=0;i<sz;i++) matriks_hasil[i][i] = 1;

		fungsi[0] = fungsi[1] = 1;
		fungsi[2] = 2;
		for(int i=3;i<sz;i++){
			fungsi[i] = i-2;
		}
		fungsi[sz-1]++;

		modexp_matriks(N-M);
		
		// for(int i=0;i<sz;i++) for(int j=0;j<sz;j++){
		// 	cout << matriks_hasil[i][j] << " ";
		// 	if(j == sz-1) cout << endl;
		// }

		for(int i=0;i<sz;i++){
			ans = (ans + matriks_hasil[2][i]*fungsi[i] % MOD)%MOD;
		}
		cout << ans << endl;
	}
}
