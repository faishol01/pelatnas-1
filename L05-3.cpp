#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

#define PUB push_back
#define fi first
#define se second

int N, tipe[300005], child[300005][2], precomp[300005];
bool nilai[300005], ans[300005];

bool operasi(int id, bool val1, bool val2){
	if(id == 0) return (val1 & val2);
	else if(id == 1) return (val1 | val2);
	else if(id == 2) return (val1 ^ val2);
	else if(id == 3) return (!val1);
}

bool DFS(int pos){
	if(pos == -1) return 0;

	if(tipe[pos] == 4){
		precomp[pos] = nilai[pos];
		return nilai[pos];
	}else{
		return precomp[pos] = operasi(tipe[pos], DFS(child[pos][0]), DFS(child[pos][1]));
	}
}

void DFS2(int pos){
	if(tipe[pos] <= 2){
		bool ret1 = operasi(tipe[pos], precomp[child[pos][0]]^1, precomp[child[pos][1]]);
		bool ret2 = operasi(tipe[pos], precomp[child[pos][0]], precomp[child[pos][1]]^1);
		
		if(ret1 != precomp[pos]) 
			DFS2(child[pos][0]);
		
		if(ret2 != precomp[pos]) 
			DFS2(child[pos][1]);
	}else if(tipe[pos] == 3){
		DFS2(child[pos][0]);
	}else{
		ans[pos] ^= 1;
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	memset(child, -1, sizeof child);

	cin >> N;
	for(int i=1;i<=N;i++){
		cin >> tipe[i];

		if(tipe[i] <= 2) cin >> child[i][0] >> child[i][1];
		else if(tipe[i] == 4) cin >> nilai[i];
		else cin >> child[i][0];
	}
	
	DFS(1);
	for(int i=1;i<=N;i++){
		if(tipe[i] == 4) ans[i] = precomp[1];
	}
	
	DFS2(1);

	for(int i=1;i<=N;i++)
		if(tipe[i] == 4) cout << ans[i];
	cout << endl;

	return 0;
}
