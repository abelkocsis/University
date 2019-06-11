**Vizsga feladatsor:**

**Haladó Haskell vizsga**

A feladatsor megoldására 2 óra áll rendelkezésre. A vizsgán tetszőleges segédeszköz használható. Ha valakinek nincs meg a +/- pontszám, az jelezze felém, neki beugrót kell írnia. Amennyiben ez utólag derül ki, úgy a vizsga érvénytelen. A feladatsor megoldásához kiindulási alapnak a következő kódbázist javaslom: repó link. A Solution.hs-ben az összeollózott verzió található, ilyen formában kell majd beadni a végleges megoldást is.

**Bevezető**

Feladatunk, hogy a While nyelvet kiegészítsük pointerekkel, és memória műveletekkel. A bevezető részben ehhez adunk egy rövid elméleti áttekintést. A műveletek pontos szintaxisa és szemantikája a feladat leírásában található.

**Memória műveletek**

Bizonyos programozási nyelvek lehetőséget biztosítanak a memória közvetlen kezelésére. Ezt úgy valósítják meg, hogy az alaptípusokon túl bevezetnek egy új típust, a pointer típust. Egy pointer tulajdonképpen nem más, mint egy cím a memória egy adott területére. Pointerek segítségével olvashatjuk, és írhatjuk is a memóriát, valamint kérhetünk pointerek még nem használt, szabad memóriaterületekre. Fontos megjegyezni, hogy adott memóriacímre több pointer is mutathat egyszerre.

**Memóriaműveletek**

Három memória műveletet fogunk bevezetni: store, fetch és update. A store segítségével tudunk majd új memóriaterületeket lefoglalni, és egy pointert kérni az újonnan lefoglalt területre. A fetch segítségével képesek leszünk olvasni egy adott pointer általt mutatott memóriaterületet. Végül pedig az update fog felelni egy adott memóriaterületen lévő érték módosításáért.

Korábban említettük, hogy egy címre több pointer is mutathat, tehát bevezetünk pointerek közötti alias-olást is. Ez tulajdonképpen pointereken értelmezett értékadás. A memóriára nincsen hatással, csak egy új pointert kérünk egy már korábban megcímzett területre.

**Példák**

Az alábbiakban a memória modell pontos meghatározása nélkül mutatunk néhány példát arra, miként működnek az új memóriaműveleteink, és az alias-olás.

Kód

            p <- store 5;
            x <- fetch p;
            update p (x+1);
            y <- fetch p    

Eredmény

            x == 5
            y == 6

Kód

            p <- store 5;
            x <- fetch p;
            q ~ p;           // alias
            update q (x+1);
            y <- fetch p

Eredmény

            x == 5
            y == 6


**Feladat**

Feladatunk, hogy a While nyelvet kiegészítsük pointerekkel, és memória műveletekkel.

**Szintaxis**

**Pointerek**

Adjuk hozzá az absztrakt szintaxishoz a pointereket, és definiáljunk hozzájuk parsert! (1 pont)

Vegyünk fel egy Ptr nevű típust, aminek egyetlen adatkonstruktora van: Ptr :: Name -> Ptr (ez a Var-hoz nagyon hasonló). Majd a var parser alapján (azonosító felismerése + wrappelés Ptr-be) írjunk egy parser-t a pointerekhez is: Parser Ptr.

**Memóriaműveletek absztrakt szintaxisa**

Vegyük fel a következő típussal rendelkelző adatkonstruktorokat a Statement típusba (3 pont):

Store :: Expr -> Ptr -> Statement
Fetch :: Ptr -> Var -> Statement
Update :: Ptr -> Expr -> Statement
Alias :: Ptr -> Ptr -> Statement
Megjegyzés

