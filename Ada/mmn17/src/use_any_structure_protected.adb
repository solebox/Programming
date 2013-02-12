with Text_IO; use Text_IO;

package body use_any_structure_protected is
   package my_any_structure_pack is new Any_Structure(structure => stack, Element => Integer,init => init, insert => push,remove => pop );
   package my_any_structure_protected_pack is new Any_Structure_Protected(my_any_structure_pack);
   use my_any_structure_protected_pack;


   procedure any_structure_protected_use_case(m,n:in Integer) is
      p_stack:protected_structure;
      task print_stack is
         entry stack_writer_done;
      end print_stack;
      task type stack_writer is
         entry start_positive(m:in Integer);
         entry start_negative(n:in Integer);
      end stack_writer;

      task body stack_writer is
         task_n:Integer range Integer'First..-1;
         task_m:Integer range 1..Integer'Last;

      begin
         select
            accept start_positive(m:in Integer) do
               task_m := m;
            end start_positive;
            for i in 1..task_m loop
               p_stack.insert(i);
               delay 1.0; -- 1.0
            end loop;
             print_stack.stack_writer_done;
         or
            accept start_negative(n:in Integer) do
               task_n := n;
            end start_negative;
            for i in reverse task_n..-1 loop
               p_stack.insert(i);
               delay 0.5; -- 0.5
            end loop;
            print_stack.stack_writer_done;
         or
            Terminate;
         end select;
      end stack_writer;



      task body print_stack is
         number:Integer;
         counter:Natural := 0;
      begin
         loop
            select
               accept stack_writer_done do
                  null;
               end stack_writer_done;
               counter := counter + 1;
               if counter = 2 then
                  begin
                     for i in 0..(m-n) loop
                        p_stack.remove(number);
                        put_line(Integer'Image(number));
                     end loop;
                  exception
                     when others =>
                        raise STACK_PRINTING_HAS_FAILED;
                  end;
               end if;
            or
                 terminate;
            end select;
         end loop;
      end print_stack;

      type stack_writer_array is array(positive range <>) of stack_writer;
      my_stack_writer_array:stack_writer_array(1..2);
   begin
      if n >= 0 or m <= 0 then
         raise INVALID_INPUT_FOR_EXAMPLE_PROCEDURE;
      end if;
      p_stack.init;
      my_stack_writer_array(1).start_positive(m);
      my_stack_writer_array(2).start_negative(n);
   end any_structure_protected_use_case;


end use_any_structure_protected;