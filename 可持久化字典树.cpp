/*************************************************************************
    > File Name: 1295.cpp
    > Author: PumpkinYing
    > Created Time: 2018/5/10 6:49:33
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

const int maxn = 50010;
int nxt[maxn*30][2],num[maxn*30];
int root[maxn];
int cnt = 0;

int newNode()
{
	nxt[cnt][0] = nxt[cnt][1] = -1;
	num[cnt] = 0;
	return cnt++;
}

void Insert(int pos,int val)
{
	int pcur = root[pos] = newNode();
	int ppre = root[pos-1];
	for(int i = 30;i >= 0;i--)
	{
		int cur = (val>>i);
		val -= (cur<<i);
		nxt[pcur][cur] = newNode();
		if(ppre != -1)
		{
			nxt[pcur][1-cur] = nxt[ppre][1-cur];
			ppre = nxt[ppre][cur];
		}
		pcur = nxt[pcur][cur];
		if(ppre != -1) num[pcur] = num[ppre]+1;
		else num[pcur] = 1;
	}
}

int query(int l,int r,int val)
{
	int ret = 0;
	int pl = root[l-1];
	int pr = root[r];
	for(int i = 30;i >= 0;i--)
	{
		int cur = (val>>i);
		val -= (cur<<i);
		int lnum;
		if(pl == -1 || nxt[pl][1-cur] == -1) lnum = 0;
		else lnum = num[nxt[pl][1-cur]];
		if(nxt[pr][1-cur] != -1 && num[nxt[pr][1-cur]]-lnum > 0) 
		{
			ret += (1<<i);
			pr = nxt[pr][1-cur];
			if(pl != -1) pl = nxt[pl][1-cur];
		}
		else 
		{
			pr = nxt[pr][cur];
			if(pl != -1) pl = nxt[pl][cur];
		}
	}
	return ret;
}

int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	root[0] = -1;
	for(int i = 1;i <= n;i++)
	{
		int x;
		scanf("%d",&x);
		Insert(i,x);
	}
	while(q--)
	{
		int l,r,x;
		scanf("%d%d%d",&x,&l,&r);
		printf("%d\n",query(l+1,r+1,x));
	}
    return 0;
}
