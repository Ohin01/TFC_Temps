#include <bits/stdc++.h>
using namespace std;


long long rand(long long a, long long b) {
    return a + (rand() % (b-a+1));
}
int main(int argc, const char** argv) {
    srand(atoi(argv[1]));

    int t = rand(1, 2);
    cout<<t<<endl;

    while(t--) {
        int n = rand(1, 50);
        cout<<n<<"\n";

        int vol[n];

        for(int i=0; i<n; ++i) {
            vol[i] = rand(1, 50);


            cout<<vol[i]<<" ";
        }
        cout<<endl;

        for(int i=0; i<n; ++i) cout<<rand(0, vol[i])<<" ";
        cout<<endl;


    }

}