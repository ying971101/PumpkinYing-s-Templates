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

struct Edge {
	int to;
	int val;
	Edge(int t,int v) : to(t), val(v) {}
};

const int maxn = 10010;
vector<Edge> G[maxn];

void addEdge(int u,int v,int w) {
	G[u].push_back(Edge(v,w));
	G[v].push_back(Edge(u,w));
}

int vis[maxn];

int n,k;
int ans = 0;
vector<int> dep;

void getDep(int x,int pre,int d) {
	int sz = G[x].size();
	for(int i = 0;i < sz;i++) {
		Edge e = G[x][i];
		if(vis[e.to] || e.to == pre) continue;
		dep.push_back(d+e.val);
		getDep(e.to,x,d+e.val);
	}
}

int getNum(int x,int inid) {
	dep.clear();
	getDep(x,0,inid);

	dep.push_back(inid);
	sort(dep.begin(),dep.end());
	int len = dep.size();

	int ret = 0;
	int l = 0,r = len-1;

	for(;r >= 0;r--) {
		while(l < len && dep[l]+dep[r] <= k) l++;
		ret += min(l,r);
	}
	
	//printf("%d Ret: %d\n",x,ret);
	return ret;
}

int size[maxn],mx[maxn];
void getCenter(int x,int pre,int tot,int& center) {
	size[x] = 1;
	mx[x] = 0;
	int sz = G[x].size();
	for(int i = 0;i < sz;i++) {
		Edge e = G[x][i];
		if(e.to == pre || vis[e.to]) continue;
		getCenter(e.to,x,tot,center);
		mx[x] = max(mx[x],size[e.to]);
		size[x] += size[e.to];
	}
	mx[x] = max(mx[x],tot-size[x]);
	if(mx[x] < mx[center]) center = x;
}

void getSize(int x,int pre) {
	size[x] = 1;
	int sz = G[x].size();
	for(int i = 0;i < sz;i++) {
		Edge e = G[x][i];
		if(e.to == pre) continue;
		getSize(e.to,x);
		size[x] += size[e.to];
	}
}

void work(int x,int pre) {
	vis[x] = 1;
	int sz = G[x].size();
	ans += getNum(x,0);
	for(int i = 0;i < sz;i++) {
		Edge e = G[x][i];
		if(vis[e.to] || e.to == pre) continue;
		ans -= getNum(e.to,e.val);
		int center = 0;
		mx[center] = 1e9;
		getCenter(e.to,x,size[x],center);
		work(center,0);
	}
}

void init() {
	ans = 0;
	mem(vis,0);
	for(int i = 0;i < maxn;i++) G[i].clear();
}


int main() {
	while(~scanf("%d%d",&n,&k) && n) {
		init();

		for(int i = 0;i < n-1;i++) {
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			addEdge(u,v,w);
		}

		getSize(1,0);
		work(1,0);

		printf("%d\n",ans);
	}

	return 0;
}
