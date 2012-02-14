with Text_IO; use Text_IO;
package body Points is
   Procedure print_point(p:in Point) is
   begin
      put("x: "& Integer'image(p.x)&" y: "& Integer'image(p.y));
   end print_point;
   procedure set_coordinates(p:in out Point;x,y:Integer) is
   begin
      p.x := x;
      p.y := y;
   end set_coordinates;
end Points;