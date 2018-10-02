#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define PUB push_back

const ll MOD = 1e9+7;
const double EPS = 1e-15;
const double PI = acos(-1);

struct Point{	
	ll x, y;
	Point(): x(0), y(0){}
	Point(ll _x, ll _y): x(_x), y(_y){}

	bool operator<(Point a) const{
		return ((x == a.x) ? (y < a.y):(x < a.x));
	}
};

struct Vec{
	ll x, y;
	Vec(): x(0), y(0){}
	Vec(Point a, Point b){
		x = b.x - a.x;
		y = b.y - a.y; }
};

ll crossProduct(Vec a, Vec b){
	return (a.x * b.y - a.y * b.x);
}

int orientation(Point a, Point b, Point c){
	// -1 = CW, 0 = Collinear, 1 = CCW

	ll cross = crossProduct(Vec(b, a), Vec(b, c));
	if(cross > 0) return 1;
	else if(cross == 0) return 0;
	else return -1;
}

ll findArea(vector<Point> P){
	// Assume open Polygon
	ll ret = 0;
	for(int i=0;i<P.size()-1;i++){
		ret += P[i].x * P[i+1].y;
		ret -= P[i].y * P[i+1].x;
	}

	ret += P[P.size()-1].x * P[0].y;
	ret -= P[P.size()-1].y * P[0].x;

	ret = abs(ret);
	return ret;
}

bool rev_cmp(Point a, Point b){
	return ((a.x == b.x) ? (a.y > b.y):(a.x > b.x));
}

void ConvexHull(vector<Point> &dt, vector<Point> &P){
	// Monotone chain algorithm
	// No same point in dt
	vector<Point> up, low;

	// Find upper hull
	sort(dt.begin(), dt.end());

	up.PUB(dt[0]); up.PUB(dt[1]);
	for(int i=2;i<dt.size();i++){
		int arah = orientation(up[up.size()-2], up.back(), dt[i]);

		while(arah != 1){
			up.pop_back();

			if(up.size() == 1) break;
			arah = orientation(up[up.size()-2], up.back(), dt[i]);			
		}

		up.PUB(dt[i]);
	}

	for(int i=0;i<up.size();i++) P.PUB(up[i]);

	// Find lower hull
	sort(dt.begin(), dt.end(), rev_cmp);
	
	low.PUB(dt[0]); low.PUB(dt[1]);
	for(int i=2;i<dt.size();i++){
		int arah = orientation(low[low.size()-2], low.back(), dt[i]);
		
		while(arah != 1){	
			low.pop_back();

			if(low.size() == 1) break;
			arah = orientation(low[low.size()-2], low.back(), dt[i]);
		}
		
		low.PUB(dt[i]); 
	}

	for(int i=1;i<low.size()-1;i++) P.PUB(low[i]);
}

int N;
ll areaBenda, areaTempat;
vector<Point>benda, tempat;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N;
	for(int i=0;i<N;i++){
		ll x, y;
		cin >> x >> y;

		benda.PUB(Point(x,y));
	}
	
	areaBenda = findArea(benda);

	ConvexHull(benda, tempat);

	areaTempat = findArea(tempat);
	double ans = double(areaTempat-areaBenda)*100.0/(double) areaTempat;
	cout << fixed << setprecision(4) << ans << endl;
}
