#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

#define PUB push_back
#define fi first
#define se second

const int LOG_TWO = log2(5e4+5);

int N, Q;
vector<pl>adjL[50005];
int depth[50005];
pl sparse[LOG_TWO+1][50005];

void DFS(int prn, int pos, int d){
	depth[pos] = d;
	sparse[0][pos].fi = prn;

	for(pl nxt:adjL[pos]){
		if(nxt.fi == prn) continue;
		sparse[0][nxt.fi].se = nxt.se;
		DFS(pos, nxt.fi, d+1);
	}
}

ll query(int u, int v, bool id){
	// id = 0 -> find LCA
	// id = 1 -> find distance

	ll dist = 0;
	if(depth[u] < depth[v]) swap(u, v);

	for(int i=LOG_TWO;i>=0;i--){
		if(depth[sparse[i][u].fi] >= depth[v]){
			dist += sparse[i][u].se;
			u = sparse[i][u].fi;
		}
	}
	
	if(u == v) return ((!id) ? u:dist);

	for(int i=LOG_TWO;i>=0;i--){
		if(sparse[i][u].fi != sparse[i][v].fi){
			dist += sparse[i][u].se + sparse[i][v].se;

			u = sparse[i][u].fi;
			v = sparse[i][v].fi;
		}
	}

	dist += sparse[0][u].se + sparse[0][v].se;
	return ((!id) ? sparse[0][u].fi:dist);	
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	memset(sparse, -1, sizeof sparse);
	memset(depth, -1, sizeof depth);

	cin >> N;
	for(int i=0;i<N-1;i++){
		int u, v, w;
		cin >> u >> v >> w;
		adjL[u].PUB({v, w});
		adjL[v].PUB({u, w});
	}
	
	DFS(-1, 0, 0);
	for(int i=1;i<=LOG_TWO;i++)
		for(int j=1;j<=N;j++)
			if(sparse[i-1][j].fi != -1){
				sparse[i][j].fi = sparse[i-1][sparse[i-1][j].fi].fi;
				sparse[i][j].se = sparse[i-1][j].se +
									sparse[i-1][sparse[i-1][j].fi].se;
			}
	
	cin >> Q;
	while(Q--){
		ll ans = 0;
		int arr[5];
		for(int i=0;i<5;i++) cin >> arr[i];
		
		int lca_bef = query(arr[0], arr[1], 0);
		ans += query(arr[0], arr[1], 1);

		for(int i=2;i<5;i++){
			int lca_tmp = query(lca_bef, arr[i], 0);
			if(lca_tmp == lca_bef){
				for(int j=i-1;j>=0;j--){
					int lca_tmp_tmp = query(arr[j], arr[i], 0);
					if(depth[lca_tmp_tmp] > depth[lca_tmp])
						lca_tmp = lca_tmp_tmp;
				}
				ans += query(lca_tmp, arr[i], 1);
			}else{
				ans += query(lca_bef, arr[i], 1);
				lca_bef = lca_tmp;
			}
		}

		cout << ans << endl;
	}
}
