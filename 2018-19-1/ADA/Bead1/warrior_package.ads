generic
    type Resource is (<>);
    type Obstacle is (<>);
    with function Tool(O : in Obstacle) return Resource;
    type Bag is private;

    with procedure Empty(B : in out Bag);
    with procedure Add(B: in out Bag; I: Resource);
    with procedure Remove(B: in out Bag; I: Resource);
    with function Has_Any(B: in out Bag; I: Resource) return Boolean;
package Warrior_Package is
    type Warrior is private;

    procedure Init (W : in out Warrior);

    procedure Fight (W : in out Warrior; O : Obstacle);

    procedure Collect (W : in out Warrior; R : in Resource);

    function Is_Alive(W: in Warrior) return Boolean;

private
    type Warrior is record
        Status : Boolean := True;
        Inventory : Bag;
    end record;
end Warrior_Package;