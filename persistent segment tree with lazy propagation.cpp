const int MAX = 200010;
int seg[20 * MAX], lazy[20 * MAX], L[20 * MAX], R[20 * MAX], NEW = 2;
int n;
void build(int id = 1, int l = 0, int r = n - 1){
	seg[id] = 0;
	if (l == r)return;
	int mid = (l + r) >> 1;
	L[id] = NEW++;
	R[id] = NEW++;
	build(L[id], l, mid);
	build(R[id], mid + 1, r);
}
int update(int x, int y , int z, int id, int l = 0, int r = n - 1){
	if (l > y || r < x) return id;
	int ID = NEW++;
	if (l >= x && r <= y){
		lazy[ID] = z + lazy[id];
		seg[ID] = (r - l + 1) * z + seg[id];
		L[ID] = L[id]; // don't continue updating left and right
		R[ID] = R[id];
		return ID;
	}
	int mid = (l + r) >> 1;
	if (lazy[id]){
		L[id]=update(l, r, lazy[id], L[id], l, mid); // continue updating left, it will change L[id] to new one
		R[id]=update(l, r, lazy[id], R[id], mid + 1, r);
		lazy[id] = 0;
	}

	L[ID] = update(x, y, z, L[id], l, mid);
	R[ID] = update(x, y, z, R[id], mid + 1, r);
	seg[ID] = seg[L[ID]] + seg[R[ID]];
	return ID;
}
int query(int x, int y , int id, int l = 0, int r = n - 1){
	if (l > y || r < x) return 0;
	if (l >= x && r <= y) return seg[id];
	int mid = (l + r) >> 1;
	if (lazy[id]){
		L[id] = update(l, r, lazy[id], L[id], l, mid);
		R[id] = update(l, r, lazy[id], R[id], mid + 1, r);
		lazy[id] = 0;
	}
	return query(x,y ,  L[id], l, mid) + query(x,y, R[id], mid + 1, r);
}
