
/*
	lazy propagation to update values  in a range
	
	Horrible Query

	World is getting more evil and it's getting tougher to get into the Evil League of Evil. Since the legendary Bad Horse has retired, now you have to correctly answer the evil questions of Dr. Horrible, who has a PhD in horribleness (but not in Computer Science). You are given an array of N elements, which are initially all 0. After that you will be given C commands. They are -
	0 p q v - you have to add v to all numbers in the range of p to q (inclusive), where p and q are two indexes of the array.

	1 p q - output a line containing a single integer which is the sum of all the array elements between p and q (inclusive)
	Input
	In the first line you'll be given T, number of test cases.

	Each test case will start with N (N <= 100 000) and C (C <= 100 000). After that you'll be given C commands in the format as mentioned above. 1 <= p, q <= N and 1 <= v <= 10^7.
	Output
	Print the answers of the queries.
	Input:
	1
	8 6
	0 2 4 26
	0 4 8 80
	0 4 5 20
	1 8 8 
	0 5 7 14
	1 4 8
	Output:
	80  
	508

*/

#include<bits/stdc++.h>
using namespace std;
void updateInRangeLazyPro(long long* tree ,long long* lazy, long long start, long long end, long long treeIndex, long long sr, long long er, long long inc){
        
    if(start>end){
        return  ;
    }

    if(lazy[treeIndex] != 0){
		tree[treeIndex] += lazy[treeIndex]*(end-start+1);
		if(start != end){
			//leaves exist
			lazy[2*treeIndex + 1] += lazy[treeIndex];
			lazy[2*treeIndex + 2] += lazy[treeIndex];
		}
		lazy[treeIndex] = 0;
	}

 
	//no overlap
	if( er < start || sr > end ){
		return;
	}

	//complete overlap
	if(sr<=start && er>=end){
		tree[treeIndex] += inc*(end-start+1);
        if(start!=end){
            lazy[2*treeIndex + 1] += inc;            
            lazy[2*treeIndex + 2] += inc;
        }
		return;
	}
	
	//partially overlap
	long long mid = (start+end)/2;
	updateInRangeLazyPro(tree , lazy, start, mid, 2*treeIndex +1, sr, er, inc);
	updateInRangeLazyPro(tree , lazy, mid+1, end, 2*treeIndex +2, sr, er, inc);
	tree[treeIndex] = tree[2*treeIndex +1] + tree[2*treeIndex +2];
}

long long query(long long* tree ,long long* lazy, long long start, long long end, long long treeIndex, long long left, long long right){
	
    if(lazy[treeIndex] != 0){
		tree[treeIndex] += lazy[treeIndex]*(end-start+1);
		if(start != end){
			//leaves exist
			lazy[2*treeIndex + 1] += lazy[treeIndex];
			lazy[2*treeIndex + 2] += lazy[treeIndex];
		}
		lazy[treeIndex] = 0;
	}


	//no overlap
	if( right <start || left >end){
		return 0 ;
	}

	//complete overlap
	if(left<=start && right>=end){
		return tree[treeIndex];
	}
	
	//partially overlap
	long long mid = (start+end)/2	;
	long long leftans = query(tree, lazy, start , mid, 2*treeIndex +1, left, right);
	long long rightans = query(tree, lazy, mid+1 ,end, 2*treeIndex +2, left, right);
	return leftans + rightans;
}

int main(){
	long long t;
	cin>>t;
	while(t--){
		long long n;
        long long q;
		cin>>n>>q;    
	
		long long* tree = new long long[4*n](); //tree is already build and contain sum of elements as 0 initially
		long long* lazy = new long long[4*n]();	
		long long type,a,b,c;

        while(q--){
			cin>>type;
			if(type == 0){
				cin>>a>>b>>c;
				updateInRangeLazyPro(tree,lazy,0,n-1,0, a-1,b-1,c);
			}else{
				cin>>a>>b;
				cout<<query(tree,lazy,0,n-1,0,a-1,b-1)<<endl;
			}
		}
       
	}
}