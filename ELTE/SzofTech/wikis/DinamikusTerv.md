* A főablakot létrehozzuk, majd megjelenítjük (**show**)

   * bezáráshoz (**closeEvent**) megerősítést kérünk a felhasználótól, amelyben lehetősége van azt megszakítani (**ignore**), vagy elfogadni (**accept**)

* A megjlelenítés alatt egymástól függetlenül kezeljük a játék modelljét (**GameManager**), valamint megejelenítését 
![GameWidget](uploads/724ea60a581294193d38e5a1646e1c0e/Document_1-3.jpg)

* A szerveren futó **GameModel** az *init* függvénnyel elindítja a játékot és megjeleníti a pályát, kijelöli a kezdő játékost.

* A klienstől érkező **round** hívás - amennyiben a megfelelő, soron lévő játékostól jön - elindítja a kör lekezelését.

* Amennyiben torony építése a cél, a lépést helyességét ellenőrzi a szerver. Ezután végrehajtja a kért műveletet (**Passzolás**, azaz nem csinál semmit, **Egység építése** (*createSoldier(int,int,Coordinate)*), **Torony építése**(*createTower(int,int,Coordinate)*)). A round függvény paraméterei alapján beálíltja a megfelelő adatokat (standard és erősebb katona, stb.), illetve levonja a megfelelő pénzösszeget a játékostól.

* Ezután Dijkstra algoritmussal a program kiszámolja minden katona útvonalát az ellenfél kastélyához. Ez a gyarkoatlatban azt jelenti, hogy a kastélyokhoz számítjuk ki a legrövidebb utat (*calcRoutes()*). Ezután léptetjük a katonákat (*soldiersStep()*). Ha a katonák a kastélyra lépnének, megsebzik a kastélyt.

* A következő lépésben a tornyok támadják, lőnek az ellenséges katonákra (*towersFire()*) a megadott paraméterek (*range*, *damage*) alapján.

* Utolsó lépésben a program ellenőrzi, hogy elpusztult-e valamelyik kastély. Ha igen, a játék véget ér, ha nem, a másik játékos következik.

* Ekkor a szerver elküldi az aktuális állapotot a klienseknek, és vár a következő játékos válaszára. 

![GameManager állapotai](uploads/ba2ac24d82c3afcb0fd2ca9aea64bcd7/Állapotdiagram.jpg)