#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9+7;

int T;
ll N, X, fakt[100005], derangement[100005], ans;

ll modexp(ll b, ll e, ll m){
	ll ret = 1;
	b %= m;
	while(e>0){
		if(e&1) ret = ret*b % m;

		e >>= 1;
		b = b*b % m;
	}

	return ret;
}

ll combin(ll n, ll k, ll m){
	ll ret = fakt[n];
	ret = ret * modexp(fakt[k]*fakt[n-k], m-2, m) % m;

	return ret;
}

int main(){
	fakt[0] = 1;
	derangement[1] = 0; derangement[0] = 1;

	for(int i=1;i<100005;i++){
		fakt[i] = (i * fakt[i-1]) % MOD;
		if(i > 1) derangement[i] = (i-1)*(derangement[i-1]+derangement[i-2]) % MOD;
	}

	cin >> T;
	while(T--){
		cin >> N >> X;
		
		ans = 0;
		for(int i=X;i<=N;i++){
			ll tmp;
			tmp = fakt[N];
			tmp = tmp*combin(N,i, MOD) % MOD;
			tmp = tmp*derangement[N-i] % MOD;

			ans = (ans+tmp) % MOD;
		}
		cout << ans << endl;

	}

}
