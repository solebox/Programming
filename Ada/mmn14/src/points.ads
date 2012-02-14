-- a tiny point package used only for the mere usage exaple of gqueue
package Points is
   type Point is private;

   procedure print_point(p:in Point);
   procedure set_coordinates(p:in out Point;x,y:in Integer);
private
   type Point is record
      x,y:Integer := 0;
   end record;
end Points;