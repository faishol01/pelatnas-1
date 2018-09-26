#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pl;

#define PUB push_back
#define fi first
#define se second

struct edge{
	int v;
	ll d;	
};

int N, M, Q;
ll dist[2][50005], dist_total = LLONG_MAX;
// dist[0] -> menyimpan distance dari titik 0 ke semua titik
// dist[1] -> menyimpan distance dari titik N-1 ke semua titik

vector<edge> adjL[2][50005];
// adjL[0] -> menyimpan adjacency list yang asli
// adjL[1] -> menyimpan adjacency list yang telah dibalik

priority_queue<pl> pq;
// first -> nyimpen jarak
// second -> nyimpen pos

void dijkstra(int source, int id){
	for(int i=0;i<N;i++)
		dist[id][i] = 1e18;

	dist[id][source] = 0;
	pq.push({0, source});

	while(!pq.empty()){
		ll d_tmp = -1*pq.top().fi;
		int pos = pq.top().se;
		pq.pop();

		for(edge nxt:adjL[id][pos]){
			if(dist[id][nxt.v] > d_tmp + nxt.d){
				dist[id][nxt.v] = d_tmp + nxt.d;
				pq.push({-dist[id][nxt.v], nxt.v});
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> M >> Q;
	for(int i=0;i<M;i++){
		int u, v;
		ll d;
		cin >> u >> v >> d;

		adjL[0][u].PUB({v, d});
		adjL[1][v].PUB({u, d});
	}
	
	dijkstra(0, 0);
	dijkstra(N-1, 1);

	dist_total = dist[0][N-1];
	
	while(Q--){
		int u, v;
		ll d;

		cin >> u >> v >> d;

		if(dist[0][u]+dist[1][v]+d < dist_total) cout << "Ya" << endl;
		else cout << "Tidak" << endl;
	}

	return 0;	
}
