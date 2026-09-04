#include <bits/stdc++.h>
using namespace std;
#define v vector
#define ll long long
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define f(arr, n) for(ll i = 0; i < n; i++) cin >> arr[i];

vector<bool>sieve(ll max_number)
{
  v<bool>arr(max_number+1,true);
  arr[0]=false;
  arr[1]=false;
  for(ll i=2;i*i<=max_number;i++){
      if(arr[i])
      {
        for(ll j=i*i;j<=max_number;j+=i)
          {
            arr[j]=false;
          }
      }
  }
  return arr;
}
int main()
{   
    fast_io;
    v<bool>arr=sieve(1e5);
  for(auto it:arr)
    {
      cout<<it<<" "<<endl;
    }
    
}