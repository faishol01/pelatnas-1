#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

#define PUB push_back
#define fi first
#define se second

struct koder{
	ll a, h, ind;
	koder(): a(0), h(0), ind(0) {}
	koder(ll _a, ll _h, ll _ind): a(_a), h(_h), ind(_ind) {}

	bool operator <(koder x) const{
		if(a == x.a){
			if(h == x.h) return ind < x.ind;
			return h < x.h;
		}
		return a < x.a; 
	}
};

int N, ans[300005], terkiri[100005];
vector<koder> data;
int BIT[100005];

ll htg_sama(int l, int r, int src){
	int tl = l, tr = r;
	int up = -1, low = -1;

	//upper bound
	while(l <= r){
		int mid = (l+r)/2;
		if(data[mid].h >= src){
			if(up == -1) up = mid;
			else up = min(up, mid);
			r = mid-1;
		}else if(data[mid].h < src) l = mid+1;
	}

	//lower bound
	l = tl, r = tr;
	while(l <= r){
		int mid = (l+r)/2;
		if(data[mid].h <= src){
			if(low == -1) low = mid;
			else low = max(low, mid);
			l = mid+1;
		}else if(data[mid].h > src) r = mid-1;
	}
	
	return abs(up-low)+1;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	memset(terkiri, -1, sizeof terkiri);

	cin >> N;
	for(int i=0;i<N;i++){
		koder tmp;
		tmp.ind = i;

		cin >> tmp.a >> tmp.h;
		
		data.PUB(tmp);
	}

	sort(data.begin(), data.end());
	
	for(int i=0;i<N;i++){
		if(terkiri[data[i].a] == -1)
			terkiri[data[i].a] = i;

		for(int j=data[i].h;j>0;j-=(j & (-j)))
			ans[data[i].ind] += BIT[j];
		
		for(int j=data[i].h; j<=100000; j += (j & (-j)))
			BIT[j]++;
		
		ans[data[i].ind] -= htg_sama(terkiri[data[i].a], i, data[i].h)-1;
	}

	for(int i=0;i<N;i++)
		cout << ans[i] << endl;
}
