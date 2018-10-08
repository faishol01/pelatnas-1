#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

#define PUB push_back
#define fi first
#define se second

int N, ans = 0;
string S, fin = "";
char trans[4][4] =  {{'A', 'B', 'C', 'D'},
				  {'B', 'A', 'D', 'C'},
				  {'C', 'D', 'A', 'B'},
				  {'D', 'C', 'B', 'A'}};

string ubah(string &a, int thn){
	string ret = a;

	for(int i=0;i<N;i++){
		int nxt = (i+thn) % N;
		ret[i] = trans[a[i]-'A'][a[nxt]-'A'];
	}

	return ret;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> S;
	N = S.length();
	for(int i=0;i<N;i++) fin += "A";

	for(int i=21;i>=0;i--){
		string now = ubah(S, (1 << i));
		if(now != fin){
			if(i == 21){
				cout << -1 << endl;
				return 0;
			}

			ans += (1 << i);
			S = now;	
		}
	}

	if(S == fin) cout << 0 << endl;
	else cout << ans + 1 << endl;
}
