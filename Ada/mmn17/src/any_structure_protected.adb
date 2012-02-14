package body Any_Structure_Protected is
   protected body protected_structure is

      procedure init is
      begin
         the_any_structure_pack.init(myStructure);
      end init;

      procedure insert(E: in Element) is
      begin
         the_any_structure_pack.insert(myStructure,E);
      end insert;

      procedure remove(E: out Element) is
      begin
         the_any_structure_pack.remove(myStructure,E);
      end remove;

   end protected_structure;
end Any_Structure_Protected;