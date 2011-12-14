--main.adb
with Text_IO; use Text_IO;
Procedure main is
   type Month is (jan,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec);
   type Year is array(Positive range 1..12) of Month;
   yea:Year;
   str:string(1..55);
   len:integer;
begin
    get_line(str,len);
    for i in 1..len loop
        put(str(i));
    end loop;
   new_line;
end main;
