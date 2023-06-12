import md5x3 as md5

X = b'*THIS_IS_A_TEST_INPUT_FOR_MD5X3*'
y = 0xf1eba0e1e77269c82f29b7a695dc7ae4899991ebcbeafe1c6a5fdb873621f750
Y = y.to_bytes(32, 'big')

L0 = X[0:16]
R0 = X[16:32]

L3 = Y[0:16]
R3 = Y[16:32]


Res1 = []
Res2 = []

it = 0

while it < pow(2, 16) :
    lll, rrr = md5.RF(L0, R0, it.to_bytes(2, 'big'))
    Res1.append(lll)
    it += 1;


it = 0;

while it < pow(2, 16) :
    llll, rrr = md5.RF(L3, R3, it.to_bytes(2, 'big'))
    Res2.append(llll)
    it += 1


i1 = 0 
i2 = 0
ri1 = 0
ri2 = 0

found = False

for v in Res1:
    i2 = 0
    for w in Res2:
        if v == w :
            ri1 = i1
            ri2 = i2
            found = True
            break
        i2 += 1
    if(found):
        break
    i1 += 1


k1 = ri1.to_bytes(2, 'big')
k3 = ri2.to_bytes(2, 'big')
k2 = 0


it = 0

while it < pow(2, 16) :
    enc = md5.ENC(X, k1 + it.to_bytes(2, 'big') + k3)
    if(enc == Y):
        k2 = it.to_bytes(2, 'big')
        break
    it += 1

K = k1 + k2 + k3
print(K)