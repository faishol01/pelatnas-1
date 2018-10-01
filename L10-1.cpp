#include <bits/stdc++.h>
#include "aeslibc.h"
#include "aeslibc.c"

using namespace std;

typedef long long ll;

#define PUB push_back
#define fi first
#define se second

void enkripsi(HexStr &p, HexStr &c, HexStr &k){
	Block pt, ck, ct;
	
	hexstr2block ( p, pt );
	hexstr2block ( k, ck );
	encrypt ( pt, ck, ct );
	block2hexstr ( ct, c );
}

void dekripsi(HexStr &p, HexStr &c, HexStr &k){
	Block pt, ck, ct;

	hexstr2block ( k, ck );
	hexstr2block ( c, ct );
	decrypt ( ct, ck, pt );
	block2hexstr ( pt, p );
}

int s;
string hexa = "0123456789ABCDEF";
HexStr k1, k2, awal, akhir;
map<string, string> stt;
bool ketemu = 0;

void BF(int pos, int id){
	if(pos == s){
		if(id == 0){
			HexStr c;
			enkripsi(awal, c, k1);
			if(stt.count(c) == 0) stt.insert({c, k1});
		}else{
			HexStr p;
			
			dekripsi(p, akhir, k2);
			if(stt.count(p) > 0){
				ketemu = 1;

				cout << stt[p] << endl;
				cout << k2 << endl;
			}
		}

		return;
	}

	for(int i=0;i<16;i++){
		HexStr p, c;

		if(id == 0){
			k1[pos] = hexa[i];
		}else if(id == 1){
			k2[pos] = hexa[i];
		}

		if(!ketemu) BF(pos+1, id);
	}
}

int main(){
	for(int i=1;i<=10;i++){
		freopen(("input/ioi-2001-double-crypt_"+to_string(i)+".in").c_str(), "r", stdin);
		freopen(("output/ioi-2001-double-crypt_"+to_string(i)+".out").c_str(), "w", stdout);

		ketemu = 0;
		for(int i=0;i<32;i++)
			k1[i] = k2[i] = '0';

		cin >> s;
		cin >> awal >> akhir;
		cout << "#FILE double " << i << endl;
		BF(0,0);
		BF(0,1);
	}
}	
