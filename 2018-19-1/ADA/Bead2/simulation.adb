with Ada.Numerics.Discrete_Random, Ada.Text_IO;
use Ada.Text_IO;

procedure Simulation is
    N : Integer := 10;
    subtype Size is Integer range 1..N; 
    package Random_Size is new Ada.Numerics.Discrete_Random (Size);
    use Random_Size;
    Rand: Generator;

    type Oldal is (Imperial, Rebel);
    type Esemeny is (Called, Hit, Shoot, Ended, Luk);

    type Coordinates is record
        X : Integer;
        Y : Integer;
    end record;

    protected Safe_Random is
        function Get_Coordinates return Coordinates;
    end Safe_Random;
    protected body Safe_Random is separate;
    
    type Char_Array is array (1..N, 1..N) of Character;
    type Szoveg is array(1..2) of Character;

    protected Printer is
        procedure Szoveg_Kiir(Azon : Integer; E : Esemeny);
        procedure Matrix_Kiir(M : Char_Array) ;
    end Printer;
    protected body Printer is separate;
    
    task type Base (O : Oldal) is
        entry Send_Out_Ships( N : in Integer);
        entry Ship_Lost;
        entry Destroy;
    end Base; 

   

    Death_Star : Base(Imperial);
    Rebel_Base : Base(Rebel);

    task type Ship ( Azon : Integer; O: Oldal) is
        entry Hit;
        entry Call_Back;
    end Ship;
    

    type Ship_Access is access Ship;

    type Mezo is record
            Ship_Acc : Ship_Access;
            Status : Boolean := False;
    end record;
    type Matrix is array (1..N, 1..N) of Mezo;


    protected Map is
        function Get_Hajo(C : Coordinates) return Ship_Access;
        function Get_Status(C : Coordinates) return Boolean;
        procedure Init;
        procedure End_Fight;
        procedure KiIr;
        procedure Change_Status(C: Coordinates);
        procedure Luke_Is_Here;
        function Vege_e return Boolean;
    private
        Vege: Boolean := False; 
        M : Matrix;
    end Map;

    task body Base is separate;

    task type Projectile (O : Oldal; Luke: Boolean) is
    end Projectile;

    task body Projectile is separate;

    task type Agent ( A : Ship_Access) is
    end Agent;
    task body Agent is separate; 

    protected body Map is separate;

    task body Ship is separate;
    

begin
    Map.Init;
    Map.KiIr;
    delay 5.0;
    if (not Map.Vege_e) then 
        Map.Luke_Is_Here;
    end if;
    Map.KiIr;
end Simulation;