#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

#define PUB push_back
#define fi first
#define se second

const ll MOD = 1e9+7;
const double EPS = 1e-9;
const double PI = acos(-1);

struct Point{	
	double x, y;
	Point(): x(0), y(0){}
	Point(double _x, double _y): x(_x), y(_y){}

	bool operator<(Point a) const{
		return ((x == a.x) ? (y < a.y):(x < a.x));
	}
};

struct Line{
	double a, b, c;
	Line(double _a, double _b, double _c): a(_a), b(_b), c(_c){}
	Line(Point _A, Point _B){
		a = _B.y - _A.y;
		b = _B.x - _A.x;
		c = _A.x * _B.y - _A.y * _B.x; }
	Line(Point _A, double m){
		a = -m;
		b = 1;
		c = m * _A.x - _A.y; }
};

struct Segment{
	Point a, b;
	Segment(Point _a, Point _b): a(_a), b(_b){}
};

struct Vec{
	double x, y;
	Vec(): x(0), y(0){}
	Vec(Point a, Point b){
		x = b.x - a.x;
		y = b.y - a.y; }
};

double dotProduct(Vec a, Vec b){
	return (a.x * b.x + a.y * b.y);
}

double crossProduct(Vec a, Vec b){
	return (a.x * b.y - a.y * b.x);
}

int orientation(Point a, Point b, Point c){
	// -1 = CW, 0 = Collinear, 1 = CCW

	double cross = crossProduct(Vec(b, a), Vec(b, c));
	if(cross > 0) return 1;
	else if(fabs(cross) < EPS) return 0;
	else return -1;
}

double findArea(vector<Point> P){
	// Assume open Polygon
	double ret = 0;
	for(int i=0;i<P.size()-1;i++){
		ret += P[i].x * P[i+1].y;
		ret -= P[i].y * P[i+1].x;
	}

	ret += P[P.size()-1].x * P[0].y;
	ret -= P[P.size()-1].y * P[0].x;

	ret = fabs(ret);
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
bool isActive[2005];
vector<pi>byX, byY;
ll ans = 0;

bool cmp(pi a, pi b){
	return a.fi < b.fi;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	memset(isActive, 0, sizeof isActive);

	cin >> N;
	for(int i=1;i<=N;i++){
		Point st, fi;
		cin >> st.x >> st.y >> fi.x >> fi.y;
	
		byY.PUB({st.y, i});
		byY.PUB({fi.y, -i});

		byX.PUB({st.x, i});
		byX.PUB({fi.x, i});
	}

	sort(byX.begin(), byX.end(), cmp);
	sort(byY.begin(), byY.end(), cmp);
	
	for(int i=0;i<2*N;i++){
		ll dX = byX[i+1].fi - byX[i].fi;
		ll strY = -1;

		int cnt = 0;

		isActive[byX[i].se] ^= 1;

		for(int j=0;j<2*N;j++){
			int ind = byY[j].se;

			if(ind > 0){
				if(isActive[ind]){
					if(cnt == 0)
						strY = byY[j].fi;
					
					cnt++;
				}
			}else{
				if(isActive[-ind]){
					cnt--;
				}
			}

			if(cnt == 0 && strY != -1){
				ans += dX*(byY[j].fi-strY);
				strY = -1;
			}
		}
	}

	cout << ans << endl;	
}
