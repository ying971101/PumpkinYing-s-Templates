/*************************************************************************
    > File Name: geometry.cpp
    > Author: PumpkinYing
    > Created Time: 2018/4/28 14:22:33
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

//two dimention
struct Point {
	double x,y;
	Point(double x = 0,double y = 0) : x(x),y(y) {}
};

typedef Point Vector;

Vector operator + (Vector a,Vector b) {
	return Vector(a.x+b.x,a.y+b.y);
}

Vector operator - (Point a,Point b) {
	return Vector(a.x-b.x,a.y-b.y);
}

Vector operator * (Vector a,double k) {
	return Vector(a.x*k,a.y*k);
}

Vector operator / (Vector a,double k) {
	return Vector(a.x/k,a.y/k);
}

const double eps = 1e-7;
int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	else return x < 0 ? -1 : 1;
}

double dot(Vector a,Vector b) {
	return a.x*b.x+a.y*b.y;
}

double length(Vector a) {
	return sqrt(dot(a,a));
}

double angle(Vector a,Vector b) {
	return acos(dot(a,b)/length(a)/length(b));
}

double cross(Vector a,Vector b) {
	return a.x*b.y-a.y*b.x;
}

Vector rotate(Vector a,double rad) {
	return Vector(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));
}

struct Line {
	Point a,b;
	Line(Point a = Point(0,0),Point b = Point(0,0)) : a(a),b(b) {}
};

//a,b intersect guaranteed
//also work for segments
Point getIntersection(Line a,Line b) {
	Point P = a.a;
	Point Q = b.a;
	Vector v = a.b-a.a;
	Vector w = b.b-b.a;
	Vector u = P-Q;
	double t = cross(w,u)/cross(v,w);
	return P+v*t;
}

double distance(Point p,Line l) {
	Vector v1 = l.b-l.a;
	Vector v2 = p-l.a;
	return fabs(cross(v1,v2))/length(v1);
}

typedef Line Seg;

bool onSeg(Point a,Seg s) {
	return dcmp(cross(s.a-a,s.b-a)) == 0 && dcmp(dot(s.a-a,s.b-a)) < 0;
}

bool lineIntersect(Line a,Line b) {
	Vector v1 = a.b-a.a;
	Vector v2 = b.b-b.a;
	return dcmp(cross(v1,v2)) != 0;
}

bool segIntersect(Seg a,Seg b) {
	if(onSeg(a.a,b) || onSeg(a.b,b) || onSeg(b.a,a) || onSeg(b.b,a)) return true;
	int d1,d2;
	d1 = dcmp(cross(a.a-b.a,b.b-b.a))*dcmp(cross(a.b-b.a,b.b-b.a));
	d2 = dcmp(cross(b.a-a.a,a.b-a.a))*dcmp(cross(b.b-a.a,a.b-a.a));
	if(d1 == -1 && d2 == -1) return true;
	return false;
}

bool cmp(Line a,Line b) {
	Vector v1 = a.b-a.a;
	Vector v2 = b.b-b.a;
	double ang1 = atan2(v1.y,v1.x);
	double ang2 = atan2(v2.y,v2.x);
	return ang1 < ang2;
}

const int maxn = 100010;
Line lines[maxn];
Point p[maxn];
Point poly[maxn];
Line q[maxn];

bool onLeft(Point a,Line l) {
	return cross(l.b-l.a,a-l.a) > 0;
}

int halfPlaneIntersection(int n) {
	sort(lines,lines+n,cmp);

	int l,r;
	l = r = 0;
	q[0] = lines[0];

	for(int i = 1;i < n;i++) {
		Line cur = lines[i];
		while(l < r && dcmp(cross(cur.b-cur.a,p[r-1]-cur.a)) <= 0) r--;
		while(l < r && dcmp(cross(cur.b-cur.a,p[l]-cur.a)) <= 0) l++;
		q[++r] = cur;
		if(dcmp(cross(q[r].b-q[r].a,q[r-1].b-q[r-1].a)) == 0) {
			r--;
			if(dcmp(cross(q[r].b-q[r].a,cur.a-q[r].a)) == 1) q[r] = cur;
		}
		if(l < r) p[r-1] = getIntersection(q[r-1],q[r]);
	}

	while(l < r && dcmp(cross(q[l].b-q[l].a,p[r-1]-q[l].a)) <= 0) r--;
	if(!(l < r)) return -1;

	p[r] = getIntersection(q[r],q[l]);
	for(int i = l;i <= r;i++) poly[i-l] = p[i];
	return r-l+1;
}

int main() {
	
    return 0;
}
