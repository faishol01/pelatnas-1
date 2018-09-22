#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string lbl;
ll r1, r2, c1, c2, ans = 0, pgk;

ll cnt_grup(ll i, bool eks){
	ll bagian = (i + (1LL << pgk))/(1LL << pgk);
	ll ret = bagian/2;
	
	if(eks){
		if(bagian%2 == 0) ret--;
	}
	
	return ret;
}

int main(){
	getline(cin, lbl);
	cin >> r1 >> c1 >> r2 >> c2;
	pgk = 60-c2;
	
	ans = cnt_grup(r2, 0)-cnt_grup(r1, 1);
	
	bool stt=0;
	bitset<61>biner(r2);
	for(int i=60-c1;i>=60-c2;i--){
		if(biner[i]){
			if(!stt) stt = 1;
		}else{
			if(stt){
				ans++;
				stt = 0;
			}
		}
	}

	cout << ans << endl;
}
