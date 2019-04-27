separate (Simulation)
protected body Map is
    function Get_Hajo(C : Coordinates) return Ship_Access is
    begin
        return M(C.X, C.Y).Ship_Acc;
    end Get_Hajo;
    
    function Get_Status(C : Coordinates) return Boolean is
    begin
        return M(C.X, C.Y).Status;
    end Get_Status;

    procedure Luke_Is_Here is
    begin
        M(N/2, N-1).Status := True;
        M(N/2, N-1).Ship_Acc := new Ship(69, Rebel);
    end Luke_Is_Here;

    procedure Change_Status(C: Coordinates) is
    begin
        M(C.X, C.Y).Status := False;
    end Change_Status;

    procedure KiIr is
        C : Char_Array;
    begin
        for I in 1..N loop
            for J in 1..N loop
                if (M(I,J).Status) then
                    if (M(I,J).Ship_Acc.O = Rebel) then
                        C (I, J) := 'R';
                    else
                        C (I, J) := 'I';
                    end if;
                else
                    C (I, J) := '_';
                end if;
            end loop;
        end loop;

        Printer.Matrix_Kiir(C);
    end KiIr; 

    procedure Init is
    begin
        for I in 1..N loop
            M(I, 1).Ship_Acc := new Ship(I, Imperial); 
            M(I, 1).Status := True;
        end loop;
        for I in 1..N loop
            M(I, N).Ship_Acc := new Ship(N+I, Rebel); 
            M(I, N).Status := True;
        end loop;
        Death_Star.Send_Out_Ships(N);
        Rebel_Base.Send_Out_Ships(N);
    end Init;

    procedure End_Fight is
    begin
        Vege := True;
        Printer.Szoveg_Kiir(0, Ended);
        for I in 1..N loop
            declare
                U : Agent(M(I, 1).Ship_Acc);
            begin
                M(I, 1).Status := False;
            end;
        end loop;
        for I in 1..N loop
            declare
                U : Agent(M(I, N).Ship_Acc);
            begin
                M(I, 1).Status := False;
            end;
        end loop;
        declare
            U : Agent(M(N/2, N-1).Ship_Acc);
        begin
            null;
        end;
        select
            Death_Star.Destroy;
        or
            delay 1.0;
        end select;
        select
            Rebel_Base.Destroy;
        or
            delay 1.0;
        end select;

    end End_Fight;

    function Vege_e return Boolean is
    begin
        return Vege;
    end Vege_e;
end Map;