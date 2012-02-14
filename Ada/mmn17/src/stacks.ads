package stacks is
   -- well its a regular stack,
   -- just used as an example so i do not see why it should be documented
   type Stack is private;

   procedure init(a_stack:out Stack);
   procedure push(a_stack:in out Stack; an_element:in Integer);
   procedure pop(a_stack:in out Stack; an_element:out Integer);
   function size(a_stack:in Stack) return Natural;
   STACK_MAX_SIZE:constant Positive := 100;
   UNDERFLOW,OVERFLOW:exception;
private

   type Stack_Data is Array(positive range <>) of Integer;

   type Stack is record
      data:Stack_Data(1..STACK_MAX_SIZE);
      head,tail:Positive := 1;
      size:Natural := 0;
   end record;



end stacks;