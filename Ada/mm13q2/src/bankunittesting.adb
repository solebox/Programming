with Bank;
with Accounts;use Accounts;
with Text_IO;use Text_IO;
package body BankUnitTesting is
   procedure deposit_check is
      acc:Account;
   begin
      set(acc,"lala",234234);
      Bank.insert(acc);
      Bank.deposit(234234,100);
      put_line("deposit check: OK");
   exception
      when others =>
         raise Test_Failed;
   end deposit_check;
   procedure withdrawal_check is
      acc:Account;
   begin
      set(acc,"lala",1231);
      Bank.insert(acc);
      Bank.deposit(1231,100);
      Bank.withdrawal(1231,100);
      Put_Line("withdrawal check: OK");
   exception
      when others =>
         raise Test_Failed;
  end withdrawal_check;
   procedure transfer_check is
      acc1,acc2:Account;
   begin
      set(acc1,"lala",011);
      Bank.insert(acc1);
      Bank.deposit(011,100);
      set(acc2,"kaka",022);
      Bank.insert(acc2);
      Bank.deposit(022,100);
      Bank.transfer(011,022,100);
      Put_Line("transfer check: OK");
   exception
      when others =>
         raise Test_Failed;
   end transfer_check;
   procedure get_balance_check is
      acc:Account;
   begin
      set(acc,"lala",666);
      Bank.insert(acc);
      Bank.deposit(666,100);
      if Bank.get_balance(666) = 100 then
         put_line("get balance check: OK");
      end if;
   exception
      when others =>
            raise Test_Failed;
   end get_balance_check;

   procedure get_owner_name_check is
      acc:Account;
   begin
      set(acc,"lala",777);
      Bank.insert(acc);
      Bank.deposit(777,100);
      if Bank.get_owner_name(777) = "lala" then
         put_line("get balance check: OK");
      end if;
   exception
      when others =>
         raise Test_Failed;
   end get_owner_name_check;
end BankUnitTesting;