#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef double db;
typedef std::string str;
#define sei set<int>
#define sell set<ll>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pld pair<ld,ld>
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vi>
#define vvll vector<vll>
#define vld vector<ld>
#define vstr vector<str>
#define vpii vector<pii>
#define vpll vector<pll>
#define bit(n,i) ((n>>i)&1)
#define bits(i) __builtin_popcountll(i)
#define all(v) v.begin(),v.end()
#define foa(i,v) for(auto i : v)
#define fo(i,a,b) for(int i=a;i<b;i++)
#define fo_(i,a,b) for(int i=a;i>b;i--)
#define M(a) memset(a,0,sizeof a)
#define M_(a) memset(a ,-1,sizeof a)
#define deb(x)  cerr << #x << " = " << x << endl
#define pb push_back
#define pob pop_back
#define lb lower_bound
#define ub upper_bound
#define F first
#define S second
#define OK order_of_key
#define FO find_by_order
#define nmax 10000100
const ld PI = 3.141592653589793238462643383279;
const ll inf = std::numeric_limits<ll>::max();
const int infint = std::numeric_limits<int>::max();
const ll mod = 1e9+7;
using namespace __gnu_pbds;
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int a[nmax];
int td[nmax],p[nmax];
map<int,int> ted;
ll pw(ll a,ll b){
    if(a <= 0 || b < 0) return 0;
    if(b == 0) return 1;
    if(b%2) return a*pw(a,b-1)%mod;
    ll c = pw(a,b/2);
    return c*c%mod;
}
vi divs(int n){
    vi out;
    fo(i,1,sqrt(n)+1){
        if(n%i == 0 && n/i < i) continue;
        if(n%i == 0 && n/i != i){
            out.pb(i);
            out.pb(n/i);
        }else if(n%i == 0 && n/i == i) out.pb(i);
    }
    return out;
}
ll inv(ll a, ll m = mod)
{
    ll m0 = m;
    ll y = 0, x = 1;
    ll a0 = a;

    if (m == 1)
      return 0;

    while (a > 1)
    {
        ll q = a / m;
        ll t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }

    if (x < 0)
       x += m0;

    y = (1-x*(a0))/m0;  // baraye x*a0+y*m0 = 1 hast!

    return x;
}

ll fact[nmax/10];
ll invfact[nmax/10];

ll c(ll n, ll r){
    if(r < 0 || n < 0) return 0;
    if(n < r) return 0;
    return fact[n]*invfact[n-r]%mod*invfact[r]%mod;
}
void init_c(){ //in ro hatman to main bezar!!! nmax ham taghir bede
    fact[0] = 1;
    invfact[0] = 1;
    fo(i,1,nmax/10){
        fact[i] = i*fact[i-1]%mod;
        invfact[i] = inv(fact[i]);
    }
}



vi calc_divs(int n){
    if(n == 1) return {1};
    vi out;
    int pnow,tedp;
    pnow = p[n];
    tedp = 0;
    while(n%pnow == 0){
        tedp++;
        n /= pnow;
    }
    vi recursee = calc_divs(n);
    int pp = 1;
    fo(i,0,tedp+1){
        foa(j,recursee) out.pb(j*pp);
        pp *= pnow;
    }
    return out;
}

void init_divs(){
    fo(i,2,nmax){
        if(p[i] != 0) continue;
        for(int j = i; j < nmax; j+=i) p[j] = i;
    }
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;
    cin >> t;
    init_c();
    init_divs();
    while(t--){
        int n;
        cin >> n;
        fo(i,0,n) cin >> a[i];
        ted.clear();
        fo(i,0,n) ted[a[i]]++;
        ll ans = 0;
        foa(i,ted){
            if(i.S > 1) ans += pw(2,i.S)-i.S-1;
        }
        ans = (ans+mod)%mod;
        sei dall;
        foa(i,ted){
            foa(j,calc_divs(i.F)){
                if(j == 1) continue;
                td[j] += i.S;
                ans -= c(i.S,j);
                dall.insert(j);
            }
        }
        foa(i,dall){
            if(i == 1) continue;
            ans += c(td[i],i);
        }
        ans %= mod;
        cout << (ans+mod)%mod << '\n';
        foa(i,dall) td[i] = 0;
    }

    return 0;
}