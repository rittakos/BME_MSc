# Rövid összefoglalő a Logika tárgyhoz

2022 ősz

[Egy egész jó hivatalos jegyzet.](loginfo.pdf)

[Rövid felületes összefoglaló](Matlog_peabe.pdf)

A leírtak sokszor nem teljesen pontosak, inkább csak segítik a jegyzet könnyebb megértését és kiemelik az alapokat.

---

## **Klasszikus kijelentéslogika (Propozicionális logika)**

**Atomi formulák**: $\Pi = \lbrace p_0, ..., q_0... \rbrace$
- például $\Pi = \lbrace 0,1 \rbrace$ jelölésük: $\phi, \psi, \chi...$

**Formulák** (állítás, mondat): $p$, $\neg(p \land q)$

Definíció:
- $\phi \lor \psi = \neg(\neg\phi \land \neg \psi)$ (vagy)
- $\phi \rightarrow \psi = \neg\phi \lor \psi$ (ha... akkor)
- $\bot = p \land \neg p$ (feltétel nélküli hamis)
- $\top = \neg \bot$ (feltétel nélküli igaz)
- $\phi \iff \psi = (\phi \rightarrow \psi) \land (\psi \rightarrow \phi)$ (ekvivalencia, akkor és csak akkor)

**Modell**: $M:\Pi \rightarrow \lbrace 0,1 \rbrace$ (a propozicionális logika egy modellje). Mindenre megmondja, hogy igaz vagy hamis. $\phi$ igaz $M$-ben, vagy $M$ modellje $\phi$-nek, ha $\phi^M = 1$. Ezt a $M \models \phi$ jelöli.

Ha $\phi$ minden modellben igaz, magyarul ha egy logikai formula minden esetben igazat ad, akkor **érvényes**. $\phi$ **kielégíthető**, ha van modellje, magyarul léteznek hozzá olyan változóértékek, hogy igazat ad. Két formula **ekvivalens**, ha közös a modelljük, magyarul azonos az igazságtáblájuk.

$M$ modell és $\Sigma \cup\lbrace \phi \rbrace \subseteq Form$. Ekkor:
- $M \models \sigma \iff (\forall \phi \in \Sigma)M \models \phi$

### Normálformák
- **literális**: atomi vagy annak negáltja
- **diszjunktív normálforma** (DNF): és-ek vagy-ai  
- **konjuktív normálforma** (CNF): vagy-ok és-ei


## **A kijelentéslogika bizonyításelmélete**

Logikai axiómák:
- $\phi \rightarrow (\psi \rightarrow \phi)$
- $[\phi\rightarrow(\psi\rightarrow\chi)]\rightarrow[(\phi\rightarrow\psi)\rightarrow(\phi\rightarrow\chi)]$
- $(\neg\phi\rightarrow\neg\psi)\rightarrow[(\neg\phi\rightarrow\psi)\rightarrow\phi]$

**Levezetés**: Legyen $\Sigma \subseteq Form$. A $\phi_1, \phi_2...\phi_n$ formulasorozat egy levezetés $\Sigma$-ból, ha minden $1 \leq k \leq n$-re teljesül az alábbi feltételek valamelyike:
- $\phi_k$ valamelyik axióma instanciája
- $\phi_k \in \Sigma$
- van olyan $1 \leq i,j \leq k$, hogy $\phi_i = \phi_j \rightarrow \phi_k$

**Levezethetőség**: $\phi$ levezethető $\Sigma$-ból, ha van olyan levezetés $\Sigma$-ból, aminek $\phi$ az utolsó formulája. jelölése: $\Sigma \vdash \phi$

$\Sigma \models \phi \iff \Sigma \cup\lbrace \neg \phi \rbrace$ kielégíthetetlen/inkonzisztens.

Egy formulahalmaz **konzisztens**, ha nem vezethető le belőle a fals formula. Ami kielégíthető, az konzisztens.  gazságtáblával vizsgáljuk, hogy van-e  odellje, azaz bármi olyan értéke a változóknak, hogy minden formula eredménye azonos. Ha van ilyen, konzisztens.


Egy formulahalmaz **teljes**, ha levezethető belőle minden egyes formulája.


--- ZH ---