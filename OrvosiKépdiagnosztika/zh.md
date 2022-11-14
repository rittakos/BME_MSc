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