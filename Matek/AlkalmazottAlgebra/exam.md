# Vizsgafeladatok

[A vizsga anyaga.](of_20fm.pdf)

## Algebrai structúrák

### test 

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

### vektortér, ektorterek direkt összege, lineáris kombináció, bázis, lineáris leképezés, képtér, magtér, altér, affin altér, mátrix 4 kitüntetett altere

A $V$ halmaz $\mathbb{F}$ test fölött vektortér ($V_{\mathbb{F}}$), ha tartalmaz egy $0$-val jelölt elemet és értelmezve van rajta az összeadás és a skaláris szorzás.

$U \subseteq V$ **alter**e $V$-nek, ha nem üres és zárt a vektorösszeadásra és a skalárral szorzásra.

### valós és komplex euklideszi tér, terek izomorfiája

## Mátrixon végzett manipulációk

### redukált lépcsős alak

### determináns

### nyom

### Hermite-féle) adjungált

### pszeudoinverz

### műveletek blokkmátrixokkal

### norma

## Speciális mátrixok definíciói és tulajdonságai

### elemi, permutáló

### ortogonális (hossz-, távolság-, szög-, skalárszorzat-tartás, sajátértékei, determinánsa), [ferdén] szimmetrikus és nilpotens mátrixok (sajátértékei)

### önadjungált, unitér, normális

### pozitív/negatív [szemi]definit, indefinit

### nemnegatív, pozitív, primitív, irreducibilis, reducibilis

### [duplán] sztochasztikus

### átmenetmátrix, [stacionárius] eloszlásvektor

## Egyenletrendszerek megoldhatósága

### megoldása redukált lépcsős alakkal, a minimális abszolút értékű megoldás 

### optimális megoldás és meghatározása normálegyenlettel, QR-felbontással, pszeudoinverzzel (lineáris és polinomiális regresszió) 

### homogén|inhomogén egyenletrendszek megoldásainak terei

## Hasonlóság [ortogonális] diagonalizálhatóság

### hasonlóságra invariáns tulajdonságok (rang, nullitás, determináns, nyom, karakterisztikus és minimálpolinom, sajátértékek és azok algebrai és geometriai multiplicitásai) 

### diagonalizálhatóság feltételei 

### diagonalizálhatóság mint a tér sajátalterek direkt összegére bonthatósága

### ortogonális diagonalizálhatóság szükséges és elégséges feltétele 

### unitér diagonalizálhatóság szükséges és elégséges feltétele 

### ortogonális|unitér triangularizálhatóság: Schur-felbontás

### Jordan-féle normálalak (a tér sajátalterek helyett invariáns alterek direkt összegére való bonthatósága) 

### ortogonális diagonalizálhatóság bázispárban = SVD

## Kvadratikus alak

### őtengelytranszformáció, definitség, [fő]minor, vezető főminor = sarokaldetermináns, kongruencia, tehetetlenség

## Mátrixfelbontások

### bázisfelbontás, LU-, PLU-, QR-, Schur-, saját-, spektrál-, polár-, Jordan-felbontás, SVD 

### pozitív [szemi]definit mátrixok faktorizációi, 

### pozitív szemidefinit mátrix egyetlen pozitív szemidefinit négyzetgyöke, Cholesky-felbontás

## Gyakorlati feladatok

### sortérbe eső (min.absz.értékű) megoldás meghatározása egyenlet hozzávételével és pszeudoinverzzel 


### LU-felbontás és használata egyenletrendszer megoldásához 

### áttérés másik bázisra 

### lineáris transzformáció mátrixa (vetítés, tükrözés, forgatás, Givens-forgatás, Householder-tükrözés) 

### altérre való merőleges vetítés mátrixa 

### egyenletrendszer optimális megoldásainak kiszámítása 

### pszeudoinverz kiszámítása (teljes rangú mátrixokra és ilyenek szorzatára) 

### Gram–Schmidt-ortogonalizáció

### QR-felbontás G–S-ortogonalizációból 

### egyenletrendszer megoldása QR-felbontással 

### sajátfelbontás, spektrálfelbontás, algebrai és geometriai multiplicitás kiszámítása 

### definitség eldöntése 

### pozitív szemidefinit és definit mátrixok faktorizációi, Cholesky-felbontás 

### szinguláris érték, jobb és bal szinguláris vektorok meghatározása, szinguláris felbontás 

