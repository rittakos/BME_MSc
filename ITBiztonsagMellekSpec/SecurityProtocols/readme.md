# Hálózatbiztonság

BME VIK Mérnökinformatika MSc, IT Biztonság mellékspecializáció, 2023 tavasz

## Kidolgozás

### What are the three main properties of the XOR operation?
    1. X + 0 = 0 + X = X
    2. X + X = 0
    3. if X + Y = Z, then X = Y + Z (and Y = X + Z)

### Why the simple XOR cipher be broken?
    A jelszót sokszor egymás után írjuk, olyan hosszan mint a rejtjelezendő szöveg. Ezt xor-oljuk az eredeti szöveggel. Egy újbóli xor-olás visszaadja az eredeti szöveget. A feltörés során meghatározható a jelszó hossza. Ezután a karakterek előfordulási száma alapján kitalálhatóak.

### How does the one-time pad work?
    Az üzenet byte-ait egy valódi random byte sorozattal bytonként xor-oljuk. Visszafejtésnél ugyanazokkal a random byte-okkal xor-olunk

### What does perfect secrecy mean intuitively?
    A kódolt üzenet nem rejt semmilyen utalást/információt az eredeti üzenetről.

### What are the disadvantages of the one-time pad?
    Nagy kulcs méret, ugyanolyan hosszú mint az üzenet. El kell küldeni az üzenet mellett a kulcsot is a célszemélynek. A kulcs átadása biztonsági kockázat és macerás, amit minden célszeméllyel meg kell tenni.

### How stream ciphers work? (general internal structure)
    Egy random seed alapján generált pseudo random sorozat adja a kulcsot. Ezzel a generált kulcsal ugyanúgy titkosítunk mint a one-time pad esetében.
![](img/stream.png)

### Why should the state space of a stream cipher be large?
    Különben a kulcssorozatban ismétlések fordulnak elő.

### What are the advantages of stream ciphers?
    Gyors. Kevés memória elég az információk és az algoritmus tárolására.

### What are the disadvantages of stream ciphers?
    Szinkronizáció szükséges a küldő és fogadó között. Nincs integritás védelem, a támadó módosíthatja az üzenetet és pontosan tudja ez milyen hatást vált ki, a fogadó nem biztos, hogy észreveszi a változtatást.

---

### How block ciphers work? What does it mean intuitively that a block cipher behaves like a random permutation?
    Bit-ek blokkján (általában 128 bit) működik. Az üzenet egyes blokkjait sorra egymás után titkosítja. Ha a kulcs ismeretlen, a kimenet (vagy annak része) megjósolhatatlan, még bemenet-kimenet párok ismeretében is.

### How block ciphers are constructed? What do we mean by an avalanche effect?
    Több rétegnyi egyszerű, ám nem biztonságos műveletet használnak, amiknek az eredménye egy biztonságos megoldás lesz. Az avalanche effektus azt jelenti, hogy a bemenet egy bit-jének megváltoztatása minden kimeneti bit 0,5 valószínűségű változását vonja maga után.

### What is the Kerckhoff principle? Why is it important?
    Azt jelenti, hogy egy kiptografikus rendszert úgy kell felépíteni, hogy akkor is biztonságos maradjon, ha a működése ismert (a kulcs ismeretlen). Emiatt egyedül a kulcs titokban tartására kell figyelni, az algoritmus lehet ismert.

### What are the standard attacker models in case of encryption?
    A támadás célja, a támadó rendelkezésére álló információk és a támadás mérőszámai.

### How does exhaustive key search work? What is its complexity?
    Brute force. Az összes lehetőség végigpróbálása. k hosszú kulcs esetén a komplexitás 2^(k-1).

### For a cipher to be secure, is it sufficient to have a large key size?
    Igen, az előző alapján a 128 bit hosszú kulcs már elég nagy.

### What is double encryption and how does the meet-in-themiddle attack work on it?
    Kétszer kódolunk egy blokkot különböző kulcsokkal. Ez támadható, ha tudunk egy bemenet(X) kimenet(Y) párt és két irányból próbálkozunk. Vagyis nézzük az EK1(X) és DK2(Y) lehetősége és ahol egyezést találunk, ott megkapjuk a kulcsokat.

### How does 3DES work?
$Y = DES_{K3}(DES^{-1}_{K2}(DES_{K1}(X)))$

### What are the main block cipher selection criteria?
    Effektivitás, biztonság és az elvárt követelményekkel való egyezés.

---


### Why do we need block encryption modes?

### What is the main weakness of the ECB mode? 

### How do the CBC and the CTR modes work and what are their main properties?

### How to generate unpredictable IVs for CBC?

### How to generate non-repeating counters for CTR?


