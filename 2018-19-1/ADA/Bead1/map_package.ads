generic
    type Field is (<>);
    type Warrior is private;
    with procedure Field_Action(F: in out Field; W: in out Warrior);
    Empty : Field;
package Map_Package is

    type Map(N: Positive) is private;
    type Irany is new Integer range 1..4;
    procedure Init (M : in out Map);
    procedure Put (M : in Map);
    procedure Move (M : in out Map; W : in out Warrior);
    function Is_Empty (M : in Map) return Boolean;
    procedure Set(M: in Map; I: in Irany; X : in out Positive; Y: in out Positive);

private
    type Fields_Array is array(Positive range<>, Positive range<>) of Field;
    type Pos is record
        X : Positive := 1;
        Y : Positive := 1;
    end record;

    type Map (N : Positive) is record
        Fields : Fields_Array(1..N, 1..N);
        Position : Pos;
    end record;

end Map_Package;