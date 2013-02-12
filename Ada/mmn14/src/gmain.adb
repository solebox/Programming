with Gqueue;
with Points; use Points;
-- the main procedure that shows the generic package's usage.
-- as requested in question 2 clause gimel
procedure Gmain is
   -- instanciating of the package for Point records(Point ADT)
   package my_queue is new Gqueue(Item => Point,Put_Item => print_point);
   use my_queue;
   q1,q2:my_queue.Queue;
   p0,p1,p2,p3,p4:Point;
begin
   -- creating the queues:
   create(q1);
   create(q2);
   -- setting the point values
   set_coordinates(p1,1,2);
   set_coordinates(p2,3,4);
   set_coordinates(p3,5,6);
   set_coordinates(p4,7,8);
   -- setting the point values end
   -- using the queues
   add(q1,p0);
   remove(q1,p0);
   add(q1,p1);
   add(q1,p2);
   add(q2,p3);
   add(q2,p4);
   -- printing the queues just in case (wasn't asked for)
   print(q1);
   print(q2);
end Gmain;