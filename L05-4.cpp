#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

#define PUB push_back
#define fi first
#define se second

int N, K, byk, cnt = 0;
int edgeIn[300005];
string potongan[300005];
string ans = "";

map<string, int> daftar;
vector<int>adjL[300005];

int str = -1, posisi;
unordered_map<int, int> cnt_edge;
stack<int>tmp_path;
vector<int>ans_path;

bool cmp(int a, int b){
	return potongan[a] > potongan[b];
}

int main(){
	cin >> N >> K;
	byk = N-K+1;
	
	for(int i=0;i<byk;i++){
		string s;
		cin >> s;

		string a, b;
		int indA, indB;
		a = s.substr(0, K-1);
		b = s.substr(1, K-1);

		if(daftar.count(a) > 0) indA = daftar[a];
		else{
			daftar.insert({a, cnt});
			potongan[cnt] = a;
			indA = cnt;

			cnt++;
		}
		
		if(daftar.count(b) > 0) indB = daftar[b];
		else{
			daftar.insert({b, cnt});
			potongan[cnt] = b;
			indB = cnt;
			
			cnt++;
		}

		adjL[indA].PUB(indB);
		edgeIn[indB]++;
	}
	
	for(int i=0;i<cnt;i++) sort(adjL[i].begin(), adjL[i].end(), cmp);

	// Find starting point
	for(int i=0;i<cnt;i++) if(edgeIn[i] < adjL[i].size()) str = i;

	if(str == -1){
		str = 0;
		for(int i=0;i<cnt;i++)
			if(potongan[str] > potongan[i] && adjL[i].size() > 0) str = i;
	}

	// Hierholzer's Algorithm
	for(int i=0;i<cnt;i++) cnt_edge[i] = adjL[i].size();

	tmp_path.push(str);
	posisi = str;

	while(!tmp_path.empty()){
		if(cnt_edge[posisi] > 0){
			tmp_path.push(posisi);
			int nxt = adjL[posisi].back();
 
            cnt_edge[posisi]--;
            adjL[posisi].pop_back();
 
            posisi = nxt;
		}else{
			ans_path.PUB(posisi);

			posisi = tmp_path.top();
			tmp_path.pop();
		}
	}

	for(int i=ans_path.size()-1;i>=0;i--){
		if(K == 2){
			cout << potongan[ans_path[i]];
		}else{
			if(i == 0) cout << potongan[ans_path[i]];
			else cout << potongan[ans_path[i]][0];
		}
	} cout << endl;
	
}
