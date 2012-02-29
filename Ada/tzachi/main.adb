with Text_IO; use Text_IO;
procedure main is
    type dad is abstract tagged null record;
    procedure putz(d:dad) is abstract;
    type son is new dad with null record;
    procedure putz(s:son) is
    begin
        null;
    end putz;
    num1,num2,num3:Float;
begin
    num1 := 0.1;
    num2 := 0.2;
    num3 := 0.3;
    put_line(Float'image( num1 + (num2 + num3) ));
end main;
