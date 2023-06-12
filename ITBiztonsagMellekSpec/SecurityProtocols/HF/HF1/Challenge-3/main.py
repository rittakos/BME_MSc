Y = []
X = list('Please, fill the form below with your data. Make sure you enter data as it is written in your identity document, such as your passport or driving license. If your data is inaccurate, we cannot gurantee the delivery of your order. Thank you for your understanding.  Name: ?????????? Address: ????????????????? City: ??????????? Postal code: ?? ?????')
#X = list('Please, fill the form below with your data. Make sure you enter data as it is written in your identity document, such as your passport or driving license. If your data is inaccurate, we cannot gurantee the delivery of your order. Thank you for your understanding.  Name: John Adams Address: 3??0 Irving Ave S City: Minneapolis Postal code: MN 554??')

with open('input.txt', 'r') as f:
    txt = f.read()
    t = txt.split()
    for h in t:
        Y.append(hex(int(h, 16)))

progress = 1

while (progress > 0):
    progress = 0

    for i in range(0, len(Y) - 2):
        for j in range(i + 1, len(Y) - 1):
            if(Y[i] == Y[j]):
                if('?' == X[j] and X[i] != '?'):
                    xj = int(hex(ord(X[i])), 16) ^ int(Y[i + 1], 16) ^ int(Y[j + 1], 16)
                    X[j] = chr(xj)
                    ++progress

result = ""

for c in X:
    result += c

print(result)