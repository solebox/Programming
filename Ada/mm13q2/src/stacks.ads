package Stacks is
   type Stack is private;
   procedure pop(s:in out Stack) return Integer;
   procedure push(s:in out Stack;num:Integer);
   function top(s:in Stack) return Integer;
private
   type Node;
   type NodePtr is access Node;
   type Node is record
      key:Integer;
      next,prev:NodePtr;
   end record;
   type Stack is record
      first,last:NodePtr;
      size:Integer;
   end record;
end Stacks;