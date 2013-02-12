package Accounts is
   exceeding_minimum_balance:Exception;
   exceeding_maximum_balance:Exception;
   type Account is private;

   procedure set(acc:in out Account;name:in String;acc_number:in Positive);
   procedure withdrawal(acc:in out Account;amount:in Positive); -- raises exception when pulling money with an overdraft > 100
   procedure deposit(acc:in out Account;amount:in Positive); -- raising exception when depositing more money than upper balance bound (currently its Integer'last)
   procedure transfer(acc1,acc2:in out Account;amount:in Positive); -- raising the above exception if pulling too much from acc1 or pushing too much to acc2 accordingly.

   function balance_inquiry(acc:in Account) return Integer;
   function name_inquiry(acc:in Account) return String;
   function account_number_inquiry(acc:in Account) return Positive;
   function is_initialized(acc:in Account) return Boolean; --checks if set was used on account

private
   type Client is access String;
   subtype Balance is Integer range -100..Integer'LAST;

   type Account is record
      client_name:Client:=null;
      acc_number:Positive;
      acc_balance:Balance;
   end record;
   procedure set(acc:in out Account;name:in String;acc_number:in Positive;acc_balance:in Balance);
end Accounts;