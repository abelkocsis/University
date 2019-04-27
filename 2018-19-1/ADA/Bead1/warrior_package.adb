package body Warrior_Package is

    procedure Init (W : in out Warrior) is
    begin
        Empty(W.Inventory);
        for I in Resource loop
            Add(W.Inventory, I);
        end loop;
    end Init;

    procedure Fight (W : in out Warrior; O : Obstacle) is
        Need : Resource := Tool(O);
    begin
        if Has_Any(W.Inventory, Need) then
            Remove(W.Inventory, Need);
        else
            W.Status := False;
        end if;
    end Fight;

    procedure Collect (W : in out Warrior; R : in Resource) is
    begin
        Add(W.Inventory, R);
    end Collect;

    function Is_Alive(W: in Warrior) return Boolean is
    begin
        return W.Status;
    end Is_Alive;

end Warrior_Package;