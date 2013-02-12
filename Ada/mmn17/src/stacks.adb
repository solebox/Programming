package body stacks is

   procedure init(a_stack:out Stack) is
   begin
      a_stack.size := 0;
      a_stack.head := 1;
      a_stack.tail := 1;
      a_stack.data := (others => 0);
   end init;

   procedure push(a_stack:in out Stack; an_element:in Integer) is
   begin
      if a_stack.size = STACK_MAX_SIZE then
         raise OVERFLOW;
      end if;
      a_stack.data(a_stack.tail) := an_element;
      a_stack.tail := a_stack.tail + 1;
      a_stack.size := a_stack.size + 1;
   end push;

   procedure pop(a_stack:in out Stack; an_element:out Integer) is
   begin
      if a_stack.size = 0 then
         raise UNDERFLOW;
      end if;
      a_stack.tail := a_stack.tail - 1;
      an_element := a_stack.data(a_stack.tail);
      a_stack.size := a_stack.size - 1;
   end pop;

   function size(a_stack:in Stack) return Natural is
   begin
      return a_stack.size;
   end size;

end stacks;