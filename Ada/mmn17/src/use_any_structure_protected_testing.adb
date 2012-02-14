with Text_IO; use Text_IO;
package body use_any_structure_protected_testing is
   package my_any_structure_pack is new Any_Structure(structure => stack, Element => Integer,init => init, insert => push,remove => pop );
   package my_any_structure_protected_pack is new Any_Structure_Protected(my_any_structure_pack);
   use my_any_structure_protected_pack;

   procedure test_insert_and_remove is
      struct:protected_structure;
      num:Integer;
   begin
      struct.init;
      struct.insert(3);
      struct.remove(num);
      if num != 3 then
         raise TEST_FAILED;
      end if;
   exception
      when others =>
         raise TEST_FAILED;
   end test_insert_and_remove;

end use_any_structure_protected_testing;
