#include <bits/stdc++.h>
using namespace std;

int main()
{
    bitset<8> b1;                  // 00000000
    bitset<8> b2("10110011");      // from binary string
    bitset<8> b3(13);              // 00001101

    cout << b2[0] << '\n';         // least significant bit
    cout << b2[7] << '\n';         // most significant bit

    b2[0] = 0;                     // modify bit

    bitset<8> b;
    b.set();                       // 11111111
    b.set(3);                      // set bit 3 = 1
    b.set(5, 0);                   // set bit 5 = 0
    b.reset();                     // 00000000
    b.reset(2);                    // bit 2 = 0
    b.flip();                      // invert all bits
    b.flip(3);                     // toggle bit 3

    // Count bits
    bitset<8> x("10110011");
    cout << x.count() << '\n';     // number of 1s

    // Checks
    cout << x.any() << '\n';       // any bit = 1 ?
    cout << x.none() << '\n';      // all bits = 0 ?
    cout << x.all() << '\n';       // all bits = 1 ?
    cout << x.test(2) << '\n';     // check bit 2

    // Bitwise operators
    bitset<8> a("10101010");
    bitset<8> c("11110000");

    cout << (a & c) << '\n';       // AND
    cout << (a | c) << '\n';       // OR
    cout << (a ^ c) << '\n';       // XOR
    cout << (~a) << '\n';          // NOT

    bitset<8> y("00001111");
    cout << (y << 2) << '\n';      // left shift
    cout << (y >> 2) << '\n';      // right shift
    y <<= 2;                       // inplace left shift
    y >>= 1;                       // inplace right shift

    // Conversion
    bitset<8> z("00001101");
    cout << z.to_ulong() << '\n';  // 13
    cout << z.to_ullong() << '\n'; // 13
    string s = z.to_string();

    return 0;
}
