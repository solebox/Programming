-- this is the unit testing package
-- made by kobi and yair gam
-- kobi email: solekiller@gmail.com
-- yair email: gamyair@gmail.com
package Gqueue_Testing is
   -- testing for add and remove if all elements are added and removed in the correct order
   procedure add_remove_test;
   -- testing for an underflow exception existance or in other words proper undeflow handling
   procedure underflow_exception_test;
   -- testing for a proper overflow handling procedure or in other words an existance of an overflow exception
   -- not wise to use on linked lists without a ulimit... be warned memory will be hogged
   procedure overflow_exception_test; -- to be used only in conjunction with ulimit
   TEST_FAILED:exception;
end Gqueue_Testing;