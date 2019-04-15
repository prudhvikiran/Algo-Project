#include <bits/stdc++.h>
using namespace std;
// try if this can be done in hexadecimal form----------------------
// add char to 8 bit binary-----------------------------------------
// add number to binary --------------------------------------------
string binary(int c){
	string bb = "";
	while(c){
		if(c % 2 == 0)
			bb = '0' + bb;
		else
			bb = '1' + bb;
		c /= 2;
	}
	while(bb.length() < 8)// for alphabets padded to 8bit code--------
		bb = '0' + bb;
	return bb;
}

string hextobin(string s){
	string bb[] = {"0000","0001","0010","0011","0100","0101","0110","0111",
				"1000","1001","1010","1011","1100","1101","1110","1111"};
	string bin = "";
	int l = s.length();
	for (int i = 0; i < l; ++i){
		if(s[i] <= '9')
			bin = bin + bb[int(s[i]-'0')];
		else
			bin = bin + bb[int(s[i]+10-'A')];
	}
	return bin;
}

string bintohex(string s){
	char hh[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	string hex = "";
	int l = s.length();
	int t = (4-(l%4))%4;
	int t1 = t;
	while(t--) s = '0' + s;
	for(int i = 0; i < (l+t1)/4; ++i){
		int sum = 0,k = 8;
		for(int j = 4*i; j < 4*i+4; ++j){
			if(s[j] == '1') sum += k;
			k /= 2;
		}
		hex = hex + hh[sum];
	}
	return hex;
}

void start(string &s){
	string temp = "";
	for(int i = 0; i < s.length(); ++i){
		temp = temp + binary(int(s[i]));
	}
	temp = temp + '1';
	while(temp.length() < 448)temp = temp + '0';
	//second part
	string temp1 = binary(s.length() * 8);// length info(tail) 64 bits--
	while(temp1.length()<64)// tail padding
		temp1 = '0' + temp1;
	s = temp+temp1;
}

string Xor(string a, string b){
	for(int i = 0; i < a.length(); ++i) a[i] = char((int(a[i]-'0') ^ int(b[i]-'0'))+'0');
	return a;
}
string sum(string a, string b){
	int i = 0,remainder = 0,sum[40];
	string binarySum = "";

	for(int j = a.length()-1; j >=0 ; --j){
		sum[i++] =  (int(a[j]-'0') + int(b[j]-'0') + remainder ) % 2;
		remainder = (int(a[j]-'0') + int(b[j]-'0') + remainder ) / 2;
	}
	--i;
	while(i >= 0)
		binarySum += char('0'+sum[i--]);

	return binarySum;
}
string And(string a, string b){
	for (int i = 0; i < a.length(); ++i)
		a[i] = char((int(a[i]-'0') & int(b[i]-'0'))+48);
	return a;
}
string Or(string a, string b){
	for (int i = 0; i < a.length(); ++i)
		a[i] = char((int(a[i]-'0') | int(b[i]-'0'))+48);
	return a;
}
string Not(string a){
	for(int i = 0; i < a.length(); ++i)
		a[i] = (a[i] == '0') ? '1' : '0';
	return a;
}

string fun(int i,string B,string C,string D){
	if(0 <= i && i<20)return Or(And(B,C),And(Not(B),D));
	if(20 <= i && i<40)return Xor(Xor(B,C),D);
	if(40 <= i && i<60)return Or(Or(And(B,C),And(B,D)),And(C,D));
	return Xor(Xor(B,C),D);
}

string K(int i){
	if(0 <= i && i < 20)return hextobin("5A827999");
	else if(20 <= i && i < 40)return hextobin("6ED9EBA1");
	else if(40 <= i && i < 60)return hextobin("8F1BBCDC");
	else return hextobin("CA62C1D6");
}

string ls(string s,int n){
	return (s + s.substr(0,n)).erase(0,n);
}

string sha1(string s){
	string H[5];
	H[0]=hextobin("67DE2A01");
	H[1]=hextobin("BB03E28C");
	H[2]=hextobin("011EF1DC");
	H[3]=hextobin("9293E9E2");
	H[4]=hextobin("CDEF23A9");

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

	// after all chunks-----------------------------
	// for(int i = 0;i < 5;i++){
	// 	while(H[i].length() < 160){
	// 		H[i] = '0' + H[i];
	// 	}
	// }
	// H[0] = ls(H[0],128);
	// H[1] = ls(H[1],96);
	// H[2] = ls(H[2],64);
	// H[3] = ls(H[3],32);	
	// return Or(Or(H[0],H[1]),Or(Or(H[2],H[3]),H[4]));// returns only for 1 chunck(40bytes=512 bits)--
	return H[0] + H[1] + H[2] + H[3] + H[4];
}

int main(){
	string data;
	getline(cin,data);
	start(data);
	cout << bintohex(sha1(data)) << endl;
	return 0;
}