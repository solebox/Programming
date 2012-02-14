package body find_sum_pack is
   function find_sum(A:in Input; Sum: in Integer) return natural is
      protected outer_counter is
         procedure add(how_much:in Natural);
         function get_value return Integer;
      private
         the_outer_counter:Integer := 0;
      end outer_counter;

      protected body outer_counter is
         procedure add(how_much:in Natural) is
         begin
            the_outer_counter := the_outer_counter + how_much;
         end add;

         function get_value return Integer is
         begin
            return the_outer_counter;
         end get_value;
      end outer_counter;

      task type worker is
         entry start(i:in Integer);
         entry finish;
      end worker;

      task body worker is
         inner_counter:Natural := 0;
         task_i:Integer;
      begin
         loop
	        select
	            accept start(i:in Integer) do
	               task_i := i;
	            end start;
	            for j in (task_i+1)..A'Last loop
	               if (A(task_i)+A(j)) = sum then
	                  inner_counter := inner_counter + 1;
	               end if;
	            end loop;
	            outer_counter.add(inner_counter);
	         or
	            accept finish do
	               null;
	            end;
	         or
	            terminate;
	         end select;
            end loop;
      end worker;
      type WorkerArray is array(positive range <>) of worker;
      my_worker_array:WorkerArray(1..(A'Last-1));
   begin
      for i in my_worker_array'range loop
         my_worker_array(i).start(i);
      end loop;
      for i in my_worker_array'range loop
         my_worker_array(i).finish;
      end loop;
      return outer_counter.get_value;
   end find_sum;
end find_sum_pack;