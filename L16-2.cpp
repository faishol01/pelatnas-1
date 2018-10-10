#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

#define PUB push_back
#define fi first
#define se second

ll BLOCK = 320;

struct mo_query{
	ll l, r, ind;
	mo_query(ll _l = 0, ll _r = 0, ll _ind = 0): l(_l), r(_r), ind(_ind) {}

	bool operator<(mo_query a) const{
		return ((l/BLOCK == a.l/BLOCK) ? (r < a.r):(l/BLOCK < a.l/BLOCK)); }
};

int N, Q;
ll ans[100005], data[100005], indeks_data[100005];
vector<mo_query> query;
map<int, int> stt;

int cnt[100005];

void hitung(int ind, ll &ret, int id){
	if(id == 0){
		ret += data[ind] + cnt[indeks_data[ind]];
		cnt[indeks_data[ind]]++;
	}else{
		cnt[indeks_data[ind]]--;
		ret -= data[ind] + cnt[indeks_data[ind]];
	}
}

void solve(){
	int l = 0, r = -1;
	ll tmp_ans = 0;

	for(int i=0;i<Q;i++){
		mo_query now = query[i];
		
		while(r < now.r) hitung(++r, tmp_ans, 0);
		while(now.l < l) hitung(--l, tmp_ans, 0);
		while(l < now.l) hitung(l++, tmp_ans, 1);
		while(now.r < r) hitung(r--, tmp_ans, 1);

		ans[now.ind] = tmp_ans;
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N >> Q;
	
	BLOCK = sqrt(N) + 1;

	int cnt = 0;
	for(int i=0;i<N;i++){
		cin >> data[i];
		
		if(stt.count(data[i]) == 0){
			stt.insert({data[i], cnt});
			indeks_data[i] = cnt;
			cnt++;
		}else indeks_data[i] = stt[data[i]];
	}
	
	for(int i=0;i<Q;i++){
		mo_query tmp;
		
		cin >> tmp.l >> tmp.r;
		tmp.l--; tmp.r--;
		tmp.ind = i;

		query.PUB(tmp);
	}

	sort(query.begin(), query.end());

	solve();

	for(int i=0;i<Q;i++)
		cout << ans[i] << "\n";
}
