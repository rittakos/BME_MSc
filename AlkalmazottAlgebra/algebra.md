# A 2 és 3 dimenziós tér

## Vector

**Irányított szakasz:** Olyan szakasz aminek végpontjait megkülönböztetjük, kezdő és végpont.

**Vektor:** Párhuzamosan egymásba tolható irányított szakaszok halmaza. Tehát egy irányított szakasz csak reprezentál egy vektort, de ugyanazt a vektort reprezentálja bármely párhuzamos eltoltja is. (fizikában kötött vektor és szabad vektor)

**Origó:** Kitüntetett pont. 

**Vektor hossza:** Két végpontjának távolsága. Másnéven vektor abszolút értéke vagy euklideszi normája. A 0 hosszúságú vektor, a **nullvektor**.

**Vektor állása:** Két nem nullvektor **kollineáris**nak, párhuzamosnak vagy azonos állásúnak nevezünk, ha az őket tartalmazó egyenesek párhuzamosak. Nem nullvektorok állásán az azonos állású vektorok osztályát értjük.

**Vektor iránya:** Két nemzérus kollineáris vektor **azonos irányú**, ha a kezdőpontjukból induló és a végpontjukat tartalmazó félegyenesek párhuzamosan egymásba tolhatók. Nemzérus vektorok irányán az azonos irányú vektorok osztályát értjük.

# $R^n$ tér

**Halmaz hatványa:** A $H$ halmaz elemeiből képzett rendezett elem-$n$-esek halmaza. $H^n$

**Vektorok lineáris kombinációja:** vektorok skalárszorosainak összege.

**Vektorok lineáris függetlensége:** egy $v$ vektor lineárisan független, a $\lbrace v_1, v_2, ... v_k \rbrace$ vektorrendszertől, ha $v$ nem fejezhető ki a vektorrendszer vektorainak lineáris kombinációjaként. A $v_1, v_2, ... v_k$ vektorok lineárisan függetlenek, ha egyik sem fejezhető ki a többi lineáris kombinációjaként.

**Generátorrendszer:** vektorok generátorrendszert alkotnak egy vektortérben, ha a vektortér minden vektora előáll a generátorrendszer vektorainak lineáris kombinációjaként.

**Bázis:** független vektorokból álló generátorrendszer

**Standard bázis:** $e_1=(1,0,...0), e_2=(0,1,...0)...e_n=(0,0...1)$

**Skaláris szorzás:** $u, v \in \mathbb{R}$ vektorok skaláris szorzata $u\cdot v = u_1\cdot v_1 + u_2\cdot v_2 + ... + u_n\cdot v_n$ 
- kommutatív
- dsiztributív

**Euklideszi norma, hossz:** $|u| = \sqrt{u\cdot u}$

**Távolság:** $d(u,v) = |u-v|$

**Vektorok szöge:** $cos(u,v) = \frac{u\cdot v}{|u||v|}$, nulla ha a két vektor merőleges

**Vektorral párhuzamos és merőleges összetevő:** Ha $b\in\mathbb{R}^n$ tetszőleges és $e$ egységvektor, akkor $b$ felbomlik egy $e$-vel párhuzamos és merőleges vektor összegére. $b=(b\cdot e)e+(b-(b\cdot e)e)$

**Cauchy-Bunyakovszkij-Schwarz egyenlőtlenség:** $|u\cdot v| \leq |u|\cdot|v|$, egyenlőség pontosan akkor, ha $u$ és $v$ lineárisan összefüggők.

**Polarizációs formulák:** tetszőleges $u,v \in \mathbb{R}^n$ vektorokra $u\cdot v = \frac14(|u+v|^2 - |u-v|^2)$

# Komplex számok

algebreai alak: $c = a+bi$

konjugált: $\overline{c} = a - bi$

trigonometrikus alak: $c = r(\cos\phi + i\sin\phi)$, ahol $r$ $c$ abszolút értéke $\phi$ az irányszöge.

$c = a+bi = r(\cos\phi + i\sin\phi)$
- $a = r\cos\phi$
- $b = r\sin\phi$
- $r=|c|$
- $\tg\phi = \frac ba, a \not = 0$

