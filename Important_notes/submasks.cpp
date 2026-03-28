#include<bits/stdc++.h>
using namespace std;

int main()
{
    int mask = 16;
    for (int sub = mask; ; sub = (sub - 1) & mask) 
    {
    // use sub
        if (sub == 0) break;
    }
}