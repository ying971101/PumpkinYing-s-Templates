#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <cmath>
using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
typedef long long ll;

const int maxn = 100010;
int a[maxn],b[maxn];
int cnt[maxn],ans[maxn];
int t;

vector<int> to[maxn];
void addEdge(int u,int v)
{
	to[u].push_back(v);
	to[v].push_back(u);
}

struct query
{
	int l,r;
	int id;
	int lca;
	bool operator < (const query& b) const
	{
		if(l/t == b.l/t) return r < b.r;
		return l/t < b.l/t;
	}
}qs[maxn];

int in[maxn],out[maxn];
int order[maxn*2];

int tim;
void dfs(int x,int pre)
{
	in[x] = tim;
	order[tim++] = x;
	int sz = to[x].size();
	for(int i = 0;i < sz;i++) 
	{
		int v = to[x][i];
		if(v == pre) continue;
		dfs(v,x);
	}
	out[x] = tim;
	order[tim++] = x;
}

//LCA calculation
int f[maxn][40];
int pre[maxn],dep[maxn];

void getF(int x,int d)
{
	dep[x] = d;
	if(pre[x] != -1) f[x][0] = pre[x];
	for(int i = 1;i <= 22;i++) 
		if(f[x][i-1] != -1) f[x][i] = f[f[x][i-1]][i-1];
	int sz = to[x].size();
	for(int i = 0;i < sz;i++)
	{
		if(to[x][i] == pre[x]) continue;
		pre[to[x][i]] = x;
		getF(to[x][i],d+1);
	}
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
	
//change exsistance of every point on the tree
int vis[maxn];
int num = 0;
void work(int x)
{
	if(vis[x])
	{
		cnt[a[x]]--;
		if(cnt[a[x]] == 0) num--;
		vis[x] = 0;
	}
	else 
	{
		if(cnt[a[x]] == 0) num++;
		cnt[a[x]]++;
		vis[x] = 1;
	}
}

void init(int n)
{
	for(int i = 1;i <= n;i++) to[i].clear();
	mem(vis,0);
	mem(f,-1);
	mem(pre,-1);
	t = sqrt(n)+1;
	tim = 1;
	num = 0;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);

	for(int i = 1;i <= n;i++) 
	{
		scanf("%d",&a[i]);
		b[i] = a[i];
	}

	init(n);

	sort(b+1,b+n+1);
	for(int i = 1;i <= n;i++) a[i] = lower_bound(b+1,b+1+n,a[i])-(b+1);

	for(int i = 0;i < n-1;i++) 
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addEdge(u,v);
	}

	dfs(1,0); //get dfs order
	getF(1,0); // for LCA calculation

	//get query rigions 
	for(int i = 0;i < m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		qs[i].id = i;
		qs[i].lca = getLCA(u,v);
		if(qs[i].lca == u || qs[i].lca == v) 
		{
			qs[i].lca = -1;
			if(in[u] < in[v]) qs[i].l = in[u],qs[i].r = in[v];
			else qs[i].l = in[v],qs[i].r = in[u];
		}
		else 
		{
			if(in[u] < in[v]) qs[i].l = out[u],qs[i].r = in[v];
			else qs[i].l = out[v],qs[i].r = in[u];
		}
	}

	sort(qs,qs+m);

	int curl = 0,curr = -1;

	for(int i = 0;i < m;i++)
	{
		int l = qs[i].l,r = qs[i].r;
		while(curl < l) work(order[curl++]); 
		while(curl > l) work(order[--curl]);
		while(curr < r) work(order[++curr]); 
		while(curr > r) work(order[curr--]);

		if(qs[i].lca != -1) work(qs[i].lca);
		ans[qs[i].id] = num;
		if(qs[i].lca != -1) work(qs[i].lca);
	}

	for(int i = 0;i < m;i++) printf("%d\n",ans[i]);

	return 0;
}

