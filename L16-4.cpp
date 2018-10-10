#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

#define PUB push_back
#define fi first
#define se second

int N, M;
ll data[200005], tambah[450][450];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	memset(data, 0, sizeof data);

	cin >> N >> M;

	for(int i=0;i<M;i++){
		char id;
		cin >> id;
		if(id == 'U'){
			int a, b, c;
			cin >> a >> b >> c;
			
			if(b >= 450){
				for(;a<=N;a+=b) data[a] += c;
			}else tambah[a][b] += c;
		}else{
			int x;
			cin >> x;

			int ans = data[x];
			for(int i=1;i<450;i++) ans += tambah[x%i][i];
			cout << ans << endl;
		}
	}
}
