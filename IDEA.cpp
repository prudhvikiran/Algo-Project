#include <bits/stdc++.h>
using namespace std;
bool check(string data){//Checks whether the number is 0 or not
    for(int i = 0;i < data.length();i++){
        if(data[i] != '0')return 1;
    }
    return 0;
}
int Modulus(string s){//Returns the remainder when divided by 2
    if(s[s.length()-1] % 2 == 0)return 0;
    return 1;
}

string divide(string data){//Divides the given large number by 2
    int rem = 0;    
    for(int i = 0;i < data.length();i++){
        int k = (data[i] - '0') + rem * 10;
        data[i] = char((k / 2) + '0');
        rem = k % 2;
    }
    return data;
}

string convert(string data){//Convert decimal to binary
    string s = "";
    while(check(data)){
        int mod = Modulus(data);
        if(mod == 0)s = '0' + s;
        else s = '1' + s;
        data = divide(data);
    }
    return s;
}

void append(string &data,int value){//appends zeros in the front
    while(data.length() < value){
        data = '0' + data;
    }
}
string add(string a,string b){//addition modulo of two 16 bit binary strings
    int i=0,remainder = 0,sum[20];
    string binarySum = "";
    for (int j = a.length()-1;j >=0;--j){
        sum[i++] =  (int(a[j]-'0') + int(b[j]-'0') + remainder ) % 2;
        remainder = (int(a[j]-'0') + int(b[j]-'0') + remainder ) / 2;
    }
    --i;
    while(i>=0) binarySum = char('0'+sum[i--]) + binarySum;
    return binarySum;
}

string multiply(string a, string b){//multiplication modulo of two 16 bit binary strings
    string prod="0000000000000000";
    char digit;
    int l=b.length();
    for(int j=l-1;j>=0;--j){
        digit = b[j];
        if(digit == '1')prod = add(a,prod);
        a = a.substr(1,l-1)+'0';
    }
    return prod;
}

string Xor(string a, string b){//Xor of two binary strings.
    for(int i = 0; i < a.length(); ++i) a[i]=char((int(a[i]-'0') ^ int(b[i]-'0'))+'0');
    return a;
}

string idea(string data,string key){//IDEA hashing algorithmic Function. 
    string p1=data.substr(0,16);//First substring
    string p2=data.substr(16,16);//second substring
    string p3=data.substr(32,16);//third substring
    string p4=data.substr(48,16);//fourth substring
    string k[6];//6 keys
    int left=0;
    for(int i = 0;i < 8; i++){// key generator-------------------
        int kk = (8 - left) % 8;
        for(int t = 0;t < left;t++){
            k[t] = key.substr(kk * 16, 16);
            kk++;
        }
        key = (key + key.substr(0,25)).erase(0,25);// key circular shifs by 25--
        kk=0;
        for(int t=left;t<6;t++){
            k[t]=key.substr(kk*16,16);
            kk++;
        }
        left=(left+2)%8;
        //---------------------------------
        string st[10];
        st[0]=multiply(p1,k[0]);
        st[1]=add(p2,k[1]);
        st[2]=add(p3,k[2]);
        st[3]=multiply(p4,k[3]);
        st[4]=Xor(st[0],st[2]);
        st[5]=Xor(st[1],st[3]);
        st[6]=multiply(st[4],k[4]);
        st[7]=add(st[5],st[6]);
        st[8]=multiply(st[7],k[5]);
        st[9]=add(st[6],st[8]);
        //Results of iterations.
        p1=Xor(st[0],st[8]);
        p2=Xor(st[1],st[9]);
        p3=Xor(st[2],st[8]);
        p4=Xor(st[3],st[9]);
    }
    string c1=multiply(p1,k[2]);
    string c2=add(p3,k[3]);
    string c3=multiply(p2,k[4]);
    string c4=add(p4,k[5]);
    return c1+c2+c3+c4;
}

int main(){
    string data,key;
    cin >> data >> key;
    data = convert(data);
    append(data,64);
    key = convert(key);
    append(key,128);
    cout << idea(data,key) << endl;
    return 0;
}