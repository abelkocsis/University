with Ada.Numerics.Discrete_Random, Bag_Package, Ada.Integer_Text_IO, Ada.Text_IO;
use  Ada.Integer_Text_IO, Ada.Text_IO;

procedure Test1 is
    type Dobas is new Integer range 1 .. 6;
    package Dice_Bag is new bag_package(Index => Dobas, Counter => Integer);
    use Dice_Bag;
    package Random_Dobas is new Ada.Numerics.Discrete_Random(Dobas);

    D : Dice_Bag.Bag;
    R : Dobas;
    RD : Random_Dobas.Generator;
begin
    Empty(D);
    Random_Dobas.Reset(RD);
    for I in 1..20 loop
        R := Random_Dobas.Random(RD);
        Add (D, R);
    end loop;

    while TRUE loop
        for I in Dobas loop
            if Has_Any(D, I) then
                Remove(D, I);
            else
                Put_Line(Dobas'Image(I));
                return;
            end if;
        end loop;
    end loop;
end Test1;