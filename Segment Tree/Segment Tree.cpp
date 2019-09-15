#include<bits/stdc++.h>
using namespace std;
long long n;
long long x,y,w;
long long ans;
struct tree{
	long long l,r;
	long long k;
	long long f;
}t[4*100001];
inline void down(int u)
{
	t[2*u].f+=t[u].f;
	t[2*u+1].f+=t[u].f;
	t[u*2].k+=(t[u*2].r-t[u*2].l+1)*t[u].f;
	t[u*2+1].k+=(t[u*2+1].r-t[u*2+1].l+1)*t[u].f;
	t[u].f=0;
}
inline void init(int u,int l,int r)
{
	t[u].l=l,t[u].r=r;
	if(t[u].l==t[u].r){
		cin>>t[u].k;
		return ;
	}
	long long m=(l+r)/2;
	init(2*u,l,m);
	init(2*u+1,m+1,r);
	t[u].k=t[2*u].k+t[2*u+1].k;
}
/*inline void only_add(int u)
{
	if(t[u].l==t[u].r){
		t[u].k+=w;
		return ;
	}
	if(t[u].f) down(u);
	int m=(t[u].l+t[u].r)/2;
	if(x<=m) only_add(2*u);
	else only_add(2*u+1);
	t[u].k=t[2*u+1].k+t[2*u].k;
}
inline void only_q(int u)
{
	if(t[u].l==t[u].r){
		ans+=t[u].k;
		return ;
	}
	if(t[u].f) down(u);
	int m=(t[u].l+t[u].r)/2;
	if(x<=m) only_q(2*u);
	else only_q(2*u+1);
}*/
inline void q(int u)
{
	if(t[u].l>=x&&t[u].r<=y){
		ans+=t[u].k;
		return ;
	}
	if(t[u].f) down(u);
	long long m=(t[u].l+t[u].r)/2;
	if(x<=m) q(2*u);
	if(y>m) q(2*u+1);
}
inline void add(int u)
{
	if(t[u].l>=x&&t[u].r<=y){
		t[u].k+=(t[u].r-t[u].l+1)*w;
		t[u].f+=w;
		return ;
	}
	if(t[u].f) down(u);
	long long m=(t[u].l+t[u].r)/2;
	if(x<=m) add(2*u);
	if(y>m) add(2*u+1);
	t[u].k=t[2*u+1].k+t[2*u].k;
}
int main()
{
	int m;
	cin>>n>>m;
	init(1,1,n);
	int i,a;
	cout<<"几个操作:";
	cin>>m;
	for(i=1;i<=m;i++){
		cout<<"1.单点修改\t2.单点查询\t3.区间修改\t4.区间查询\n";
		cin>>a;
		if(a==1){
			cout<<"单点修改\n";
			cout<<"第几个点:";
			cin>>x;
			cout<<"添加的值:";
			cin>>w;
			only_add(1);
			cout<<"添加完毕\n";
		}
		if(a==2){
			ans=0;
			cout<<"单点查询\n";
			cout<<"第几个点:";
			cin>>x;
			only_q(1);
			printf("第%d个点是%d\n",x,ans);
		}
		if(a==3){
			cout<<"区间修改\n";
			cout<<"左端点:";
			cin>>x;
			cout<<"右端点:";
			cin>>y;
			cout<<"单个节点添加的值:";
			cin>>w;
			add(1);
			printf("添加完毕\n");
		}
		if(a==4){
			ans=0;
			cout<<"区间查询\n";
			cout<<"左端点:";
			cin>>x;
			cout<<"右端点:";
			cin>>y;
			q(1);
			printf("从%d到%d的和是%d\n",x,y,ans);
			cout<<ans<<endl;
		}
	}
	return 0;
}
