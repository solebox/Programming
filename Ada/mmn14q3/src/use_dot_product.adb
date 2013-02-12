with GNAT.IO;  use GNAT.IO;
with dot_product;
-- this is the main program that uses the dot_product function
-- it also demonstrates the usage of dot product with an array of chars and an array of positive numbers
-- contact information:
-- solekiller@gmail.com
-- name: solekiller
-- gamyair@gmail.com
-- name: yair gam
procedure use_dot_product is
   type Numrr is array (Positive range <>) of positive;
   -- defining the "*" function that will be used in this case
   function multiply_ch(ch:Character;num:Positive) return String is
      type StrPtr is access String;
      stpt:StrPtr;
   begin
      stpt := new String'("");
      for i in 1..num loop
         stpt := new String'(stpt.all & ch);
      end loop;
      return stpt.all;
   end multiply_ch;
-- seif bet
   function my_dot_product is new dot_product(LIndex => Positive, LItem => Character, LVec => String,
                                              RIndex => Positive, RItem => Positive, RVec => Numrr,
                                              Result => String,
                                              "*" => multiply_ch,
                                              "+" => "&");
   s1:constant String(1..5) := "hello";
   numrr1:constant Numrr(1..5) := (1,3,2,2,3);
begin
      put_line(my_dot_product(s1,numrr1));
end use_dot_product;
