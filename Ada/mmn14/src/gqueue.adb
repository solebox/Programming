with Text_IO;use Text_IO;
package body Gqueue is
   function is_empty(q:in Queue) return Boolean is
   begin
      return q.head = null;
   end is_empty;

   procedure add(q:in out Queue;item_in:Item) is
      p:QueueNodePtr := q.head;
   begin
      if is_empty(q) then
         q.head := new QueueNode'(key => item_in,next => null);
         q.size := 1;
      else
         while p.next /= null loop
            p := p.next;
         end loop;
         pragma assert(p.next = null,"in add() p.next is not null");
         p.next := new QueueNode'(key => item_in, next => null);
         q.size := q.size + 1;
      end if;
   exception
      when Storage_Error =>
         raise CANT_ADD_QUEUE_FULL;
   end add;
   procedure remove(q:in out Queue;item_out:out Item) is
      p:QueueNodePtr := q.head;
   begin
      if is_empty(q) then
         raise CANT_REMOVE_ITEM_FROM_EMPTY_QUEUE;
      else
         q.head := p.next;
         item_out :=  p.key;
         q.size := q.size - 1;
      end if;
   end remove;

   procedure print(q:Queue) is
      p:QueueNodePtr := q.head;
   begin
      while p /= null loop
         put_item(p.key);
         new_line;
         p := p.next;
      end loop;
   end print;
   function size(q:Queue) return Natural is
   begin
      return q.size;
   end size;
   procedure create(q_io:in out Queue) is
      q:Queue;
   begin
      q.size := 0;
      q.head := null;
      q_io := q;
   end create;
end Gqueue;