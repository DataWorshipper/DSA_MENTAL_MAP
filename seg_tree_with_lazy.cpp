#include <bits/stdc++.h>
#define v vector
#define ll long long
using namespace std;

struct Node
{
    ll val;
};

Node merge(Node a,Node b)
{
    return {a.val+b.val};
}
Node st[400001];
Node lazy[400001];

void apply(ll p,ll l,ll r,ll x)
{
    st[p].val += (r-l+1)*x;
    lazy[p].val += x;
}

void push(ll p,ll l,ll r)
{
    if(!lazy[p].val) return;

    ll m=(l+r)/2;

    apply(2*p,l,m,lazy[p].val);
    apply(2*p+1,m+1,r,lazy[p].val);

    lazy[p].val=0;
}
void build(ll p,ll l,ll r,v<ll>&a)
{
    if(l==r)
        
    {st[p]={a[l]};
     return;
    }
    ll m=(l+r)/2;
    build(2*p,l,m,a);
    build(2*p+1,m+1,r,a);
    st[p]=merge(st[2*p],st[2*p+1]);
}
void update(ll p,ll l,ll r,ll ql,ll qr,v<ll>&a,ll x)
{
    if(qr<l || r<ql)
        return;

    if(ql<=l && qr>=r)
    {
        apply(p,l,r,x);
        return;
    }

    ll m=(l+r)/2;

    push(p,l,r);

    update(2*p,l,m,ql,qr,a,x);
    update(2*p+1,m+1,r,ql,qr,a,x);

    st[p]=merge(st[2*p],st[2*p+1]);
}

Node query(ll p,ll l,ll r,ll ql,ll qr,v<ll>&a)
{
    if(qr<l || r<ql)
        return {0};

    if(ql<=l && r<=qr)
        return st[p];

    push(p,l,r);

    ll m=(l+r)/2;

    return merge(
        query(2*p,l,m,ql,qr,a),
        query(2*p+1,m+1,r,ql,qr,a)
    );
}

    
    int main() {
    v<ll> a = {1,2,3,4,5,6,7,8};
    ll n = a.size();

    build(1, 0, n-1, a);

    cout << query(1,0,n-1,2,5,a).val << '\n';

    update(1,0,n-1,2,5,a,10);

    cout << query(1,0,n-1,2,5,a).val << '\n';
    cout << query(1,0,n-1,0,7,a).val << '\n';

    return 0;
}