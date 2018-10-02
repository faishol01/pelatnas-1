#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct edge{
	int u, v;
	ll d;
};

const ll MOD = 1e9+7;

int N, M;
ll ans_dist = 0, ans_byk = 1;
edge data[100005];

int prn[40005];

int find_prn(int a){
	if(prn[a] == a) return a;
	return prn[a] = find_prn(prn[a]);
}

bool isSameSet(int a, int b){
	return (find_prn(a)==find_prn(b));
}

void joinSet(int a, int b){
	int prnA = find_prn(a),
		prnB = find_prn(b);
	
	if(prnA != prnB)
		prn[prnA] = prnB;
}

bool cmp(edge a, edge b){
	if(a.d == b.d){
		if(a.u == b.u) return a.v < b.v;
		return a.u < b.u;
	}
	return a.d < b.d;
}

ll find_same_connect(int prn1, int prn2, int id){
	ll ret = 0;
	for(int i=0;i<3 && id+i < M;i++){
		if(data[id+i].d == data[id].d){
			int prnU = find_prn(data[id+i].u),
				prnV = find_prn(data[id+i].v);
			
			if(min(prnU, prnV) == min(prn1, prn2) && max(prnU, prnV) == max(prn1, prn2)){
				ret++;
			}		
		}
	}
	return ret;
}

bool isCanChoose3(int id){
	if(abs(id-M) < 3) return 0;
	for(int i=0;i<3 && id+i ;i++) if(data[id].d != data[id+i].d) return 0;

	int cnt = 0;
	set<int> tmp[3];
	for(int i=0;i<2;i++) for(int j=i+1;j<3;j++){
		tmp[cnt].insert(data[id+i].u);
		tmp[cnt].insert(data[id+i].v);
		tmp[cnt].insert(data[id+j].u);
		tmp[cnt].insert(data[id+j].v);
		cnt++;
	}

	if(tmp[0].size() != 3 || tmp[1].size() != 3 || tmp[2].size() != 3)
		return 0;
	for(int i=0;i<2;i++) for(int j=i+1;j<3;j++){
		for(auto elm:tmp[i]){
			if(tmp[j].find(elm) == tmp[j].end()) return 0;
		}
	}

	return 1;
}

int main(){
	for(int i=0;i<40005;i++)
		prn[i] = i;
	
	cin >> N >> M;
	for(int i=0;i<M;i++)
		cin >> data[i].u >> data[i].v >> data[i].d;

	sort(data, data+M, cmp);

	for(int i=0;i<M;i++){
		int prnU = find_prn(data[i].u),
			prnV = find_prn(data[i].v);
		
		if(prnU != prnV){
			if(isCanChoose3(i)){
				ans_byk = (ans_byk * 3)%MOD;
				joinSet(data[i].u, data[i].v);
				joinSet(data[i+1].u, data[i+1].v);
				ans_dist += data[i].d + data[i+1].d;
				i++;
			}else{
				ans_byk = (ans_byk * find_same_connect(prnU, prnV, i))%MOD;
				joinSet(data[i].u, data[i].v);
				ans_dist += data[i].d;
			}
		}
	}

	cout << ans_dist << " " << ans_byk << endl;
}
