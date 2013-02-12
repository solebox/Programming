with Gqueue_Testing; use Gqueue_Testing;
procedure run_tests is
begin
    add_remove_test;
    underflow_exception_test;
  --  overflow_exception_test; -- activate ulimit before initiating an infinit loop that will hog all your memory :)
end run_tests;