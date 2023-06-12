Simple XOR cipher
=================

You obtained an encrypted file `ciphertext.txt`, which was produced by encrypting an English text with the simple XOR cipher. Your task is to find the key and decrypt the file.

The following tools (Python programs) are provided to help your work:

### sample.py

`sample.py` is a program that can take every n-th character of an input file and save them into an output file. This is how you can call this program:

```bash
   python3 sample.py -l <plength> -f <offset> -i <inputfile> -o <outputfile>
```

For instance, if you want to save every third character of the file ciphertext.txt, starting with the first character in the file, you should run

```bash
   python3 sample.py -l 3 -f 0 -i ciphertext.txt -o ciphertext_3_0.txt
```

You can also specify an offset position to start from. For instance, if you want to save every third character of the file `ciphertext.txt`, starting with the second character in the file, you should run

```bash
   python3 sample.py -l 3 -f 1 -i ciphertext.txt -o ciphertext_3_1.txt
```

### stat.py

`stat.py` is a program which computes the ordered byte frequencies in an input file. The program determines the most frequent byte, the width of the empirical distribution of bytes (number of different bytes in the file), it computes the frequency of every byte, and orders the frequency values in descending order. This is how you can call this program:

```bash
   python3 stat.py -i <inputfile> [-o <outputfile>] 
```

If you don't specify an output file, then the program only prints the most frequent byte, its frequency, and the width of the empirical distribution on the screen. 

### xor.py

`xor.py` implements the simple XOR cipher. This is how you can call this program:

```bash
   python3 xor.py -k <keystring> -i <inputfile> -o <outputfile>
```

The very same program with the same keystring can be used for both encrypting and decrypting.


