with AccountUnitTesting;
with BankUnitTesting;
with Text_IO; use Text_IO;
procedure unit_testing is
begin
   Put_Line("#### Account Unit Testing Start ####");
   AccountUnitTesting.set_check;
   AccountUnitTesting.balance_inquiry_check;
   AccountUnitTesting.name_inquiry_check;
   AccountUnitTesting.account_number_inquiry_check;
   AccountUnitTesting.over_withdrawl_check;
   AccountUnitTesting.deposit_withdrawl_check;
   AccountUnitTesting.transfer_check;
   AccountUnitTesting.transfer_too_much_check;
   Put_Line("#### Account Unit Testing End ####");
   new_line;
   Put_Line("#### Bank Unit Testing Start ####");
   BankUnitTesting.deposit_check;
   BankUnitTesting.withdrawal_check;
   BankUnitTesting.transfer_check;
   BankUnitTesting.get_balance_check;
   BankUnitTesting.get_owner_name_check;
   Put_Line("#### Bank Unit Testing Start ####");

end unit_testing;