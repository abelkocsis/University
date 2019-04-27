separate(Simulation)
task body Projectile is
    C : Coordinates;
begin
    C := Safe_Random.Get_Coordinates;
    if (Luke) then
        if (C.X = C.Y) then
            select
                Death_Star.Destroy;
            or
                delay 0.1;
            end select;
            Printer.Szoveg_Kiir(69, Luk);
        end if;
    else
        if (Map.Get_Status(C) and then Map.Get_Hajo(C).O = O) then
            select
                Map.Get_Hajo(C).Hit;
                Map.Change_Status(C);
            or
                delay 0.0;
            end select;
            Map.KiIr;
        end if;
    end if;
end Projectile;