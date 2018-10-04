#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

#define PUB push_back
#define fi first
#define se second

const ll MOD = 1e9+7;

int N, memo[3][100005];
vector<int> adjL[100005];

int DP(int prn, int pos, int stt){
	// stt 	-> 0 : parentku putih, aku putih
	//		-> 1 : kolam
	//		-> 2 : parentku hitam, aku putih

	int &ret = memo[stt][pos];
	if(ret >= 0) return ret;

	ret = 0;
	if(stt == 1) ret = 1;
	if(stt == 0) ret = 1e6;

	for(int nxt:adjL[pos]){
		if(nxt == prn) continue;

		if(stt == 0){
			int tmp = DP(pos, nxt, 1);

			for(int nxt2:adjL[pos]){
				if(nxt2 == prn || nxt2 == nxt) continue;
				tmp += DP(pos, nxt2, 0);
			}

			ret = min(ret, tmp);
		}else if(stt == 1){
			ret += min(DP(pos, nxt, 1), DP(pos, nxt, 2));
		}else{
			ret += DP(pos, nxt, 0);
		}
	}

	return ret;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	memset(memo, -1, sizeof memo);

	cin >> N;

	for(int i=0;i<N-1;i++){
		int u, v;
		cin >> u >> v;
		adjL[u].PUB(v);
		adjL[v].PUB(u);
	}
	
	int ans = min(DP(1, 1, 0), DP(1, 1, 1));
	cout << ans << endl;
	return 0;
}
