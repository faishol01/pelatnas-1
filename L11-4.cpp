#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

#define PUB push_back
#define fi first
#define se second

const ll INF = (1LL << 60);
const ll MOD = 1e9+7;
const ll MAXMASK = (1LL << 16)+5;

int N, M;
ll dist[20][20], memo[20][MAXMASK], ans = INF;

void DP(int pos, ll mask){
	if(__builtin_popcountll(mask) == N){
		return;
	}else{
		for(int i=0;i<N;i++){
			if((mask & (1LL << i)) == 0){
				ll tmp_mask = (mask ^ (1LL << i));

				if(memo[i][tmp_mask] > memo[pos][mask] + dist[pos][i]){
					memo[i][tmp_mask] = memo[pos][mask] + dist[pos][i];
					DP(i, tmp_mask);
				}
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	for(int i=0;i<20;i++) for(ll j=0;j<MAXMASK;j++) 
		if(i == 0) memo[i][j] = 0;
		else memo[i][j] = INF;

	for(int i=0;i<20;i++) for(int j=0;j<20;j++){
		if(i == j) dist[i][j] = 0;
		else dist[i][j] = INF;
	}

	cin >> N >> M;
	for(int i=0;i<M;i++){
		ll u, v, d;
		cin >> u >> v >> d;
		dist[u][v] = d;
		dist[v][u] = d;
	}

	for(int k=0;k<N;k++){
		for(int i=0;i<N;i++) for(int j=0;j<N;j++){
			dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
		}
	}

	memo[0][1] = 0;
	DP(0, 1);

	ll ind = (1LL << N)-1;
	for(int i=1;i<N;i++)
		ans = min(ans, memo[i][ind] + dist[i][0]);

	cout << ans << endl;

	return 0;
}
