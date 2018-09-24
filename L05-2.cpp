#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

#define PUB push_back
#define fi first
#define se second

int N;
bool isAda[30], isVisit[30];
vector<int>adjL[30];
stack<int>ans;

void pecah(string a){
	for(int i=0;i<a.length()-1;i++){
		isAda[a[i]-'a'] = 1;
		adjL[a[i]-'a'].PUB(a[i+1]-'a');
	}
	isAda[a[a.length()-1]-'a'] = 1;
}

void toposort(int pos){
	isVisit[pos] = 1;

	for(int nxt:adjL[pos]){
		if(!isVisit[nxt])
			toposort(nxt);
	}

	ans.push(pos);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	memset(isAda, 0, sizeof isAda);

	cin >> N;
	for(int i=0;i<N;i++){
		string S;
		cin >> S;

		pecah(S);
	}
	
	for(int i=0;i<=30;i++){
		sort(adjL[i].begin(), adjL[i].end(), greater<int>());
	}

	for(int i=30;i>=0;i--){
		if(isAda[i] && !isVisit[i]){
			toposort(i);
		}
	}

	while(!ans.empty()){
		cout << char(ans.top()+'a');
		ans.pop();
	}
	cout << endl;
	return 0;
}
