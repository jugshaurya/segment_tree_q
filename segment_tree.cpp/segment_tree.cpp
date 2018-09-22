/* segment tree is also stored in an array just like heap data structure */


/*
	Q--> calculate the sum between given range
*/
#include<iostream>
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

	tree[treeIndex] =  tree[leftChild]  + tree[rightChild];
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
	tree[treeIndex] =  tree[leftChild]  + tree[rightChild];
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
	return ans1+ans2;

}

int main(){

	int arr[] = {1,2,3,4,5,6,7,8,9};
	int n = 9;
	int* tree = new int[4*n];
	int treeIndex = 0 ;

	/* builduing tree in O(N)*/
	buildTree(arr,tree,0,8,0);

	/* updating tree --> O(logN)*/
	int updateIndex = 3; 
	int updateValue = 21; 
	updateTree(arr, tree, updateIndex, updateValue, 0,8,0);
    
    // printing  tree array
    for(int i=0;i<4*n;i++){
        cout<<tree[i]<<" ";
    }
    cout<<endl;

    int a = 1;
    int b = 4;
    cout << query(tree, 0, 8, a, b, 0);
}









