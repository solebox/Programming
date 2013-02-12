-- written by jacob kilimnik and yair gam
-- jacob's email: solekiller@gmail.com
-- yair gam's email: gamyair@gmail.com
-- this progam is a generic queue package for any type of Items specified.
-- type Item is the type of the items that will reside in the queue
-- procedure put_item is the procedure to put the items with when needed that will be passed at instanciation to the
-- generic queue alongside with the item type for further usage in its internal functions/procedures
generic
   type Item is private;
   with procedure put_item(item_in:in Item);
package Gqueue is
   -- this is the type of the queue , its limited private since the resulting queues shouldnt be compared or asigned
   -- using the regular operands by the user, if at all needed specific procedures/function will be written.
   type Queue is limited private;
   -- a procedure for adding an item to the queue
   -- q - the qeue itself
   -- item_in - the item to add to the given queue
   procedure add(q:in out Queue;item_in:Item);
   -- a procedure to remove an item from a given queue and return it:
   -- q - the queue to remove from
   -- item_out - the variable into which the returned item will be assigned
   procedure remove(q:in out Queue;item_out:out Item);
   -- a procedure that prints out all elements that reside in the queue
   -- q - the queue to print out to STDOUT
   procedure print(q:Queue);
   -- a procedure to create an initialized queue (ada is so grand that this procedure might seem a tad redundant in out case)
   -- q_io - the variable to which the created queue will be asigned
   procedure create(q_io:in out Queue); -- cant make it a pretty function because Queue is limited private,
                                        -- i had more reasons to make it a limited private than to make create a function.

   -- a function that returns a queue's size
   -- q - the queue who's size is in question
   function size(q:Queue) return Natural;


   CANT_REMOVE_ITEM_FROM_EMPTY_QUEUE:exception;
   CANT_ADD_QUEUE_FULL:exception;

private
   type QueueNode;
   type QueueNodePtr is access QueueNode;
   type QueueNode is record
      key:Item;
      next:QueueNodePtr;
   end record;
  type Queue is record
         head:QueueNodePtr := null;
         size:Natural := 0;
   end record;
end Gqueue;