**Felhasználói felület modell**

A felhasználó a szoftver indításakor a főmenüben találja magát, amely a következő módon vázolható:
![menu](uploads/0de21ffdf47ede68cd65ff8db5344826/menu.png)
A **kilépés** menüpontot a választva a szoftver leáll.

A **beállítások** menüpont alatt állíthatja a felhasználó a szerver címét és a játék pár további tulajdonságát.

Az **új játék** kezdésével a kliens megpróbál csatlakozni a beállításokban megadott szerverhez, és amennyiben a csatlakozás sikeres, illetve ellenfél is áll rendelkezésre, akkor megjelenik a játéktér és elkezdődik a két játékos harca.
 
Az n × m –es játéktér a következőképpen vázolható:
 
![jatekter](uploads/5b267842fa248954883520b3b87d7ce9/jatekter.png)

A bal felső sarokban találhatóak a **saját adatok**: A játékos aranya és a saját kastélyának életereje.

Emellett helyet kap még a képernyő felső részén egy action bar (sáv), melyben különböző tornyok építését kezdeményezheti a felhasználó (sima, erős vagy longrange). Ha a játékos saját körében rákattint az egyikre, és megvan hozzá a tőkéje (megfelelő mennyiségű arany), akkor megjelenik a pályamátrix, a lehetséges helyek, ahova építhet zölddel jelennek meg, míg a foglaltak pirossal. Ha egy szabad helyre kattint a játékos, akkor a torony építése megkezdődik.

Az építő sáv mellett helyet kap egy kiképzést kezelő action bar, ahol a különböző egységek kiképzését kezdeményezheti a játékos (sima, erős, tank katona). Ha a saját körében a játékos rákattint az egyik egységre, és van elég aranya, akkor az egység kiképzése megkezdődik, majd ha ennek lefutása után (ennek hossza a kiképzendő egység típusától függ) az egység megjelenik a játékos bázisánál.

Emellett lehetőség van zene és hangok ki/be kapcsolására illetve a kamera forgatására, ezt mind billentyűzetről tudja a felhasználó kezelni. Lehetséges a játéktéren keresztülmenő y tengely körül forgatni, a játéktér középpontja körül (fel le irányba) mozgatni a kamerát, valamint távolítani és közelíteni is.

Végül pedig helyet kap egy menü gomb is a jobb felső sarokban, mely segítségével kiléphet az éppen futó játékból a felhasználó, és a főmenübe térhet. Ezen akcióval automatikusan elvesztette a játékot.