separate(Simulation)
task body Ship is
    Alive: Boolean := True;
begin
    while Alive loop
        select
            accept Hit;
            Printer.Szoveg_Kiir(Azon, Hit);
            if (O = Imperial) then
                select
                    Death_Star.Ship_Lost;
                or
                    delay 0.1;
                end select;
            else
                select 
                    Rebel_Base.Ship_Lost;
                or
                    delay 0.1;                    
                end select;
            end if;
            Alive := False;
        or
            accept Call_Back do
                Printer.Szoveg_Kiir(Azon, Called);
                Alive := False; --termináljon
            end Call_Back;
        or
            delay 0.5; --lőjön Projectile
            
            if (Azon = 69) then
                declare
                    P : Projectile(Imperial, True);
                begin
                    null;
                end;
            else
                if (O = Imperial) then
                    declare
                        P : Projectile(Rebel, False);
                    begin
                        null;
                    end;
                else
                    declare
                        P : Projectile(Imperial, False);
                    begin
                        null;
                    end;
                end if;
            end if;
            Printer.Szoveg_Kiir(Azon, Shoot);
        end select;
    end loop;
end Ship;