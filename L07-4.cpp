#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;

#define PUB push_back
#define fi first
#define se second

const int dC[]={0,0,+1,-1};
const int dR[]={+1,-1,0,0};

int R, C, sR, sC, fR, fC;
int maze[20][20], nearestWall[20][20], dist[20][20];
bool isVisit[20][20];

queue<pi>wall;
void BFSWall(){
	for(int i=0;i<=R+1;i++) for(int j=0;j<=C+1;j++){
		if(maze[i][j] == -1){
			wall.push({i, j});
			nearestWall[i][j] = 0;
		}
	}

	int byk = wall.size(),
		child = 0;
	int cnt = 1;

	while(!wall.empty()){
		if(byk == 0){
			cnt++;
			swap(byk, child);
		}

		int pR = wall.front().fi,
			pC = wall.front().se;
		
		wall.pop();

		for(int i=0;i<4;i++){
			int tR = pR + dR[i],
				tC = pC + dC[i];

			if(0 <= tR && tR <= R+1 && 0 <= tC && tC <= C+1){
				if(nearestWall[tR][tC] == -1){
					nearestWall[tR][tC] = cnt;

					wall.push({tR, tC});
					child++;
				}
			}
		}

		byk--;
	}

}

priority_queue<pii, vector<pii>, less<pii> >pq;
void dijkstra(){
	dist[sR][sC] = 0;
	pq.push({0, {sR, sC}});

	while(!pq.empty()){
		int pR = pq.top().se.fi,
			pC = pq.top().se.se;
		int dist_tmp = pq.top().fi;
		
		pq.pop();

		for(int i=0;i<4;i++){
			int tR = pR + dR[i],
				tC = pC + dC[i];

			if(0 <= tR && tR <= R+1 && 0 <= tC && tC <= C+1){
				if(maze[tR][tC] != -1 && dist[tR][tC] > dist_tmp+1){
					dist[tR][tC] = dist_tmp+1;
					pq.push({dist_tmp+1, {tR, tC}});
				}
			}
		}

		//cari tembok ter-
		for(int i=pR-1;i>0;i--){
			if(maze[i][pC] == -1) break;
			if(maze[i][pC] != -1 && maze[i-1][pC] == -1){
				if(dist_tmp + nearestWall[pR][pC] < dist[i][pC]){
					dist[i][pC] = dist_tmp + nearestWall[pR][pC];
					pq.push({dist[i][pC], {i, pC}});
				}

				break;
			}
		}

		for(int i=pR+1;i<=R;i++){
			if(maze[i][pC] == -1) break;
			if(maze[i][pC] != -1 && maze[i+1][pC] == -1){
				if(dist_tmp + nearestWall[pR][pC] < dist[i][pC]){
					dist[i][pC] = dist_tmp + nearestWall[pR][pC];
					pq.push({dist[i][pC], {i, pC}});
				}
				
				break;
			}
		}

		for(int i=pC-1;i>0;i--){
			if(maze[pR][i] == -1) break;
			if(maze[pR][i] != -1 && maze[pR][i-1] == -1){
				if(dist_tmp + nearestWall[pR][pC] < dist[pR][i]){
					dist[pR][i] = dist_tmp + nearestWall[pR][pC];
					pq.push({dist[pR][i], {pR, i}});
				}

				break;
			}
		}

		for(int i=pC+1;i<=C;i++){
			if(maze[pR][i] == -1) break;
			if(maze[pR][i] != -1 && maze[pR][i+1] == -1){
				if(dist_tmp + nearestWall[pR][pC] < dist[pR][i]){
					dist[pR][i] = dist_tmp + nearestWall[pR][pC];
					pq.push({dist[pR][i], {pR, i}});
				}

				break;
			}
		}
	}
}

void init(){
	memset(maze, -1, sizeof maze);
	memset(nearestWall, -1, sizeof nearestWall);
	
	for(int i=0;i<20;i++) for(int j=0;j<20;j++)
		dist[i][j] = 999999999;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	init();

	cin >> R >> C;
	for(int i=1;i<=R;i++) for(int j=1;j<=C;j++){
		char x;
		cin >> x;
		if(x == '.') maze[i][j] = 0;
		else if(x == 'O'){
			maze[i][j] = 1;
			sR = i;
			sC = j;
		}else if(x == 'X'){
			maze[i][j] = 2;
			fR = i;
			fC = j;
		}
	}

	BFSWall();
	dijkstra();


	if(dist[fR][fC] == 999999999) cout << -1 << endl;
	else cout << dist[fR][fC] << endl;

	return 0;	
}