### legjobb 𝑘-rangú közelítés

## Nagyobb súllyal szereplő feladatok

### vektornormák és mátrix 1-, 2- ∞- és Frobenius-
normájának kiszámítása
- 1-Norma: legnagyobb abszolút oszlopösszeg
- $\infty$-norma: legnagyobb abszolút sorösszeg
- 2-norma: legnagyobb szinguláris érték, vagyis az $A^T A$ legnagyobb sajátértékének négyzetgyöke
- Frobenius-norm: elemek négyzetösszegének négyzetgyöke
- $||A||_a = \max_{||x||_a=1}||Ax||_a$

### Jordan bázis keresése 3x3 mátrixokra

A mátrix esetén Jordan láncnak nevezzük azt a sorozatot, ahol $xxx$ és $xxx$ A sajátvektora.

### Jordan-normálalak meghatározása

### Mátrixfüggvény a Jordan-alakból és Hermite polimomból

### Perron-vektorok és a Perron–Frobenius tételekben szereplő mátrixhatárértékek kiszámítása

### nemnegatív mátrix reducibilitásának és primitívségének eldöntése

Írjuk fel azt a gráfot amiben annyi csúcs van ahány sora/oszlopa (négyzetes) van a mátrixnak. Legyen irányított él az i. és j. csúcs között, ha mátrix i. sorának j. eleme nem 0.

Ekkor a mátrix:
- Irreducibilis, ha a gráfban bármely két csúcs között vezet irányított út
- Reducibilis: ha nem irreducibilis
- Primitív: ha irreducibilis és a főátlójában van pozitív elem. A hatványokat is kell vizsgálni. Akorr van a mátrix k. hatványának főátlójában pozitív elem, ha a gráfban van k hosszú kör

## Kiemelt tételek

### lineáris algebra alaptétele

Dimenziótétel: Bármely A ∈ $F
^{m×n}$ mátrix esetén a sortér dimenziójának
(=rangjának) és a nulltér dimenziójának (=nullitásának)
összege n. Képlettel:
$dim(S(A)) + dim(N (A)) = n$.


Minden valós mátrix sortere és nulltere merőleges kiegészítő
alterei egymásnak.

### legjobb közelítés tétele

### diagonalizálhatóságra valamint az ortogonális és unitér diagonalizálhatóságra vonatkozó feltételek

### Sylvester-féle tehetetlenségi törvény

### Cayley-Hamilton tétel

### Jordan-féle normálalak

### Perron- és Perron–Frobenius-tételek









# ZH

## Sortérbe eső megoldással felírni lineáris egyenletrendszer összes megoldását (rref alkalmazása)

- Hozzuk az egyetlenrendszer bővített mátrixát redukált lépcsős alakra.
- oldjuk meg az egyenletrendszert, parameteresn
- határozzuk meg a nullteret kifeszítő vektorokat
- adjuk hozza ezeket az gyenletrendszerhez és oldjuk meg
- megkapjuk a sortérbe eső megoldást és azzal kifejezve az összeset

$$ x+y+z+w=3 $$
$$ x+y-z-w=1 $$

A bővített mátrix és redukált lépcsős alakja:

$$ \begin{vmatrix}
1 & 1 & 1 & 1 & 3 \\
1 & 1 & -1 & -1 & 1
\end{vmatrix} \rightarrow  
\begin{vmatrix}
1 & 1 & 0 & 0 & 2 \\
0 & 0 & 1 & 1 & 1
\end{vmatrix} $$

Oldjuk meg az egyenletrendszert:

$$ \begin{vmatrix} x\\ y\\ x\\ w\\ \end{vmatrix}  = \begin{vmatrix} 2-s\\ s\\ 1-t\\ t\\ \end{vmatrix} = \begin{vmatrix} 2\\ 0\\ 1\\ 0\\ \end{vmatrix} + \begin{vmatrix} -1\\ 1\\ 0\\ 0\\ \end{vmatrix}s + \begin{vmatrix} 0\\ 0\\ -1\\ 1\\ \end{vmatrix}t $$

A nullteret a $(-1,1,0,0)$, $(0,0,-1,1)$ vektrotok feszítik ki.

Ezekkel egészítsük ki az egyenletrendszert:

