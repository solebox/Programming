with Accounts;use Accounts;
package Bank is
   type AccountNode is private;
   -- all possible exceptions
   account_doesnt_exist:exception;
   exceeding_minimum_balance:exception;
   exceeding_maximum_balance:exception;
   account_not_initialize_please_use_set:exception;
   cant_deposit_to_account_that_doesnt_exist:exception;
   cant_insert_an_already_existing_account_number:exception;
   cant_withdrawal_from_account_that_doesnt_exist:exception;
   cant_make_transfer_between_accounts_that_dont_exist:exception;

   -- inserts a bank account into the Bank data stracture
   -- a - an Account instance to be inserted
   procedure insert(a:in Account);
   -- prints out to screen all Account instances present in the Bank data structure
   procedure put_all;
   -- deposits a specified amount of money to an account instance in the Bank
   -- the Account instance is located using its number
   -- if the account doesnt exist then an exception will raise:
   -- cant_deposit_to_account_that_doesnt_exist
   procedure deposit(account_number:in Positive;amount:in Positive);
   -- withdrawals money from a an account given its number and an amount to withdrawal
   -- if an amount too big is withdrawn the exceeding_minimum_balance will rise
   -- if an account with the given number doesn exist the cant_withdrawal_from_account_that_doesnt_exist exception
   -- will arise
   procedure withdrawal(account_number:in Positive;amount:in Positive);
   -- transfers from account_from to account_to a given amount of money
   -- if any of the accounts doesnt exist the cant_make_transfer_between_accounts_that_dont_exist exception
   -- will rise, if the pulled amount from account_from is too big and updates it balance lower than the
   -- overdraft allowed the exceeding_minimum_balance exception will rise
   procedure transfer(account_from:in Positive;account_to:in Positive;amount:in Positive);
   -- returns the balance of the account corresponding to the given account number
   -- if the account doesnt exist the account_doesnt_exist exception arises
   function get_balance(account_number:in Positive) return Integer;
   -- returns the owner of the account corresponding to the given account number
   -- if the account doesnt exist the account_doesnt_exist exception arises
   function get_owner_name(account_number:in Positive) return String;


private
   procedure init;
   type AccountNodePtr is access AccountNode;
   type AccountNode is record
      acc:Account;
      next:AccountNodePtr;
   end record;
end Bank;
