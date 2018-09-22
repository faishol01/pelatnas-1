#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

#define PUB push_back
#define fi first
#define se second

const int MAXN = 1e5+5;

int N, Q;
int num[MAXN], byk[MAXN], sum[MAXN];
vector<int>UFDS[MAXN];

void gabung(int dari, int ke){
	if(dari == ke) return;

	sum[ke] += sum[dari];
	byk[ke] += byk[dari];

	sum[dari] = 0;
	byk[dari] = 0;

	while(!UFDS[dari].empty()){
		int now = UFDS[dari].back();
		UFDS[dari].pop_back();
		
		if(num[now] == dari){
			UFDS[ke].push_back(now);
			num[now] = ke;
		}
	}
}

void pindah(int x, int ke){
	byk[num[x]]--;
	sum[num[x]] -= x;
	
	byk[ke]++;
	sum[ke] += x;

	num[x] = ke;
	UFDS[ke].push_back(x);
}

int main(){
	for(int i=1;i<MAXN;i++){
		num[i] = i;
		sum[i] = i;
		byk[i] = 1;

		UFDS[i].PUB(i);
	}

	cin >> N >> Q;
	
	// cout << "=============\n";
	// 	for(int i=1;i<=N;i++){
	// 		cout << i << " -> ";
	// 		for(auto nxt:UFDS[i]) cout << i << " ";
	// 			cout << endl;
	// 	}
	// cout << "=============\n";

	while(Q--){
		int id;
		cin >> id;
	
		if(id == 1){
			int p, q;
			cin >> p >> q;

			if(byk[num[p]] > byk[num[q]]) gabung(num[q], num[p]);
			else gabung(num[p], num[q]);

		}else if(id == 2){
			int p, q;
			cin >> p >> q;

			if(num[p] != num[q]) pindah(p, num[q]);

		}else{
			int p;
			cin >> p;

			cout << byk[num[p]] << " " << sum[num[p]] << endl;
		}

		// cout << "=============\n";
		// for(int i=1;i<=N;i++){
		// 	cout << i << " -> ";
		// 	for(auto nxt:UFDS[i]) cout << nxt << " ";
		// 		cout << endl;
		// }
		// cout << "=============\n";
	}
}
