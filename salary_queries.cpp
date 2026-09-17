#include <bits/stdc++.h>
using namespace std;

#define v vector
#define ll long long
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define f(arr, n) for(ll i = 0; i < n; i++) cin >> arr[i];

struct Node
{
    ll cnt;
};

Node merge(Node a, Node b)
{
    return {a.cnt + b.cnt};
}

Node st[3200005];

void build(ll p, ll l, ll r, v<ll>& freq)
{
    if(l == r)
    {
        st[p].cnt = freq[l];
        return;
    }

    ll m = (l + r) / 2;

    build(2*p, l, m, freq);
    build(2*p+1, m+1, r, freq);

    st[p] = merge(st[2*p], st[2*p+1]);
}

void update(ll p, ll l, ll r, ll idx, ll val)
{
    if(l == r)
    {
        st[p].cnt += val;
        return;
    }

    ll m = (l + r) / 2;

    if(idx <= m)
        update(2*p, l, m, idx, val);
    else
        update(2*p+1, m+1, r, idx, val);

    st[p] = merge(st[2*p], st[2*p+1]);
}

Node query(ll p, ll l, ll r, ll ql, ll qr)
{
    if(qr < l || ql > r)
        return {0};

    if(ql <= l && r <= qr)
        return st[p];

    ll m = (l + r) / 2;

    return merge(
        query(2*p, l, m, ql, qr),
        query(2*p+1, m+1, r, ql, qr)
    );
}

int main()
{
    fast_io;

    ll n, q;
    cin >> n >> q;

    vector<ll> salary(n + 1);
    set<ll> s;

    for(ll i = 1; i <= n; i++)
    {
        cin >> salary[i];
        s.insert(salary[i]);
    }

    vector<char> type(q);
    vector<ll> x(q), y(q);

    for(ll i = 0; i < q; i++)
    {
        cin >> type[i] >> x[i] >> y[i];

        if(type[i] == '!')
        {
            s.insert(y[i]);
        }
        else
        {
            s.insert(x[i]);
            s.insert(y[i]);
        }
    }

    
    vector<ll> vals(s.begin(), s.end());

    ll sz = vals.size();

    
    vector<ll> freq(sz, 0);

    for(ll i = 1; i <= n; i++)
    {
        ll rank = lower_bound(vals.begin(), vals.end(), salary[i])
                  - vals.begin();

        freq[rank]++;
    }

    build(1, 0, sz-1, freq);

    for(ll i = 0; i < q; i++)
    {
        if(type[i] == '!')
        {
            ll oldRank =
                lower_bound(vals.begin(), vals.end(), salary[x[i]])
                - vals.begin();

            ll newRank =
                lower_bound(vals.begin(), vals.end(), y[i])
                - vals.begin();

            update(1, 0, sz-1, oldRank, -1);
            update(1, 0, sz-1, newRank, +1);

            salary[x[i]] = y[i];
        }
        else
        {
            ll l =
                lower_bound(vals.begin(), vals.end(), x[i])
                - vals.begin();

            ll r =
                lower_bound(vals.begin(), vals.end(), y[i])
                - vals.begin();

            cout << query(1, 0, sz-1, l, r).cnt << '\n';
        }
    }
}