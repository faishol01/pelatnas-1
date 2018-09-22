#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int B, N;
ll ind_mod[100005], prefsum_mod[100005];

int main(){
	memset(ind_mod, -1, sizeof ind_mod);
	ind_mod[0] = 0;
	
	cin >> B >> N;
	for(int i=1;i<=N;i++){
		int x;
		cin >> x;
		prefsum_mod[i] = (x+prefsum_mod[i-1])%B;		
	}
	
	for(int i=1;i<=N;i++){
		ll x = prefsum_mod[i];
		if(ind_mod[x] == -1) ind_mod[x] = i;
		else{
			cout << i;
			for(int j=i-1;j>ind_mod[x];j--){
				cout << " " <<j;
			}
			cout << endl;

			break;
		}
	}

}
