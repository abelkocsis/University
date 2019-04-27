with Ada.Integer_Text_IO, Ada.Text_IO;
use  Ada.Integer_Text_IO, Ada.Text_IO;

procedure Torlendo is
    K : Integer := Integer'Last;
begin
    K := K + 1;
    if not K'Valid then
        K := Integer'First;
    end if;
end Torlendo;