#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

#define PUB push_back
#define fi first
#define se second

int N;
ll light[100005], pjg[100005], ans = 0;
stack<ll> kanan, kiri;

int main(){
	cin >> N;
	for(int i=0;i<N;i++)
		cin >> light[i];

	//kanan -> kiri
	for(int i=0;i<N;i++){
		while(!kanan.empty() && light[kanan.top()] > light[i]){
			int ind = kanan.top();
			kanan.pop();

			pjg[ind] = (i-ind);
		}
		kanan.push(i);
	}

	while(!kanan.empty()){
		int ind = kanan.top();
		kanan.pop();

		pjg[ind] = N-ind;
	}

	//kiri -> kanan
	for(int i=N-1;i>=0;i--){
		while(!kiri.empty() && light[kiri.top()] > light[i]){
			int ind = kiri.top();
			kiri.pop();

			pjg[ind] += (ind-i);
		}
		kiri.push(i);
	}

	while(!kiri.empty()){
		int ind = kiri.top();
		kiri.pop();

		pjg[ind] += ind+1;
	}	

	for(int i=0;i<N;i++){
		ans = max(ans, (pjg[i]-1)*light[i]);
	}
	cout << ans << endl;
}
