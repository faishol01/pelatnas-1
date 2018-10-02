#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

#define PUB push_back
#define fi first
#define se second

const ll MOD = 1e9+7;
const double EPS = 1e-9;

struct Edge{
	int u, v;
	Edge(): u(0), v(0){}
	Edge(int _u, int _v): u(_u), v(_v){}

	bool operator<(Edge a)const{
		return ((u == a.u) ? (v < a.v):(u < a.u));
	}
};

int N, M;
int idAwal[1000005];
vector<int> teman_satu;
vector<Edge> edgL;

vector<int>ans;
bool isJoin[1000005];

void checkFriend(int pos){
	int anggota = ans.size(),
		cnt = 0;

	for(int i=idAwal[pos];i < 2*N && edgL[i].u == pos;i++){
		if(isJoin[edgL[i].v]) cnt++;
	}

	if(cnt == anggota){
		ans.PUB(pos);
		isJoin[pos] = 1;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	memset(idAwal, -1, sizeof idAwal);

	cin >> N >> M;
	for(int i=0;i<M;i++){
		int u, v;
		cin >> u >> v;
	
		edgL.PUB(Edge(u, v));
		edgL.PUB(Edge(v, u));

		if(u == 1) teman_satu.PUB(v);
		if(v == 1) teman_satu.PUB(u);
	}
	
	sort(edgL.begin(), edgL.end());
	sort(teman_satu.begin(), teman_satu.end());
	
	int cnt = 0;
	for(Edge pos:edgL){
		if(idAwal[pos.u] == -1){
			idAwal[pos.u] = cnt;
		}
		cnt++;
	}
	
	ans.PUB(1);
	isJoin[1] = 1;
	if(!teman_satu.empty()){
		ans.PUB(teman_satu.front());
		isJoin[teman_satu.front()] = 1;
	}

	int sz = teman_satu.size();
	for(int i=1;i<sz;i++){
		checkFriend(teman_satu[i]);
	}

	for(int i=0;i<ans.size()-1;i++) cout << ans[i] << " ";
	cout << ans.back() << endl;

	return 0;
}
