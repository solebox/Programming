with use_any_structure_protected; use use_any_structure_protected;
with stacks; use stacks;
procedure main is
   s:Stack;
begin
   for i in 1..10 loop
      push(s,i);
   end loop;
   any_structure_protected_use_case(5,-5);
end main;