#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

#define PUB push_back
#define fi first
#define second

const int INF = 999999999;

int N, M, ans = INF;
int warna[105];
int dist[105][105];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	for(int i=0;i<105;i++) for(int j=0;j<105;j++){
		if(i != j) dist[i][j] = INF;
		else dist[i][j] = 0;
	}

	cin >> N >> M;
	for(int i=0;i<N;i++)
		cin >> warna[i];

	for(int i=0;i<M;i++){
		int u, v;
		cin >> u >> v;
		u--; v--;

		if(warna[u] == warna[v]){
			dist[u][v] = 0;
			dist[v][u] = 0;
		}else{
			dist[u][v] = 1;
			dist[v][u] = 1;
		}
	}

	for(int i=0; i<N;i++) for(int j=0;j<N;j++) for(int k=0;k<N;k++){
		dist[j][k] = min(dist[j][k], dist[j][i]+dist[i][k]);
	}

	for(int i=0;i<N;i++){
		int tmp = 0;

		for(int j=0;j<N;j++){
			tmp = max(tmp, dist[i][j]);
		}

		ans = min(tmp, ans);
	}

	cout << ans << endl;

	return 0;	
}