Ha $c = r(\cos\phi + i\sin\phi)$
- $c^{-1} = r^{-1}(\cos\phi - i\sin\phi)$
- $c^n = r^{-n}(\cos n\phi + i\sin n\phi)$
- $\sqrt[n]{c} = \sqrt[n]{r}(\cos \frac{\phi +2k\pi}{n} - i\sin\frac{\phi +2k\pi}{n})$, $n\in\mathbb{N}^+$, $k = 0, 1, ...n-1$

**Euklideszi tér**, olyan valós vektortér, ahol értelmezett a $<.,.>$ skaláris szorzás

# Testek

**Test:** egy legalább két elemet tartalmazó (jelölje ezeket $0$ és $1$) és két bináris művelettel (összeadás és szorzás) ellátott $\mathbb{F}$ halmaz, melyre bármely $a,b,c,d \in \mathbb{F}, d\not ={0}$ esetén fennállnak a következő tulajdonságok:

|+|$\cdot$||
|:---:|:---:|:---:|
|$a+b = b+a$|$ab=ba$|kommutativitás|
|$(a+b)+c=a+(b+c)$|$(ab)c = a(bc)$|asszociativitás|
|$0+a = a$|$1a = a$|van zéruselem és egységelem|
|$\exist x\in \mathbb{F} : a+x = 0$|$\exist y\in \mathbb{F} : dy = 1$|ellentett és reciprok|
|$(a+b)c=ac+bc$||disztributivitás|

**Gyűrű:** egy legalább egy elemet tartalmazó (jelölje ezt $0$) és két bináris művelettel (összeadás és szorzás) ellátott $R$ halmaz, melyre bármely $a,b,c \in R$ esetén fennállnak a következő tulajdonságok:

|+|$\cdot$||
|:---:|:---:|:---:|
|$a+b = b+a$|($ab=ba$)|kommutativitás|
|$(a+b)+c=a+(b+c)$|$(ab)c = a(bc)$|asszociativitás|
|$0+a = a$|($1a = a$)|van zéruselem és egységelem|
|$\exist x\in \mathbb{F} : a+x = 0$||ellentett|
|$(a+b)c=ac+bc$||disztributivitás|

Ha a szorzás kommutatív is, kommutatív gyűrűt kapunk. Ha van egységeleme, egységelemes gyűrűről beszélünk, ha ezeken kívül még kommutatív is, egységelemes kommutatív gyűrűről.

Egy $G$ gyűrű **nullosztómentes**, ha bármely $a,b \in G$ és $ab = 0$ esetén $a=0$ vagy $b=0$. 

Minden test nullosztómentes.

A nullosztómentes egységelemes kommutatív gyűrűt **integritási tartomány**nak nevezzük.

# Vektortér

A $V$ halmaz $\mathbb{F}$ test fölött vektortér ($V_{\mathbb{F}}$), ha tartalmaz egy $0$-val jelölt elemet és értelmezve van rajta az összeadás és a skaláris szorzás.

$U \subseteq V$ **alter**e $V$-nek, ha nem üres és zárt a vektorösszeadásra és a skalárral szorzásra.

# Mátrix

Egy mátrix oszlopvektorai által kifeszített alteret **oszloptér**nek,
a sorvektorai által kifeszített alteret **sortér**nek nevezzük.

# Lineáris leképezés

Legyen $V$ és $W$ két $\mathbb{F}$ test fölötti vektortér. Azt mondjuk, hogy egy $A: V \rightarrow W$ leképezés **lineáris**, ha homogén és additív, azaz bármely $x,y \in V$ elemre és $c \in \mathbb{F}$ skalárra:
- $A(cx) = cAx$ (homogén)
- $A(x+y) = Ax + Ay$ (additív)

A $V\rightarrow V$ leképezést **lineáris transzformáció**nak nevezzük.

# Egyenletrendszerek

Az $A$ együtthatómátrixú homogén lineáris egyenletrendszer megoldásainak alterét az $A$ mátrix **nullter**ének nevezzük és $N (A)$-val jelöljük

# Mátrixfelbontások

**Bázisfelbontás**: $A_{m*n}$ mátrix
- redukált lépcsős alakjának nemzérus soraiból álló r × n-es részmátrixa legyen R
- az R főoszlopainak megfelelő A-beli  szlopok alkotta m × r-es részmátrix legyen B

$$ A = BR $$

$A = LU$ **LU-felbontás** ha $L$ alsó egység háromszögmátrix $U$ felső háromszögmátrix
- nincs mindig ilyen

