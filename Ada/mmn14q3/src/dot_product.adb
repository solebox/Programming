function dot_product(leftv: Lvec;rightv:Rvec) return Result is
   type ResultPtr is access Result;
   li:LIndex;
   ri:RIndex;
   rp:ResultPtr;
begin
   -- deal with empty vectors ::fixme::
   li := leftv'FIRST;
   ri := rightv'FIRST;
   rp := new Result'(leftv(li) *  rightv(ri));
   ri := RIndex'SUCC(ri);
   li := LIndex'SUCC(li);
   if leftv'LENGTH <= rightv'LENGTH then
      for i in li..leftv'LAST loop
         rp := new Result'(rp.all + (leftv(i)*rightv(ri)));
         ri := RIndex'SUCC(ri);
      end loop;
      -- do this
   else
      for i in ri..rightv'LAST loop
         rp := new Result'(rp.all + (leftv(li)*rightv(i)));
         li := LIndex'SUCC(li);
      end loop;
      -- do that
   end if;
   return rp.all;
end dot_product;