/*

Maximum Pair Sum
Send Feedback
You are given a sequence A[1], A[2], ..., A[N], ( 0 ≤ A[i] ≤ 10^8 , 2 ≤ N ≤ 10^5 ). There are two types of operations and they are defined as follows:
Update:
This will be indicated in the input by a 'U' followed by space and then two integers i and x.
U i x, 1 ≤ i ≤ N, and x, 0 ≤ x ≤ 10^8.
This operation sets the value of A[i] to x.
Query:
This will be indicated in the input by a 'Q' followed by a single space and then two integers i and j.
Q x y, 1 ≤ x < y ≤ N.
You must find i and j such that x ≤ i, j ≤ y and i != j, such that the sum A[i]+A[j] is maximized. Print the sum A[i]+A[j].
Input
The first line of input consists of an integer N representing the length of the sequence. 
Next line consists of N space separated integers A[i]. Next line contains an integer Q, Q ≤ 10^5, representing the number of operations. Next Q lines contain the operations.
Output
 Output the maximum sum mentioned above, in a separate line, for each Query.
Input:
5
1 2 3 4 5
6
Q 2 4
Q 2 5
U 1 6
Q 1 5
U 1 7
Q 1 5
Output:
7
9
11
12
*/


#include<bits/stdc++.h>
using namespace std;
	
struct node{
	int max;
	int secondMax;
};

void buildTree(int* arr, node* tree, int start, int end, int treeIndex){
	if(start == end){
		tree[treeIndex].max = arr[start];
		tree[treeIndex].secondMax = INT_MIN;
		return;	
	}

	int mid = (start + end)/2;
	buildTree(arr,tree, start, mid, 2*treeIndex + 1);
	buildTree(arr,tree, mid+1, end, 2*treeIndex + 2);

	node leftChild = tree[2*treeIndex + 1];
	node rightChild = tree[2*treeIndex + 2];

	tree[treeIndex].max = max(leftChild.max, rightChild.max);
	tree[treeIndex].secondMax = min( 	max(rightChild.max, leftChild.secondMax) ,
									 	max(leftChild.max, rightChild.secondMax)
									 );
}

void updateTree(int* arr, node* tree, int start, int end, int treeIndex,int updateIndex, int updateValue){
	if(start == end){
		arr[start] = updateValue;
		tree[treeIndex].max = updateValue;
		tree[treeIndex].secondMax = INT_MIN;
		return ;
	}

	int mid = (start+end)/2;
	if(updateIndex <= mid){
		updateTree(arr, tree, start, mid, 2*treeIndex + 1, updateIndex, updateValue);
	}else{
		updateTree(arr, tree, mid+1, end, 2*treeIndex + 2, updateIndex, updateValue);
	}

	node leftChild = tree[2*treeIndex + 1];
	node rightChild = tree[2*treeIndex + 2];

	tree[treeIndex].max = max(leftChild.max, rightChild.max);
	tree[treeIndex].secondMax = min( max(rightChild.max, leftChild.secondMax) ,
									 max(leftChild.max, rightChild.secondMax)
									 );

}

node query(node* tree, int start, int end, int treeIndex,  int a, int b){
	node ans;
	//[a,b] lies completely outside [start ,end]
	if( b < start || end < a ){
		ans.max = INT_MIN;
		ans.secondMax = INT_MIN;
		return ans;
	}

	//[start,end] lies completely inside [a,b] i.e 
	if(start>=a && end<=b){
		ans.max = tree[treeIndex].max ;
		ans.secondMax =  tree[treeIndex].secondMax ;
		return ans;
	}

	//lies partially inside partially outside
	int mid = (start +end)/2;
	node leftquery = query(tree, start, mid, 2*treeIndex + 1, a,b);
	node rightquery = query(tree, mid+1, end, 2*treeIndex + 2, a,b);

	ans.max = max(leftquery.max, rightquery.max);
	ans.secondMax = min( max(rightquery.max, leftquery.secondMax) ,
						max(leftquery.max, rightquery.secondMax)
					);
	return ans;
}

int main(){

	int n;
	cin>>n;

	int* arr = new int[n];
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}

	int q;
	cin>>q;

	node* tree = new node[3*n];
	buildTree(arr,tree, 0, n-1, 0);

	char ch;
	int a,b;
	while(q--){
		cin>>ch>>a>>b;
		if(ch == 'U'){
			updateTree(arr,tree,0,n-1, 0, a-1, b);
		}else{
			node ans = query(tree, 0, n-1, 0, a-1, b-1);
          	cout<< ans.max + ans.secondMax <<endl;
		}
	}
}









