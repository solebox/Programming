with find_sum_pack; use find_sum_pack;
with Text_IO; use Text_IO;
procedure use_find_sum is
   A:constant Input := (1,2,3,4,5,6);

begin
   put_line(Integer'image(find_sum(A,7)));
end use_find_sum;
