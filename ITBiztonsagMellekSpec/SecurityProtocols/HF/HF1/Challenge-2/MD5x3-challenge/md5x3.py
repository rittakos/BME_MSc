from Crypto.Hash import MD5
from Crypto.Util.strxor import strxor 

class TypeError(Exception):
    def __init__(self, message):
        self.message = message

class LengthError(Exception):
    def __init__(self, message):
        self.message = message

def RF(L, R, RK):
    md5 = MD5.new()
    md5.update(RK[0:1]+R+RK[1:2])
    return strxor(L, md5.digest()), R

def ENC(X, K):

    if type(K) != bytes:
        raise TypeError("Key must be of type bytes!")
        return
    
    if len(K) != 6:
        raise LengthError("Key length must be of length 6 bytes!")
        return
    
    if type(X) != bytes:
        raise TypeError("Input block must be of type bytes!")
        return
    
    if len(X) != 32:
        raise LengthError("Block length must be of length 32 bytes!")
        return    
    
    K0 = K[0:2]
    K1 = K[2:4]
    K2 = K[4:6]
    
    L, R = X[0:16], X[16:32]
    L, R = RF(L, R, K0)
    L, R = R, L
    L, R = RF(L, R, K1)
    L, R = R, L
    L, R = RF(L, R, K2)
    Y = L + R
    
    return Y 

def DEC(Y, K):

    if type(K) != bytes:
        raise TypeError("Key must be of type bytes!")
        return
    
    if len(K) != 6:
        raise LengthError("Key length must be of length 6 bytes!")
        return
    
    if type(Y) != bytes:
        raise TypeError("Input block must be of type bytes!")
        return
    
    if len(Y) != 32:
        raise LengthError("Block length must be of length 32 bytes!")
        return    
    
    K0 = K[0:2]
    K1 = K[2:4]
    K2 = K[4:6]
    
    L, R = Y[0:16], Y[16:32]
    L, R = RF(L, R, K2)
    L, R = R, L
    L, R = RF(L, R, K1)
    L, R = R, L
    L, R = RF(L, R, K0)
    X = L + R
    
    return X 
