with Text_IO; use Text_IO;
procedure fibo is
    type IntArray is array(Natural range <>) of Integer; 
    type IntArrayPtr is access IntArray;
    function fibor(arr0:IntArrayPtr;n:Integer) return Integer is
    begin
        if n = 0 or n = 1 then
             arr0.all(n) := 1;
            return 1;
        else
            arr0.all(n) := fibor(arr0,n-1)+fibor(arr0,n-2);
            return arr0.all(n);
        end if;
    end fibor;
    arr1:IntArrayPtr := new IntArray(0..45);
    temp:Integer;
begin
    temp := fibor(arr1,45);
    for i in arr1'range loop
        put_line(Integer'Image(arr1(i)));    
    end loop;

end fibo;
