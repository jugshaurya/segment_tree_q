/*

https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/help-ashu-1/
	Even Or Odd

Ashu and Shanu are best buddies. One day Shanu gives Ashu a problem to test his intelligence.He gives him an array of N natural numbers and asks him to solve the following queries:-
Query 0 :- modify the element present at index i to x.
Query 1:- count the number of even numbers in range l to r inclusive.
Query 2:- count the number of odd numbers in range l to r inclusive.
Input:
First line of the input contains the number N. Next line contains N natural numbers. 
Next line contains an integer Q followed by Q queries.

0 x y - modify the number at index x to y. 

1 x y - count the number of even numbers in range l to r inclusive.

2 x y - count the number of odd numbers in range l to r inclusive.

Constraints:
1<=N,Q<=10^5

1<=l<=r<=N 

0<=Ai<=10^9

1<=x<=N

0<=y<=10^9

Note:-
indexing starts from 1.

Sample Input
6
1 2 3 4 5 6
4
1 2 5
2 1 4
0 5 4
1 1 6
Sample Output
2
2
4
*/



#include<bits/stdc++.h>
using namespace std;

struct evenOdd{
    int even;
    int odd;
};

void buildTree(int* arr, evenOdd* tree, int start, int end, int treeIndex){
	if(start == end){
        if(arr[start] & 1){
            tree[treeIndex].odd = 1;
            tree[treeIndex].even = 0;
            return;
        }
        tree[treeIndex].even = 1;
        tree[treeIndex].odd = 0;
		return ;
	}

	int mid = (start+end)/2;
	buildTree(arr,tree,start, mid, 2*treeIndex + 1);
	buildTree(arr,tree,mid+1, end, 2*treeIndex + 2);

	int leftChild = 2*treeIndex + 1;
	int rightChild = 2*treeIndex + 2;

	tree[treeIndex].even =  tree[leftChild].even + tree[rightChild].even ;
	tree[treeIndex].odd =  tree[leftChild].odd + tree[rightChild].odd ;
}

void updateTree(int* arr, evenOdd* tree, int updateIndex, int updateValue, int start, int end, int treeIndex){

	if(start == end){
		arr[start] = updateValue;
        if(arr[start] & 1){
            tree[treeIndex].odd = 1;
            tree[treeIndex].even = 0;
            return;
        }
        tree[treeIndex].even = 1;
        tree[treeIndex].odd = 0;
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

    tree[treeIndex].even =  tree[leftChild].even + tree[rightChild].even ;
	tree[treeIndex].odd =  tree[leftChild].odd + tree[rightChild].odd ;
}

evenOdd query(evenOdd* tree,int start, int end,  int a, int b, int treeIndex){
	evenOdd obj ;

	if(b < start || end < a ){
        obj.even = 0 ;
        obj.odd = 0 ;
		return obj;
	}

	//[start,end] lies completely inside [a,b] i.e 
	if(start>=a && end<=b){
		return tree[treeIndex];
	}

	//lies partially  inside partially outside
	int mid = (start +end)/2;
	evenOdd ans1 = query(tree, start, mid, a,b, 2*treeIndex + 1);
	evenOdd ans2 = query(tree, mid+1, end, a, b, 2*treeIndex + 2);
	obj.even = ans1.even + ans2.even;
	obj.odd = ans1.odd + ans2.odd;
    return obj;
}

int main(){
	int n;
	cin>>n;

	int* arr = new int[n];
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}

	evenOdd* tree = new evenOdd[4*n];
	buildTree(arr, tree, 0, n-1, 0);

    int q;
    cin>>q;

    int ch,a,b;
	while(q--){
		cin>>ch>>a>>b;
		if(ch == 0){
            updateTree(arr,tree,a-1,b,0,n-1,0);
		}else if(ch == 1){
            //calcuate even no.
            cout<<query(tree, 0, n-1, a-1, b-1, 0).even<<endl;
		}else{
            //calcuate odd no.
            cout<<query(tree, 0, n-1, a-1, b-1, 0).odd<<endl;   
         }
	}
}	