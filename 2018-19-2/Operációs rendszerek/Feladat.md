**1. beadandó**

Készítsen C programot amely megoldja a következő feladatot:

Pezseg a lakáspiac! Soha ekkora lehetőségek nem voltak benne! A "Varázs-Lak Kft" teljes felújítást vállal! Rendelkezik festő, burkoló(hideg,meleg), villanyszerelő, víz-gáz-fűtésszerelő, konyha(egyedi) bútor készítő, lakberendező kapacitással. Egy ügyfél jelentkezése során a társaság rögzíti a kért munkák adatait (lakóingatlan címe, mérete és a megrendelt részmunkák listáját(pl: festés, burkolás, viz-gáz szerelés, stb. és a munka elvégzésének határidejét!)). 
Az elkészült alkalmazás legyen képes kilistázni a beérkezett rendeléseket, tudjon új rendelést felvenni, törölni egy meglévőt illetve módosítani egy rendelés adatait.

Készítsünk C programot, amellyel a leírt tevékenység elvégezhető. Az adatokat fájlban tároljuk.

**2. beadandó**

Varázs-Lak Kft (szülő) minden részmunkát egy nap alatt végez el. Egy munka kiválasztás algoritmusa az SDF (Shortest Deadline First). Munkaerőhiány van, így csak egy felújító csapata(gyerek) van Varázs-Lak Kft-nek. Ha van munka, akkor Varázs-Lak Kft elindít egy csapatot a munka elvégzésére. A felújító folyamat jelzéssel tudatja, hogy készen áll a feladatra, amire válaszul a Kft csövön átküldi a kiválasztott munka (ha több is van akkor SDF alapján választ egyet) adatait. A felújító csapat 10% valószínűséggel nem tudja tartani a határidőt. A felújítás eredményét a felújító csapat üzenetsoron küldi vissza, majd befejezi tevékenységét! (Az eredmény csak azt tartalmazza, hogy határidőn belül sikerült-e elvégezni a munkát.) A Kft a kapott eredményt kiírja és rögzíti.

Készítsen C programot, amellyel a leírt tevékenység elvégezhető.

**ZH**

Operációs rendszerek ZH. 2019 május 16. 14 óra. A programnak az os.inf.elte.hu gépen kell futni. „Esőisten siratja” az országot, esőben virágzik az akác, veszélyben az akácméz! A főméhész (szülő) figyelemmel kíséri az időjárást és irányítja a mobil kaptármozgató csapatot. (gyerek)

1. Miután a radaros előrejelzés alapján egy akácos felett kitisztul az ég, főméhész (szülő) riasztja(jelzés) a mobil csapatot(gyerek), hogy készüljenek. A csapat miután megkapta a jelzést, képernyőre írja azt, hogy riasztás érkezett, majd amint a csapat útra kész (1-3 másodperc, véletlenszerűen) visszaírja üzenetsoron, hogy „Csapat útra kész!”. Ezt a szülő képernyőre írja, majd bevárja a csapat befejezését és maga is terminál.

2. A főméhész miután megkapta a csapat értesítését, hogy útra készen vannak, elküldi az akácos GPS koordinátáit(2 egész szám, X,Y) csövön keresztül a mobil csapatnak. A koordináták értékeit mindkét fél a képernyőre írja a PID értékükkel együtt, majd befejezik tevékenységüket.

3. Miután a mobil csapat megkapta az akácos koordinátákat, elindulnak elfoglalni a területet. Amint elfoglalták azt, osztott memóriába írják, hogy az „ X,Y GPS koordinátájú akácos elfoglalva!”. Ezt a tartalmat szülő a képernyőre írja.

4. Több csapat is pályázik az értékes akácosokra, védje mutex használattal az osztottmemóriát.