#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

#define PUB push_back
#define fi first
#define se second

struct apa{
	int u, v;
	ll dist;
};

int N, A[1005][1005];
bool isValid = 1;
vector<pi>adjL[1005];

vector <apa> edgL;

int prn[1005];

int find_prn(int a){
	if(prn[a] == a) return a;
	else return prn[a] = find_prn(prn[a]);
}

bool isSame(int a, int b){
	return (find_prn(a) == find_prn(b));
}

void joinSet(int a, int b){
	int prnA = find_prn(a),
		prnB = find_prn(b);

	if(prnA == prnB) return;
	prn[prnA] = prnB;
}

bool cmp(apa a, apa b){
	if(a.dist == b.dist){
		if(a.u == b.u) return a.v < b.v;
		return a.u < b.u;
	}
	return a.dist < b.dist;
}

void DFS(int root, int bef, int pos, ll tot){
	if(A[root][pos] != tot){
		isValid = 0;
		return;
	}

	for(pi nxt:adjL[pos]){
		if(bef != nxt.fi)
			DFS(root, pos, nxt.fi, tot+nxt.se);
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	for(int i=0;i<1005;i++) prn[i] = i;

	cin >> N;
	for(int i=0;i<N;i++) for(int j=0;j<N;j++){
		cin >> A[i][j];
		if(i < j) edgL.PUB({i, j, A[i][j]});
	}
	
	sort(edgL.begin(), edgL.end(), cmp);

	for(apa dt:edgL){
		if(!isSame(dt.u, dt.v)){
			joinSet(dt.u, dt.v);
			adjL[dt.u].PUB({dt.v, dt.dist});
			adjL[dt.v].PUB({dt.u, dt.dist});
		}
	}

	for(int i=0;i<N;i++){
		DFS(i, -1, i, 0);
	}

	if(isValid) cout << "Ya\n";
	else cout << "Tidak\n";
}
