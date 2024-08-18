# 👉🏻 TP Fundamentos de Programación
> ℹ️ En este curso (me gusta pensar a las _materias_ como _cursos_ porque: por un lado le da más sentido a la palabra _cursar_, y por otro me da la sensación de estar haciendo cursos divertidos y eligiendo cada uno, no simplemente _yendo a la facultad_ como todo el mundo) hay dos TPs. El segundo es el que estoy subiendo. El tema es que en realidad se los podría considerar un solo TP, dado que el TP1 es armar la parte básica del juego, y el TP2 es "terminarlo". Digo _"terminarlo"_ entre comillas porque **_esto es desarrollo de software pibe_**, y ningún _software_ **nunca** va a estar 100% terminado.
- 🤔 ¿Qué es? Un **juego** de **Perry el Ornitorrinco**.
- 🐾 ¿Curso? **Fundamentos de Programación**.
- 💊 ¿Cátedra? **[Mariano Méndez](https://fundamendez.com.ar)**.
- ⌚ ¿Cuándo? **Primer cuatrimestre de 2024**.
- ©️ ¿Lenguaje? ~Argentino y _yankeelandés_~ **C**.

# 📺 _Demo_
https://github.com/user-attachments/assets/e8b00da0-879b-41c6-a4ca-08858172b418

# 📏 Instrucciones de juego
> 🗣️ Parafraseando, dicen por ahí que _[el mejor software es aquel que no requiere explicación o documentación alguna](https://wptavern.com/the-best-documentation-is-no-documentation)_. Pero ~_I'm just a girl_~ solo soy un pibe de primer año, y me da un toque de fiaca dedicarle tantísimo tiempo a lograr eso con este programa, que además es tan rústico que para lograrlo casi que debería pasarlo a [Python con PyGame](https://github.com/LucasDondo/python_crash_course) u otra opción gráfica similar…
- **🎯 Objetivo:** desactivar todas las bombas (`B`).
- **🤔 ¿Cómo?** Pasando por encima de ellas con Perry (`P`).
- **🕹️ Pero, ¿cómo lo muevo a Perry?** Con las teclas `W`, `A`, `S` y `D`.
- **🕵🏻‍♂️ ¿La tecla `Q` me sirve de algo?** Sí. Con eso te camuflas o descamuflas.
  - 🐶 Si estás camuflado, sos Perry mascota, y tus familiares no te pueden hacer daño, pero vos tampoco podés desactivar bombas.
  - 🔫 Si no estás camuflado, sos Perry espía y podés desactivar bombas, pero tus familiares te pueden hacer daño.
- **💪🏻 ¿Soy inmortal?** Obvio que no, salamín. Tenés tres vidas. Si perdés las tres, perdés el juego.
- **❤️ ¿Y de qué maneras podría perder esas vidas? (Para evitarlo digo.)**
  - 👨‍👩‍👧‍👦 Estando a un _cuadradito_ (calculado según la [distancia del taxista](https://es.wikipedia.org/wiki/Geometr%C3%ADa_del_taxista)) de tus familiares Phineas (`H`), Ferb (`F`) y Candace (`C`).
  - 🤖 Estando a dos _cuadraditos_ de algún robot (`R`) (aparece uno nuevo cada diez movimientos de Perry) (si es que estás camuflado).
    - 🦾 Si no estás camuflado, destruís al robot (gastando cinco puntos de energía).
  - ⚡ Quedándote sin energía.
  - 💣 Si alguna bomba explota (tienen un temporizador que avanza cada vez que movés a Perry).
- **🎩 ¿Y eso de los sombreros (`S`)?** Si te lo pones, te sumas una vida.
- **🍬 Última pregunta… ¿Y las golosinas (`G`)?** Al comerlas, te suman veinte puntos de energía.
> 😜 _Pro tip_: Las _flechitas_ que están arriba y a la izquierda del mapa te indican dónde está Perry, para que no lo pierdas.
