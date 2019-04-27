separate (Simulation)
task body Agent is
begin
    select
        A.Call_Back;
    or
        delay 1.0;
    end select;
    
end Agent;