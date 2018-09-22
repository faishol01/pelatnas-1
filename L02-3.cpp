#include <bits/stdc++.h>
using namespace std;

int a, b, c, d, ans = 1;

bool isValid(int x){
	if(x == 0) return 0;
	return (b/x > (a-1)/x) && (d/x > (c-1)/x);
}

int main(){
	int n;
	
	cin >> n;
	
	while(n--){
		ans = 1;
		
		cin >> a >> b >> c >> d;
		for(int i=1; i <= sqrt(1e9); i++){
			if(isValid(i)) ans = max(ans, i);
			if(isValid(b/i)) ans = max(ans, b/i);
			if(isValid(d/i)) ans = max(ans, d/i);
		}
		cout << ans << endl;
	}
}
