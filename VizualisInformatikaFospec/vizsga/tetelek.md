# Tételek

2022 ősz

---

## T1. Röntgen képalkotás: Ismertesse a röntgen alapú képalkotó készülékek felépítését (mi található egy röntgencsőben, mi a kollimátor szerepe, hogyan épül fel egy röntgen detektor)! Mi a foto-elektromos kölcsönhatás, illetve mit értünk röntgen fotonok Compton szóródása alatt? Milyen energiaspektrummal jellemezhető a röntgen sugárzás? Adja meg a Beer-Lambert törvényt, és értelmezze az összefüggést! Mi a sugárkeményedés, hogyan kompenzálható és miért jelent problémát? 

[kidolgozás](t1.md)

--- 

## T2. Általános képalkotás: Mit nevezünk elektromágneses sugárzásnak? Milyen jellemzőkkel bír? Mit nevezünk hangnak? Vázlatosan ismertesse a félvezetők felépítését, sávszerkezetét! Hogy épül fel, és hogyan működik egy MOS kondenzátor? Hogyan épülnek fel a CCD érzékelők? Mi a szcintilláció? Milyen veszteséges és veszteségmentes képtömörítő eljárásokat ismer? Röviden ismertesse őket! Mit értünk a megvilágítás inherens zaja alatt? Milyen eloszlású zajról beszélhetünk ebben az esetben? Ez milyen érzékelő típusnál használható fel közvetlenül?

[kidolgozás](t2.md)

--- 

## T3. Lineáris rendszerelmélet: Definiálja egy lineáris rendszer impulzus válaszát, illetve a dirac-delta függvényt! Mit értünk LTI rendszer alatt? Mit értünk ez rendszer identifikációja alatt? Adjon példát LTI rendszer identifikációjára! Mi egy rendszer PSF, illetve MTF leírója? Mi a képalkotás általános (3D -> 2D) modellje? Mit értünk effektív felbontás alatt? Mi az SNR, illetve a CNR. Mi az NPS, NNPS, NEQ, DQE minősítők definíciója, illetve azok értelmezése? 

[kidolgozás](t3.md)

--- 

## T4. Inverz problémák: Mit étünk 2D inverz probléma alatt? Ennek megoldására milyen eljárásokat ismer? Definiálja általánosan és hasonlítsa össze a ML, illetve a MAP becsléseket! Az előzőleg felsorolt eljárások mely becsléstípusba sorolhatóak? Hasonlítsa össze a direkt dekonvolúciót, a csonkolt dekonvolúciót, a Wiener inverz szűrést, valamint a RL eljárást! 

[kidolgozás](t4.md)

--- 

## T5. Vezesse le, hogy egy folytonos jel véges számú mintát eredményező matematikai mintavételezése során hogyan változik/változhat a jel, illetve spektrumának az alakja? Milyen kapcsolatban áll egymással a Folytonos FT, a DTFT, a DFT, a DFS, illetve a Folytonos FS? Vezesse le a Nyquist Shannon mintavételi törvényt! Mit értünk koherens mintavételezés és mit értünk ablakozás alatt? Mit mond ki a konvolúciós tétel, és miként alkalmazható gyakorlati problémák megoldására? 

[kidolgozás](t5.md)

--- 

## T6. Mit értünk egy kép hisztogramja, illetve kontrasztja alatt? Adjon egy algoritmust egy kép hisztogramjának kiegyenlítésére! Az eljárás növeli, vagy csökkenti a bemeneti kép kontrasztját? Mikor érdemes adaptív hisztogram módosítást végezni? A zajszűrés milyen módszereit ismeri? Melyiknek mi a jellemzője, mikor alkalmazandóak? Mi a KLT (PCA) transzformáció lényege? Hogyan lehet képek szűrésére alkalmazni? Mi a homomorfikus, illetve mi a rank szűrés milyen esetekben célszerű ezeket használni? Miben térnek el általánosan az adaptív szűrők a konvencionális LTI szűrőktől? Mikor érdemes adaptív szűrőket használni (nevezzen is meg egy konkrét esetet)? Milyen élkiemelő szűréseket ismer? Mi a legfőbb probléma a zónás szűrésekkel? 

