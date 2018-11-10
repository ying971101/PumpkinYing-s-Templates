const int maxn = 1010;
const int up = 26;

int cnt = 0,root = 0;

struct Node {
	int num,fail,last;
	int nxt[up];
	void clear() {
		mem(nxt,-1);
		num = fail = last = 0;
	}
}ns[maxn];

int newNode() {
	ns[cnt].clear();
	return cnt++;
}

void Insert(char* s) {
	int len = strlen(s);
	int p = root;
	for(int i = 0;i < len;i++) {
		int pos = s[i]-'A';
		if(ns[p].nxt[pos] == -1) ns[p].nxt[pos] = newNode();
		p = ns[p].nxt[pos];
	}
	ns[p].num++;
}

void getFail() {
	queue<int> q;
	for(int i = 0;i < up;i++) {
		int x = ns[root].nxt[i];
		if(x == -1) ns[root].nxt[i] = root;
		else {
			ns[x].fail = ns[x].last = root;
			q.push(x);
		}
	}

	while(!q.empty()) {
		int t = q.front();
		q.pop();
		for(int i = 0;i < up;i++) {
			int x = ns[t].nxt[i];
			if(x == -1) {
				ns[t].nxt[i] = ns[ns[t].fail].nxt[i];
			}
			else {
				ns[x].fail = ns[ns[t].fail].nxt[i];
				q.push(x);
				if(ns[ns[x].fail].num > 0) ns[x].last = ns[x].fail;
				else ns[x].last = ns[ns[x].fail].last;
			}
		}
	}
}

void init() {
	cnt = 0;
	root = newNode();
}

