pll minRange(int l, int r, int x, int lx, int rx)
    {
        if (rx <= l || lx >= r)
        return {INF, 1};

        if (lx >= l && rx <= r)
        return mn[x];

        int mid = (lx + rx) / 2;

        pll left = minRange(l, r, 2 * x + 1, lx, mid);
        pll right = minRange(l, r, 2 * x + 2, mid, rx);

        if (left.ff == right.ff)
        {
            return make_pair(right.ff, left.ss + right.ss);
        }

        else
        return min(left, right);
    }