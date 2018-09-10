/*************************************************************************
    > File Name: Ê÷Á´ÆÊ·Ö.cpp
    > Author: PumpkinYing
    > Created Time: 2018/5/8 22:22:07
 ************************************************************************/

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

const int maxn = 10010;
int fa[maxn],son[maxn],top[maxn],siz[maxn],dep[maxn],id[maxn],pre[maxn];
int tot = 1;
vector<int> to[maxn];

void init() {
	for(int i = 0;i < n;i++) to[i].clear();
	tot = 1;
	mem(son,0);
}

void addEdge(int u,int v) {
	to[u].push_back(v);
}

int dfs1(int x,int p,int d) {
	pre[x] = p;
	dep[x] = d;
	int sz = to[x].size();
	int hv = 0,mx = 0;
	siz[x] = 1;
	for(int i = 0;i < sz;i++) {
		int t = dfs1(to[x][i],x,d+1);
		if(t > mx) mx = t,hv = to[x][i];
		siz[x] += t;
	}
	son[x] = hv;
	return siz[x];
}

void dfs2(int x,int p) {
	id[x] = tot++;
	if(son[x]) {
		top[son[x]] = top[x];
		dfs2(son[x],x);
	}
	int sz = to[x].size();
	for(int i = 0;i < sz;i++) {
		int v = to[x][i];
		if(v == son[x]) continue;
		top[v] = v;
		dfs2(v,x);
	}
}

int solve(int u,int v,int vl) {
	int ret = 0;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u,v);
		ret = max(ret,query(id[u],id[top[u]],vl));
		u = pre[top[u]];
	}
	if(dep[u] < dep[v]) swap(u,v);
	ret = max(ret,query(id[u],id[v],vl));
	return ret;
}
