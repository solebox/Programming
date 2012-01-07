--main.adb
with Text_IO; use Text_IO;
Procedure main is
   type Month is (jan,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec);
   type Year is array(Positive range 1..12) of Month;
   type StringPtr is access String;
   type i_acc is access integer;
   yea:Year;
   str:string(1..55);
   len:integer;
    function foo(S:String) return String is
        stpt:StringPtr;
        i:i_acc;
    begin
       stpt := new String'(S&S&S); 
        return stpt.all;
    end foo;
begin
    get_line(str,len);
        put(foo(str(1..len)));
   new_line;
   for i in 1..1 loop
       put_line("wazzzzzzza");
   end loop;
end main;