[kidolgozás](t6.md)

--- 

## T7. Mit értünk szegmentálás alatt? Milyen szegmentáló módszereket ismer, hogyan csoportosítaná őket? Mi az EM eljárás lényege és hogyan alkalmazható szegmentálásra? Mi a régió alapú szegmentálás definíciója, milyen eljárásokat ismer a megvalósítására? Mit értünk egy kép textúrája alatt? Mit nevezünk ko-okkurencia mátrixnak? Hogyan definiálná ez alapján egy régió homogenitását, kontrasztját? Mi a Hough transzformáció, milyen problémák esetén alkalmazná?

[kidolgozás](t7.md)

--- 

## T8. Mi az ASM / AAM eljárások lényege, mik a fő lépései? Mi a PCA lényege? Milyen céllal használjuk a PCA, illetve a Prokrusztész analízis eljárásokat ASM alapú szegmentáció esetén? Milyen közelítéseket alkalmaz az ASM eljárás? Mi a Fourier sor alakmodell lényege? Foglalja össze az ACM Snake eljárás lényegét! Miért szükséges a belső energia definiálása Snake esetén? Milyen gyakorlati nehézségek léphetnek fel az eljárás használata során és ennek kompenzálására milyen módszereket ismer? Mi a GVF regularizáció szerepe? Mi a kétfázisú szegmentálás lényege? 

[kidolgozás](t8.md)

--- 

## T9. Orvosi képdiagnosztika területén mikor és milyen célból alkalmazunk regisztrációs eljárásokat? Mi a merev transzformáció? Miben különbözik tőle az affin és a projektív transzformáció? Mit értünk elasztikus transzformáció alatt? Milyen előnyökkel, és milyen hátrányokkal bír a jellemző alapú regisztráció az intenzitás alapú regisztrációs eljárásokhoz képest? Mi az ortogonális Prokrusztész transzformáció? Miért és milyen torzítások esetén alkalmazható Fourier transzformáció alapú regisztráció? Mi két egymáshoz regisztrált kép együttes hisztogramjának a definíciója? Mit olvasható le ilyen hisztogramokról? 

[kidolgozás](t9.md)

--- 

## T10. A Beer-Lambert törvény alapján röntgen rekonstrukciós eljárásoknak mi az első lépése, és miért szükséges ez a lépés? Definiálja formálisan a 2D Radon transzformációt! Mit mond ki a Fourier vetítősík tétel, hogyan alkalmazható rekonstrukciós eljárások esetén? Tömören ismertesse az FBP eljárás működését, és érveljen az eljárás helyessége mellett! FBP esetén hogyan lehetséges zajos projekciók kezelése? Hasonlítsa össze a Paralell-beam, a Fan-beam, és a Cone-beam sugár geometriájú készülékeket! Melyik eseté

[kidolgozás](t10.md)

--- 

## T11. Mi a Kaczmarz iteráció lényege? Hogyan alkalmazható az eljárás CT, illetve PET modalitás rekonstrukciójára? Értelmezze az SART, valamint az SIRT eljárások módosító összefüggéseit! Mit jelent a projekciók inkonzisztenciája, az additív iteratív eljárások mennyire érzékenyek erre? Mit tud mondani a Gordon ART, az SART, illetve a SIRT zajérzékenységéről?

[kidolgozás](t11.md)

--- 

## T12. Ismertesse a Pozitron emissziós tomográfia alapú képalkotás működési elvét! Ismertesse az MLEM eljárást PET modalitás rekonstrukciós problémáján alkalmazva, értelmezze annak módosító összefüggését! Mi a tömörített érzékelés alapötlete? Hogyan alkalmazható ez rekonstrukciók esetén? Mit értünk kvantitatív képalkotás alatt? CT esetén a csillapítási együtthatókat milyen „mértékegységben” állítjuk vissza? Mit értünk sugárkeményedés, részleges térfogat, foton éhezés, fém, illetve szóródásból eredő artifakt alatt? Ezeket hogyan lehet kompenzálni, azok hogyan degradálják a rekonstruált kép minőségét?

[kidolgozás](t12.md)
