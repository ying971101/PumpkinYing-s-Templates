const int maxn = 10010;
const double eps = 1e-8;

struct Point {
	double x,y,z;
	void read() {
		scanf("%lf%lf%lf",&x,&y,&z);
	}
	Point(double _x = 0,double _y = 0,double _z = 0) : x(_x),y(_y),z(_z) {}
	Point operator - (const Point& b) const {
		return Point(x-b.x,y-b.y,z-b.z);
	}
	double len() {
		return x*x+y*y+z*z;
	}
	void print() {
		cerr<<x<<' '<<y<<' '<<z<<endl;
	}
}ps[maxn];

Point cross(Point a,Point b) {
	return Point(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}

double dis(Point a,Point b) {
	return (a-b).len();
}

Point Gauss(double a[][5],int n) {
	int m = 4;
    for (int i = 1;i <= n;i++) {
        int l = i;
        for (int j = i+1;j <= n;j++)
			if (abs(a[j][i]) > abs(a[l][i])) l = j;
        if (l != i) {
            for (int j = 1;j <= m;j++) swap(a[l][j],a[i][j]);
		}
        double t = a[i][i]; 
        for (int j = 1;j <= m;j++)
            a[i][j] /= t;
        for (int j = 1;j <= n;j++)
            if (j != i && a[j][i] != 0) {
                double t = a[j][i];
                for (int k = 1;k <= m;k++)
                    a[j][k] -= t*a[i][k];
            }
    }

	return Point(a[1][4],a[2][4],a[3][4]);
}

Point getMid_2(Point a,Point b) {
	return Point((a.x+b.x)/2,(a.y+b.y)/2,(a.z+b.z)/2);
}

Point getVertic(Point a,Point b,Point c) {
	return cross(a-b,a-c);
}

double sqr(double x) {
	return x*x;
}

int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}

Point getMid_3(Point a,Point b,Point c) {
	Point n = getVertic(a,b,c);
	double para[5][5];
	para[1][1] = 2*(a.x-b.x);
	para[1][2] = 2*(a.y-b.y);
	para[1][3] = 2*(a.z-b.z);
	para[1][4] = sqr(a.x)+sqr(a.y)+sqr(a.z)-sqr(b.x)-sqr(b.y)-sqr(b.z);

	para[2][1] = 2*(a.x-c.x);
	para[2][2] = 2*(a.y-c.y);
	para[2][3] = 2*(a.z-c.z);
	para[2][4] = sqr(a.x)+sqr(a.y)+sqr(a.z)-sqr(c.x)-sqr(c.y)-sqr(c.z);

	para[3][1] = n.x;
	para[3][2] = n.y;
	para[3][3] = n.z;
	para[3][4] = n.x*a.x+n.y*a.y+n.z*a.z;

	Point ret = Gauss(para,3);
	return ret;
}

Point getMid_4(Point a,Point b,Point c,Point d) {
	double para[5][5];
	para[1][1] = 2*(a.x-b.x);
	para[1][2] = 2*(a.y-b.y);
	para[1][3] = 2*(a.z-b.z);
	para[1][4] = sqr(a.x)+sqr(a.y)+sqr(a.z)-sqr(b.x)-sqr(b.y)-sqr(b.z);

	para[2][1] = 2*(a.x-c.x);
	para[2][2] = 2*(a.y-c.y);
	para[2][3] = 2*(a.z-c.z);
	para[2][4] = sqr(a.x)+sqr(a.y)+sqr(a.z)-sqr(c.x)-sqr(c.y)-sqr(c.z);

	para[3][1] = 2*(a.x-d.x);
	para[3][2] = 2*(a.y-d.y);
	para[3][3] = 2*(a.z-d.z);
	para[3][4] = sqr(a.x)+sqr(a.y)+sqr(a.z)-sqr(d.x)-sqr(d.y)-sqr(d.z);

	Point ret = Gauss(para,3);
	return ret;
}

void shuffle(int n) {
	for(int i = 0;i < n;i++) {
		swap(ps[i],ps[rand()%n]);
	}
}

double solve(int n) {
	shuffle(n);
	Point O = ps[0];
	double r = 0;
	for(int i = 0;i < n;i++) {
		if(dcmp(dis(O,ps[i])-r) <= 0) continue;
		O = ps[i];
		r = 0;

		for(int j = 0;j < i;j++) {
			if(dcmp(dis(O,ps[j])-r) <= 0) continue;
			O = getMid_2(ps[i],ps[j]);
			r = dis(O,ps[j]);

			for(int k = 0;k < j;k++) {
				if(dcmp(dis(O,ps[k])-r) <= 0) continue;
				O = getMid_3(ps[i],ps[j],ps[k]);
				r = dis(O,ps[k]);

				for(int l = 0;l < k;l++) {
					if(dcmp(dis(O,ps[l])-r) <= 0) continue;
					O = getMid_4(ps[i],ps[j],ps[k],ps[l]);
					r = dis(O,ps[l]);
				}
			}
		}

	}
	return r;
}

int main() {

	srand(1019);

	int n;
	while(~scanf("%d",&n) && n) {
		for(int i = 0;i < n;i++) ps[i].read();
		double ans = solve(n);
		printf("%.3f\n",sqrt(ans));
	}
	return 0;
}
