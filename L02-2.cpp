#include <bits/stdc++.h>
using namespace std;

int T, N;
double ans[] = {0, 0.4, 0.2, 0.2, 0.4};

int main(){
	cin >> T;
	while(T--){
		cin >> N;
		cout << fixed << setprecision(2) << ans[N%5] << endl;
	}
}
