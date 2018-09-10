/*************************************************************************
    > File Name: 3D_ConvexHull.cpp
    > Author: PumpkinYing
    > Created Time: 2018/8/14 20:03:49
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
#define PII pair<int,int>
typedef long long ll;

const int maxn = 310;
const double eps = 1e-7;

int vis[maxn][maxn];

struct Point
{
	double x,y,z;
	Point (double _x = 0,double _y = 0,double _z = 0) : x(_x), y(_y), z(_z) {}
	bool operator == (const Point& b) const 
	{
		return fabs(x-b.x) < eps && fabs(y-b.y) < eps && fabs(z-b.z) < eps;
	}
}ps[maxn];

typedef Point Vector;

Vector operator + (Vector a, Vector b) 
{
	return Vector(a.x+b.x,a.y+b.y,a.z+b.z);
}

Vector operator - (Point a,Point b)
{
	return Vector(a.x-b.x,a.y-b.y,a.z-b.z);
}

double operator * (Vector a,Vector b)
{
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

Vector cross(Vector a,Vector b)
{
	return Vector(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}

double vlen(Vector a)
{
	return a*a;
}

struct Plane
{
	int v[3];
	Plane(int a = 0,int b = 0,int c = 0)
	{
		v[0] = a;
		v[1] = b;
		v[2] = c;
	}
	Vector normal(Point* p) 
	{
		return cross(p[v[1]]-p[v[0]],p[v[2]]-p[v[0]]);
	}
	int cansee(Point* p,int i) 
	{
		return (p[i]-p[v[0]])*normal(p) > 0 ? 1 : 0;
	}
};

vector<Plane> convexHull_3D(Point* p,int n)
{
	vector<Plane> cur;
	cur.push_back(Plane(0,1,2));
	cur.push_back(Plane(2,1,0));

	for(int i = 3;i < n;i++) 
	{
		vector<Plane> nxt;
		for(int j = 0;j < cur.size();j++)
		{
			Plane& f = cur[j];
			int res = f.cansee(p,i);
			if(!res) nxt.push_back(f);
			for(int k = 0;k < 3;k++) vis[f.v[k]][f.v[(k+1)%3]] = res;
		}
		for(int j = 0;j < cur.size();j++)
		{
			for(int k = 0;k < 3;k++) 
			{
				int a = cur[j].v[k], b = cur[j].v[(k+1)%3];
				if(vis[a][b] != vis[b][a] && vis[a][b]) 
					nxt.push_back(Plane(a,b,i));
			}
		}
		cur = nxt;
	}
	return cur;
}

double rand01() {return rand()/(double)RAND_MAX;}
double randeps() {return (rand01() - 0.5)*eps;}

Point add_noise(Point p)
{
	return Point(p.x+randeps(),p.y+randeps(),p.z+randeps());
}

Point noise_p[maxn];
int mk[maxn];

double volume(Point a,Point b,Point c,Point d)
{
	return cross(b-a,c-a)*(d-a);
}

bool same(Plane a,Plane b,Point* p)
{
	return fabs(volume(p[a.v[0]],p[a.v[1]],p[a.v[2]],p[b.v[0]])) < eps && 
		fabs(volume(p[a.v[0]],p[a.v[1]],p[a.v[2]],p[b.v[1]])) < eps && 
		fabs(volume(p[a.v[0]],p[a.v[1]],p[a.v[2]],p[b.v[2]])) < eps;
}

int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		mem(vis,0);
		mem(mk,0);

		for(int i = 0;i < n;i++) 
		{
			scanf("%lf%lf%lf",&ps[i].x,&ps[i].y,&ps[i].z);
			noise_p[i] = add_noise(ps[i]);
		}

		for(int i = 0;i < n;i++)
		{
			for(int j = i+1;j < n;)
			{
				if(ps[i] == ps[j]) 
				{
					swap(ps[j],ps[n-1]);
					swap(noise_p[j],noise_p[n-1]);
					n--;
				}
				else j++;
			}
		}

		vector<Plane> ans = convexHull_3D(noise_p,n);
		int sz = ans.size();
		for(int i = 0;i < sz;i++) 
		{
			if(!mk[i])
			{
				for(int j = i+1;j < sz;j++) 
				{
					if(same(ans[i],ans[j],ps)) mk[j] = 1;
				}
			}
		}

		int cnt = 0;
		for(int i = 0;i < sz;i++) if(!mk[i]) cnt++;
		printf("%d\n",cnt);
	}
    return 0;
}
