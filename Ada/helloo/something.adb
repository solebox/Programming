with ada.text_io; use ada.text_io;

procedure table1 is
    start, finish: Integer;   -- Beginning and end of table
begin
    -- Output header
    put_line("          I       I**2       I**3");
    start := 2;
    for i in start .. finish loop
        put(i, 11);
        put(i**2, 11);
        new_line;
    end loop;

    numberOfRows := finish - start + 1;

    if numberOfRows <= 0 then
        put_line("Start:" & Integer'image(start));
    elsif numberOfRows = 1 then
        put_line("Start and finish are the same!");
    else
        put("Number of rows: ");
    end if;
end table1;

