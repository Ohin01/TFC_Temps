#include <bits/stdc++.h>
using namespace std;

int main() {
    // ----------------------------
    // 1. DECLARATION
    // ----------------------------
    bitset<8> a;                 // all 0
    bitset<8> b(13);             // from integer
    bitset<8> c(string("10101"));// from string

    cout << "a (default)      : " << a << "\n";
    cout << "b (from 13)      : " << b << "\n";
    cout << "c (from string)  : " << c << "\n\n";


    // ----------------------------
    // 2. SET / RESET / FLIP
    // ----------------------------
    a.set();        // all 1
    cout << "a.set()          : " << a << "\n";

    a.reset();      // all 0
    cout << "a.reset()        : " << a << "\n";

    a.flip();       // invert
    cout << "a.flip()         : " << a << "\n\n";


    // ----------------------------
    // 3. SINGLE BIT OPERATIONS
    // ----------------------------
    bitset<8> x;

    x.set(2);       // set bit 2
    x.set(5);       // set bit 5
    cout << "x after set(2,5) : " << x << "\n";

    x.reset(2);
    cout << "x reset(2)       : " << x << "\n";

    x.flip(5);
    cout << "x flip(5)        : " << x << "\n\n";


    // ----------------------------
    // 4. QUERY OPERATIONS
    // ----------------------------
    cout << "x.count()        : " << x.count() << "\n";
    cout << "x.any()          : " << x.any() << "\n";
    cout << "x.none()         : " << x.none() << "\n";
    cout << "x.all()          : " << x.all() << "\n\n";
    //bs[i] returns a boolean (0 or 1)


    // ----------------------------
    // 5. BITWISE OPERATIONS
    // ----------------------------
    bitset<8> p(string("10101010"));
    bitset<8> q(string("11001100"));

    cout << "p                : " << p << "\n";
    cout << "q                : " << q << "\n";

    cout << "p & q            : " << (p & q) << "\n";
    cout << "p | q            : " << (p | q) << "\n";
    cout << "p ^ q            : " << (p ^ q) << "\n";
    cout << "~p               : " << (~p) << "\n\n";


    // ----------------------------
    // 6. SHIFT OPERATIONS
    // ----------------------------
    bitset<8> s(string("00001111"));

    cout << "s                : " << s << "\n";
    cout << "s << 2           : " << (s << 2) << "\n";
    cout << "s >> 2           : " << (s >> 2) << "\n\n";


    // ----------------------------
    // 7. CONVERSION
    // ----------------------------
    bitset<8> num(29);

    cout << "num              : " << num << "\n";
    cout << "to_ullong()      : " << num.to_ullong() << "\n";
    cout << "to_string()      : " << num.to_string() << "\n\n";


    // ----------------------------
    // 8. INDEX ACCESS
    // ----------------------------
    cout << "num[0]           : " << num[0] << "\n";
    cout << "num[3]           : " << num[3] << "\n\n";


    // ----------------------------
    // 9. CLASSIC SUBSET SUM IDEA
    // ----------------------------
    bitset<20> dp;
    dp[0] = 1;

    vector<int> arr = {3, 5, 2};

    for (int x : arr) {
        dp |= (dp << x);
    }

    cout << "Subset sum dp    : " << dp << "\n";

    cout << "Possible sums: ";
    for (int i = 0; i < 20; i++) {
        if (dp[i]) cout << i << " ";
    }
    cout << "\n";

    return 0;
}