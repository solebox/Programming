--Points.ads
package Points is
   type Coordinate is new float;
   type Point is Private;

   procedure set(P:in out Point; x,y:in Coordinate);
   procedure put(P:in Point);

   function "+"(P1,P2:in Point) return Point;
   function "-"(P1,P2:in Point) return Point;

Private
   type Point is record
      x:Coordinate;
      y:Coordinate;
   end record;
end Points;