with Text_IO;use Text_IO;
package body Bank is
   head:AccountNodePtr;
   function find_by_account_number(account_number:in Positive) return AccountNodePtr is
      p:AccountNodePtr:=head;
   begin
      while p /= null and then account_number_inquiry(p.acc) /= account_number loop
         p := p.next;
      end loop;
      return p;
   end find_by_account_number;
   procedure insert(a:in Account) is
      p,f:AccountNodePtr;
   begin
      if not is_initialized(a) then
         raise account_not_initialize_please_use_set;
      end if;
      if find_by_account_number(account_number_inquiry(a)) /= null then
         raise cant_insert_an_already_existing_account_number;
      end if;
      p:= head;
      f:= p;
      while p /= null loop
         f := p;
         p := p.next;
      end loop;
      if (f = null) then
         head := new AccountNode;
         head.acc := a;
         head.next := null;

        -- pragma assert(f.acc = a,"account not asigned");

      else
         f.next := new AccountNode;
         f.next.acc := a;
         f.next.next := null;
         --pragma assert(f.next.acc = a,"account not asigned");
      end if;
   end insert;
   procedure put_all is
      p:AccountNodePtr := head;
   begin
     -- pragma assert(p = null,"p is null");
     pragma assert(head /= null,"head is null");
      while p /= null loop
         put("Client Name:"&name_inquiry(p.acc)&","&
             " Account Number:"&Integer'Image(account_number_inquiry(p.acc))&","&
             " Balance: "&Integer'Image(balance_inquiry(p.acc)));
         new_line;
         p := p.next;
      end loop;
      new_line;
   end put_all;
   procedure init is
   begin
      head:=null;
   end init;

   procedure deposit(account_number:in Positive;amount:in Positive) is
      p:AccountNodePtr := null;
   begin
      p := find_by_account_number(account_number);
      if p /= null then
         deposit(p.acc,amount);
      else
         raise cant_deposit_to_account_that_doesnt_exist;
      end if;
   end deposit;
   procedure withdrawal(account_number:in Positive;amount:in Positive) is
      p:AccountNodePtr := null;
   begin
      p := find_by_account_number(account_number);
      if p /= null then
         withdrawal(p.acc,amount);
      else
         raise cant_withdrawal_from_account_that_doesnt_exist;
      end if;
   end withdrawal;
   procedure transfer(account_from:in Positive;account_to:in Positive;amount:in Positive) is
      account1:AccountNodePtr := null;
      account2:AccountNodePtr := null;
   begin
      account1 := find_by_account_number(account_from);
      account2 := find_by_account_number(account_to);
      if account1 /= null and account2 /= null then
         transfer(account1.acc,account2.acc,amount);
      else
         raise cant_make_transfer_between_accounts_that_dont_exist;
      end if;
   end transfer;
   function get_balance(account_number:in Positive) return Integer is
      p:AccountNodePtr;
   begin
      p := find_by_account_number(account_number);
      if p /= null then
         return balance_inquiry(p.acc);
      else
         raise account_doesnt_exist;
      end if;
   end get_balance;
   function get_owner_name(account_number:in Positive) return String is
      p:AccountNodePtr;
   begin
      p := find_by_account_number(account_number);
      if p /= null then
         return name_inquiry(p.acc);
      else
         raise account_doesnt_exist;
      end if;
   end get_owner_name;
begin
   init;
end Bank;
