#include <bits/stdc++.h>
#include "/home/dell/algo_project/SHA1.h"
string func(string pad,string data){
	string s = pad;
	string H[5];
	H[0]=hextobin("67DE2A01");
	H[1]=hextobin("BB03E28C");
	H[2]=hextobin("011EF1DC");
	H[3]=hextobin("9293E9E2");
	H[4]=hextobin("CDEF23A9");

	int t = 2;
	while(t--){
		string w[80];
		for(int i = 0; i < 16; ++i) w[i] = s.substr(i*32,32);
		for(int i = 16; i < 80; ++i){
			string xx = Xor(Xor(w[i-3],w[i-8]),Xor(w[i-14],w[i-16]));
			w[i] = ls(xx,1);
		}
		string A = H[0],B = H[1],C = H[2],D = H[3],E = H[4];
		for (int i = 0; i < 80; ++i){
			string temp = sum(sum(sum(ls(A,5),fun(i,B,C,D)),sum(E,w[i])),K(i));
			E = D;
			D = C;
			C = ls(B,30);
			B = A;
			A = temp;
		}
		H[0] = sum(H[0],A);
		H[1] = sum(H[1],B);
		H[2] = sum(H[2],C);
		H[3] = sum(H[3],D);
		H[4] = sum(H[4],E);
		s = data;
	}
	return H[0] + H[1] + H[2] + H[3] + H[4];
}
string HMAC(string data, string key, string ipad, string opad){
	ipad = Xor(ipad,key);
	opad = Xor(opad,key);

	string temp = func(ipad,data);
	while(temp.length() < 512)temp = '0' + temp;	
	return func(opad,temp);
}

int main(){
	string data;
	cin >> data;
	string key,ipad,opad;
	ipad = "00110110";
	while(ipad.length() < 512)ipad = ipad + ipad;
	opad = "01011100";
	while(opad.length() < 512)opad = opad + opad;
	key = "FDC3A1690AB";
	key = hextobin(key);
 	while(key.length() < 512)key = '0' + key;
	start(data);
	cout << bintohex(HMAC(data,key,ipad,opad)) << endl;
	return 0;	
}