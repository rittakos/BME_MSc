import sys, getopt

keystring = ''
inputfile = ''
outputfile = ''

try:
    opts, args = getopt.getopt(sys.argv[1:],'hk:i:o:')
except getopt.GetoptError:
    print('Usage: xor.py -k <keystring> -i <inputfile> -o <outputfile>')
    sys.exit(2)

for opt, arg in opts:
    if opt == '-h':
        print('Usage: xor.py -k <keystring> -i <inputfile> -o <outputfile>')
        sys.exit()
    elif opt == '-k':
        keystring = arg
    elif opt == '-i':
        inputfile = arg
    elif opt == "-o":
        outputfile = arg
      
if keystring == '': keybytes = '\x00'
else: keybytes = keystring.encode('utf-8')
keylen = len(keybytes)

if len(inputfile) == 0:
    print('Error: Name of input file is missing.')
    sys.exit(2)

if len(outputfile) == 0:
    print('Error: Name of output file is missing.')
    sys.exit(2)

# read the plaintext from the input file
ifile = open(inputfile, 'rb')
plaintext = ifile.read()
ifile.close()

ciphertext = b''
for i in range(len(plaintext)):
    ciphertext += (plaintext[i] ^ keybytes[i%keylen]).to_bytes(1, 'big')
print(ciphertext)

# write the ciphertext into the output file
ofile = open(outputfile, 'wb')
ofile.write(ciphertext)
ofile.close()
