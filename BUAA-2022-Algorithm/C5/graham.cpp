/*
 * Graham-scan convex-hull experiment using polar-angle sorting and a stack.
 * The output loop attempts to list points starting at the origin.
 */

//#pragma comment(linker, "/STACK:1024000000,1024000000")
  
#include<stdio.h>
#include<string.h> 
#include<math.h> 
   
#include<map>  
//#include<set>
#include<deque> 
#include<queue> 
#include<stack> 
#include<bitset>
#include<string> 
#include<fstream>
#include<iostream> 
#include<algorithm> 
using namespace std; 
  
#define ll long long 
#define Pair pair<int,int>
//#define max(a,b) (a)>(b)?(a):(b)
//#define min(a,b) (a)<(b)?(a):(b)
#define clean(a,b) memset(a,b,sizeof(a))// 水印
//std::ios::sync_with_stdio(false);
//  register
const int MAXN=1e3+10;
const int INF32=0x3f3f3f3f;
const ll INF64=0x3f3f3f3f3f3f3f3f;
const ll mod=1e9+7;
const double EPS=1.0e-8;
const double PI=acos(-1.0);

struct Point{
	double x,y;
	Point(double _x=0,double _y=0){
		x=_x;y=_y;
	}
	friend Point operator + (const Point &a,const Point &b){
		return Point(a.x+b.x,a.y+b.y);
	}
	friend Point operator - (const Point &a,const Point &b){
		return Point(a.x-b.x,a.y-b.y);
	}
	friend double operator ^ (Point a,Point b){//向量叉乘 
		return a.x*b.y-a.y*b.x;
	}
};
struct V{
	Point start,end;double ang;
	V(Point _start=Point(0,0),Point _end=Point(0,0),double _ang=0.0){
		start=_start;end=_end;ang=_ang;
	}
	friend V operator + (const V &a,const V &b){
		return V(a.start+b.start,a.end+b.end);
	}
	friend V operator - (const V &a,const V &b){
		return V(a.start-b.start,a.end-b.end);
	}
};
struct Circle{
	double r;
	Point centre;
	Circle(Point _centre=Point(0,0),double _r=0){
		centre=_centre;r=_r;
	}
};
Point Dots[MAXN];
Point stk[MAXN];int top;
int n;

double Distance(Point a,Point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double Parellel(double key){
	return fabs(key)<EPS?0:key;
}
int Cmp(Point a,Point b){
	double res=Parellel((a-Dots[1])^(b-Dots[1]));
	if(res>0) return 1;
	if(res==0&&Distance(a,Dots[1])<Distance(b,Dots[1])) return 1;
	return 0;
}
void Graham(){
	sort(Dots+2,Dots+1+n,Cmp);
	top=2;stk[1]=Dots[1];stk[2]=Dots[2];
	for(int i=3;i<=n;++i){
		while(top>=2&&((stk[top]-stk[top-1])^(Dots[i]-stk[top-1]))<EPS) --top;
		stk[++top]=Dots[i];
	}stk[top+1]=stk[1];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%lf%lf",&Dots[i].x,&Dots[i].y);
	}int k=1;
	for(int i=2;i<=n;++i){
		if(Dots[i].y<Dots[k].y||(Dots[i].y==Dots[k].y&&Dots[i].x<Dots[k].x)){
			k=i;
		}
	}swap(Dots[1],Dots[k]);
	Graham();
	double ans=0;
	for(int i=1;i<=top;++i){
		if(stk[i].x==0&&stk[i].y==0){
			for(int j=i;j<=top;++j){
				printf("(%lf,%lf)\n",Dots[j].x,Dots[j].y);
			}
			for(int j=1;j<i;++j){
				printf("(%lf,%lf)\n",Dots[j].x,Dots[j].y);
			}break;
		}
	}
}

/*
10
0 0
70 -50
60 30
-30 -50
80 20
50 -60
90 -20
-30 -40
-10 -60
90 10


*/
