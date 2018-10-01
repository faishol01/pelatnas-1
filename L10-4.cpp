#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define PUB push_back
#define fi first
#define se second

int N, ans[1000005], tmp[1000005];

void build_killer(int l, int r, int x, int y, int cnt){
	if(abs(l-r)+1 == 1) ans[tmp[l]] = x;
	else{
		int pivot = (l+r)/2;
		if(cnt%2 == 1){
			swap(tmp[l], tmp[pivot]);
			ans[tmp[l]] = x;
			build_killer(l+1, r, x+1, y, cnt+1);	
		}else{
			swap(tmp[r], tmp[pivot]);
			ans[tmp[r]] = y;
			build_killer(l, r-1, x, y-1, cnt+1);
		}
		
	}
}

int main(){
	for(int i=0;i<=1000000;i++) tmp[i] = i;

	cin >> N;
	build_killer(1, N, 1, N, 1);
	for(int i=1;i<N;i++)
		cout << ans[i] << " ";
	cout << ans[N] << endl;
}
