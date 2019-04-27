with Ada.Numerics.Discrete_Random, Ada.Text_IO;
use Ada.Text_IO;

package body Map_Package is

    procedure Init (M : in out Map) is
        package Random_Field is new Ada.Numerics.Discrete_Random(Field);
        RF : Random_Field.Generator;
    begin
        Random_Field.Reset(RF);
        for I in M.Fields'Range(1) loop
            for J in M.Fields'Range(2) loop
                M.Fields(I, J) := Random_Field.Random(RF);
            end loop;
        end loop;
    end Init;

    procedure Put (M : in Map) is
    begin
        for J in M.Fields'Range(2) loop
            for I in M.Fields'Range(1) loop
                Put(Field'Image(M.Fields(I, J)));
                Put(" ");
            end loop;
            Put_Line("");
        end loop;
        Put_Line("");
        Put_Line("");
    end Put;

    procedure Move (M : in out Map; W : in out Warrior) is
        package Random_Irany is new Ada.Numerics.Discrete_Random(Irany);
        RI : Random_Irany.Generator;
        I : Irany;
        X : Positive;
        Y : Positive;
    begin
        Random_Irany.Reset(RI);
        I := Random_Irany.Random(RI);
        X := M.Position.X;
        Y := M.Position.Y;

        Set (M, I, X, Y);
        Put("Pozíció: ");
        Put(Positive'Image(X));
        Put(" ");
        Put_Line(Positive'Image(Y));

        M.Position.X := X;
        M.Position.Y := Y;

        Field_Action(M.Fields(X, Y), W);
        
    end Move;

    function Is_Empty (M : in Map) return Boolean is
    begin
        for I in M.Fields'Range(1) loop
            for J in M.Fields'Range(2) loop
                if not (M.Fields(I, J)=Empty) then
                    return false;
                end if;
            end loop;
        end loop;
        return true;
    end Is_Empty;

    procedure Set(M: in Map; I: in Irany; X : in out Positive; Y: in out Positive) is
    begin
        if I = 1 then
            if X = M.Fields'Last then
                X := M.Fields'First;
            else
                X := X + 1;
            end if;
            Put_Line("Lépés: jobbra");
        else
            if I = 2 then
                if X = M.Fields'First then
                    X := M.Fields'Last;
                else
                    X := X - 1;
                end if;
                Put_Line("Lépés: balra");
            else
                if I = 3 then
                    if Y = M.Fields'Last then
                        Y := M.Fields'First;
                    else
                        Y := Y + 1;
                    end if;
                    Put_Line("Lépés: le");
                else
                    if Y = M.Fields'First then
                        Y := M.Fields'Last;
                    else
                        Y := Y - 1;
                    end if;
                    Put_Line("Lépés: fel");
                end if;
            end if;
        end if;

    end Set;


end Map_Package;