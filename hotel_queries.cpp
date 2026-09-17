#include <bits/stdc++.h>
#define ll long long
#define v vector
#define f(arr, n) for(ll i = 0; i < n; i++) cin >> arr[i];
using namespace std;
const ll INF=100000007;

struct Node
{
  ll mx;  
};

Node merge(Node a ,Node b)
{
    return {max(a.mx,b.mx)};
}

Node st[800001];

void build(ll p,ll l,ll r,v<ll>&a)
{
    if(l==r)
    {
        st[p].mx=a[l];
        return;
    }
    ll m=(l+r)/2;
    build(2*p,l,m,a);
    build(2*p+1,m+1,r,a);
    st[p]=merge(st[2*p],st[2*p+1]);
}

void update(ll p,ll l,ll r,ll x)
{
    if(l==r)
    {
        st[p].mx=x;
        return;
    }
    ll m=(l+r)/2;
    update(2*p,l,m,x);
    update(2*p+1,m+1,r,x);
    st[p]= merge(st[2*p],st[2*p+1]);
}

Node query(ll p,ll l,ll r ,ll ql,ll qr)
{
    if(qr<l||ql>r)
    {
        return {-INF};
    }
    if(ql<=l &&qr>=r)
    {
        return st[p];
    }
    ll m=(l+r)/2;
    return(merge(query(2*p,l,m,ql,qr),
    query(2*p+1,m+1,r,ql,qr)));
    
}

ll find(ll p,ll l,ll r,ll val)
{
    if(st[p].mx < val)
        return -1;

    if(l == r)
    {
        st[p].mx -= val;
        return l;
    }

    ll m=(l+r)/2;

    ll idx;

    if(st[2*p].mx >= val)
        idx=find(2*p,l,m,val);
    else
        idx=find(2*p+1,m+1,r,val);

    st[p]=merge(st[2*p],st[2*p+1]);

    return idx;
}

int main()
{
    ll n,m;
    cin>>n>>m;

    v<ll>a(n);
    v<ll>b(m);

    f(a,n);
    f(b,m);

    build(1,0,n-1,a);

    v<ll>ans;

    for(ll i=0;i<m;i++)
    {
  ll idx=find(1,0,n-1,b[i]);
        if(idx==-1)
            cout<<0<<" ";
        else
            cout<<idx+1<<" ";
    }

   
}