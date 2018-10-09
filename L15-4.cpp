#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

#define PUB push_back
#define fi first
#define se second

const int MAXE = 10e3+5;
const ll INF = 10e10;

int N, L;
ll M, segtree[MAXE];
ll lazy[MAXE];

void push_pending(int ind, int ls, int rs){
	if(lazy[ind] != INF){
		if(ls != rs){
			lazy[2*ind] = min(lazy[ind], lazy[2*ind]);
			lazy[2*ind+1] = min(lazy[ind], lazy[2*ind+1]);
		}

		segtree[ind] = min(segtree[ind], lazy[ind]);
	}

	lazy[ind] = INF;
}

void update(int ind, int l, int r, int upd_l, int upd_r, ll val){
	if(r < upd_l || l > upd_r) return;

	push_pending(ind, l, r);
	
	if(upd_l <= l && r <= upd_r){
		lazy[ind] = min(lazy[ind], val);
		return;
	}

	int mid = (l+r)/2;
	update(2*ind, l, mid, upd_l, upd_r, val);
	update(2*ind + 1, mid+1, r, upd_l, upd_r, val);

	segtree[ind] = min(segtree[2*ind], segtree[2*ind + 1]);
}

ll query(int ind, int l, int r, int q_ind){
	push_pending(ind, l, r);
	
	if(l==r){
		return segtree[ind];
	}

	int mid = (l+r)/2;
	if(q_ind <= mid) return query(2*ind, l, mid, q_ind);
	else return query(2*ind + 1, mid+1, r, q_ind);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	for(int j=0;j<MAXE;j++){
		segtree[j] = INF;
		lazy[j] = INF;
	}

	cin >> N >> M >> L;
	update(1, 0, L, 0, 0, 0);

	for(int i=0;i<N;i++){
		int a, b;
		ll c;
		cin >> a >> b >> c;

		for(int i=L;i>=0;i--){
			ll cost = query(1, 0, L, i);

			if(cost <= M)
				update(1, 0, L, a+i, min(b+i, L), c + cost);
		}
	}

	int ans = query(1, 0, L, L);
	if(ans > M) cout << "MUSTAHIL" << endl;
	else cout << ans << endl;
}
