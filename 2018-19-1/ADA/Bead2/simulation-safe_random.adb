separate (Simulation)
protected body Safe_Random is
    function Get_Coordinates return Coordinates is
        A : Coordinates;
    begin
        Reset(Rand);
        A.X := Random(Rand);
        A.Y := Random(Rand);
        return A;
    end Get_Coordinates;
end Safe_Random;