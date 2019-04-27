--    type Index is (<>); -- 1..6
--    type Counter is private; --természetes szám
package body Bag_Package is

    procedure Empty(H: in out Bag) is
    begin
        for I in Index loop
            H(I) := Counter'First;
        end loop;
    end Empty;

    procedure Add(H: in out Bag; I: Index) is
    begin
        H(I) := Counter'Succ(H(I));
    end Add;

    procedure Remove(H: in out Bag; I: Index) is
    begin
        H(I) := Counter'Pred(H(I));
    end Remove;

    function Has_Any(H: in out Bag; I: Index) return Boolean is
    begin
        return H(I) > Counter'First;
    end Has_Any;

end Bag_Package;