# cook your dish here
import sys
import random
from collections import defaultdict

class DefaultDict:
    def __init__(self, default=None):
        self.default = default
        self.x = random.randrange(1, 1 << 31)
        self.dd = defaultdict(default)

    def __repr__(self):
        return "{"+", ".join(f"{k ^ self.x}: {v}" for k, v in self.dd.items())+"}"

    def __eq__(self, other):
        for k in set(self) | set(other):
            if self[k] != other[k]: return False
        return True

    def __or__(self, other):
        res = DefaultDict(self.default)
        for k, v in self.dd: res[k] = v
        for k, v in other.dd: res[k] = v
        return res

    def __len__(self):
        return len(self.dd)

    def __getitem__(self, item):
        return self.dd[item ^ self.x]

    def __setitem__(self, key, value):
        self.dd[key ^ self.x] = value

    def __delitem__(self, key):
        del self.dd[key ^ self.x]

    def __contains__(self, item):
        return item ^ self.x in self.dd

    def items(self):
        for k, v in self.dd.items(): yield (k ^ self.x, v)

    def keys(self):
        for k in self.dd: yield k ^ self.x

    def values(self):
        for v in self.dd.values(): yield v

    def __iter__(self):
        for k in self.dd: yield k ^ self.x

class Counter(DefaultDict):
    def __init__(self, aa=[]):
        super().__init__(int)
        for a in aa: self.dd[a ^ self.x] += 1

    def __add__(self, other):
        res = Counter()
        for k in set(self) | set(other):
            v = self[k]+other[k]
            if v > 0: res[k] = v
        return res

    def __sub__(self, other):
        res = Counter()
        for k in set(self) | set(other):
            v = self[k]-other[k]
            if v > 0: res[k] = v
        return res

    def __and__(self, other):
        res = Counter()
        for k in self:
            v = min(self[k], other[k])
            if v > 0: res[k] = v
        return res

    def __or__(self, other):
        res = Counter()
        for k in set(self) | set(other):
            v = max(self[k], other[k])
            if v > 0: res[k] = v
        return res

class Set:
    def __init__(self, aa=[]):
        self.x = random.randrange(1, 1 << 31)
        self.st = set()
        for a in aa: self.st.add(a ^ self.x)

    def __repr__(self):
        return "{"+", ".join(str(k ^ self.x) for k in self.st)+"}"

    def __len__(self):
        return len(self.st)

    def add(self, item):
        self.st.add(item ^ self.x)

    def discard(self, item):
        self.st.discard(item ^ self.x)

    def __contains__(self, item):
        return item ^ self.x in self.st

    def __iter__(self):
        for k in self.st: yield k ^ self.x

    def pop(self):
        return self.st.pop() ^ self.x

    def __or__(self, other):
        res = Set(self)
        for a in other: res.add(a)
        return res

    def __and__(self, other):
        res = Set()
        for a in self:
            if a in other: res.add(a)
        for a in other:
            if a in self: res.add(a)
        return res

# sys.setrecursionlimit(200005)
int1 = lambda x: int(x)-1
pDB = lambda *x: print(*x, end="\n", file=sys.stderr)
p2D = lambda x: print(*x, sep="\n", end="\n\n", file=sys.stderr)
def II(): return int(sys.stdin.readline())
def LI(): return list(map(int, sys.stdin.readline().split()))
def LLI(rows_number): return [LI() for _ in range(rows_number)]
def LI1(): return list(map(int1, sys.stdin.readline().split()))
def LLI1(rows_number): return [LI1() for _ in range(rows_number)]
def SI(): return sys.stdin.readline().rstrip()
dij = [(0, 1), (-1, 0), (0, -1), (1, 0)]
# dij = [(0, 1), (-1, 0), (0, -1), (1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)]
inf = (1 << 63)-1
# inf = 4294967295
md = 10**9+7
# md = 998244353

class Sieve:
    def __init__(self, n):
        self.plist = [2]
        min_prime_factor = [2, 0]*(n//2+1)
        for x in range(3, n+1, 2):
            if min_prime_factor[x] == 0:
                min_prime_factor[x] = x
                self.plist.append(x)
                if x**2 > n: continue
                for y in range(x**2, n+1, 2*x):
                    if min_prime_factor[y] == 0:
                        min_prime_factor[y] = x
        self.min_prime_factor = min_prime_factor

    def isprime(self, x):
        return self.min_prime_factor[x] == x

    def pf(self, x):
        pp, ee = [], []
        while x > 1:
            mpf = self.min_prime_factor[x]
            if pp and mpf == pp[-1]:
                ee[-1] += 1
            else:
                pp.append(mpf)
                ee.append(1)
            x //= mpf
        return pp, ee

    # unsorted
    def factor(self, a):
        ff = [1]
        pp, ee = self.pf(a)
        for p, e in zip(pp, ee):
            ff, gg = [], ff
            w = p
            for _ in range(e):
                for f in gg: ff.append(f*w)
                w *= p
            ff += gg
        return ff

def nHr(hn, hr):
    return nCr(hn+hr-1, hr-1)

def nPr(com_n, com_r):
    if com_r < 0: return 0
    if com_n < com_r: return 0
    return fac[com_n]*ifac[com_n-com_r]%md

def nCr(com_n, com_r):
    if com_r < 0: return 0
    if com_n < com_r: return 0
    return fac[com_n]*ifac[com_r]%md*ifac[com_n-com_r]%md

n_max = 100005
fac = [1]
for i in range(1, n_max+1): fac.append(fac[-1]*i%md)
ifac = [1]*(n_max+1)
ifac[n_max] = pow(fac[n_max], md-2, md)
for i in range(n_max-1, 1, -1): ifac[i] = ifac[i+1]*(i+1)%md

sv = Sieve(10**7)

def solve():
    n = II()
    aa = LI()

    ac = Counter(aa)
    fc = Counter()
    ans = 0
    for a, c in ac.items():
        ans += pow(2, c, md)-1
        for f in sv.factor(a):
            fc[f] += c
            ans -= nCr(c, f)
            ans %= md

    for f, c in fc.items():
        if f == 1: continue
        ans += nCr(c, f)
        ans %= md

    print(ans)

    # ***************************************

testnumber = II()
# testnumber = 1
for testcase in range(testnumber):
    solve()
    # print("YES" if solve() else "NO")