#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

#define PUB push_back
#define fi first
#define se second

const int LOG_TWO = log2(2e5+5);

struct query{
	int x, y, z;
	query(): x(0), y(0), z(0) {}
	query(int _x, int _y, int _z): x(_x), y(_y), z(_z) {}
};

int Q, N = 1;
int depth[200005], sparse[LOG_TWO+1][200005];
vector<int>adjL[200005];
vector<query>data;

void DFS(int prn, int pos, int d){
	depth[pos] = d;
	sparse[0][pos] = prn;

	for(int nxt:adjL[pos])
		DFS(pos, nxt, d+1);
}

int find_LCA(int u, int v){
	if(depth[u] < depth[v]) swap(u, v);

	for(int i=LOG_TWO;i>=0;i--){
		if(depth[sparse[i][u]] >= depth[v])
			u = sparse[i][u];
	}
	
	if(u == v) return u;

	for(int i=LOG_TWO;i>=0;i--){
		if(sparse[i][u] != sparse[i][v]){
			u = sparse[i][u];
			v = sparse[i][v];
		}
	}
	
	return sparse[0][u];
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	memset(depth, -1, sizeof depth);
	memset(sparse, -1, sizeof sparse);

	cin >> Q;
	while(Q--){
		int id, x, y, z;
		cin >> id >> x;
		if(id == 1) adjL[x].PUB(++N);
		else{
			cin >> y >> z;
			data.PUB(query(x, y, z));
		}
	}

	// Build sparse table for LCA
	DFS(-1, 1, 0);
	for(int i=1;i<=LOG_TWO;i++)
		for(int j=1;j<=N;j++)
			if(sparse[i-1][j] != -1)
				sparse[i][j] = sparse[i-1][sparse[i-1][j]];
	
	// Solve query 
	for(query elm:data){
		int xy = find_LCA(elm.x, elm.y),
			xz = find_LCA(elm.x, elm.z),
			yz = find_LCA(elm.y, elm.z);

		if(xy == xz && xz == yz) cout << xy << endl;
		else if(xz == xy) cout << yz << endl;
		else if(yz == xy) cout << xz << endl;
		else if(xz == yz) cout << xy << endl;
	}
}
