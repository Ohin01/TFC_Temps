#include <bits/stdc++.h>
using namespace std;


string status;
bool bad(long long vol, long long con) {
    return con * 2 <= vol;
}
pair<long long, long long>mergeSegment(pair<long long, long long>p,
    pair<long long, long long>q) {
        return make_pair(p.first, q.second);
}

void handle0(vector<pair<int,int>> &rng) {
    cout<<"Yes\n";

    vector<pair<int,int>>mergedSegments;

    for(auto pr : rng) {
        int l = pr.first, r = pr.second;
        if(l != r) mergedSegments.emplace_back(l+1, r+1);
    }

    cout<<mergedSegments.size()<<"\n";
    for(auto pr : mergedSegments) {
        cout<<pr.first<<" "<<pr.second<<"\n";
    }
}
void handle12(vector<long long>&vol, vector<long long>&water, vector<pair<int,int>>&rng) {
    int m = status.size();

    int at = -1;
    for(int i=0; i+1<m; ++i) {
        long long curVol = vol[i] + vol[i+1];
        long long curWater = water[i] + water[i+1];

        if(!bad(curVol, curWater)) {
            at = i;
            break;
        }
    }

    if(at == -1) {
        cout<<"No\n";
    } else {
        rng[at] = mergeSegment(rng[at], rng[at+1]);
        rng.erase(rng.begin() + at + 1);

        handle0(rng);
    }
}
void handle4(vector<long long>&vol, vector<long long>&water, vector<pair<int,int>>&rng) {
    int at = -1;

    for(int i=0; i+1<status.size(); ++i) if(status[i] != status[i+1]) {
        long long curVol = vol[i] + vol[i+1];
        long long curWater = water[i] + water[i+1];

        if(!bad(curVol, curWater)) {
            at = i;
            break;
        }
    }

    if(at != -1) {
        rng[at] = mergeSegment(rng[at], rng[at+1]);
        rng.erase(rng.begin() + at + 1);

        handle0(rng);
    } else {
        for(int i=0; i+3<status.size(); ++i) {
            if(status[i] == 'B' && status[i+1] == 'G' && status[i+2] == 'G' && status[i+3] == 'B') {
                long long curVol = vol[i] + vol[i+1] + vol[i+2] + vol[i+3];
                long long curWater = water[i] + water[i+1] + water[i+2] + water[i+3];

                if(!bad(curVol, curWater)) {
                    at = i;
                }
            }
        }

        if(at == -1) {
            cout<<"No\n";
        } else {
            pair<long long, long long>curSegment = rng[at];

            int cnt = 4;
            while(cnt--) {
                curSegment = mergeSegment(curSegment, rng[at]);
                rng.erase(rng.begin() + at);
            }
            rng.insert(rng.begin()+at, curSegment);

            handle0(rng);
        }
    }
}
bool handle5(vector<long long>&vol, vector<long long>&water, vector<pair<int,int>>&rng) {
    int m = status.size();

    int at1 = -1, at2 = -1;
    for(int i=0; i+1<m; ++i) {
        long long curVol = vol[i] + vol[i+1];
        long long curWater = water[i] + water[i+1];

        if(!bad(curVol, curWater)) {
            if(at1 == -1) at1 = i, ++i;
            else at2 = i;
        }
    }

    if(at2 == -1) {
        return false;
    } else {
        rng[at2] = mergeSegment(rng[at2], rng[at2+1]);
        rng.erase(rng.begin() + at2 + 1);

        rng[at1] = mergeSegment(rng[at1], rng[at1+1]);
        rng.erase(rng.begin() + at1 + 1);

        handle0(rng);

        return true;
    }
}
void solve() {
    int n; cin>>n;
    
    vector<long long>V(n), W(n);
    for(long long &x : V) cin>>x;
    for(long long &x : W) cin>>x;

    vector<long long>canV, canW;
    vector<pair<int,int>>rng;

    status.clear();
    for(int i=0; i<n; ++i) {
        if(!bad(V[i], W[i])) {
            canV.push_back(V[i]);
            canW.push_back(W[i]);
            rng.emplace_back(i, i);

            status += 'G';
        } else {
            int j = i;

            long long cumV = 0, cumW = 0;
            while(j < n && bad(V[j], W[j])) {
                cumV += V[j];
                cumW += W[j];

                ++j;
            }
            canV.push_back(cumV);
            canW.push_back(cumW);
            rng.emplace_back(i, j-1);

            i = j-1;

            status += 'B';
        }
    }

    bool alter = true;
    int m = status.size();
    for(int i=1; i<m; ++i) alter &= status[i] != status[i-1];

    if(count(status.begin(), status.end(), 'G') * 2 > m) {
        handle0(rng);
        return;
    }
    if(m % 2 == 0 && alter) {

        handle12(canV, canW, rng);
        return;
    }

    if(m % 2 == 0) {
        handle4(canV, canW, rng);
        return;
    }

    assert(m & 1);
    assert(alter);

    if(handle5(canV, canW, rng)) return;


    long long sufVol = 0, sufWater = 0;
    int till = m-1;

    int foundLeft = -1, foundRight = -1;
    for(int i=m-2; i>0; i-=2) { //iterating through G
        long long curVol = canV[i-1] + canV[i] + canV[i+1];
        long long curWater = canW[i-1] + canW[i] + canW[i+1];

        if(!bad(sufVol + curVol, sufWater + curWater)) {
            foundLeft = i-1, foundRight = till;
            break;
        }

        long long newSufVol = sufVol + canV[i+1] + canV[i];
        long long newSufWater = sufWater + canW[i+1] + canW[i];

        if(!bad(newSufVol, newSufWater)) sufVol = newSufVol, sufWater = newSufWater;
        else till = i-1, sufVol = 0, sufWater = 0;
    }

    //cerr<<foundLeft<<" "<<foundRight<<endl;

    if(foundLeft == -1) {
        cout<<"No\n";
    } else {
        vector<pair<int,int>>newRng;
        for(int i=0; i<m; ++i) {
            if(i >= foundLeft && i <= foundRight) {
                if(i == foundLeft) newRng.push_back(rng[i]);
                else newRng.back() = mergeSegment(newRng.back(), rng[i]);
            } else {
                newRng.push_back(rng[i]);
            }
        }
        handle0(newRng);
    }


}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while(t--) {
        solve();
    }
    return 0;
}