# Funkcionális Analízis

Általános jelölések:
- $V$ egy vektortér $\mathbb{F} = \mathbb R/ \mathbb{C}$ felett
- skalárszorzás: $< v,w >$

## Skaláris szorzat

Legyen $V$ egy vektortér $\mathbb{F} = \mathbb R/ \mathbb{C}$ felett. A $<,>: V\times V \rightarrow \mathbb{F}$ leképezést akkor nevezzük **skaláris szorzat**nak ha: $\forall$ $v,w_1,w_2\in V$, $\lambda_1, \lambda_2 \in \mathbb{F}$:
- $< v,w > = \overline{< w,v >}$    (konjugált)
- $< v, \lambda_1 w_1 + \lambda_2 w_2 > = \lambda_1< v, w_1 > + \lambda_2< v,w_2 >$
- $< v,v > \ge 0$, egyenlőség akkor és csakakkor, ha $v=0/_{mm}$ (majdnem mindenütt)

A $V$ tér egy rögzített skaláris szorzattal **skalár szorzatos tér**.

A 2. kritérium esetén fontos, hogy konvenciótól függően a skaláris szorzás egyik változóban lineáris, másikban konjugált lineáris. $<\lambda_1 w_1 + \lambda_2 w_2, v> = \overline\lambda_1< w_1,v > + \overline\lambda_2< w_2,v >$

### Természetes hossz skalár szorzatos térben

$$||v|| := \sqrt{< v,v >}$$


Tulajdonságai:
- $||v|| \ge 0$, egyenlőség akkkor és csakakkor, ha $v=0$
- $||\lambda v|| = |\lambda|\cdot||v||$

## Cauchy-Schwarz egyenlőtlenség

$$|< v,w >| \le ||v||\cdot||w||$$

egyenlőség akkor és csakakkor, ha $v$ és $w$ párhuzamos, vagyis egymás skalárszorosai.
 
$$|< f, g >|^2 \le < f,f >\cdot< g,g >$$

## $L^2/l^2$ terek

Legyen $S$ egy megszámlálható halmaz (indexhalmaz). Legyen $\Omega \subset \mathbb{R}^d$ tartomány. Legyen $\mathbb F = \mathbb R/\mathbb C$.

$$l^2(S, \mathbb F) = \left\lbrace a: S\rightarrow\mathbb F | \sum_{k\in S}|a_k|^2 < \infty\right\rbrace \rightarrow <a,b> = \sum_{k\in S} \overline a_kb_k$$

$$L^2(\Omega, \mathbb F) = \left\lbrace f: \Omega\rightarrow\mathbb F | \int_{\Omega}|f|^2 < \infty\right\rbrace_{/_{mm}} \rightarrow <f,g> = \int_{\Omega} \overline fg$$

$L^2$ és $l^2$ skalár szorzatos teret alkotnak (vektorterek).

## Háromszögegyenlőtlenség

$$||v+w|| \le ||v||+||w||$$

## Norma

Egy $||.||:V\rightarrow \mathbb R$ **norma**, ha:
- $||v|| \ge 0$ és $0$, ha $v = 0$
- $\forall \lambda: ||\lambda v|| = | \lambda|\cdot||v||$
- háromszögegyenlőtlenség: $||v+w|| \le ||v||+||w||$

$V$ tér egy rögzített normával **normált tér**.

---

## Ortogonalitás

$V$, skalárszorzatos tér. 
- $v, w\in V$ merőlegesek (ortogonálisak) ($v \perp w$), ha $<v, w> \ge 0$ és $<v,v> = 0$
- $\sigma, \sigma_1, \sigma_2 \subset V:$ $\sigma_1 \perp \sigma_2$, ha $\forall v\in\sigma_1, w\in\sigma_2:v\perp w$
- $\sigma^{\perp} = \left\lbrace v\in V | \forall w \in\sigma : v \perp w\right\rbrace$

Tulajdonságai:
- $v \perp w \Leftrightarrow w \perp v$
- $\sigma_1 \subset \sigma_2 \Rightarrow \sigma_2^\perp \subset \sigma_1^\perp$
- $\sigma \subset\left(\sigma^\perp\right)^\perp$
- $\sigma^\perp$ mindig altér

### ONS: OrtoNormált Rendszer
$e_\alpha \in V(\alpha \in I)$, $<e_\alpha, e_\beta> = \left\lbrace1: \alpha=\beta, 0: \alpha\not=\beta\right\rbrace$

Ha $e_\alpha$ ONS, akkor lineárisan függetlenek.

**ONB**: OrtoNormált Bázis: ONS ami bázis is, kifeszíti a teret.

Legyen $e_1...e_n$ ONS $V$-ben, $v \in V$. Ekkor $v_{||} = \sum\limits_{k=1}^{n}<e_k, v>e_k \in U=Span\lbrace e_1...e_n\rbrace$(kifeszít) és $v-v_{||} \in U^\perp$. $v_{||} v$ vetülete $U$-ra.

A $v_{||}$ vetített vektorra: $\forall u\in U, ||v - u|| \ge ||v-v_{||}||$, egyenlőség, ha $v=v_{||}$.

