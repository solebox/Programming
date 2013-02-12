--Points.adb
with Text_IO; use Text_IO;
package body Points is

   procedure set(p:in out Point; x,y:in Coordinate) is
   begin
      p.x := x;
      p.y := y;
   end set;
   procedure put(p:in Point) is
   begin
      Text_IO.Put_Line("Point Coordinates: X=>"&Coordinate'image(p.x)&
                       ", Y=>"&Coordinate'image(p.y));
   end put;
   function "+"(p1,p2:in Point) return Point is
      res:Point;
   begin
      res := (p1.x+p2.x,p1.y+p2.y);
     return  res;
   end "+";
   function "-"(p1,p2:in Point) return Point is
      res:Point := (p1.x-p2.x,p1.y-p2.y);
   begin
      return res;
   end "-";


end Points;