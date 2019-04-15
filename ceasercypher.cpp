#include <bits/stdc++.h>
using namespace std;
void encrypt(string &s,int shift){//--encryption--
	for(int i = 0;i < s.length();++i){
		if('a' <= s[i] && s[i] <= 'z'){
			s[i] = char('a' + ((s[i] + shift - 'a') % 26));
		}
		else if('A' <= s[i] && s[i] <= 'Z'){
			s[i] = char('A' + ((s[i] + shift - 'A') % 26));
		}
	}
	cout << s << endl;
}
void decrypt(string &s,int shift){//--decryption--
	for(int i = 0;i < s.length();++i){
		if('a' <= s[i] && s[i] <= 'z'){
			s[i] = char('a' + ((26+(s[i] - shift - 'a') % 26)) % 26);
		}
		else if('A' <= s[i] && s[i] <= 'Z'){
			s[i] = char('A' + ((26+(s[i] - shift - 'A') % 26)) % 26);
		}
	}
	cout << s << endl;	
}
int main(){
	cout << "Enter the string" << endl;
	string s;	
	cin >> s;	
	cout << "Enter the shift" << endl;
	int shift;
	cin >> shift;
	encrypt(s,shift);
	decrypt(s,shift);
	return 0;
}