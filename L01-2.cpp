#include "simplification.h"

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

#define fi first
#define se second
#define PUB push_back

int grup = 1, byk;
vector<int>angka;

void init(int N, std::vector<int> C) {
    byk = N;

    angka.PUB(C[0]);
    for(int i=1;i<N;i++){
    	angka.PUB(C[i]);
    	if(C[i] != C[i-1]) grup++;
    }

//    cerr << "grup: " << grup << endl;
}

int update(int x, int c) {
    x--;
    
    if(angka[x] != c){
    	if(x==0){
    		if(angka[x] == angka[x+1]) grup++;
    		
    		if(c == angka[x+1]) grup--;
    	}else if(x==byk-1){
    		if(angka[x] == angka[x-1]) grup++;
    		
    		if(c == angka[x-1]) grup--;
    	}else{
    		if(angka[x] == angka[x-1] && angka[x] == angka[x+1]) grup += 2;
    		else if(angka[x] == angka[x-1] || angka[x] == angka[x+1]) grup++;
    		
    		if(c == angka[x-1] && c == angka[x+1]) grup -= 2;
    		else if(c == angka[x-1] || c == angka[x+1]) grup--;
    	}

    	angka[x] = c;
    }

    return byk-grup;
}
