with text_io; use text_io;
with unit_testing_for_dot_product; use unit_testing_for_dot_product;
procedure use_unit_testing_for_dot_product is
         begin
        put_line("hello");
        if int_with_int then
           put_line(" int with int is O.K.");
        else
           put_line("There is a problem on int with int");
        end if;
        if float_with_float then
           put_line(" float with float is O.K.");
        else
           put_line("There is a problem on float with float");
        end if;

end  use_unit_testing_for_dot_product;




