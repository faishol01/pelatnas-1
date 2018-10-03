#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

#define PUB push_back
#define fi first
#define se second

int N, K, ans = 0;
int data[100005];
vector<int> adjL[100005];

int DFS(int prn, int pos){
	int depth = 1;
	for(int nxt:adjL[pos]){
		depth = max(DFS(pos, nxt), depth);
	}

	if(depth == K && prn != 1){
		ans++;
		data[pos] = 1;
		return 1;
	}else return depth+1;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> K;
	for(int i=1;i<=N;i++){
		cin >> data[i];
		
		if(i > 1)
			adjL[data[i]].PUB(i);
	}
	
	if(data[1] != 1){
		ans++;
		data[1] = 1;
	}

	DFS(1, 1);

	// for(int i=1;i<=N;i++) cout << i%10 << " ";
	// cout << endl;
	// for(int i=1;i<=N;i++) cout << data[i] << " ";
	// cout << endl;

	cout << ans << endl;

	return 0;	
}

/*
14 2
1 1 1 3 4 4 5 5 5 5 6 6 6 6

expected output: 2

7 3 
1 1 1 3 4 5 5

expected output: 1
*/
