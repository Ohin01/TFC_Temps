#include<bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;
  
  vector<double> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  sort(v.begin(),v.end());
  for (int i = 0; i < n - 1; i++)
  {
    v[i + 1] = (v[i] + v[i + 1]) / 2.0;
  }
  cout << fixed << setprecision(5) << v[n - 1] << endl;
  return 0;
}