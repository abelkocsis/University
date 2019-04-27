separate (Simulation)
protected body Printer is
    procedure Szoveg_Kiir(Azon : Integer; E : Esemeny) is
    begin
            Put(Integer'Image(Azon));
            case (E) is
                when Called =>
                    Put_Line(" is called back.");
                when Hit =>
                    Put_Line(" is killed."); 
                when Shoot =>
                    Put_Line (" is shooting.");
                when Ended =>
                    Put_Line ("THE END. //Disney will continue but it won't be the same.");
                when Luk =>
                    Put_Line (" Szkájvóker Lajos megérezte az Erőt");
            end case;
    end Szoveg_Kiir;

    procedure Matrix_Kiir(M : Char_Array) is
    begin
        for I in 1..N loop
            for J in 1..N loop
                Put(M(I,J));
            end loop;
            Put_Line("");
        end loop;
        Put_Line("");
    end Matrix_Kiir;
end Printer;