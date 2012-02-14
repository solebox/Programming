with GNAT.IO;  use GNAT.IO;
with Accounts; use Accounts;
with Bank;
procedure banking is
   acc1:Account;
   acc2:Account;
   acc3:Account;
begin
   set(acc => acc1,name => "George",acc_number => 8493729);
   set(acc => acc2, name => "Sara", acc_number => 2342987);
   set(acc => acc3, name => "Robert", acc_number => 2342983);
   deposit(acc1,100);
   deposit(acc2,200);
   deposit(acc3,300);
   Bank.insert(acc1);
   Bank.insert(acc2);
   Bank.insert(acc3);
   Bank.deposit(2342983,100);
   Bank.withdrawal(2342983,100);
   Bank.transfer(2342983,8493729,100);
   Bank.withdrawal(account_number_inquiry(acc3),300);
   Bank.put_all;
   Put_Line ("Ohayo Mondo!");
end banking;
