-- this is a generic package that gets as a parameter any instance of any_structure and turns it into a protected structure
with Any_Structure;
generic
   with package the_any_structure_pack is new Any_Structure(<>);
   use the_any_structure_pack;
package Any_Structure_Protected is

   protected type protected_structure is
      -- this function initializes the protected data structure
      procedure init;
      -- this function inserts the given element E into the data structure we are protecting
      procedure insert(E: in Element);
      -- this function removes the first element and returns it inside E for further use.
      procedure remove(E: out Element);
   private
      myStructure:Structure;
   end protected_structure;

end Any_Structure_Protected;