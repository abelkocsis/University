#include "mezo.h"
#include "jatekos.h"

using namespace std;


Mezo* Ingatlan::akcio(Jatekos *jatekos)
{
    return this;
}

/*Mezo* Ingatlan::akcioOvatos(Ovatos *ovatos)
{
    if (ovatos->)
    ovatos->penzValt(3);
    return this;
}

Mezo* Ingatlan::akcioTaktikus(Taktikus *taktikus)
{
    taktikus->penzValt(-5);
    return this;
}

*/

Mezo* Szolgaltatas::akcio(Jatekos *jatekos)
{
    jatekos->penzValt(-1*(this->mennyit));
    return this;
}

/*Mezo* Szolgaltatas::akcioOvatos(Ovatos *ovatos)
{
    ovatos->penzValt(-2);
    return Ingatlan::Instance();
}

Mezo* Szolgaltatas::akcioTaktikus(Taktikus *taktikus)
{
    taktikus->penzValt(-2);
    return Szerencse::Instance();
}*/

Mezo* Szerencse::akcio(Jatekos *jatekos)
{
    jatekos->penzValt((this->mennyit));
    return this;
}

/*Mezo* Szerencse::akcioOvatos(Ovatos *ovatos)
{
    ovatos->penzValt(-4);
    return Szolgaltatas::Instance();
}

Mezo* Szerencse::akcioTaktikus(Taktikus *taktikus)
{
    taktikus->penzValt(6);
    return this;
}*/
