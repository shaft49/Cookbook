class DynamicSegmentTree {
private:
	struct node {
		node *l,*r;
		ll sum,lazy;
 
		node() {
			l = r = nullptr;
			sum = lazy = 0;
		}
 
	};
 
    node* root;
    ll left_lim, right_lim;
 
	void process(node *n,ll st,ll en,ll val) {
		n->sum = val * (en-st+1);
		n->lazy = 0;
		if(st != en) {
			if( n->l == nullptr) n->l = new node();
			if( n->r == nullptr) n->r = new node();
			n->l->lazy = val;
			n->r->lazy = val;
		}
	}
 
 
	void update(node *n,ll st,ll en,ll l,ll r,ll val) {
		if ( n->lazy)
			process(n,st,en,n->lazy);
 
		if( en < l || r < st) return;
 
		if(l <= st && en <=r) {
			process(n,st,en,val);
			return;
		}
 
		ll mid = (st+en)/2;
 
		if( n->l == nullptr) n->l = new node();
		if( n->r == nullptr) n->r = new node();
 
		update(n->l,st,mid,l,r,val);
		update(n->r,mid+1,en,l,r,val);
 
		n->sum = n->l->sum + n->r->sum;
 
	}
	
	ll query(node *n,ll st,ll en,ll l,ll r) {
		if ( n->lazy)
			process(n,st,en,n->lazy);
 
		if( en < l || r < st) return 0LL;
 
		if(l <= st && en <=r)
			return n->sum;
 
		ll mid = (st+en)/2;
 
		if( n->l == nullptr) n->l = new node();
		if( n->r == nullptr) n->r = new node();
 
        ll s1 = query(n->l,st,mid,l,r);
        ll s2 = query(n->r,mid+1,en,l,r);
 
		return s1 + s2;
	}
public:
        DynamicSegmentTree() {
			root = new node();
			left_lim = 1LL;
			right_lim = 500000000LL;
        }
 
        void update(ll l,ll r,ll val) {
			update(root, left_lim, right_lim, l, r, val);
        }
 
        ll query(ll l,ll r) {
            return query(root, left_lim, right_lim, l, r);
        }
};