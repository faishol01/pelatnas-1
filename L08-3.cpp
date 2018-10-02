#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const double PI = acos(-1.0);
const double EPS = 1e-9;

struct Point{
	ll x, y;
	
	Point(){x = y = 0;}
	Point(ll _x, ll _y):x(_x), y(_y) {}	
};

struct Line{
	//store ax + by + c = 0
	ll a, b, c;

	Line(){a = b = c = 0;}
	Line(ll _a, ll _b, ll _c): a(_a), b(_b), c(_c) {}
};

struct Vec{
	ll x, y;
	Vec(ll _x, ll _y): x(_x), y(_y) {}
};

Vec toVec(Point a, Point b){
	return Vec(b.x - a.x, b.y - a.y);
}

Vec scale(Vec v, ll k){
	return Vec(v.x * k, v.y * k);
}

ll vecSquare(Vec u){
	return u.x*u.x + u.y*u.y;
}

ll dotProduct(Vec a, Vec b){
	return (a.x * b.x + a.y * b.y);
}

ll crossProduct(Vec a, Vec b){
	return (a.x * b.y - a.y * b.x);
}

int orientation(Point a, Point b, Point c){
	// -1 = CW, 0 = Colliniear, 1 = CCW
	ll cross = crossProduct(toVec(a, b), toVec(a, c));

	if(cross == 0) return 0;
	else if(cross > 0) return 1;
	else return -1;
}

double angle(Point a, Point o, Point b){
	Vec oa = toVec(o, a),
		ob = toVec(o, b);
	return acos(dotProduct(oa, ob) / sqrt((vecSquare(oa)+vecSquare(ob))));
}

bool insidePolygon(vector<Point> polygon, Point p){
	double sum_rad = 0;
	for(int i=0;i<polygon.size()-1;i++){
		if(orientation(p, polygon[i], polygon[i+1]) == 1)
			sum_rad += angle(polygon[i], p, polygon[i+1]);
		else sum_rad -= angle(polygon[i], p, polygon[i+1]);
	}

	return fabs(fabs(sum_rad)-2*PI) < EPS;
}

ll distTwoPointSq(Point a, Point b){
	return pow((a.x-b.x),2)+pow((a.y-b.y), 2);
}

Line toLine(Point a, Point b){
	return Line(a.y-b.y, b.x-a.x, a.x*b.y-b.x*a.y);
}

ll N, ans;
Point data[2005];
vector<Line> tarik;
bool stt[2005][2005];

ll hitung(ll x){
	if(x < 3) return 0;
	return x*(x-1)*(x-2)/6;
}

ll hitung2(ll x){
	if(x < 2) return 0;
	return x*(x-1)/2;
}

bool cmp(Line a, Line b){
	if(a.a == b.a){
		if(a.b == b.b) return a.c < b.c;
		return a.b < b.b;
	}
	return a.a < b.a;
}

int main(){
	cin >> N;
	for(int i=0;i<N;i++){
		cin >> data[i].x >> data[i].y;
	}
	ans = hitung(N);
	
	for(int i=0;i<N;i++){
		vector<Line>tmp;
		
		for(int j=i+1;j<N;j++){
			tmp.push_back(toLine(data[i], data[j]));
			
			ll fpb = __gcd(tmp.back().a, __gcd(tmp.back().b, tmp.back().c));
			tmp.back().a /= fpb;
			tmp.back().b /= fpb;
			tmp.back().c /= fpb;
		}

		sort(tmp.begin(), tmp.end(), cmp);
		
		ll pos = 0;
		for(int j=1;j<tmp.size();j++){
			if(tmp[j].a != tmp[j-1].a || tmp[j].b != tmp[j-1].b || tmp[j].c != tmp[j-1].c){
				ll byk = j-pos;
				ans -= hitung2(byk);
				pos = j;
			}
		}

		ans -= hitung2(tmp.size()-pos);
	}

	cout << ans << endl;
}
