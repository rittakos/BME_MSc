import socket
import time
import os
import hashlib
import requests
import http.client
import ssl

ip = "152.66.249.144"
ports = [1337, 2674, 4011]

def knock(ports):
    delay = 1
    for port in ports:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.setblocking(False)
        sock.connect_ex((ip, port))
        sock.close()
        time.sleep(delay)

def calc(eqParts):
    res = int(eqParts[1])
    idx = 2
    while idx < len(eqParts):
        if eqParts[idx] == "=":
            return res
        if eqParts[idx] == "+":
            res = res + int(eqParts[idx + 1])
        if eqParts[idx] == "-":
            res = res - int(eqParts[idx + 1])
        idx = idx + 2
        
def sendNeptun(s):
    data = s.recv(1024)
    print(f"{data!r}")
    s.sendall(b"Z8WK8D")
    data = s.recv(1024)
    print(f"{data!r}")

def calcEqs(s):
    data = s.recv(1024)
    string = f"{data!r}"
    print(string)
    eqNum = int((string.split('\\n')[0]).split()[4])

    idx = 1
    eqParts = (string.split('\\n')[2]).split()
    res = calc(eqParts)
    s.sendall(bytes(str(res), 'ascii'))
    while idx < eqNum:
        d = s.recv(1024)
        eq = f"{d!r}"
        print(eq)
        res = calc(eq.split())
        s.sendall(bytes(str(res), 'ascii'))
        if idx == eqNum - 1:
            lastResult = str(res)
        idx = idx + 1

    data = s.recv(1024)
    print(f"{data!r}")

def sha1(s):
    data = s.recv(1024)
    string = f"{data!r}"
    print(string)
    toHash = string.split('\'')[1]
    sha1 = hashlib.sha1(bytes(toHash, 'ascii'))
    s.sendall(bytes(sha1.hexdigest(), 'ascii'))
    data = s.recv(1024)
    print(f"{data!r}")
    data = s.recv(1024)
    print(f"{data!r}")

    succes = False
    extension = 0
    while succes == False:
        newToHash = toHash + str(extension)
        sha1 = hashlib.sha1(bytes(newToHash, 'ascii'))
        res = bytes(sha1.hexdigest(), 'ascii')
        if res[0:4] == b'0000':
            succes = True
            break
        extension = extension + 1

    s.sendall(bytes(toHash + str(extension), 'ascii'))

def getFlag(s):
    data = s.recv(2048)
    print(f"{data!r}")
    data = s.recv(1024)
    print(f"{data!r}")
    data = s.recv(2048)
    print(f"{data!r}")

    BASE_URL = 'http://152.66.249.144'
    AUTH_URL = BASE_URL
    CREDENTIALS = {'neptun': 'z8wk8d', 'password': 'crysys'}

    session = requests.Session()
    session.post(AUTH_URL, data=CREDENTIALS)
    print(session.cookies)

    file_url = BASE_URL + '/getcert.php'
    resp = session.get(file_url, stream=True)

    if resp.status_code == 200:
        filename ='cert.pem'
        with open(filename, 'wb') as f:
            for chunk in resp.iter_content(chunk_size=1024):
                if chunk:
                    f.write(chunk)

    file_url = BASE_URL + '/getkey.php'
    resp = session.get(file_url, stream=True)

    if resp.status_code == 200:
        filename ='key.pem'
        with open(filename, 'wb') as f:
            for chunk in resp.iter_content(chunk_size=1024):
                if chunk:
                    f.write(chunk)


    final_conn = session.get(   'https://152.66.249.144', cert=('cert.pem', 'key.pem'),
                                headers={'User-agent': 'CrySyS'}, verify=False)

    print(final_conn.text)

knock(ports)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.settimeout(1)
s.connect_ex((ip, 8888))

sendNeptun(s)
calcEqs(s)
sha1(s)
getFlag(s)

s.close()
