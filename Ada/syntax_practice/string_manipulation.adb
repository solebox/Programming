--main.adb
with is_prime;
with Ada.Text_IO; use Ada.Text_IO;
procedure main is
   str1:string(1..100);
   str1_len:positive;
begin--
   Get_Line(str1,str1_len);
   for i in 1..str1_len loop
      if str1(i) = 'f' then
         str1(i) := '*';
      end if;
   end loop;
   put_line(str1(1..str1_len));
end main;
--
