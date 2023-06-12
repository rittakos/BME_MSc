import sys, getopt

inputfile = ''
outputfile = ''

try:
    opts, args = getopt.getopt(sys.argv[1:],'hi:o:')
except getopt.GetoptError:
    print('Usage: stat.py -i <inputfile> [-o <outputfile>]')
    sys.exit(2)

for opt, arg in opts:
    if opt == '-h':
        print('Usage: stat.py -i <inputfile> [-o <outputfile>]')
        sys.exit()
    elif opt == '-i':
        inputfile = arg
    elif opt == "-o":
        outputfile = arg
      
if len(inputfile) == 0:
    print('Error: Name of input file is missing.')
    sys.exit(2)

#if len(outputfile) == 0:
#    print('Error: Name of output file is missing.')
#    sys.exit(2)

ifile = open(inputfile, 'rb')
text = ifile.read()
ifile.close()
text_length = len(text)

count = [0]*256
for i in range(text_length): count[text[i]] += 1

max_count = max(count)
max_index = count.index(max_count)
print('Most frequent byte: ' + hex(max_index))

max_freq = max_count/text_length
print(f'Frequency of most frequent byte: {max_freq:.3f}')

stat = sorted(count, reverse=True)
cut = stat.index(0)
stat = stat[:cut]
#print(stat)

print('Profile width: ' + str(cut))

if len(outputfile) > 0:
    ofile = open(outputfile, 'w')
    ofile.write('Profile width: ' + str(cut) + '\n')
    ofile.write('Most frequent byte: ' + hex(max_index) + '\n')
    ofile.write('Ordered letter freqiencies: ' + '\n')
    for n in stat:
        freq = n / text_length
        ofile.write(f'{freq:.3f}' + '\n')
    ofile.close()
