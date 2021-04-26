A feladat az ELTE Szoftvertechnológia kurzusára készítettük egy három fős csapatban Varga Balázzsal és Krupinszki Balázzsal.

# TeamEC Tower defense játék

[Specifikáció és követelményelemzés](https://github.com/abelkocsis/University/blob/master/2018-19-2/Szoftvertechnológia/wikis/SpecifikacioEsKovetelmenymenedzsment.md)

[Megoldási terv](https://github.com/abelkocsis/University/blob/master/2018-19-2/Szoftvertechnológia/wikis/MegoldasiTerv.md)

**Projekt betöltése és futtatása**

  * Töltsük le a GitLab-on lévő fájlokat!
    
  * A számítógépünk PATH directory-jába adjuk hozzá a TowerDefense/TowerDefense/OGLPack/bin/x64 helyen található DLL fájlokat!
  
  * Töltsük le a teljes Boost könyvtár 1.70-es verzióját (más verzió esetén a VS projektben módosítsuk az include pathokat) a https://www.boost.org/users/download/ linkről, 
    buildeljük a bináris fájlokat (windowson : https://www.boost.org/doc/libs/1_62_0/more/getting_started/windows.html), majd helyezzük a PATH-ba a boost könyvtárát.
  
  * Nyissuk meg a projektet Visual Studio 2017-ben a TowerDefense/TowerDefense.sln fájl segítségével!

  * Fordítsuk le, és futtassuk a fájlt!

**Végleges megoldás használata**

  * A Specifikációnak megfelelően működik a játék két számítógépen, amenniyben azok ugyan ahhoz a hálózathoz csatlakoznak. A személyek felváltva léphetnek.
 
  * A pénzről és a kastályok életértől a bal felső sarokban kaphat információt.
   
  * Az aktuális (soron következő) játékos színét a háttér jelzi.
   
  * A Esc billenytű hatására kiléphetünk, az M billentyű hatására zene szólal meg.

    
  
