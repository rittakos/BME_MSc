# Minta ZH

[Feladatok](http://home.mit.bme.hu/~hadhazi/Oktatas/OKD20/mintazh.pdf)

## 1

## 2

## 3

## 4

## 5

## 6

# Ellenőrző kérdések

### Vázlatosan ismertesse egy röntgen alapú képalkotó berendezés felépítését! Hogyan keletkezik a röntgen foton, mi határozza meg az energiáját? Mit nevezünk kollimátornak? Mit mond ki az inverz négyzetes törvény? Vázlatosan ismertesse, hogy miből áll egy röntgen detektor? 

**Fotoelektromos kölcsönhatás** során a beérkező foton kiüt egy elektront, ami energiát ad le foton (röntgen) formájában. Energiája a **Beer-Lambert törvény** alapján függ a belépő intenzitástól, az anyagra jellemző lineáris csillapítási együtthatótól és az amyag vastagságától.

**Kollimátor a sugárnyaláb szélességét korlátozza**.

Inverz négyzetes törvény: Minél messzebb vagyunk a sugár kiindulási pontjától, annál kevesebb sugár halad át egységnyi területen. Az **intenzitás fordítottan arányos a távolság négyzetével**.

Röntgen detektor részei: Szcintillátor, ami a röntgen sugarakat látható fénnyé alakítja. Pixelek, amik érzékeléséhez három darab fotodióda szükséges.

### Értelmezze a lentebbi összefüggést! Saját szavaival adj meg, hogy mit modellez? Monokromatikus röntgensugár esetén hogyan egyszerűsödik az összefüggés? Hogy nevezzük azt az artifaktot, mely abból ered, hogy hibásan monokromatikusnak feltételezzük a röntgensugarat?

$$ \int {\int {I_0(E) * exp(- \mu(x(s), E))}ds}dE $$

A sugár kilépő intenzitása függ  a belépő intenzitástól (energiafüggő), az anyag vastagságától és a csillapítási együtthatótól (energiafüggő).

Monokromatikus esetben $I = I_0 \cdot e^{-x\mu}$

Szóródás

### Mi történik foto-elektromos kölcsönhatás, illetve Compton szóródás esetén? Milyen fizikai anyagok milyen jellegű interakcióit írják le ezek a jelenségek? Értelmezze a lentebb megadott összefüggést! Ez az előbb felsorolt két hatás közül melyiket írja le? Leginkább mely változótól függ ezen kölcsönhatás bekövetkezésének a valószínűsége? Mely energiatartományokban domináns a fentebb megnevezett két kölcsönhatás?

$$ E_f = E_{he} + E_{eke} $$

A fotoelektromos jelenség során egy foton ütközik egy belső elektron hélyon levő elektronnal és kiüti azt, a helyére lépő kintebbi elektron energiát ad le foton formájában. Compton szóródáskor az ütközés külső hélyon történik és minél nagyobb a szoródás szöge, annál több elektront veszít a foton.

Foton és elektron rugalmatlan ütközését. A fotoelektromos kölcsönhatást jellemzi

A foton energiája megegyezik a kilökött elektron mozgási és töltési energiájával.

Annál gyakoribb minél nagyobb rendszámú az elem és minél lassabb a foton.

Alacsonyabb energiatartományokban.

### Mi a szcintilláció lényege? Milyen esetekben van rá szükség? Nevezzen meg egy konkrét ilyen esetet! Mi a sötétáram, valamint az erősítéskorrekció lényege? Mit nevezünk bakscatternek?

A röntgen sugarakat látható fénnyé alakítja. 

Ha a detektor nem képes a magas energiájú röntegn sugarakat érzékelni. 

Röntgen vizsgálatkor. 

A sötétárom amikor fény érzékelés nélkül is folyik áram a diódában.

Backscatter, amikor a visszaverődő fotonok rossz helyen detektálódnak.

---

### Mit jelent a fény kettős természete (hullámmozgás és kvantumelméleti megközelítés). A fénynek, mint elektromágneses sugárzásnak milyen tulajdonságait ismeri? Mitől függ egy foton energiája? Ez mit befolyásol orvosi képalkotás során?

Egyszerre hullám és részecske. 

Sebessége állandó, polarizálható.

Energiája a frekvenciájától függ. 

Energiája meghatározza hogyan lép kölcsönhatásba atomokkal, fotoelektromos kölcsönhatás.

### Ismertesse a fényérzékelés folyamatát! Hogyan működnek a félvezetők? Mit jelentenek az alábbi fogalmak: vegyértéksáv, vezetési sáv, tiltott sáv, lyuk, elektron, N típus, P típusú félvezető? Hogyan épülnek fel és hogyan működnek a fényérzékeny MOS kapacitások?

Fény &rarr; fotodióda &rarr; kondenzátor &rarr; analóg erősítő &rarr; A/D átalakító &rarr; digitális feldolgozás

Félvezető: A vezetési sáv (elektron többlet) és a vegyértéksáv (lyuk többlet) között mozoghatnak a elektronok. N típusúnál több az elektron, P típusúnál több a lyuk.

Fényérzékeny MOS kondenzátor: elektróda, szigetelő, P félvezető és N félvzető alkotja. Foton hatására egy elektron és egy lyuk keletkezik.

### Hogyan épülnek fel és hogy működnek a CCD érzékelők? Mit nevezünk szcintillációnak és mikor van rá szükség? Hogyan működnek és hogyan épülnek fel a látható fotonoknál nagyobb energiájú fotonokra (pl. uv, röntgen, gamma sugarak) érzékeny detektorok?

A CCD fényérzékeny MOS kondenzátorokból áll. Egy pixelhez 3db kondenzátor szükséges. A kondenzátorhármasok egy négyzetrácson helyezkednek el.

Szcintillátort akkor használunk ha láthatalan sugárból szeretnénk látható fényt kapni. Működése a fotoelektromos kölcsönhatáson alapul.

A nagy energiájú fotonok úgy detektálhatóak, hogy egy szcisztillátor mögé helyezzük a detektort.



### Mit nevezünk képalkotás során inherens zajnak. Mi okozza? Mekkora a „mértéke”? Mit értünk egy képalkotó rendszer dinamika tartománya alatt? Értelmezze az alábbi összefüggést: $D = log_2((FWC / P)/(P*RN +ADCN))$ . Tipikusan milyen zajok terhelik a képalkotás során rögzített képeket.

Inherens zajt az okozza, hogy a fotonok eloszlása nem egyenletes sem az érzékelú felületén, sem az időben Értéke $Q$ vagy $\sqrt{Q}$ diától függ.

Dinamikatartomány a kép legvilágosabb és legsötétebb pixel közötti tartomány.

A képlet azt határozza meg, hogy a dinamikatartomány hány biten ábrázolható. 

Zajok:
- kiolvasasi zaj
- analog-digitalis konverzio zaja
- mos kapacitas hiba
- szisztematikus zaj

### Hogyan működik a Graphics Interchange Format alapú képtárolás? Ismertesse a Portable Network Graphics formátum során alkalmazott tömörítési eljárás főbb lépéseit!

GIF:
- 8 bites képek
- LZW veszteségmentes tömörítés:
  - szótárat inicializálunk minden lehetséges pixel intenzitással
  - kikeressük a kódolni kívánt sorozat azon leghosszabb eddig még nem kódolt prefixét (W), mely már szerepel a szótárban (k kóddal)
  - hozzátoldjuk a tömörített kép végéhez k-t, majd bővítjük a szótárat [W|a]-val, ahol a a tömörítendő bitfolyam W utáni első eleme
  - második lépés ismétlése
- animált is lehet

PNG tömörítés:
- szűrés:
  - predikciót hajtunk végre minden pixelre és az eltérést a jósolt és valós érték között tároljuk. A második lépésben ezt tömörítjük
- Deflate:
  - LZ77, 
  - Huffman kódolás

### Ismertesse a Joint Photographic Experts Group formátum tömörítő eljárásának főbb lépéseit. Milyen melléktermékeket okozhat ez a fajta tömörítő eljárás?

JPEF tömörítés:
- színtér transzformáció, ahol RGB-ből Y'CrCb-be konvertál.
- színcsatornák alulmintavételezése, mivel a fényerőre sokkal érzékenyebb az emberu szem
- blokkosítás, ahol 8x8-as diszjunk blokkok jönnek létre, ha szükséges extrapolálás után
- DCT (diszkrét koszinusz transzformáció), blokkonként, intenzitások 0 középpontú skálázása után:
 
  $$ f(u, v) = \alpha(u, v) * cos \left[ {{(2x + 1)u * \pi} \over {16}} \right] * cos \left[ {{(2y + 1)v * \pi} \over {16}} \right] $$

- kvantálás:

  - $$  B_{(i, j)} = round \left( {{DCT\{I_{(i, j)}\}} \over {Q}} \right) $$

    - $B_{(i, j)}$: kvantálás utáni együtthatók
    - $I_{(i, j)}$: $(i, j)$-edik blokkja az bemeneti képnek
    - $Q$: szabványban meghatározott kvantálási mátrix skakárszorosa
- kódolás, amikor az együtthatókat cikk-cakk trajektória (pálya) mentén sorosítja, majd ezen futáshossz és Huffman kódolást alkalmaz.


melléktermékek:
- ringing effektus, ami a meredek átmenető aluláteresztés. 
- blokkosodás, amit a blokkonkénti tömörítés okoz és mértéke arányos a Q amplitúdójával. 
- elszíneződés, ami a Cr és Cb túlzótt alulmintavételezése miatt alakul ki. 
- elmosás, ami a tömörítés fokától függ.

### Ismertesse a DICOM szabvány képtárolásának főbb jellemzőit, valamint a szabvány általánosabb jellegét!

A szabványt leíró konténerek tag-ekből állnak. Egy képet egy tag-gel jelölünk, amihezt tartozik egy másik tag, ami megmondja a formátumát a képnek. Ezek mellet van lehetőség metaadatok tárolására is.

A szabvány meghatározza a képek archiválásának módját (hálózat felépítése, protokol). Ennek betartása lehetővé teszi, hogy a képek ne vesszenek el és könnyen össze lehessen hasonlítani őket.

---

### Mi a $h(t)$ súlyfüggvényű LTI rendszer $s(t)$ gerjesztő jelre adott válasza (és a válaszfüggvény spektruma)? Mi az LTI rendszerek identifikációja során a feladat és ennek megvalósítása milyen módszerekkel lehetséges (adjon 3 példát az identifikáció megvalósítására, az egyes példák esetén térjen ki az adott módszer realizálhatóságára is)? 

válasz: $s*h$, spektruma ennek Fourier transzformáltja.

Identifikáció során a rendszer átvieteli függvényének meghatározása a cél. Módszer az egységimpulzus gerjesztése, egységugrás gerjesztése, szinuszos vizsgálójellel, bemeneti zajjal...

### Mit definiál egy képalkotó rendszer esetén a Point Spread Function (PSF) és a Modulation Transfer Function (MTF), ezek milyen kapcsolatban állnak a képalkotó rendszer súlyfüggvényével, illetve átviteli függvényével. Formálisan ismertesse az általános képalkotás (3D objektumból 2D projekcióba képző) megfigyelési modelljét (interpretálja a modell tagjainak a jelentését)!

PSF, a beérkező részecskék eloszlását határozza meg. MTF olyan átviteli függvény ami H/H(0,0), H az atviteli függveny. Az előbbi a súlyfüggvény.

$$g(x,y) = \int_{-\infty}^{\infty}{\int_{-\infty}^{\infty}{\int_{0}^{\infty}{h(x,y;\alpha,\beta,\gamma) \cdot f(\alpha,\beta,\gamma)}d\gamma}d\alpha}d\beta + \eta(x, y) $$

- $f(\alpha,\beta,\gamma)$: gerjesztés
- $\eta(x, y)$: additív zaj
- $h(x,y;\alpha,\beta,\gamma)$: sújfüggvény (PFS)


### Lineáris, eltolás invariáns képalkotó rendszerek esetén definiálja az effektív felbontás fogalmát! Hogyan mérhető a rendszer súlyfüggvényének (PSF) ismeretében? Adjon példát foton fluxusának mérésén alapuló képalkotó rendszerek (pl. konvencionális fényképezőgép, röntgen detektor, stb.) esetén az effektív felbontás meghatározására (milyen fantomokkal / vizsgálóábrákkal történik a mérés)! Mi az effektív felbontáson, mint metrikán alapuló minősítés legjelentősebb hiányossága?

xxx

### Definiálja a jel/zaj viszony (SNR) fogalmát (általános jelfeldolgozási szemszögből). Képek esetén mi az SNR definíciója? Definiálja a kontraszt/ zaj arányt (CNR) és részletesen fejtse ki, hogy képek esetén hogyan számítandó. Alkalmazható-e a CNR nemlineáris rendszerek minősítésére (válaszát indoklással támassza alá)?

$SNR = 10 \log_{10}(P_{signal} / P_{noise})$

Képalkotó rendszerek esetén $SNR = \mu / std()$

$CNR$

Képeknél kiválasztunk két területet amik között kontrasztot vizsgálunk. Plusz egy referencia területet. $CNR = \frac{|\mu(A) - \mu(B)|}{std(N)}$

Használható nemlineáris rendszerekre is.

### Milyen valószínűségi folyamattal modellezhető a foton sugárzás folyamata. Definiálja az inherens zaj fogalmát. Ideális detektor által rögzített kép jel / zaj aránya (SNR) hogyan viszonyul a felületét érő sugárzás jel / zaj arányához (SNR), és mi a pontos értéke, ha a detektor egy érzékelőelemébe átlagosan Q foton csapódik?

Véletlen Poisson folyamattal.

A fotonok eloszlása nem egyenletes sem az időben, sem az érzékelő felületén, ez okozza az inherens zajt.

Megegyezik. 

xxx

### Definiálja a zaj teljesítmény spektrum (NPS), a normalizált zaj teljesítmény spektrum (NNPS), illetve a zaj ekvivalens kvantum (NEQ) fogalmát mind saját szavával, mind formálisan! Ezen mérőszámok szerinti összehasonlításnál milyen megkötéssel kell élnünk a vizsgálósugárzás dózisára (fotonjainak számára)? Mi a Detektált kvantum hatékonyság (DQE) formális definíciója és interpretációja (ez utóbbit elég szövegesen megadni)?

xxx