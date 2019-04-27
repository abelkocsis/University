with Ada.Numerics.Discrete_Random, Bag_Package, Ada.Integer_Text_IO, Ada.Text_IO, Warrior_Package, Map_Package;
use  Ada.Integer_Text_IO, Ada.Text_IO;

procedure Simulation is
    type Field is (Empty, Stone, Wood, Sword, Water, Trap, Enemy);
    subtype Resource is Field range Stone .. Sword;
    subtype Obstacle is Field range Water .. Enemy;

    function Tool (O : in Obstacle) return Resource is
    begin
        if O = Water then
            return Stone;
        end if;
        if O = Trap then
            return Wood;
        end if;
        if O = Enemy then
            return Sword;
        end if;
        return Stone;
    end Tool;


    package My_Bag is new Bag_Package(Index => Resource, Counter => Integer);
   
    package My_Warrior is new Warrior_Package(
        Resource =>         Resource,
        Obstacle =>         Obstacle,
        Tool =>             Tool,
        Bag =>              My_Bag.Bag,
        Empty =>            My_Bag.Empty,
        Add =>              My_Bag.Add,
        Remove =>           My_Bag.Remove,
        Has_Any =>          My_Bag.Has_Any

    );
    use My_Warrior;

    procedure Field_Action(F: in out Field; W: in out Warrior) is
    begin
        if F in Resource then
            Collect(W, F);
            Put("Collect: ");
            Put_Line(Resource'Image(F));
        end if;
        if F in Obstacle then
            Fight(W, F);
            Put("Fight: ");
            Put_Line(Obstacle'Image(F));
        end if;
        if Is_Alive(W) then
            F := Empty;
        end if;
        Put_Line("");
    end Field_Action;

    package My_Map is new Map_Package(
        Field =>            Field,
        Warrior =>          Warrior,
        Field_Action =>     Field_Action,
        Empty =>            Empty
    );
    use My_Map;

    MW : Warrior;
    S : Positive;
    
begin
    Put_Line("Adja meg a pálya méretét!");
    Get(S);
    Put_Line("Köszönöm!");
    Put_Line("Játék kezdése:");
    declare
        MM : Map(S);
    begin
        My_Map.Init(MM);
        My_Warrior.Init(MW);
        Put(MM);
        while Is_Alive(MW) AND NOT Is_Empty(MM) loop
            Move(MM, MW);
        end loop;
        Put(MM);
        if Is_Alive(MW) then
            Put_Line("WON!");
        else
            Put_Line("Lost :(");
        end if;
    end;
    
    
end Simulation;