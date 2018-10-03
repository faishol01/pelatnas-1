#include <bits/stdc++.h>
using namespace std;

#define PUB push_back

const double EPS = 1e-9;

int N, M, K, ansId = 0;
double sumE[5005];
int dist[2][5005];
vector<int>adjL[5005];

int ways[2][5005];
queue<int>q;

void traverse(int a, int b, int id){
	int jrk = 1,
		cnt = 1,
		child = 0;

	ways[id][a] = 1; dist[id][a] = 0;
	q.push(a);
	while(!q.empty()){
		if(cnt == 0){
			jrk++;
			swap(cnt, child);
		}

		int pos = q.front();
		q.pop();

		for(int nxt:adjL[pos]){
			if(dist[id][nxt] == -1){
				dist[id][nxt] = jrk;
				ways[id][nxt] += ways[id][pos];
				q.push(nxt);
				child++;
			}else if(dist[id][nxt] == jrk)
				ways[id][nxt] += ways[id][pos];
		}

		cnt--;
	}
}

int main(){
	for(int i=0;i<5005;i++)
		sumE[i] = 0;
	 
	cin >> N >> M;
	for(int i=0;i<M;i++){
		int u, v;
		cin >> u >> v;

		adjL[u].PUB(v);
		adjL[v].PUB(u);
	}

	cin >> K;
	for(int i=0;i<K;i++){
		int a, b;
		cin >> a >> b;
		
		memset(ways, 0, sizeof ways);
		memset(dist, -1, sizeof dist);
	
		traverse(a, b, 0);
		traverse(b, a, 1);
		
		int tot_ways = ways[0][b],
			tot_dist = dist[0][b];
		for(int j=0;j<N;j++){
			if(dist[0][j]+dist[1][j] == tot_dist){
				double tmp = max(ways[0][j], ways[1][j]);
				tmp /= (double) tot_ways;
				sumE[j] += tmp;
			}
		}
	}

	for(int i=0;i<N;i++)
		if(sumE[i]-sumE[ansId] > EPS)
			ansId = i;

	cout << ansId << endl;
}
