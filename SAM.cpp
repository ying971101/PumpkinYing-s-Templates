const int maxn = 300010;
const int up = 30;
const ll mod = 1e9+7;

struct state {
	int len,pre;
	int nxt[up];
}ns[maxn*2];

int cnt = 0;

int newNode(int l) {
	ns[cnt].len = l;
	ns[cnt].pre = -1;
	mem(ns[cnt].nxt,-1);
	return cnt++;
}

int root = 0;
int last = 0;

void init() {
	cnt = last = 0;
	root = newNode(0);
}

//广义sam取消注释并每次插入串之后把last更新为root
void extend(int x) {
	int p = last;
	int np;

	/*
	if(ns[p].nxt[x] != -1 && ns[ns[p].nxt[x]].len == ns[p].len+1) {
		last = ns[p].nxt[x];
		return;
	}
	*/

	np = newNode(ns[p].len+1);

	/*
	if(ns[p].nxt[x] != -1) {
		int q = ns[p].nxt[x];
		for(int i = 0;i < up;i++) ns[np].nxt[i] = ns[q].nxt[i];
		ns[np].pre = ns[q].pre;
		ns[q].pre = np;
		while(p != -1 && ns[p].nxt[x] == q)
			ns[p].nxt[x] = np,p = ns[p].pre;
		last = np;
		return;
	}
	*/

	while(p != -1 && ns[p].nxt[x] == -1)
		ns[p].nxt[x] = np,p = ns[p].pre;
	if(p == -1) ns[np].pre = root;
	else {
		int q = ns[p].nxt[x];
		if(ns[p].len+1 == ns[q].len) 
			ns[np].pre = q;
		else {
			int clone = newNode(ns[p].len+1);
			for(int i = 0;i < up;i++)
				ns[clone].nxt[i] = ns[q].nxt[i];
			ns[clone].pre = ns[q].pre;
			for(;p != -1 && ns[p].nxt[x] == q;p = ns[p].pre)
				ns[p].nxt[x] = clone;
			ns[q].pre = ns[np].pre = clone;
		}
	}

	last = np;
}
