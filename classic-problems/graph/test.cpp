while (!q2.empty())
    {
        pair<ll, pair<ll, pair<bool, bool>>> front = *q2.begin();
        q2.erase(q2.begin());

        ll node = front.ss.ff;
        ll wt = front.ff;
        bool prev = front.ss.ss.ss;
        bool onhorse = front.ss.ss.ff;

        int prevst = prev? 2:0;

        int state = onhorse? 2:0;

        vis2[node][prevst] = true;

        for (auto child: graph[node])
        {
            //if (vis2[child.ff])
            //continue;

            ll newstate = 0;

            ll chnode = child.ff;
            ll chwt = child.ss;

            if (onhorse || horse[node])
            {
                onhorse = true;
                chwt /= 2;
                newstate = 2;
            }

            if (dist2[node][state] + chwt < dist2[chnode][state])
            {
                dist2[chnode][state] = min(dist2[chnode][state], dist2[node][state] + chwt);
            }

            bool neww= newstate ==0? false:true;

            if (!vis2[chnode][state])
            q2.insert({chwt, {chnode, {onhorse, neww}}});
        }
    }