-- rec.adb
with Text_IO; use Text_IO;
package Ada.Integer_Text_IO is new Ada.Text_IO.Integer_IO (Integer);
procedure rec is
    function two_num_sum(x,y:in Integer) return Integer is
    begin
        return x+y;
    end two_num_sum;
    type Look is (disguasting,hedious,ugly,ok,cute,pretty,sexy,hot,amazing);
    type Girl(looks:Look := ok) is record
        age:Positive;
        name:String(1..20);
        sign:String(1..20);
        case looks is
            when disguasting|hedious|ugly =>
                num_of_pimples:Positive;
            when ok| cute =>
                swallows:Boolean;
            when pretty|sexy|hot|amazing =>
                willingness_to_fuck:Integer;
            when others =>
                null;
        end case;
    end record;
    jessica_alba:Girl(looks => amazing); 
begin
    jessica_alba.age := 22;
    jessica_alba.willingness_to_fuck := -5;
    New_Line;
end rec;
