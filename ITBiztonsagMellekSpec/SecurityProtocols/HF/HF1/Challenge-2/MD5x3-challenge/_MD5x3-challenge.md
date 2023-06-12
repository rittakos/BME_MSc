MD5x3
=====

MD5x3 is a block cipher that has a 3-round Feistel structure and its round function is based on the MD5 hash function. The block size of MD5x3 is 32 bytes and its key length is 48 bits (6 bytes). The encryption operation is illustrated in the figure below, where | means concatenation of byte strings and (+) denotes the XOR operation:

    X = L0|R0

         L0                    R0
         |                     |
         |     +-----+         |
         |     |     |<--- K0  |
        (+)<---| MD5 |<--------+
         |     |     |<--- K1  |
         |     +-----+         |
         |                     |
         |         +-----+     |
         |  K2 --->|     |     |
         +-------->| MD5 |--->(+)
         |  K3 --->|     |     |
         |         +-----+     |
         |                     |
         |     +-----+         |
         |     |     |<--- K4  |
        (+)<---| MD5 |<--------+
         |     |     |<--- K5  |
         |     +-----+         |
         |                     |
         L3                    R3

    Y = L3|R3

The input block X is first divided into 2 halves, L0 and R0, 16 bytes each. The right half R0 is hashed together with the first 2 bytes K0, K1 of the key (see figure), the result MD5(K0|R0|K1) is XORed with the left half L0, and then the two halves are swapped. This makes up one round. The same operation is repeated in the remaining 2 rounds, except that the swap of the two halves is omitted at the end of the last round, and each round uses the next 2 bytes from the key, i.e., K2, K3, and K4, K5. We obtain the output Y by concatenating the two halves at the end.

A Python implementation of MD5x3 is provided for your convenience in md5x3.py. It is written in Python 3 and it uses the MD5 implementation and string XORing from the PyCryptodome package as a dependence. 

The following test plaintext block (without apostrophes) 

    '*THIS_IS_A_TEST_INPUT_FOR_MD5X3*'

was encrypted with an unknown key, and the resulting ciphertext block in hex format is

    `f1eba0e1e77269c82f29b7a695dc7ae4899991ebcbeafe1c6a5fdb873621f750`

Break the cipher and figure out the 6-byte key! 

### Note 

As the round function of MD5x3 is based on MD5, you need to install PyCryptodome in order to use the `md5x3.py` script or the RF function from it. To install PyCryptodome, run

```bash
    pip3 install pycryptodome
```
