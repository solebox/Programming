--with text_io; use text_io;
with dot_product;

package body unit_testing_for_dot_product is

   function int_with_int return boolean is
      type vector1 is array (positive range<>) of integer;
      vec1: vector1:=(1,2,3);
      type vector2 is array (positive range<>) of integer;
      vec2: vector2:=(-1,5,-5);
      flag:boolean:=false;

      function int_with_int is new dot_product(LIndex => positive, LItem =>integer,
      LVec =>vector1,RIndex => positive, RItem =>integer,RVec =>vector2, Result=>integer,"*"=>"*","+"=>"+");
        begin
         flag:=int_with_int(vec1, vec2)=-6;
         return flag;
      end int_with_int;

   function float_with_float return boolean is
   type vector1 is array (positive range<>) of float;
      vec1: vector1:=(1.0,2.0,3.0);
      type vector2 is array (positive range<>) of float;
      vec2: vector2:=(-1.0,5.0,-5.0);
      flag:boolean:=false;

      function fl_with_fl is new dot_product(LIndex=> positive,LItem => float,
      LVec => vector1,RIndex=> positive, RItem => float,RVec=>vector2, Result=>float,"*"=>"*","+"=>"+");

      begin
         flag:=fl_with_fl(vec1, vec2)=-6.0;
         return flag;
      end float_with_float;


--function float_with_int return boolean;

end unit_testing_for_dot_product;
