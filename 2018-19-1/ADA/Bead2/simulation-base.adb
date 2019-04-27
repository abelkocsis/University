separate(Simulation)
task body Base is
    Hajoszam : Integer;
    D : Boolean := True;
begin
    while (D) loop
        select
            accept Send_Out_Ships( N : in Integer) do
                Hajoszam := N;
            end Send_Out_Ships;
        or
            accept Ship_Lost;
            Hajoszam := Hajoszam - 1;
            if (Hajoszam = 0) then
                D := False;
                Map.End_Fight;
            end if;
            Map.KiIr;
        or
            accept Destroy;
            Hajoszam := 0;
            D := False;
            Map.End_Fight;
        or
            delay 0.1;
        end select;
    end loop;
end Base;