Kiszámolása: 
- U a felső háromszög mátrix
- $L = \begin{vmatrix}
1 & 0 & ... & 0\\
l_{21} & 1 &... & 0\\
. & . & &.\\
l_{m1} & l_{m2} & ...& 1
\end{vmatrix}$, ahol $l_{ij} = \frac{a_{ij}}{a_{jj}}$

**PLU felbontás**: $PA = LU$, azaz $A = P^TLU$, $P$ permutáló
- nem csak négyzetes alakúakra

# Merőleges vetítés

**Gram mátrix:**

$$G(v_1, v_2 ... v_k) = [\left< v_i, v_j \right>] = \begin{vmatrix}
\left< v_1, v_1 \right> &  ... & \left< v_1, v_k \right>\\
. & . & .\\
\left< v_k, v_1 \right> & ...&  \left< v_k, v_k \right>
\end{vmatrix}$$

# Pszeudo inverz

 Az A mátrix (Moore–Penrose-féle) pszeudoinverze az az $A^+$ mátrix, melyre tetszőleges $b$ esetén az $Ax = b$  gyenletrendszer minimális abszolút értékű optimális megoldása $A^+b$ .

# Ortogonalizáció

GS-Ortogonalizáció

# QR felbontás

$A$ teljes oszlopranggú. $A=QR$ QR felbontás, ha $Q$ az $A$-val azonos méretű szemiortogonális (oszlopai vagy sorai ortonormált rendszert alkotnak) és $R$ négyzetes felsőháromszög mátrix, főátlójában pozitív elemekkel.

# ZH

## Sortérbe eső megoldással felírni lineáris egyenletrendszer összes megoldását (rref alkalmazása)

- Hozzuk az egyetlenrendszer bővített mátrixát redukált lépcsős alakra.
- oldjuk meg az egyenletrendszert, parameteresn
- határozzuk meg a nullteret kifeszítő vektorokat
- adjuk hozza ezeket az gyenletrendszerhez és oldjuk meg
- megkapjuk a sortérbe eső megoldást és azzal kifejezve az összeset
	
## LU- vagy PLU-felbontás meghatározása, és azzal egy egyenletrendszer megoldása

LU: $Ax = b, A = LU$ azaz $LUx = b$ megoldása:
- $Ax = b \Leftrightarrow Ly = b, Ux = y$

PLU: $Ax = b \Leftrightarrow PAx = Pb \Leftrightarrow LUx = Pb \Leftrightarrow Ly = Pb, Ux = y$
	
## bázisfelbontás kiszámítása
	
lád fentebb

## altérbe eső merőleges vetület kiszámítása
	
$V$ egy euklideszi tér $W$ egy végesdimenziós altere, melynek $B = \lbrace v_1, v_2 ... v_k \rbrace$ bázisa, $v \in V$. Ekkor $proj_Wv = c_1v_1 + c_2v_k + ... + c_kv_k$, ahol a $c = (c_1, c_2, ... c_k)$  vektor a $Gc=b$ egyenletrendszer megoldása, $G$ a $B$ vektoraihoz tartozó Gram-mátrix és $[b]_i = \left< vi, v \right>$

## pszeudoinverz kiszámítása

Ha a valós $A$ teljes oszlopreangú, akkor $A^+ = (A^TA)^{-1}A^T$, ha teljes sorrangú akkor $A^+ = A^T(AA^T)^{-1}$. Ha $A = BC$, $B$ teljes oszloprangú $C$ teljes sorrangú (bázisfelbontás), akkor $A^+ = C^+B^+$

## GS-ortogonalizáció

A-ra ortogonális B vektorrendszer kiszámíátsa:

Ortonormált rendszer $= \lbrace \frac{b_1}{|b_1|}, \frac{b_2}{|b_2|}, ... \frac{b_k}{|b_k|}   \rbrace$

$b_1 = a_1$ és 

$$ b_{i+1} = a_{i + 1} \sum_{j=1}^i \frac{\left< b_j, a_{i + 1} \right>}{|b_j|^2}b_j $$

## QR-felbontás meghatározása, és abból egyenletrendszer megoldása, vagy  pszeudoinverz kiszámítása

$A=QR$ és $b \in \mathbb{R}^n$, ekkor $Ax = b$ egyenletrendszer egyetlen sortérbe eső optimális megoldása $\hat{v} = R^{-1}Q^Tb$ ami megkaoható a $R\hat v= Q^Tb$ egyenletrendszerből