/*
	https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/2-vs-3/https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/2-vs-3/

*/


#include<bits/stdc++.h>
using namespace std;

int modularExp(int a, int len, int mod){
    if(len == 0){
        return 1;    
    }
    if(len == 1){
        return a;
    }
    int smallans = modularExp( a, len/2, mod);
    smallans = (smallans* smallans ) % mod;
    if(len&1){
        smallans =  (smallans * a) % mod;
    }

    return smallans;
}

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

	int rightLength = end - mid;
	tree[treeIndex] = (tree[leftChild] * (modularExp(2,rightLength,3)) + tree[rightChild]) % 3;	
}

void updateTree(int* arr, int* tree, int updateIndex, int updateValue, int start, int end, int treeIndex){

	if( start == end){
		arr[start] = updateValue;
        tree[treeIndex] = updateValue;
        return;
	}

	int mid = (start + end)/2;
	if(updateIndex <= mid){
		updateTree(arr,tree,updateIndex, updateValue, start, mid, 2*treeIndex + 1);
	}else{
		updateTree(arr,tree,updateIndex, updateValue, mid+1, end, 2*treeIndex + 2);
	}

	int leftChild = 2*treeIndex + 1;
	int rightChild = 2*treeIndex + 2;

	int rightLength = end - mid;
	tree[treeIndex] = (tree[leftChild] * (modularExp(2,rightLength,3)) + tree[rightChild]) % 3;	
}

int query(int* tree,int start, int end,  int a, int b, int treeIndex){
	
	//[a,b] lies completely outside [start ,end]
	if( b < start || end < a ){
		return 0;
	}

	//[start,end] lies completely inside [a,b] i.e 
	if(start>=a && end<=b){
		return tree[treeIndex];
	}

	//lies partially  inside partially outside
	int mid = (start +end)/2;
	int ans1 = query(tree, start, mid, a,b, 2*treeIndex + 1);
	int ans2 = query(tree, mid+1, end, a, b, 2*treeIndex + 2);

	int rightLength = end - mid + 1 ;
	return (ans1 * (modularExp(2,rightLength,3)) + ans2) % 3;	
}

int main(){
	int n;
	cin>>n;
    string str;
    cin>>str;
	int* arr = new int[n];
	for(int i=0;i<n;i++){
		arr[i] = (str[i] -'0');
	}

	int* tree = new int[4*n];
	buildTree(arr, tree, 0, n-1, 0);
    // for(int i=0;i<4*n;i++){
	// 	cout<<tree[i]<<" ";
	// }

    int q ;
    cin>>q;

    int type, a,b;
	while(q--){
		cin >> type;
		if(type == 0){
			cin>> a >> b;
			cout<<query(tree,0 ,n-1, a, b, 0)<<endl;
		}else{
			cin>>a;
			if(arr[a] == 0){
				updateTree(arr, tree, a, 1, 0, n-1, 0);
			}
		}
	}
}











