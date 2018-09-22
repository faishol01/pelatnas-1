#include <bits/stdc++.h>
using namespace std;

string lbl;
int R, C, angka, pR1 = 1, pC1 = 1, pR2, pC2;

int main(){
	cin >> R >> C;
	
	pR2 = R;
	pC2 = C;

	for(int i=0;i<R*C;i++){
		cin >> angka;
		
		if(angka == 2){
			cout << pR1 << " " << pC1 << endl;
			
			pC1++;
			if(pC1 > C){
				pC1 = 1;
				pR1++;
			}
		}else{
			cout << pR2 << " " << pC2 << endl;

			pC2--;
			if(pC2 == 0){
				pC2 = C;
				pR2--;
			}
		}
	}
}
