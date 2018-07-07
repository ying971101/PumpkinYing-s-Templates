const int maxn = 200010;
int a[maxn];

vector<int> to[maxn];
void addEdge(int u,int v)
{
	to[u].push_back(v);
	to[v].push_back(u);
}

int clk[maxn],blk[maxn];
struct query
{
	int l,r;
	int id;
	bool operator < (const query& b) const
	{
		if(blk[l] == blk[b.l]) return clk[r] < clk[b.r];
		return blk[l] < blk[b.l];
	}
}qs[maxn];

//for blocking
int blkcnt = 0;
int tim = 0,top = 0,t;
int sta[maxn],ans[maxn];

//for LCA
int f[maxn][40];
int pre[maxn],dep[maxn];

//get f array and divide blocks on tree
void dfs(int x,int d)
{
	int bot = top;
	clk[x] = tim++;
	dep[x] = d;

	for(int i = 1;i <= 22;i++) 
		if(f[x][i-1] != -1) f[x][i] = f[f[x][i-1]][i-1];
	
	int sz = to[x].size();
	for(int i = 0;i < sz;i++)
	{
		if(to[x][i] == f[x][0]) continue;
		f[to[x][i]][0] = x;
		dfs(to[x][i],d+1);
		if(top-bot >= t)
		{
			blkcnt++;
			while(top != bot) blk[sta[top--]] = blkcnt;
		}
	}
	sta[++top] = x;
}

int getLCA(int u,int v)
{
	if(dep[u] < dep[v]) swap(u,v);
	for(int i = 22;i >= 0;i--)
	{
		if(f[u][i] != -1 && dep[f[u][i]] >= dep[v]) u = f[u][i];
		if(dep[u] == dep[v]) break;
	}
	if(u == v) return u;
	for(int i = 22;i >= 0;i--)
		if(f[u][i] != f[v][i]) u = f[u][i],v = f[v][i];

	return f[u][0];
}

void move(int l,int r)
{
	while(l != r) 
	{
		if(dep[l] < dep[r]) swap(l,r);
		work(a[l]);
		l = f[l][0];
	}
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,m;
		scanf("%d%d",&n,&m);

		//init
		t = sqrt(n);
		for(int i = 1;i <= n;i++) to[i].clear();
		mem(f,-1);
		mem(pre,-1);
		
		for(int i = 0;i < n-1;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			addEdge(u,v);
		}

		//divide block
		tim = 0,blkcnt = 0,top = 0;
		dfs(1,0);
		blkcnt++;
		while(top) blk[sta[top--]] = blkcnt;

		//pretreatment of queries
		for(int i = 0;i < m;i++) 
		{
			int u,v;
			scanf("%d%d",&u,&v);
			if(clk[u] > clk[v]) swap(u,v);
			qs[i].l = u;
			qs[i].r = v;
			qs[i].id = i;
		}

		sort(qs,qs+m);

		//Mo cpt
		move(qs[0].l,qs[0].r);

		int lca = getLCA(qs[0].l,qs[0].r);
		work(a[lca]);
		ans[qs[0].id] = findAns();
		work(a[lca]);

		for(int i = 1;i < m;i++)
		{
			move(qs[i-1].l,qs[i].l);
			move(qs[i-1].r,qs[i].r);

			int lca = getLCA(qs[i].l,qs[i].r);
			work(a[lca]);
			ans[qs[i].id] = findAns();
			work(a[lca]);
		}

		for(int i = 0;i < m;i++) printf("%d\n",ans[i]);

	}

	return 0;
}
