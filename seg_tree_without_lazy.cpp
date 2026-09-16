#include <bits/stdc++.h>
using namespace std;
#define v vector
#define ll long long
//Node definition
struct Node
{
    ll val;    
};
//Merging of Nodes
Node merge(Node a,Node b)
{
    return {a.val+b.val};
}

Node st[400001];
// Build the seg tree
void build(ll p,ll l,ll r,v<ll>&a)
{
    if(l==r)
    {st[p]={a[l]};
     return;}
    ll m=(l+r)/2;
    build(2*p,l,m,a);
    build(2*p+1,m+1,r,a);
    st[p]=merge(st[2*p],st[2*p+1]);
    
}
// Point Update
void update(ll p,ll l,ll r,ll idx,ll x,v<ll>&a)
{
    if(l==r)
    {
        st[p]={x};
        return;
    }
    ll m=(l+r)/2;
    if(idx<=m)
    {
        update(2*p,l,m,idx,x,a);
    }
    else
        update(2*p+1,m+1,r,idx,x,a);
    st[p]=merge(st[2*p],st[2*p+1]);
}
// Range Query
Node query(ll p,ll l,ll r,ll ql,ll qr,v<ll>&a)
{
    if(qr<l ||ql>r)
        return {0};

    if(ql<=l && qr>=r)
        return st[p];

    ll m=(l+r)/2;
    return merge(query(2*p,l,m,ql,qr,a),query(2*p+1,m+1,r,ql,qr,a));
}
int main() {
    v<ll> a = {1, 2, 3, 4, 5, 6, 7, 8};

    ll n = a.size();

    build(1, 0, n-1, a);

    cout << "Sum [0,7] = " << query(1,0,n-1,0,7,a).val << '\n';
    cout << "Sum [2,5] = " << query(1,0,n-1,2,5,a).val << '\n';
    cout << "Sum [4,4] = " << query(1,0,n-1,4,4,a).val << '\n';

    update(1,0,n-1,3,10,a);   // a[3] = 10

    cout << "After a[3]=10:\n";
    cout << "Sum [0,7] = " << query(1,0,n-1,0,7,a).val << '\n';
    cout << "Sum [2,5] = " << query(1,0,n-1,2,5,a).val << '\n';

    update(1,0,n-1,0,100,a);  // a[0] = 100

    cout << "After a[0]=100:\n";
    cout << "Sum [0,2] = " << query(1,0,n-1,0,2,a).val << '\n';

    return 0;
}


