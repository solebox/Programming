package body Accounts is
   procedure set(acc:in out Account;name:in String;acc_number:in Positive;acc_balance:in Balance) is
   begin
      acc.client_name := new String'(name);
      acc.acc_number := acc_number;
      acc.acc_balance := acc_balance;
   end set;
   procedure set(acc:in out Account;name:in String;acc_number:in Positive) is
   begin
      set(acc,name,acc_number,0);
   end set;
   procedure withdrawal(acc:in out Account;amount:in Positive) is
   begin
      acc.acc_balance := acc.acc_balance - amount;
   exception
         when Constraint_Error =>
            raise exceeding_minimum_balance;
   end withdrawal;
   procedure deposit(acc:in out Account;amount:in Positive) is
   begin
      acc.acc_balance := acc.acc_balance + amount;
   exception
      when Constraint_Error =>
         raise exceeding_maximum_balance;
   end deposit;
   procedure transfer(acc1,acc2:in out Account;amount:in Positive) is
   begin
      withdrawal(acc1,amount);
      deposit(acc2,amount);
   end transfer;
   function balance_inquiry(acc:in Account) return Integer is
   begin
      return acc.acc_balance;
   end balance_inquiry;
   function name_inquiry(acc:in Account) return String is
   begin
      return acc.client_name.all;
   end name_inquiry;
   function account_number_inquiry(acc:in Account) return Positive is
   begin
      return acc.acc_number;
   end account_number_inquiry;
   function is_initialized(acc:in Account) return Boolean is
   begin
      if acc.client_name /= null  then
         return True;
      end if;
      return FALSE;
   end is_initialized;
end Accounts;