with Text_IO; use Text_IO;
procedure main is
    type dad is abstract tagged null record;
    procedure putz(d:dad) is abstract;
    type son is new dad with null record;
    procedure putz(s:son) is
    begin
        null;
    end putz;

begin
    put_line("lol");
end main;
