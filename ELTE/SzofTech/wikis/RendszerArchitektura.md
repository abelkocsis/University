A program háromrétegű architektúrával épül fel: modell, hálózati, megjelenítési réteg. A megvalósítás során objektumelvű szemléletet fogunk követni.

**Modell réteg**

A következő osztályokra/logikai egységekre mindenképp szükség lesz:
* **Pálya**: egy n*m-es mátix, ahol 
   * lekérdezhető minden mezőről, hogy mi van rajta (Field típus: Empty, Soldier, Tower, Castle)
   * meg van valósítva a távolság számítás, 
   * legrövidebb út keresés a kastélyok és egyéb mezők között
* **Torony**, ami a következőket kell, hogy tárolja/megvalósítsa: 
   * Játékos
   * Pozíció
   * Lőtáv
   * Sebzés
   * Hatótávban lévő ellenségek közül választás, támadás (Fire)
* **Játékos**
   * Név
   * Kastély életerő
   * Tornyok (vektor)
   * Katonák (vektor)
   * Pénz
   * Kastély megtámadása (hitCastle)
* **Katona**
   * Játékos
   * Pozíció
   * Életerő
   * Sebzés


**Hálózati réteg**

Feladata a kommunikáció a kliensek (játékosok), és a szerver között. A kliens mindig csak a játékos döntéseit küldi el a szervernek. A szerver ezt validálja, majd ennek megfelelően változtatja a modell állapotát. A szerver a lépésre válaszként elküldi a klienseknek a játéktér állapotát.

**Megjelenítési réteg**

A játék 3 dimenziós megjelenítéssel rendelkezik.
A 3 dimenziós grafikai számításokat OpenGL-el végezzük, míg a megjelenítést és a grafikus ablakot az SDL biztosítja. Az OpenGL 4.5-ös verzióját használja a szoftver, így a szoftver- és hardverkövetelményeket ez nagyban befolyásolja. 
A szoftver a számításokat a GPU-n végzi (grafikus processzor), így az erősebb videokártya hiánya nagy mértékben csökkentheti a játék teljesítményét és használhatóságát.
A grafikus ablak az elsődleges monitoron jelenik meg teljes képernyős módban, és a felbontása megegyezik az elsődleges képernyő asztali felbontásával.
