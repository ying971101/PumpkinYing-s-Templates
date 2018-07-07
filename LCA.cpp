/*************************************************************************
    > File Name: LCA.cpp
    > Author: PumpkinYing
    > Created Time: 2018/6/19 20:30:07
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
int f[maxn][20];
int pre[maxn],dep[maxn];

vector<int> to[maxn];

void init()
{
	mem(f,-1);
	mem(pre,-1);
	for(int i = 0;i < maxn;i++) to[i].clear();
}

void addEdge(int u,int v)
{
	to[u].push_back(v);
	to[v].push_back(u);
}

void getF(int x,int d)
{
	dep[x] = d;
	if(pre[x] != -1) f[x][0] = pre[x];
	for(int i = 1;i <= 15;i++) 
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
	for(int i = 15;i >= 0;i--)
	{
		if(f[u][i] != -1 && dep[f[u][i]] >= dep[v]) u = f[u][i];
		if(dep[u] == dep[v]) break;
	}
	if(u == v) return u;
	for(int i = 15;i >= 0;i--)
	{
		if(f[u][i] != f[v][i]) u = f[u][i],v = f[v][i];
	}
	return f[u][0];
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		init();
		mem(de,0);
		int n;
		scanf("%d",&n);
		for(int i = 0;i < n-1;i++) 
		{
			int u,v;
			scanf("%d%d",&u,&v);
			addEdge(u,v);
			de[v]++;
		}
		int root;
		for(int i = 1;i <= n;i++) if(de[i] == 0) root = i;
		getF(root,0);
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%d\n",getLCA(u,v));
	}

    return 0;
}
