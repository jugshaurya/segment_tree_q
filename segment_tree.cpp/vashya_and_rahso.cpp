/*
	Vasya Vs Rehso
Send Feedback
Queen Vasya is preparing for a war against Rhezo. She has N warriors in total arranged in a line. Let us number the warriors by numbers from 1 to N. She will fight Rhezo's army for Q days, and each day she can choose only one warrior.
For each warrior, we know 2 values associated with him, let us call these A and B. Each day Vasya can choose her warrior from a range Li to Ri, she must choose the warrior with maximum A value. If there is more than 1 warrior having the same maximum A value, she chooses the warrior with minimum B value. If still there is more than 1 warrior with same maximum A value and same minimum B value, she chooses the one with lower index in line.
You being the hand of Queen Vasya, need to help her in choosing the warrior for each day.
Input:
First line contains a single integer N, denoting the number of warriors Queen Vasya has. 
Second line contains N space separated integers Ai. Third line contains N space separated integers Bi.
Next line contains a single integer Q, denoting the number of days Queen Vasya chooses a warrior. 
Each of the next Q lines contains 2 integers Li and Ri.
Output:
For each Li and Ri, print the index of the warrior that Queen Vasya should choose.
Constraints:
1≤ N,Q ≤10^6
1≤ Ai,Bi ≤10^9
1≤Li≤Ri
Sample Input
5
1 8 4 6 8
4 8 6 3 7
4
1 4
2 4
3 4
1 5
Sample Output
2
2
4
5
*/


#include<bits/stdc++.h>
using namespace std;


int compare(int left, int right, int* a, int* b){
	int ans;
	if(a[left] > a[right]){
		ans = left;
	}else if(a[left] < a[right]){
		ans = right;
	}else{
		if(b[left] > b[right]){
			ans = right;
		}else if(b[left] < b[right]){
			ans = left;
		}else{
			ans = min(left,right);
		}
	}

	return ans;
}

void buildTree(int* a, int* b,int* tree, int start, int end, int treeIndex){
	if(start == end){
		tree[treeIndex] = start; 
		return;
	}

	int mid = (start +end)/2;
	buildTree(a,b,tree,start, mid, 2*treeIndex +1);
	buildTree(a,b,tree, mid+1, end, 2*treeIndex +2);

	int left = tree[2*treeIndex +1];
	int right = tree[2*treeIndex +2];

	tree[treeIndex] = compare(left, right ,a,b);
}

int query(int* tree , int start, int end ,int treeIndex ,int l ,int r, int* a, int* b){
	if(r < start || l > end){
		return -1;
	}

	if(l<=start && r>=end){
        return tree[treeIndex];
	}

	int mid = (start +end)/2;
	if(l>mid){
		//return right part only else left will give -1 index which is not valid
		return query(tree, mid+1, end, 2*treeIndex +2, l, r,a,b);
	}	
	if(r<=mid){
		return query(tree, start, mid, 2*treeIndex +1, l, r,a,b);
	}

	int leftIndex = query(tree, mid+1, end, 2*treeIndex +2, l, r,a,b);
	int rightIndex = query(tree, start, mid, 2*treeIndex +1, l, r,a,b);

	return compare(leftIndex , rightIndex,a,b);
}



int main(){

	int n;
	cin>>n;

	int* a = new int[n];
	int* b = new int[n];
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	for(int i=0;i<n;i++){
		cin>>b[i];
	}

	int* tree = new int[4*n];
	buildTree(a,b,tree,0,n-1, 0);

	int q;
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		cout<<query(tree,0,n-1, 0, l-1, r-1,a,b) + 1 <<endl;
	}
}














