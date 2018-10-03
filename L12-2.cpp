#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

#define PUB push_back
#define fi first
#define se second

int N;
ll ans = 0;
pl data[100005];
priority_queue<ll>pq;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> N;
	for(int i=0;i<N;i++)
		cin >> data[i].fi >> data[i].se;
	
	for(int i=N-1;i>=0;i--){
		ans += data[i].se;
		if(i&1){
			// Captain
			if(i == N-1) ans += data[i].fi-data[i].se;
			else{
				ll tmp = -1*pq.top(),
					tmp2 = data[i].fi-data[i].se;
				pq.pop();
				ans += min(tmp, tmp2);
				pq.push(-1*max(tmp, tmp2));
			}
		}else{
			// Assistant
			pq.push(-1*(data[i].fi-data[i].se));
		}
	}

	cout << ans << endl;		

	return 0;	
}
/*
10
100000 98387 
100000 2734
100000 2348
100000 349
100000 23
100000 83742
100000 2382
100000 859
100000 24
100000 1

expected output: 601131

*/
