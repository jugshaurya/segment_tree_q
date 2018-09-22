/*

https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/range-minimum-query/
Q-->	Minimum In SubArray
	Range Minimum Query
Given an array A of size N, there are two types of queries on this array.
1) qlr: In this query you need to print the minimum in the sub-array A[l:r].
2) uxy: In this query you need to update A[x]=y.

Input:
First line of the test case contains two integers, N and Q, size of array A and number of queries.
Second line contains N space separated integers, elements of A.
Next Q lines contain one of the two queries.

Output:
For each type 1 query, print the minimum element in the sub-array A[l:r].

Contraints:
1≤N,Q,y≤10^5
1≤l,r,x≤N
*/


#include<bits/stdc++.h>
using namespace std;

void buildTree(int* arr, int* tree, int start, int end, int treeIndex){
	if(start == end){
		tree[treeIndex] = arr[start];
		return ;
	}

	int mid = (start+end)/2;
	buildTree(arr,tree,start, mid, 2*treeIndex + 1);
	buildTree(arr,tree,mid+1, end, 2*treeIndex + 2);

	int leftChild = 2*treeIndex + 1;
	int rightChild = 2*treeIndex + 2;

	tree[treeIndex] =  min(tree[leftChild] , tree[rightChild] );
}

void updateTree(int* arr, int* tree, int updateIndex, int updateValue, int start, int end, int treeIndex){

	if( start == end){
		//that start and end would updatIndex
		arr[start] = updateValue;
        tree[treeIndex] = updateValue;
        return;
	}

	int mid = (start + end)/2;
	if(updateIndex <= mid){
		//go ot left
		updateTree(arr,tree,updateIndex, updateValue, start, mid, 2*treeIndex + 1);
	}else{
		//go to right
		updateTree(arr,tree,updateIndex, updateValue, mid+1, end, 2*treeIndex + 2);
	}

	int leftChild = 2*treeIndex + 1;
	int rightChild = 2*treeIndex + 2;
	tree[treeIndex] =  min(tree[leftChild] , tree[rightChild]);
}

int query(int* tree,int start, int end,  int a, int b, int treeIndex){
	
	//[a,b] lies completely outside [start ,end]
	if( b < start || end < a ){
		return INT_MAX;
	}

	//[start,end] lies completely inside [a,b] i.e 
	if(start>=a && end<=b){
		return tree[treeIndex];
	}

	//lies partially  inside partially outside
	int mid = (start +end)/2;
	int ans1 = query(tree, start, mid, a,b, 2*treeIndex + 1);
	int ans2 = query(tree, mid+1, end, a, b, 2*treeIndex + 2);
	return min(ans1,ans2);

}

int main(){
	int n;
	int q;
	cin>>n>>q;

	int* arr = new int[n];
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}

	int* tree = new int[4*n];
	buildTree(arr, tree, 0, n-1, 0);

    // for(int i=0;i<4*n;i++){
    //     cout<<tree[i]<<" ";
    // }

    // cout<<endl;
	char ch;
    int a,b;
	while(q--){
		cin>>ch>>a>>b;
    
		if(ch == 'q' || ch == 'Q'){
			cout<<query(tree,0 ,n-1, a-1, b-1, 0)<<endl;
		}else{
			updateTree(arr, tree, a-1, b, 0, n-1, 0);
		}
	}
}	
