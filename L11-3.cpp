#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e6;
const int MAXMASK = (1 << 11)+5;

int R, C;
int memo[10][501][MAXMASK];

void next(int pR, int pC, int &tR, int &tC){
	tR = pR + 1;
	tC = pC;
	
	if(tR == R){
		tR = 0;
		tC++;
	}
}

int get_mask(int mask_now, int id){
	// List of id
	// ## = 0	## = 1	## = 2	#. = 3	.# = 4 
	// ##		#.		.#		##		##

	int ret = mask_now;
	ret |= (1 << (R+1));
	
	if(id <= 1 || id == 3)
		ret |= (1 << R);
	if(id <= 2 || id == 4)
		ret |= (1 << 1);
	if(id == 0 || id == 2 || id == 3)
		ret |= (1 << 0);
	if(id == 4)
		ret |= (1 << 2);

	return (ret << 1) % (1 << (R+2));
}

bool isOff(int mask, int ind){
	return ((mask & (1 << ind)) == 0); 
}

int DP(int pR, int pC, int mask){
	// Base case
	if(pC == C ){
		if(mask == 0) return 1;
		else return 0;
	}

	int &ret = memo[pR][pC][mask];
	if(ret >= 0) return ret;
	
	ret = 0;
	
	int tR, tC;
	next(pR, pC, tR, tC);

	if(!isOff(mask, R+1)){
		ret = (ret + DP(tR, tC, get_mask(mask, 5))) % MOD;
	}else{
		if(pR < R-1){
			if(isOff(mask, 0) && isOff(mask, 1) && isOff(mask, R)){
				ret = (ret + DP(tR, tC, get_mask(mask, 0))) % MOD;
			}
			if(isOff(mask, 1) && isOff(mask, R)){
				ret = (ret + DP(tR, tC, get_mask(mask, 1))) % MOD;
			}
			if(isOff(mask, 0) && isOff(mask, 1)){
				ret = (ret + DP(tR, tC, get_mask(mask, 2))) % MOD;
			}
			if(isOff(mask, 0) && isOff(mask, R)){
				ret = (ret + DP(tR, tC, get_mask(mask, 3))) % MOD;
			}
		}

		if(pR > 0){
			if(isOff(mask, 2) && isOff(mask, 1)){
				ret = (ret + DP(tR, tC, get_mask(mask, 4))) % MOD;
			}
		}
	}

	return ret;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	memset(memo, -1, sizeof memo);

	cin >> R >> C;
	cout << DP(0, 0, 0)%MOD << endl;

	return 0;
}
