/*************************************************************************
  > File Name: 3D_geometry.cpp
  > Author: PumpkinYing
  > Created Time: 2018年08月10日 21:27:22
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

const double eps = 1e-10;

struct Point {
	ll x,y,z;
	Point(ll _x = 0,ll _y = 0,ll _z = 0) : x(_x),y(_y),z(_z) {}
	bool operator == (const Point& b) const {
		return x == b.x && y == b.y && z == b.z;
	}
};

typedef Point Vector;

Vector operator + (Vector a,Vector b) {
	return Vector(a.x+b.x,a.y+b.y,a.z+b.z);
}

Vector operator - (Point a,Point b) {
	return Vector(a.x-b.x,a.y-b.y,a.z-b.z);
}

ll operator * (Vector a,Vector b) {
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

Vector cross(Vector a,Vector b) {
	return Vector(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}

Vector operator * (double a,Vector b) {
	return Vector(a*b.x,a*b.y,a*b.z);
}

//平方之后的长度
ll vlen(Vector a) {
	return a*a;
}

struct Frac {
	ll p,q;
	Frac(ll _p = 0,ll _q = 1) : p(_p),q(_q) {}
	bool operator < (const Frac& b) const {
		return p*b.q < q*b.p;
	}
	void print() {
		ll s[35];
		for(int i = 0;i <= 32;i++) {
			s[i] = p/q;
			p %= q;
			p *= 10;
		}
		s[31] += 5;
		for(int i = 31;i > 0;i--) {
			if(s[i] > 9) {
				s[i] -= 10;
				s[i-1]++;
			}
			else break;
		}
		printf("%lld.",s[0]);
		for(int i = 1;i <= 30;i++) printf("%lld",s[i]);
		printf("\n");
	}
};


struct Segment {
	Point a,b;
	Segment(Point _a = Point(0,0,0),Point _b = Point(0,0,0)) : a(_a),b(_b) {}
};

typedef Segment Line;

ll pointDis(Point a,Point b) {
	Vector v = a-b;
	return vlen(v);
}

//距离均为平方之后
Frac pointLineDis(Point p,Line l) {
	return Frac(vlen(cross(p-l.a,l.b-l.a)),pointDis(l.a,l.b));
}


//不平行直线距离
Frac lineDis(Line a,Line b) {
	Vector n = cross(a.a-a.b,b.a-b.b);
	return Frac(((a.a-b.a)*n)*((a.a-b.a)*n),vlen(n));
}

//-1在a远离b方向 1在b远离a方向
int getDir(Point p,Segment l) {
	if((p-l.a)*(l.b-l.a) < 0) return -1;
	if((p-l.b)*(l.a-l.b) < 0) return 1;
	return 0;
}

Frac pointSegDis(Point p,Segment l) {
	if(l.a == l.b) return Frac(pointDis(p,l.a),1);
	if(getDir(p,l) == -1) return Frac(pointDis(p,l.a),1);
	if(getDir(p,l) == 1) return Frac(pointDis(p,l.b),1);
	return pointLineDis(p,l);
}

Frac segDis(Segment a,Segment b) {
	Frac ans(1e9,1);
	Vector n = cross(a.a-a.b,b.a-b.b);
	Vector p1 = cross(a.b-a.a,n);
	Vector p2 = cross(b.b-b.a,n);

	//判断是否平移之后交叉
	if(((b.a-a.a)*p1)*((b.b-a.a)*p1) < 0 && ((a.a-b.a)*p2)*((a.b-b.a)*p2) < 0) {
		if(vlen(n) != 0) ans = lineDis(a,b);
		else ans = Frac(0,1);
	}

	ans = min(ans,pointSegDis(a.a,b));
	ans = min(ans,pointSegDis(a.b,b));
	ans = min(ans,pointSegDis(b.a,a));
	ans = min(ans,pointSegDis(b.b,a));
	return ans;
}
