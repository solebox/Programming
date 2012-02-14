with stacks; use stacks;
with any_structure;
with Any_Structure_Protected;
package use_any_structure_protected is
    -- the usecase that was requested in the question
   procedure any_structure_protected_use_case(m,n:in Integer);

   STACK_PRINTING_HAS_FAILED:exception;
   INVALID_INPUT_FOR_EXAMPLE_PROCEDURE:exception;

end use_any_structure_protected;