#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, double> pdi;

#define PUB push_back
#define fi first
#define se second

const ll MOD = 1e9+7;
const double EPS = 1e-9;

struct Point{
	double x, y;
	Point():x(0), y(0){}
	Point(double _x, double _y): x(_x), y(_y){}

	bool operator<(Point a) const{
		return ((x == a.x) ? (y < a.y):(x < a.x)); }
};

struct dt{
	double t;
	int id;
	
	dt(double _t, int _id): t(_t), id(_id){}

	bool operator<(dt a) const{
		return a.t-t < EPS;
	}
};

double distTwoPoints(Point a, Point b){
	double x = pow(a.x-b.x, 2);
	double y = pow(a.y-b.y, 2);

	return sqrt(x+y);
}

bool found = 0;
double wkt_total[105];
double wkt_tempuh[105][105]; // menyimpan waktu tempuh dari titik ke-i ke ke-j
Point titik[105];
int N;

priority_queue<dt> pq;

int main(){
	ios_base::sync_with_stdio(0);

	for(int i=0;i<105;i++) wkt_total[i] = 999999999999.0;
	wkt_total[0] = 0.0;
		
	for(int i=0;i<2;i++) cin >> titik[i].x >> titik[i].y;
	cin >> N;
	for(int i=2;i<2+N;i++) cin >> titik[i].x >> titik[i].y;

	for(int i=2;i<2+N;i++) for(int j=2;j<2+N;j++){
		if(i == j) wkt_tempuh[i][j] = 0;
		else{
			double jarak = distTwoPoints(titik[i], titik[j]);
			
			wkt_tempuh[i][j] = 2.0;
			if(50.0-jarak >= EPS){
				wkt_tempuh[i][j] += (50.0-jarak)/5.0;
			}else{
				wkt_tempuh[i][j] += (jarak-50.0)/5.0;
			}
		}
	}

	for(int i=2;i<2+N;i++){
		double jarak1 = distTwoPoints(titik[0], titik[i]);
		wkt_tempuh[0][i] = jarak1/5.0;

		double jarak2 = distTwoPoints(titik[1], titik[i]);
		wkt_tempuh[i][1] = 2;
		if(50.0-jarak2 >= EPS){
			wkt_tempuh[i][1] += (50.0-jarak2)/5.0;
		}else{
			wkt_tempuh[i][1] += (jarak2-50.0)/5.0;
		}
	}
	wkt_tempuh[0][1] = distTwoPoints(titik[0], titik[1])/5.0;
	
	//Dijkstra Algo
	int cnt = 0;
	pq.push(dt(0.0, 0));
	while(!pq.empty()){
		int pos = pq.top().id;
		double dist = pq.top().t;

		pq.pop();
		
		if(pos == 1) continue;

		for(int i=0;i<2+N;i++){
			if(i == pos) continue;
			if(wkt_total[i]-(dist+wkt_tempuh[pos][i]) > EPS){
				wkt_total[i] = dist+wkt_tempuh[pos][i];
				pq.push(dt((dist+wkt_tempuh[pos][i]), i));
			}
		}
	}

	cout << fixed << setprecision(6) << wkt_total[1] << endl;

	return 0;
}
