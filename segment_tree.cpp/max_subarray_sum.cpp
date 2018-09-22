/*

Maximum Sum In Subarray
Send Feedback
You are given a sequence A[1], A[2], ..., A[N] . ( |A[i]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:
Query(x,y) = Max { a[i]+a[i+1]+...+a[j] ; x ≤ i ≤ j ≤ y }.
Given M queries, your program must output the results of these queries.
Input
The first line of the input file contains the integer N.
In the second line, N numbers follow.
The third line contains the integer M.
M lines follow, where line i contains 2 numbers xi and yi.
Output
Your program should output the results of the M queries, one 
query per line.
Sample Input:
3 
-1 2 3 
1
1 2
Sample Output:
2
*/
/*

Maximum Sum In Subarray
Send Feedback
You are given a sequence A[1], A[2], ..., A[N] . ( |A[i]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:
Query(x,y) = Max { a[i]+a[i+1]+...+a[j] ; x ≤ i ≤ j ≤ y }.
Given M queries, your program must output the results of these queries.
Input
The first line of the input file contains the integer N.
In the second line, N numbers follow.
The third line contains the integer M.
M lines follow, where line i contains 2 numbers xi and yi.
Output
Your program should output the results of the M queries, one 
query per line.
Sample Input:
3 
-1 2 3 
1
1 2
Sample Output:
2
*/

#include<bits/stdc++.h>
using namespace std;
	
struct node{
	int maxSum;
	int sum;
	int bestPrefixSum;
	int bestSuffixSum;

    node(){
        maxSum = sum = bestPrefixSum =bestSuffixSum = INT_MIN;
    }

};

node merge( node leftChild, node rightChild){
    node ans;
    ans.sum = leftChild.sum + rightChild.sum;
	ans.bestPrefixSum = max(leftChild.bestPrefixSum, leftChild.sum + rightChild.bestPrefixSum);
	ans.bestSuffixSum = max(rightChild.bestSuffixSum , rightChild.sum + leftChild.bestSuffixSum);
	ans.maxSum = max(leftChild.maxSum, max(rightChild.maxSum,leftChild.bestSuffixSum +
                                           rightChild.bestPrefixSum));
    return ans;
}

void buildTree(int* arr, node* tree, int start, int end, int treeIndex){
	
  	if(start == end){
        tree[treeIndex].maxSum = arr[start];
        tree[treeIndex].sum = arr[start];
        tree[treeIndex].bestPrefixSum = arr[start];
        tree[treeIndex].bestSuffixSum = arr[start];		
		return;
	}

	int mid = (start + end)/2;
	buildTree(arr,tree, start, mid, 2*treeIndex + 1);
	buildTree(arr,tree, mid+1, end, 2*treeIndex + 2);

	node leftChild = tree[2*treeIndex + 1];
	node rightChild = tree[2*treeIndex + 2];

	tree[treeIndex] = merge(leftChild, rightChild);
}

node maxSubarraySum(node* tree, int start, int end, int treeIndex,  int a, int b){
	
	if( b < start || end < a ){
      	node ans = node();
		return ans;
	}

	if(start>=a && end<=b){
		return tree[treeIndex];
	}

	int mid = (start + end)/2;
  	if(a>mid){
      return maxSubarraySum(tree, mid+1, end, 2*treeIndex + 2, a,b);
    }
  
  	if(b<=mid){
      return maxSubarraySum(tree, start, mid, 2*treeIndex + 1, a,b);
 	 }
  
	node leftChild = maxSubarraySum(tree, start, mid, 2*treeIndex + 1, a,b);
	node rightChild = maxSubarraySum(tree, mid+1, end, 2*treeIndex + 2, a,b);
	
  	return merge(leftChild, rightChild);
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

	node* tree = new node[4*n];
	buildTree(arr,tree, 0, n-1, 0);
  	int a,b;
	while(q--){
		cin >> a >> b;
		node ans = maxSubarraySum(tree, 0, n-1, 0, a-1 , b-1);
		cout<< ans.maxSum << endl;
	}
}















