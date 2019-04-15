#include <bits/stdc++.h>
using namespace std;
#define ll long long int
ll cal_exp(ll n,ll ph){// clculates e-
	for(ll i = 2;i < ph;i++){
		if(__gcd(i,ph) == 1 && (n % i))return i;
	}
	cout << "RSA won't work with these inputs" << endl;
	return 0;
}

ll gcdExtended(ll a,ll b, ll &x,ll &y){ 
    if(!a){ 
        x = 0;
        y = 1; 
        return b; 
    } 
    ll x1, y1; 
    ll gcd = gcdExtended(b%a, a,x1, y1); 
    x = y1 - (b/a) * x1; 
    y = x1; 
    return gcd; 
}

ll modInverse(ll a, ll m){ // inverse mod function
    ll x, y; 
    ll g = gcdExtended(a, m, x, y); 
    ll res = (m + x%m) % m; 
    return res; 
} 


ll pow(ll a,ll b,ll n){
	if(!b)return 1;
	else if(!(b & 1)) return pow(a*a,b/2,n) % n;
	return (a * pow(a*a,b/2,n)) % n;
}

void encrypt(ll *k,int l,ll e,ll n){// encryption function--
	for(int i = 0;i < l;i++){
		k[i] = pow(k[i]-96,e,n);
		k[i] = k[i] + 96;
	}
	cout << "Encrypted message is: ";
	for(int i = 0;i < l;i++){
		cout << char(k[i]);
	}
	cout << endl;
}

void decrypt(ll *k,int l,ll d,ll n){// decryption function--
	for(int i = 0;i < l;i++){
		k[i] = k[i] - 96;
		k[i] = pow(k[i],d,n);
		k[i] = k[i] + 96;
	}
	cout << "Decrypted message is: ";
	for(int i = 0;i < l;i++){
		cout << char(k[i]);
	}
	cout << endl;	
}

int main(){
	cout << "Enter two primes numbers" << endl;
	ll p,q;//primes
	cin >> p >> q;

	//Public key	
	ll n = p * q;//First part of Public key
	ll ph = (p-1) * (q-1);//Euler Totient Fucntion
	ll e = cal_exp(n,ph);//calculates the encrypt key 
	//Private key
	ll d = modInverse(e,ph);//calculates the decrypt key
	//String input
	cout << e << " " << d << endl;
 	string s;
	cin >> s;
	int l = s.length();
	ll k[l];
	for(int i = 0;i < l;i++)k[i] = s[i];
	encrypt(k,l,e,n);
	decrypt(k,l,d,n);
	return 0;
}