#include <bits/stdc++.h>
using namespace std;
bool safe(int **p,int n,int row,int col,int v){
	for(int i = 0;i < n;i++){
		if(p[row][i] == v || p[i][col] == v)return 0;
	}
	if(n == 6){
		int startr = 2 * (row / 2);
		int startc = 3 * (col / 3);
		for(int i = startr;i <= startr+1;i++){
			for(int j = startc;j <= startc+2;j++){
				if(p[i][j] == v)return 0;
			}
		}
		return 1;
	}
	int k = sqrt(n);
	int startr = k * (row / k);
	int startc = k * (col / k);
	for(int i = startr;i <= startr+k-1;i++){
		for(int j = startc;j <= startc+k-1;j++){
			if(p[i][j] == v)return 0;
		}
	}
	return 1;	
}

bool check(int **p,int n,int &row,int &col){
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			if(p[i][j] == 0){row = i;col = j;return 1;}
		}
	}
	return 0;
}	
bool solve(int **p,int n){
	int row,col;
	bool b = check(p,n,row,col);
	if(!b) return 1;
	for(int i = 1;i <= n;i++){
		if(safe(p,n,row,col,i)){
			p[row][col] = i;
			if(solve(p,n))return 1;
			else p[row][col] = 0;
		}
	}
	return 0;
}
void display(int **p,int n){
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++)cout << p[i][j] << " ";
		cout << endl;
	}
}
int main(){
	cout << "Enter the size of sudoku puzzle(2/4/6/9)" << endl;
	int n;
	cin >> n;
	int **p = new int*[n];
	for(int i = 0;i < n;i++)p[i] = new int[n];
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++)cin >> p[i][j];
	}	
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			if(p[i][j]){
				int k = p[i][j];
				p[i][j] = -1;
				if(!safe(p,n,i,j,k)){
					cout << "Input given is wrong!" << endl;
					return 0;
				}
				p[i][j] = k;
			}
		}
	}	
	if(solve(p,n) == 0)cout << "No Solution Exists!" << endl;
	else{
		display(p,n);
	}
	return 0;
}