$$ \begin{vmatrix} 
1 & 1 & 0 & 0 & 2\\ 
0 & 0 & 1 & 1 & 1\\ 
-1 & 1 & 0 & 0 & 0 \\ 
0 & 0 & -1 & 1 & 0\\ \end{vmatrix} \rightarrow
\begin{vmatrix} 
1 & 0 & 0 & 0 & 1\\ 
0 & 1 & 0 & 0 & 1\\ 
0 & 0 & 1 & 0 & \frac12 \\ 
0 & 0 & 0 & 1 & \frac12\\ \end{vmatrix} $$

vagyis a sortérbe eső megoldás a $(1, 1, \frac12, \frac12)$, az összes megoldás:

$$ \begin{vmatrix} x\\ y\\ x\\ w\\ \end{vmatrix}  = \begin{vmatrix} 1\\ 1\\ \frac12\\ \frac12\\ \end{vmatrix} + \begin{vmatrix} -1\\ 1\\ 0\\ 0\\ \end{vmatrix}s + \begin{vmatrix} 0\\ 0\\ -1\\ 1\\ \end{vmatrix}t $$
	
## LU- vagy PLU-felbontás meghatározása, és azzal egy egyenletrendszer megoldása

LU: $Ax = b, A = LU$ azaz $LUx = b$ megoldása:
- $Ax = b \Leftrightarrow Ly = b, Ux = y$

PLU: $Ax = b \Leftrightarrow PAx = Pb \Leftrightarrow LUx = Pb \Leftrightarrow Ly = Pb, Ux = y$
	
## bázisfelbontás kiszámítása
	
lásd fentebb

$$ A = \begin{vmatrix} 
1 & 2 & 3 & 4 & 5\\ 
2 & 4 & 8 & 6 & 2\\ 
1 & 2 & 7 & 0 & -11 \\ \end{vmatrix} $$

A redukált lépcsős alakban:

$$ A = \begin{vmatrix} 
1 & 2 & 0 & 7 & 17\\ 
0 & 0 & 1 & -1 & -4\\ 
0 & 0 & 0 & 0 & 0 \\ \end{vmatrix} $$

ebből:

$$ R = \begin{vmatrix} 
1 & 2 & 0 & 7 & 17\\ 
0 & 0 & 1 & -1 & -4\\ \end{vmatrix} $$

$$ B = \begin{vmatrix} 
1 & 3 \\ 
2 & 8 \\ 
1 & 7 \\ \end{vmatrix}  $$

$$ A = BR $$

## altérbe eső merőleges vetület kiszámítása
	
$V$ egy euklideszi tér $W$ egy végesdimenziós altere, melynek $B = \lbrace v_1, v_2 ... v_k \rbrace$ bázisa, $v \in V$. Ekkor $proj_Wv = c_1v_1 + c_2v_k + ... + c_kv_k$, ahol a $c = (c_1, c_2, ... c_k)$  vektor a $Gc=b$ egyenletrendszer megoldása, $G$ a $B$ vektoraihoz tartozó Gram-mátrix és $[b]_i = \left< vi, v \right>$

## pszeudoinverz kiszámítása

Ha a valós $A$ teljes oszloprangú, akkor $A^+ = (A^TA)^{-1}A^T$, ha teljes sorrangú akkor $A^+ = A^T(AA^T)^{-1}$. Ha $A = BC$, $B$ teljes oszloprangú $C$ teljes sorrangú (bázisfelbontás), akkor $A^+ = C^+B^+$

## GS-ortogonalizáció

A-ra ortogonális B vektorrendszer kiszámíátsa:

Ortonormált rendszer $= \lbrace \frac{b_1}{|b_1|}, \frac{b_2}{|b_2|}, ... \frac{b_k}{|b_k|}   \rbrace$

$b_1 = a_1$ és 

$$ b_{i+1} = a_{i + 1} - \sum_{j=1}^i \frac{\left< b_j, a_{i + 1} \right>}{|b_j|^2}b_j $$

## QR-felbontás meghatározása, és abból egyenletrendszer megoldása, vagy  pszeudoinverz kiszámítása

QR felbontás meghatározásához GS-ortogonalizációval meghatározható Q.

$A=QR$ és $b \in \mathbb{R}^n$, ekkor $Ax = b$ egyenletrendszer egyetlen sortérbe eső optimális megoldása $\hat{v} = R^{-1}Q^Tb$ ami megkaoható a $R\hat v= Q^Tb$ egyenletrendszerből