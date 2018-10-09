#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

#define PUB push_back
#define fi first
#define se second

const int MAXE = 4e5+5;

int N, M, Q;
ll ans = 0;
ll segtreeCol[MAXE], segtreeRow[MAXE];

int id, R, C, K, R1, C1, R2, C2;

void update_segtree(int ind, int l, int r, int ind_upd, ll val, int id){
	if(l==r){
		if(id == 1) segtreeRow[ind] += val;
		else segtreeCol[ind] += val;

		return;
	}

	int mid = (l + r) / 2;
	if(ind_upd <= mid) update_segtree(2*ind, l, mid, ind_upd, val, id);
	else update_segtree(2*ind + 1, mid+1, r, ind_upd, val, id);

	if(id == 1)
		segtreeRow[ind] = segtreeRow[2*ind] + segtreeRow[2*ind + 1];
	else
		segtreeCol[ind] = segtreeCol[2*ind] + segtreeCol[2*ind + 1];

}

ll query_segtree(int ind, int l, int r, int find_l, int find_r, int id){
	if(r < find_l || find_r < l) return 0;

	if(find_l <= l && r <= find_r){
		if(id == 1) return segtreeRow[ind];
		else return segtreeCol[ind];
	}

	ll ret = 0;
	int mid = (l + r) / 2;

	ret += query_segtree(2*ind, l, mid, find_l, find_r, id);
	ret += query_segtree(2*ind + 1, mid + 1, r, find_l, find_r, id);

	return ret;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	memset(segtreeRow, 0, sizeof segtreeRow);
	memset(segtreeCol, 0, sizeof segtreeCol);

	cin >> N >> M >> Q;
	while(Q--){
		cin >> id;
		if(id == 1){
			cin >> R >> K;
			update_segtree(1, 1, N, R, K, id);
		}else if(id == 2){
			cin >> C >> K;
			update_segtree(1, 1, M, C, K, id);
		}else{
			cin >> R1 >> C1 >> R2 >> C2;
			ans = query_segtree(1, 1, N, R1, R2, 1)*(C2-C1+1);
			ans += query_segtree(1, 1, M, C1, C2, 2)*(R2-R1+1);
			cout << ans << endl;
		}
	}
}