A fenti absztrakt szintaxis biztosít számunkra néhány nagyon hasznos tulajdonságot. Például garantálva van, hogy egy pointer mindig egy valid memóriaterületre fog mutatni. Továbbá, ha még extra megszorításokat teszünk a store-ra, akkor az is garantálva van, hogy egy memóriaterület sosem fog “elveszni”, mindig mutatni fog rá egy pointer. Ezek a tulajdonságok rendkívül sok fejfájástól tudnak megkímélni minket (lásd C++).

**Memóriaműveletek konkrét szintaxisa**

Egészítsük ki a Statement-et felismerő parser-t, hogy az újonnan bevezetett konstrukciókat is felismerje! (4 pont)

Alább látható az egyes új utasítások konkrét szintaxisa. A ...-tal jelölt részeket már korábban megadtuk.

            var ::= ...

            ptr ::= ...

            statement ::= ...
                        | <ptr> <- store <expr>
                        | <var> <- fetch <ptr>
                        | update <ptr> <expr>
                        | <ptr> ~ <ptr>

Megjegyzés: Ügyeljünk a memória műveletek neve és argumentumai közötti szóközre. A szintaxis hasonló a Haskell-es függvényalkamazás szintaxisához. A nyilak és a hullám körül nem szükséges szóközöknek lennie, de lehetnek.

            update p x   CORRECT
            updatepx     INCORRECT
            update px    INCORRECT
            updatep x    INCORRECT

            p <- store x CORRECT
            p<-store x   CORRECT
            q~p          CORRECT
            q ~ p        CORRECT

**Memóriamodell**

A jelenlegi kiértékelő állapotunk változókhoz rendel futási idejű értékeket. Az újonnan bevezetett műveletek jelentésének definiálásához ezt az állapotot ki kell egészítenünk. Az új állapotunkban továbbra is szerepelni fog a változók leképezése, azonban kiegészül a pointerek leképezésével memóriacímekre, és a memória címek leképezésével futási idejú értékekre. Továbbá szükségünk lesz a “következő szabad” memóriaterület címére is. A memóriacímeket egész számokkal fogjuk reprezentálni, nullától kezdődően.

**Kiértékelő állapot**

Definiáljuk az RTState típust, amelynek egyetlen adatkonstruktora az alább látható RTState! (1 pont)

RTState :: Map Var RTVal -> Map Ptr Int -> Map Int RTVal -> Int -> RTState
Megjegyzés: Mivel négy mezője van az RTState adatkonstrukronak, ezért érdemes record syntax-szal deklarálni.

**Kiértékelő kontexus**

Egészítsük ki az Eval monádot, hogy a változók leképezése helyett az RTState-et használja! (1 pont)

**Szemantika**

A következőkben megadjuk az új utasítások szemantikáját/jelentését. Az alábbiakban, amikor létrehozásról beszélünk, akkor mindig egy adott Map-be való új kulcs-érték pár beszúrására gondolunk.

Ügyeljünk arra, hogy a mostani állapotunk összetettebb, mint a korábbi. Ez azt jelenti, hogy mindig, amikor módosítanunk kell, akkor azt a következőképpen tesszük: Lekérdezzük a jelenlegi állapotot, szétszedjük darabjaira (pattern match), “módosítjuk” a megfelelő értékeket, újra összepakoljuk (létrehozunk egy új RTState-et), majd végül felülírjuk a korábbi állapotot az újonnan összerakottal.

A hibák kezelésére használjuk az Except monádot, és a throwError függvényt!

Megjegyzés: +1 pont jár, ha minden hibanélküli viselkedés helyesen működik.

**Hibakezelés (bónusz +2 pont)**

Ez a feladat nem feltétlenül szükséges a további feladatok megoldásához, csupán elegánsabbá teszi a kódot.

Definiáljuk a tryM :: MonadError e m => Maybe a -> e -> m a függvényt! A függvény feladat, hogy hibajelzés nélküli Maybe típusú értékeket, hibajelzéses MonadError típusú értékké alakít. A MonadError-ra gondolhatunk úgy is, mint egy általános Either-re. Az Either pedig csak abban különbözik a Maybe-től, hogy a hibás állapotot egy külön típussal tudjuk reprezentálni (hibajelzés).

