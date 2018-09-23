#include <bits/stdc++.h>
using namespace std;

int N, Q, prn[200005];

int find_prn(int x){
	if(prn[x] == x) return x;
	return prn[x] = find_prn(prn[x]);
}

void gabung(int x, int y){
	int pX = find_prn(x),
		pY = find_prn(y);
	
	if(pX == pY) return;

	prn[pX] = pY;
}

bool isFriend(int x, int y){
	return (find_prn(x) == find_prn(y));
}

bool isEnemy(int x, int y){
	return ((find_prn(x) == find_prn(y+N)) || (find_prn(x+N) == find_prn(y)));
}

void setEnemy(int x, int y){
	if(isFriend(x, y)) cout << -1 << endl;
	else{
		gabung(x, y+N);
		gabung(x+N, y);

		cout << 1 << endl;
	}
}

void setFriend(int x, int y){
	if(isEnemy(x, y)) cout << -1 << endl;
	else{
		gabung(x, y);
		gabung(x+N, y+N);

		cout << 1 << endl;
	}
}

int main(){
	for(int i=0;i<200005;i++) prn[i] = i;

	cin >> N >> Q;
	while(Q--){
		int id, x, y;
		cin >> id >> x >> y;

		if(id == 1) setFriend(x, y);
		else if(id == 2) setEnemy(x, y);
		else if(id == 3) cout << isFriend(x, y) << endl;
		else cout << isEnemy(x, y) << endl;
	}
}
