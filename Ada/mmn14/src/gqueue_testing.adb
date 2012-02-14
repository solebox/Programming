with Gqueue;
with Points; use Points;
with TEXT_IO;use Text_IO;
package body Gqueue_Testing is
   procedure add_remove_test is
      package my_queue is new Gqueue(Item => Point,Put_Item => print_point);
      use my_queue;
      q:Queue;
      temp,p1,p2:Point;
   begin
      create(q);
      add(q,p1); -- not initialized the coordinates because im comparing addresses here
      add(q,p2);
      remove(q,temp);
      if temp /= p1 then
         raise TEST_FAILED;
      end if;
      remove(q,temp);
      if temp /= p2 then
         raise TEST_FAILED;
      end if;
      put_line("add_remove: 200 OK");
   end add_remove_test;
   procedure underflow_exception_test is
      package my_queue is new Gqueue(Item => Point,Put_Item => print_point);
      use my_queue;
      q:Queue;
      p:Point;
   begin
      create(q);
      remove(q,p);
   exception
      when CANT_REMOVE_ITEM_FROM_EMPTY_QUEUE =>
         put_line("undeflow: 200 OK");
      when others =>
         raise TEST_FAILED;
   end underflow_exception_test;
   procedure overflow_exception_test is -- to be used only in conjunction with ulimit
      package my_queue is new Gqueue(Item => Point,Put_Item => print_point);
      use my_queue;
      q:Queue;
      p1:Point;
   begin
      create(q);
      while 1 = 1 loop
         add(q,p1);
      end loop;
   exception
      when CANT_ADD_QUEUE_FULL =>
         put_line("overflow: 200 OK ( hope you used ulimit :) )");
      when others =>
         raise TEST_FAILED;
   end overflow_exception_test;
end Gqueue_Testing;