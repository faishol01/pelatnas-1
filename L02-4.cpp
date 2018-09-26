#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N;
ll data[200005];
queue<ll>q;
set<ll>found;

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> data[i];
		
		int sz = q.size();
		while(sz--){
			ll tmp = q.front();
			q.pop();
			
			tmp = __gcd(tmp, data[i]);
			
			if(found.find(tmp) == found.end()){
				found.insert(tmp);
				q.push(tmp);
			}
		}
		
			found.insert(data[i]);
			q.push(data[i]);
	}

	cout << found.size() << endl;
}
