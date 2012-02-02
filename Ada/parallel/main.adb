with Text_IO; use Text_IO;
procedure main is
    task type Int is
        entry Set(i:in Integer);
        entry Get(i:out Integer);
    end Int;

    task body Int is
        theInt:Integer;
        initialized:Boolean := false;
    begin
        loop
            select
                accept Set(i:in Integer) do
                    theInt := i;
                end Set;
            or
                accept Get(i:out Integer) do
                    i := theInt;
                end Get;
            or
                Terminate;
            end select;
        end loop;
    end Int;
    tmp:Integer;
    tasky:Int;
begin
    tasky.set(3);
    tasky.get(tmp);
    put_line(Integer'Image(tmp));
    null;
end main;
