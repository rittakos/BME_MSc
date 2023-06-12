import sys, getopt

inputfile = ''
outputfile = ''
plength = 1
offset = 0

try:
    opts, args = getopt.getopt(sys.argv[1:],'hl:f:i:o:')
except getopt.GetoptError:
    print('Usage: sample.py -l <plength> -f <offset> -i <inputfile> -o <outputfile>')
    sys.exit(2)

for opt, arg in opts:
    if opt == '-h':
        print('Usage: sample.py -l <plength> -f <offset> -i <inputfile> -o <outputfile>')
        sys.exit()
    elif opt == '-l':
        plength = int(arg)
    elif opt == '-f':
        offset = int(arg)
    elif opt == '-i':
        inputfile = arg
    elif opt == "-o":
        outputfile = arg
      
if len(inputfile) == 0:
    print('Error: Name of input file is missing.')
    sys.exit(2)

if len(outputfile) == 0:
    print('Error: Name of output file is missing.')
    sys.exit(2)

ifile = open(inputfile, 'rb')
text = ifile.read()
ifile.close()
text_length = len(text)

sampled_text = b''
i = offset
while i < text_length:
    sampled_text += text[i].to_bytes(1, 'big')
    i += plength

ofile = open(outputfile, 'wb')
ofile.write(sampled_text)
ofile.close()
