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

$$l^2(S, \mathbb F) = \left\lbrace a: S\rarr\mathbb F | \sum_{k\in S}|a_k|^2 < \infin\right\rbrace \rightarrow <a,b> = \sum_{k\in S} \overline a_kb_k$$

$$L^2(\Omega, \mathbb F) = \left\lbrace f: \Omega\rightarrow\mathbb F | \int_{\Omega}|f|^2 < \infin\right\rbrace_{/_{mm}} \rightarrow <f,g> = \int_{\Omega} \overline fg$$

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
