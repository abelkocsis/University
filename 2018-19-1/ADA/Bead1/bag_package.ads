generic
    type Index is (<>); -- 1..6
    type Counter is (<>); --természetes szám
package Bag_Package is

    type Bag is private;

    procedure Empty(H: in out Bag);

    procedure Add(H: in out Bag; I: Index);

    procedure Remove(H: in out Bag; I: Index);
    
    function Has_Any(H: in out Bag; I: Index) return Boolean;

private

    type Bag is array(Index) of Counter;

end Bag_Package;