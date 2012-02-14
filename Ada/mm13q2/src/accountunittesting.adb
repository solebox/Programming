with Accounts; use Accounts;
with Text_IO; use Text_IO;
package body AccountUnitTesting is
   procedure set_check is
      acc:Account;
   begin
      set(acc,"lala",200);
      put_line("set check: OK");
   exception
      when others =>
        raise Test_Failed;
   end set_check;
   procedure balance_inquiry_check is
      acc:Account;
   begin
      set(acc,"lala",100);
      deposit(acc,200);
      if balance_inquiry(acc) = 200 then
         Put_Line("balance_inquiry check: OK");
      else
         raise Test_failed;
      end if;
   exception
      when others =>
         raise Test_Failed;
   end balance_inquiry_check;
   procedure name_inquiry_check is
      acc:Account;
   begin
      set(acc,"Lala",200);
      if name_inquiry(acc) = "Lala" then
         Put_Line("name inquiry check: OK");
      else
         raise Test_Failed;
      end if;
   exception
      when others =>
         raise Test_Failed;
   end name_inquiry_check;
   procedure account_number_inquiry_check is
      acc:Account;
   begin
      set(acc,"nna",28930);
      if account_number_inquiry(acc) = 28930 then
         put_line("account number inquiry check: OK");
      else
         raise Test_Failed;
      end if;
   exception
      when others =>
         raise Test_Failed;
   end account_number_inquiry_check;
   procedure over_withdrawl_check is
      acc:Account;
   begin
      set(acc,"lala",222);
      deposit(acc,100);
      withdrawal(acc,201);
   exception
      when exceeding_minimum_balance =>
         put_line("over withdrawal check: OK");
      when others =>
         raise Test_Failed;
   end over_withdrawl_check;
   procedure deposit_withdrawl_check is
      acc:Account;
   begin
      set(acc,"ada",121);
      deposit(acc,300);
      withdrawal(acc,100);
      if balance_inquiry(acc) = 200 then
         Put_Line("deposit_withdrawl_check: OK");
      else
         raise Test_Failed;
      end if;
   exception
      when others =>
         raise Test_Failed;
   end deposit_withdrawl_check;
   procedure transfer_check is
      acc1:Account;
      acc2:Account;
   begin
      set(acc1,"lamba",222);
      set(acc2,"kamba",111);
      deposit(acc1,200);
      deposit(acc2,100);
      transfer(acc1,acc2,100);
      if balance_inquiry(acc1) = 100 and balance_inquiry(acc2) = 200 then
         Put_Line("transfer check: OK");
      else
         raise Test_Failed;
      end if;
   exception
      when others =>
         raise Test_Failed;
   end transfer_check;
   procedure transfer_too_much_check is
      acc1:Account;
      acc2:Account;
   begin
      set(acc1,"mama",1);
      set(acc2,"papa",2);
      deposit(acc1,100);
      deposit(acc2,100);
      transfer(acc1,acc2,100);
      transfer(acc1,acc2,100);
      begin
         transfer(acc1,acc2,100);
      exception
         when exceeding_minimum_balance =>
            Put_line("transfer too much check: OK");
         when others =>
            raise Test_Failed;
      end;
   exception
      when others =>
        raise Test_Failed;
   end transfer_too_much_check;

end AccountUnitTesting;