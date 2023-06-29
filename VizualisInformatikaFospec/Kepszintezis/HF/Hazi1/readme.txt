Rittgasszer Ákos, Z8WK8D

Kiindulásnak a 2. labor eredményét használtam.

Választott feladatok:
 - Wrap shading
 - Shadow map

 Wrap shading

 w egy uniform float változó 0 és 1 között. 
 Ennek és a f(θ, w) = (cos(θ) + w)/(1 + w) képlet használata segítségével
 írtam meg a shadert.

 Shadow Map

 A megvalósítás logikája, hogy a fényforrásból kiindulva kiszámítjuk a 
 fragmentek mélységét. Ennek a mélységét. Ez azt jelenti, hogy megnézzük 
 mik vannak árnyékban, vagyis a fényforrás és közöttük helyezkedik el másik objektum.
 Ennek a pixel shaderben minden pixelre el tudjuk dönteni, hogy árnyékban van-e.
 Ha igen, sötétebben rajzoljuk ki.

 A shadow fragment és vertex shader célja, hogy kiszámolja magát a shadow map-et 
 mint textúrát. Ezt kellene továbbadni az objektumok rajzolását végző shaderenek,
 hogy ahol van árnyék, ott legyen sötétebb a kép.

 Sajnos nem sikerült összeraknom működőképes állapotba. Nem tudtam a shadow shader-ek
 által meghatározott textúrát felhasználni a végső rajzoláskor.
 Igyekeztem a shadereket megírni de kipróbálni nem tudtam a kotlin kódok átírásával.
 Visszaállítottam egy olyan állapotot amikor látható az első feladat működése,
 az ezt akadályozó kódrészeket kikommenteztem.