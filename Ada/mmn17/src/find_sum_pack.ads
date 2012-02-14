package find_sum_pack is
   type Input is array(positive range <>) of Integer;
   function find_sum(A:in Input; Sum: in Integer) return Natural;
end find_sum_pack;