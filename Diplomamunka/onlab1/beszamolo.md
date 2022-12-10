# Önlab1 beszámoló

## Cím dia - 1

Üdvözlök mindenkit! Feladatomul egy dungeon generátort választootam.

## Feladat - 2

A feladat célja egy szobákból álló rendszert összerakni. Az egyes szomszédos szobák között lehet ajtókat nyitni. Ezek az ajtók egy útvesztőt alkotnak. Az egész rendszert nevezzük Dungeon-nak, magyarul kazamatának. A feladat érdekessége abban rejlik, hogy mind az egész alaprajza mind a szobák alakja tetszőleges konvex sokszög alakú lehet.

## Részfeladatok - 3

A generálás három részre bontható. Ezek a szobákra bontás, az útvesztő meghatározása ajtók lehejezésével és a szobák berendezése akadájokkal.

A generáló algoritmuson kívül még más eszközök is részei feladatnak. 

Az egyik ilyen egy megjelenítő és CAD program. Ez arra használható, hogy a generált eredményt grafikus formában is meg tudjuk jeleníteni. Képes arra is, hogy felparaméterezzük az algoritmust és megadjuk grafikusan az alaprajzát.

Másik részfeladat, hogy egy generált dungeont megjelenítsünk egy játékmotor segítségével.

## Tervezés - Adatszerkezet - 4

A tervezési fázis első lépéseként meghatároztam milyen fogalmakat kell modelleznem. Ezek a foglamak meghatározás és fontos adatainak kinyerése elengedhetetlen ahhoz, hogy meghatározzuk a megfelelő adatszerkezetet.

Mindenképp fontos számunkra az alaprajz. Ez szobákból és ajtókból áll elsosorban. Fontos, hogy tisztában legyünk, hogy melyik szobák szomszédosak, ez segít a megjelenítésben.

A szobákról ismerendő legfontosabb információk az alakjuk, a helyük és a berendezésük.

A fogalmak tisztázása során két kulcsfontosságú adatszerkezeti fogalom merül fel. Ezek a poligon és a gráf.

## Tervezés - modulok - 5

A tervezés során felbontottam a feladatot modulokra. Ezek a modulok mindegyik egyetlen, jól elkülönülő felelősséggel bír. Ez abban segít, hogy ne keveredjenek a fogalmak egymással.

A matematikai és geometriai modul felelősségei a nevükből adódnak. Az általuk tartalmazott fogalmakkal képesek az algoritmusok dolgozni.

A Base modul elsősorban a fejlesztés és a hibakeresés segítéséhez készült. Itt olyan általános funkcionalitások kapnak helyet mint például a logger.

A DungeonGenerátor a legmagasabb szintű modul. Ez leginkább a kényelmesebb használatot és az egységes interface-t biztosítja.

## Fejlesztés - általában - 6

A fejlesztés kezdetekor lerögzítettem néhány alapelvet amit szem elött tudok tartani. A választott nyelv a c++.

Úgy döntöttem, hogy először mindenhez saját implementációt fogok írni. Azonban ha ezek fenntartása túl sok munka lenne, vagy nehezen implementálható tudásra lenne szükségem, akkor lecserélem valamilyen külső könyvtárra.

Mivel a fejlesztés során rengeteg olyan kérdés merülhet fel amire nem gondoltam igyekszem arra figyelni, hogy a kód minél könnyebben kiegészíthető legyen. Ebben az OO tervezési elvek nyújtanak segítséget. Erre egy példa, hogy a saját implementációimat elrejtem egy-egy wrapper osztály mögé, ami lehetővé teszi az egyszerű lecserélésüket.

## Fejlesztés - modulok - 7

A fejelsztés alapvetően modulonként történik. Ettől abban az esetben térek el, hogyha valamelyik alacsonyabb szintű modulból hiányzik funkcionalitás.

Fontos, hogy mindegyik modul felelőssége jól meghatározott legyen. Amennyiben elmosódik ez a felelősség szükséges újragondolni a funkcionalitások helyét.

A kényelmes használathoz fontos, hogy minden modul egy tiszta interface-szel rendelkezzen. Ehhez csak ha nagyon muszáj akkor szabad nyúlni, ugyanis ez más modulokra is hatással van. Ehhez az instabil részeket célszerű lehet wrapper osztályokba csomagolni.

## Fejlesztés - szerkezet - 8

A már említett mdóodulok mindegyik önálló fordítási egységként kezelendő. Ezek statikus könyvtárként használhatóak más modulokban. Fontos, hogy ne sértsük meg a modulok között  felállított függőségeket, mivel ez összezavarja a program szerkezetét.

## Fejlesztés - folytatás - 9

A fejlesztés első lépése a generáló algoritmus elkészítése. Ennek folytatásakor várhatóan szükség lesz refaktorálásokra.

Amennyiben ez már biztosít egy alapvető funkcionalitást, akkor lehet elkezdeni foglalkozni a megjelenítőkkel.

## Tesztelés - 10

Az elsődleges tesztelés modulonként történik Unit tesztek segítségével. Ezek célja a jól működő funkcionalitás fenntartása.

Mivel az algoritmis véletlenszerű lesz, ezért magas szintű tesztelése macerásabb. Erre az elsődleges eszköz a megjelenítő. Ennek segítségével elsősorban a már nagyjából működő algoritmust lehet finomhangolni.

## Jövőben - 11

Alapvetően a fejlesztés még kezdeti stádiumban van. Ennek befelyezése után lehet hosszútávú továbbfejlesztésekben gondolkodni. Ilyen lehet új algoritmusok bevezetése pédául az útvesztő generálásához. Egy másik irány, a szerkesztő program megvalósítása webes felületen. Ha pedig a generált rendszert szeretnék bonyolítani, akkor egy lehetőség, ha az eddig 2Ds kazamatát kiterjesztjük 3 dimenzióba.