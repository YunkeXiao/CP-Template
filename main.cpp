#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define ii pair<int,int>
#define iii pair<int,pair<int,int>>
#define vii vector<pair<int,int>>
#define vvi vector<vector<int>>

typedef long long ll;
typedef unsigned long long ull;
typedef unordered_map<ll, ll> ump;
typedef map<ll, ll> mp;
typedef unordered_set<ll> uset;

#define pb push_back
#define mp make_pair
#define fi first
#define se second


//**************************************** GRAPH ******************************************
//**********DSU**********
ll findp(ll v, ll plist[], ll slist[]) {
    if (plist[v] == v) {
        return v;
    } else {
        plist[v] = findp(plist[v], plist, slist);
        return plist[v];
    }
}

bool unionp(ll a, ll b, ll plist[], ll slist[]) {
    ll ap = findp(a, plist, slist), bp = findp(b, plist, slist);
    if (ap == bp) {
        return false;
    }
    plist[bp] = ap;
    slist[ap] += slist[bp];
    return true;
}

//**********dijkstra*********
//adj is start->end->value
vector<ll> dijkstra(int start, vector<vector<pair<ll, ll>>> adj
//        ,vector<int> & p
) {
    const int INF = 1000000000;
    ll n = (ll) adj.size();
    vector<ll> d;
    d.assign((unsigned long) n, INF);
//    p.assign(n, -1);

    d[start] = 0;
    set<pair<ll, ll>> q;
    q.insert({0, start});
    while (!q.empty()) {
        ll v = q.begin()->second;
        q.erase(q.begin());

        for (auto edge : adj[v]) {
            ll to = edge.first;
            ll len = edge.second;

            if (d[v] + len < d[to]) {
                q.erase({d[to], to});
                d[to] = d[v] + len;
//                p[to] = v;
                q.insert({d[to], to});
            }
        }
    }
    return d;
}

//**************************************** MATH ******************************************
//**********Powerset**********
vvi powerSet(int set[], int set_size) {
    ll pow_set_size = (ll) pow(2, set_size);
    int counter, j;
    vvi output;
    for (ll count = 0; count < pow_set_size; count++) {
        vi comb;
        for (j = 0; j < set_size; j++) {
            if ((count >> j) & 1) {
                comb.pb(set[j]);
            }
        }
        output.pb(comb);
    }
    return output;
}

//**********N choose K**********
ll nck(ll n, ll k) {
    ll out = n;
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;
    for (int i = 2; i <= k; i++) {
        out *= (n - i + 1);
        out /= i;
    }
    return out;
}
//**********sieve**********
//If prime factor, if case is prime, endloop != 1, add endloop value to list
vi sieve(ll n) {
    ll size = n + 10;
    bitset<10000010> p;
    vi primes;
    p.set();
    p[0] = p[1] = false;
    for (ll i = 2; i <= size; i++) {
        if (p[i]) {
            for (ll j = i * 2; j <= size; j += i) { p[j] = false; }
            primes.pb((int) i);
        }
    }
    return primes;
}

//**********isPrime**********
bool isPrime(ll n) {
    // Sieve (Modify size for max)
    ll size = n + 10;
    bitset<10000010> bs;
    vi primes;
    bs.set();
    bs[0] = bs[1] = false;
    for (ll i = 2; i <= size; i++) {
        if (bs[i]) {
            for (ll j = i * i; j <= size; j *= i) { bs[j] = false; }
            primes.pb((int) i);
        }
    }
    if (n <= 10000010) { return bs[n]; }
    for (int i = 0; i < (int) primes.size(); i++) { if (n % primes[i] == 0) { return false; }}
    return true;
};

//**********modpow***********
ll modpow(ll n, ll e, ll mod) {
    ll output = 1, x = n % mod, y = e;
    while (y > 0) {
        if (y & 1) { output = (output * x) % mod; }
        y = y >> 1;
        x = (x * x) % mod;
    }
    return output;
}

//**********GCD/LCM**********
// GCD(a, b, c) = GCD(a, GCD(b, c))
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll lcm(ll a, ll b) { return a * (b / gcd(a, b)); }


//*********************************************************************************************************************

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    return 0;
}




/*
                                               ⠶⣿⣭⡧⡤⣤⣻⣛⣹⣿⣿⣿⣶⣄
                                             ⣼⣊⣤⣶⣷⣶⣧⣤⣽⣿⣿⣿⣿⣿⣿⣷
                                             ⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇
                                         ⢀⣠⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧
                                        ⠸⠿⣿⣿⠿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣻⣿⣿⣿⣿⣿⡆
                                         ⢸⣿⣿⡀⠘⣿⡿⢿⣿⣿⡟⣾⣿⣯⣽⣼⣿⣿⣿⣿⡀
                                       ⢀⡠⠚⢛⣛⣃⢄⡁⢀⢀⢀⠈⠁⠛⠛⠛⠛⠚⠻⣿⣿⣿⣷
                                  ⣴⣶⣶⣶⣷⡄⠊⠉⢻⣟⠃⢀⢀⢀⢀⡠⠔⠒⢀ ⢀ ⢀ ⢀⢹⣿⣿⣿⣄
                                ⢠⣾⣿⣿⣿⣿⣿⣿⣿⣶⣄⣙⠻⠿⠶⠒⠁⢀⢀⣀⣤⣰⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄
                                ⢿⠟⠛⠋⣿⣿⣿⣿⣿⣿⣿⣟⡿⠷⣶⣶⣶⢶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄
                                     ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠉⠙⠻⠿⣿⣿⡿
                                     ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
                                     ⢸⣿⣿⣿⣿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
                                     ⢸⣿⣿⣿⣿⣄⠈⠛⠿⣿⣿⣿⣿⣿⣿⣿⡿⠟⣹⣿⣿⣿⣿⣿⣿⣿⣿⠇
                                      ⢻⣿⣿⣿⣿⣧⣀⢀⢀⠉⠛⠛⠋⠉⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⠏
                                       ⢻⣿⣿⣿⣿⣿⣷⣤⣄⣀⣀⣤⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋
                                        ⠙⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛
                                           ⢹⣿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠁
                                           ⢸⣿⡇ ⠈⠙⠛⠛⠛⠛⠛⠛⠻⣿⣿⣿⠇
                                           ⣸⣿⡇            ⢨⣿⣿
                                          ⣾⣿⡿⠃            ⢸⣿⡏
                                          ⠻⠿             ⢠⣿⣿⡇
*/