A definíció megadásához használjuk a MonadError által biztosított függvényeket (return és throwError).

Példa speciálisan az Either típusra

            (tryM (Just 0) "error" :: Either String Int) == Right 0
            (tryM Nothing  "error" :: Either String Int) == Left "error"

Példa a használatra

Before:

            evalVar :: Var -> Eval RTVal
            evalVar v = do
              vars <- gets variables
              let mVal = Map.lookup v vars
              case mVal of
                Just val -> return val
                Nothing  -> throwError $ "Undefined variable"

After:

            evalVar :: Var -> Eval RTVal
            evalVar v = do
              vars <- gets variables
              val <- tryM (Map.lookup v vars) "Undefined variable"
              return val
            After after:

            evalVar :: Var -> Eval RTVal
            evalVar v = do
              vars <- gets variables
              tryM (Map.lookup v vars) "Undefined variable"
            store (3 pont)

A <ptr> <- store <expr> utasítás kiértékeli az <expr> kifejezést, majd létrehoz egy új memóriaterületet, melynek címe a “következő szabad” memóriaterület* címével egyezik meg, a hozzátartozó érték pedig a kiértékélet kifejezés értéke. Ezután létrehoz egy új pointert, amelynek neve <ptr>, a hozzátartozó cím pedig az előzőleg létrehozott memóriaterület címe. Végül eggyel növeli a “következő szabad” memóriaterület címét.

Abban az esetben, amikor a pointer már korábban definiálva volt (szerepel a leképezésben), dobjunk hibát a következő hibaüzenettel: "Pointer already defined".

(*): RTState utolsó mezője

**fetch (3 pont)**

A <var> <- fetch <ptr> utasítás lekérdezi a <ptr>-hez tartozó címet, ami alapján kikeresi a pointer által mutatott memóriaterületen lévő értéket. Végül ezt az értéket a <var>-hoz rendeli. Ha a változó a fetch előtt is létezett, akkor felülírja a hozzátartozó értéket, egyébként létrehoz egy új változot az új névvel.

Ha a pointer nem létezik, akkor dobjunk hibát a "Pointer not found" üzenettel. Ha a pointer létezik, de valami oknál fogva az általa mutatott memóriaterület nem, akkor dobjunk hibát a "Location not found" üzenettel.

**update (3 pont)**

Az update <ptr> <expr> utasítás kiértékeli az <expr> kifejezést, és a <ptr> általt mutatott memóriaterület értékét felülírja a kifejezés értékével.

Ha a pointer nem létezik, akkor dobjunk hibát a "Pointer not found" üzenettel. Ha a pointer létezik, de valami oknál fogva az általa mutatott memóriaterület nem, akkor dobjunk hibát a "Location not found" üzenettel.

**alias (2 pont)**

A <ptr> ~ <ptr> utasítás létrehoz egy új pointert a baloldalon látható <ptr> nevével, és a hozzátartozó címet a jobboldalon látható <ptr> címére állítja.

Ha a baloldali pointer már létezik, akkor dobjunk hibát a "Pointer already defined" hibaüzenettel. Ha a baloldali pointer még nincs definiálva, azonban a jobboldali sincs, akkor dobjunk hibát a "Pointer not found" üzenettel.

**Pontozás**
Az feladatok helyes megoldásával összesen 24 pont szerezhető, azonban a ponthatárok 20 ponthoz vannak igazítva.

Megjegyzés: Légyszi a feltöltésetekhez majd írjátok oda az órai +pontokat. Köszi!

**Ponthatárok**
2: 11-12
3: 13-15
4: 16-17
5: 18-

*Kód alapja: https://github.com/Anabra/Advanced-Haskell-Practice*
*Tanár: Podlovics Péter*