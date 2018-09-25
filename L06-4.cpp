#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define PUB push_back
#define fi first
#define se second

struct apa{
	int u, v, tipe;
};

int N, M, K, bthBatu, bthBeton;
int bykBatu = 0, bykBeton = 0;
int hbgBatu[20005], hbgBeton[20005];
bool isUrgent[100005];
bool isAmbil[100005];
vector<apa>jalan;

int prn[20005];

int find_prn(int a){
	if(prn[a] == a) return a;
	else return prn[a] = find_prn(prn[a]);
}

bool isSame(int a, int b){
	return (find_prn(a) == find_prn(b));
}

void joinSet(int a, int b){
	int prnA = find_prn(a),
		prnB = find_prn(b);

	if(prnA == prnB) return;
	prn[prnA] = prnB;
}

bool cmp(apa a, apa b){
	return a.tipe < b.tipe;
}

void find_urgent(){
	for(int i=0;i<M;i++){
		if(jalan[i].tipe == 1){
			if(!isSame(jalan[i].u, jalan[i].v)){
				joinSet(jalan[i].u, jalan[i].v);
			}
		}
	}

	for(int i=0;i<M;i++){
		if(jalan[i].tipe == 0){
			if(!isSame(jalan[i].u, jalan[i].v)){
				isUrgent[i] = 1;
				joinSet(jalan[i].u, jalan[i].v);
			}
		}
	}
}

int main(){
	for(int i=0;i<20005;i++) prn[i] = i;

	cin >> N >> M >> K;
	bthBatu = K;
	bthBeton = N-K-1;

	for(int i=0;i<M;i++){
		int x, y, z;
		cin >> x >> y >> z;

		jalan.PUB({x, y, z});

		if(z == 0){
			hbgBatu[x]++;
			hbgBatu[y]++;
			bykBatu++;
		}else{
			hbgBeton[x]++;
			hbgBeton[y]++;
			bykBeton++;
		}
	}
	
	sort(jalan.begin(), jalan.end(), cmp);

	find_urgent();
	for(int i=1;i<=N;i++) prn[i] = i;

	// Ambil yang urgent
	for(int i=0;i<M;i++){
		if(bthBatu > 0 && isUrgent[i]){
			joinSet(jalan[i].u, jalan[i].v);
			isAmbil[i] = 1;
			bthBatu--;
		}
	}

	
	// MST biasa
	for(int i=0;i<M;i++){
		if(!isAmbil[i]){
			if(jalan[i].tipe == 0 && bthBatu > 0){
				if(!isSame(jalan[i].u, jalan[i].v)){
					isAmbil[i] = 1;
					bthBatu--;
					joinSet(jalan[i].u, jalan[i].v);
				}
			}else if(jalan[i].tipe == 1 && bthBeton > 0){
				if(!isSame(jalan[i].u, jalan[i].v)){
					isAmbil[i] = 1;
					bthBeton--;
					joinSet(jalan[i].u, jalan[i].v);
				}
			}
		}
	}

	for(int i=1;i<=N;i++) if(!isSame(1, i)){
		cout << "no solution" << endl;
		return 0;
	}

	for(int i=0;i<M;i++)
		if(isAmbil[i])
			cout << jalan[i].u << " " << jalan[i].v << " " << jalan[i].tipe << endl;
}
