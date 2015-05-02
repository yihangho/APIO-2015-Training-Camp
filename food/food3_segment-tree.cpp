#include <iostream>
#include <vector>

using namespace std;

vector<long long> tree;

/*
assume that you start with non-empty order, and the previous order are stored in array floor[], here is how you initialize.
void initialize(int node, int l, int r){
	if(l == r){
		tree[node] = floor[l];
		return;
	}
	
	int lnode = 2*node, rnode = 2*node+1;
	initialize(lnode, l, (l+r)/2);
	initialize(rnode, (l+r)/2+1, r);
	
	tree[node] = tree[lnode] + tree[rnode];
	return;
}
*/

void update(int node, int l, int r, int target, int newval){
	if(target < l || target > r){		//invalid range
		return;
	}
	if(l == r){			//target found, question: why this indeed is the target?
		tree[node] += newval;
		return;
	}
	
	int lnode = 2*node, rnode = 2*node+1;
	update(lnode, l, (l+r)/2, target, newval);
	update(rnode, (l+r)/2+1, r, target, newval);
	
	tree[node] = tree[lnode] + tree[rnode]; //update this node;
	return;	
}

long long query(int node, int l, int r, int ltarget, int rtarget){
	if(rtarget < l || ltarget > r){		//invalid range
		return 0;
	}
	if(ltarget <= l && rtarget >= r){	//in range
		return tree[node];
	}
	
	int lnode = 2*node, rnode = 2*node+1, mid = (l+r)/2;
	long long lval, rval;
	lval = query(lnode, l, mid, ltarget, rtarget);
	rval = query(rnode, mid+1, r, ltarget, rtarget);

	return lval+rval;
}

int main(){
	int n, q, type, y1, y2, floor, package;
	cin >> n >> q;
	tree.assign(4*n, 0);
	while(q--){
		cin >> type;
		if(type == 1){
			cin >> floor >> package;
			update(1, 1, n, floor, package);
		}
		else{
			cin >> y1 >> y2;
			cout << query(1, 1, n, y1, y2) << endl;
		}
	}
	
	return 0;
}