from Crypto.Util.strxor import strxor 

original =  b'2021:02:01|11:23:38|21450|A74635|B29846|00003500'

new =       b'2031:02:01|11:23:39|21451|A74635|B29846|10003500'

# b'2021:02:01|11:23'
# b':38|21450|A74635'
# b'|B29846|00003500'

# b'2031:02:01|11:23'
# b':39|21451|A74635'
# b'|B29846|10003500'

#print (original[0:16])
#print (original[16:32])
#print (original[32:48])

xor = strxor(strxor(original[0:16], original[16:32]), original[32:48])
newXor = strxor(strxor(new[0:16], new[16:32]), new[32:48])

print(xor)
print(newXor)
print(xor == newXor)