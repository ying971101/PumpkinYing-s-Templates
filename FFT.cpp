/*************************************************************************
    > File Name: FFT.cpp
    > Author: PumpkinYing
    > Created Time: 2018/6/17 19:40:34
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

const double PI = acos(-1.0);

struct Complex 
{
    double x,y;
    Complex(double _x = 0.0,double _y = 0.0) : x(_x),y(_y) {}
    Complex operator - (const Complex& b) const
    {
        return Complex(x-b.x,y-b.y);
    }
    Complex operator + (const Complex& b) const 
    {
        return Complex(x+b.x,y+b.y);
    }
    Complex operator * (const Complex& b) const 
    {
        return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
    }
};

void init(Complex* y,int n)
{
    int i,j,k;
    for(i = 1,j = n/2;i < n-1;i++)
    {
        if(i < j) swap(y[i],y[j]);
        k = n/2;
        while(j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}

void FFT(Complex* y,int n,int on)
{
    init(y,n);
    for(int h = 2;h <= n;h <<= 1)
    {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0;j < n;j += h)
        {
            Complex w(1,0);
            for(int k = j;k < j+h/2;k++)
            {
                Complex u = y[k];
                Complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    
    if(on == -1)
    {
        for(int i = 0;i < n;i++)
            y[i].x /= n;
    }
}

const int maxn = 50010;

int num[maxn<<2];
Complex x1[maxn<<2],x2[maxn<<2];
char s1[maxn],s2[maxn];

int main()
{
    while(~scanf("%s%s",s1,s2))
    {

        mem(num,0);

        int l1 = strlen(s1),l2 = strlen(s2);
        int len = 1;

        while(len < (l1<<1) || len < (l2<<1)) len <<= 1;

        int i;
        for(i = 0;i < l1;i++) x1[i] = Complex(s1[l1-i-1]-'0',0);
        for( ;i < len;i++) x1[i] = Complex(0,0);
        FFT(x1,len,1);

        for(i = 0;i < l2;i++) x2[i] = Complex(s2[l2-i-1]-'0',0);
        for( ;i < len;i++) x2[i] = Complex(0,0);
        FFT(x2,len,1);

        for(int i = 0;i < len;i++) x1[i] = x1[i]*x2[i];
        FFT(x1,len,-1);
        for(int i = 0;i < len;i++) num[i] = (int)(x1[i].x+0.5);

        for(int i = 0;i < len;i++) 
        {
            num[i+1] += num[i]/10;
            num[i] %= 10;
        }

        while(num[len] == 0 && len > 0) len--;

        for(i = len;i >= 0;i--) printf("%d",num[i]);
        printf("\n");

    }
    return 0;
}
