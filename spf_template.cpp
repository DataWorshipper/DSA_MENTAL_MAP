#include <bits/stdc++.h>
using namespace std;
#define v vector
#define ll long long
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define f(arr, n) for(ll i = 0; i < n; i++) cin >> arr[i];

vector<ll>spf(ll max_number)
{
  v<ll>spf_arr(max_number+1,0);
  for(ll i=2;i<=max_number;i++)
    {
      spf_arr[i]=i;
    }
  for(ll i=2;i*i<=max_number;i++)
    {
      if(spf_arr[i]==i)
      {
        for(ll j=i*i;j<=max_number;j+=i)
          {
            if(spf_arr[j]==j)
              spf_arr[j]=i;
          }
      }
    }
  return spf_arr;
}
int main()
{   
    fast_io;
    v<ll>spf_arr=spf(1e5);
    ll number=60;
  /*Prime Factorization complexity->o(logn)
  */
  while(number!=1)
    {
      cout<<spf_arr[number]<<" ";
      number/=spf_arr[number];
    
    }
  
    
}