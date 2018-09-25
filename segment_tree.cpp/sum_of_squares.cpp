/*
	Segment trees are extremely useful. In particular "Lazy Propagation" (i.e. see here, for example) allows one to compute sums over a range in O(lg(n)), and update ranges in O(lg(n)) as well. In this problem you will compute something much harder:

The sum of squares over a range with range updates of 2 types:

1) increment in a range

2) set all numbers the same in a range.

Input
There will be T (T <= 25) test cases in the input file. First line of the input contains two positive integers, N (N <= 100,000) and Q (Q <= 100,000). The next line contains N integers, each at most 1000. Each of the next Q lines starts with a number, which indicates the type of operation:

2 st nd -- return the sum of the squares of the numbers with indices in [st, nd] {i.e., from st to nd inclusive} (1 <= st <= nd <= N).

1 st nd x -- add "x" to all numbers with indices in [st, nd] (1 <= st <= nd <= N, and -1,000 <= x <= 1,000).

0 st nd x -- set all numbers with indices in [st, nd] to "x" (1 <= st <= nd <= N, and -1,000 <= x <= 1,000).

Output
For each test case output the “Case <caseno>:” in the first line and from the second line output the sum of squares for each operation of type 2. Intermediate overflow will not occur with proper use of 64-bit signed integer.

Example
Input:
2
4 5
1 2 3 4
2 1 4
0 3 4 1
2 1 4
1 3 4 1
2 1 4
1 1
1
2 1 1

Output:
Case 1:
30
7
13
Case 2:
1
*/



#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX 400005

struct  node{
	ll sum = 0;
	ll squareSum = 0 ;
};

struct node_p{
    string str="";
    ll data = 0;
};

node tree[MAX];
node_p lazy[MAX];
ll arr[1000005];

void buildtree(ll start, ll end, ll treeIndex){
	if(start == end){
		tree[treeIndex].sum = arr[start];
		tree[treeIndex].squareSum = arr[start] * arr[start];
		return;
	}

	ll mid = (start + end)/2;
	buildtree(start, mid, 2*treeIndex+1);
	buildtree(mid+1, end, 2*treeIndex+2);
	tree[treeIndex].sum = tree[2*treeIndex+1].sum  + tree[2*treeIndex +2].sum;
	tree[treeIndex].squareSum = tree[2*treeIndex+1].squareSum  + tree[2*treeIndex +2].squareSum;
}

void update(ll start, ll end, ll treeIndex , ll type, ll sr,ll er, ll val){
	
	//pending lazy updates
	node_p p = lazy[treeIndex];
	string str = p.str;
	ll number = p.data;
	ll len = end - start + 1;
	if(str != ""){
		if(str == "inc"){
			tree[treeIndex].squareSum += number*number*len + 2* number * tree[treeIndex].sum; 
			tree[treeIndex].sum += number * len; 
			if(start != end){
	            lazy[2*treeIndex + 1].str = "inc";
	            lazy[2*treeIndex + 1].data = number;
                lazy[2*treeIndex + 2].str = "inc";
	            lazy[2*treeIndex + 2].data = number;
			}
		}else if(str == "same"){
			tree[treeIndex].squareSum = number*number*len; 
			tree[treeIndex].sum = number * len; 
			if(start!=end){
	            lazy[2*treeIndex + 1].str = "same";
	            lazy[2*treeIndex + 1].data = number;
                lazy[2*treeIndex + 2].str = "same";
	            lazy[2*treeIndex + 2].data = number;
			}
		}
		lazy[treeIndex].str = "";
		lazy[treeIndex].data = 0 ;
	}

	if(er<start || sr>end){
		return;
	}

	if(sr<=start && er>=end){
		ll len = end - start + 1;
		if(type == 1){
			// increment
			tree[treeIndex].squareSum += val*val*len + 2 * val * tree[treeIndex].sum; 
			tree[treeIndex].sum += val * len; 
			 lazy[2*treeIndex + 1].str = "inc";
            lazy[2*treeIndex + 1].data = val;
            lazy[2*treeIndex + 2].str = "inc";
            lazy[2*treeIndex + 2].data = val;
		}else{
			tree[treeIndex].squareSum = val*val*len; 
			tree[treeIndex].sum = val * len; 
			 lazy[2*treeIndex + 1].str = "same";
            lazy[2*treeIndex + 1].data = val;
            lazy[2*treeIndex + 2].str = "same";
            lazy[2*treeIndex + 2].data = val;
		}
		return;
	}

	ll mid = (start +end)/2;
	update(start, mid, 2*treeIndex+1 , type,sr,er, val);
	update(mid+1,end, 2*treeIndex+2 , type,sr,er, val);
	tree[treeIndex].sum = tree[2*treeIndex+1].sum  + tree[2*treeIndex +2].sum;
	tree[treeIndex].squareSum = tree[2*treeIndex+1].squareSum  + tree[2*treeIndex +2].squareSum;
}

ll query(ll start, ll end, ll treeIndex, ll sr, ll er){
	// pending lazy step
	node_p p = lazy[treeIndex];
	string str = p.str;
	ll number = p.data;
	ll len = end - start + 1;
		if(str != ""){
		if(str == "inc"){
			tree[treeIndex].squareSum += number*number*len + 2* number * tree[treeIndex].sum; 
			tree[treeIndex].sum += number * len; 
			if(start != end){
	            lazy[2*treeIndex + 1].str = "inc";
	            lazy[2*treeIndex + 1].data = number;
                lazy[2*treeIndex + 2].str = "inc";
	            lazy[2*treeIndex + 2].data = number;
			}
		}else if(str == "same"){
			tree[treeIndex].squareSum = number*number*len; 
			tree[treeIndex].sum = number * len; 
			if(start!=end){
	            lazy[2*treeIndex + 1].str = "same";
	            lazy[2*treeIndex + 1].data = number;
                lazy[2*treeIndex + 2].str = "same";
	            lazy[2*treeIndex + 2].data = number;
			}
		}
		lazy[treeIndex].str = "";
		lazy[treeIndex].data = 0 ;
	}
	
	if(er<start || sr> end){
		return 0;
	}

	if(sr<=start && er>=end){
		return tree[treeIndex].squareSum;
	}

	ll mid = (start +end)/2;
	ll ans1 = query(start,mid,2*treeIndex+1,sr,er);
	ll ans2 = query(mid+1,end,2*treeIndex+2,sr,er);
	return ans2 + ans1;
}

int main(){
	ll t;
	cin>>t;
    for(ll i=1;i<=t;i++){
        cout<<"Case "<<i<<":"<<endl;        
		ll n,q;
		cin>>n>>q;
		for(ll i=0;i<n;i++){
			cin>>arr[i];
		}

		buildtree(0, n-1, 0);
		while(q--){
			ll type;
			cin>>type;
			if(type == 2){
				ll st;
				ll nd;
				cin>>st>>nd;
				cout<< query(0, n-1, 0, st-1, nd-1)<<endl; 
			}else if(type == 1){
				//1 is to inc
				ll a,b,c;
				cin>>a>>b>>c;
				update(0, n-1, 0, type , a-1, b-1, c);
			}else{
				//0 is make same in a range
				ll a,b,c;
				cin>>a>>b>>c;
				update(0, n-1, 0, type , a-1, b-1, c);
			}
		}
	}
} 
 












