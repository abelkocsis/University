**Hatékonyság**

• A 3 dimenziós grafika miatt jelentősebb terhelés a GPU, valamint a GPU-hoz tartozó VRAM (video memória) részére. Háttértár részére csak az objektumok és a hangfájlok beolvasásakor esik nagyobb terhelés, ezen betöltések a játék elején megtörténnek, így a szoftver további futása során már jelentéktelen a terhelés.

• A memóriára eső terhelés a kiválasztható egységek és a katonák számával arányos.

• A processzorra eső terhelést jelentősebben a katonák száma befolyásolja.

• Mivel a játék nem rendelkezik beépített gépi ellenféllel, így szükséges hálózati kapcsolat a futtatásához, ám nem jelentős a hálózati terhelés.

• A játék hatékonysága erősen függ a számítógépben használt Grafikus Processzortól (GPU), így a gyors futás és jó játékélmény érdekében ajánlott az erősebb videokártya használata.


**Megbízhatóság**

• Hiányzó fájlok, vagy az erőforrások hiánya esetén a keretrendszer (SDL) hibaüzenettel jelez a felhasználó felé. A fájlok illetve erőforrások biztosítása és a szoftver újraindítása esetén a hibajelenség megszűnik.

• Sérült fájlok esetén, a sérüléstől függően vagy elérhetőek a funkciók, vagy amennyiben nem az elvárt szerkezetnek megfelelő a sérült fájl (pl : a modelleket leíró .obj fájl), hibajelenség léphet fel, ezt hibaüzenettel jelzi a szoftver.

**Biztonság**

• A hálózaton a szerver és a kliensek között átküldött adatok biztonsága nem garantált

• A pálya aktuális állása egy központi szerveren van tárolva, a kliensek innen kapják meg ezt minden egyes Tick-ben

• A kliensen csak a megjelenítéshez, illetve az egységek leírásához szükséges adatok vannak tárolva

• A kliensek a játékban történt akciókat elküldik a szervernek, majd a szerver kiértékeli őket és ennek megfelelően változtatja a modellt



**Hordozhatóság**

• A legtöbb Windows alapú számítógépen biztosított a használat, így Windows 8 (vagy annál újabb) alapú rendszer esetén futtatható az alkalmazás, amennyiben a számítógépen elérhető a DirectX 11 (vagy újabb) verziója. Ehhez DirectX 11-et támogató hardver is szükséges.

• A szoftver a README.md fájlban leírt telepítést igényli.


**Felhasználhatóság**

• Intuitív felhasználói felület

• md file a funkciók ismertetésére