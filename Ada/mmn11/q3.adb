-- q3.adb
with Text_IO; use Text_IO;
procedure q3 is
    package POS_IO is new Integer_IO(Positive);
    use POS_IO;
    type Day is (Saturday,Sunday,Monday,Tuesday,Wednesday,Thursday,Friday);
    type Month is (Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec);
    type Date is record
        day:Positive range 1..30;
        month:Positive range 3..14;
        y:Natural;
        c:Natural;
        bc:Boolean;
    end record;
    procedure userInputIntoDateRecord(input_in:in Integer;date_io:in out Date) is
        type Year is array(Month range Jan..Dec)  of Positive;
        year_arr:Year :=  (13,14,3,4,5,6,7,8,9,10,11,12);
        input:Integer := input_in;
        tmp:Integer;
    begin
        date_io.bc := false;
        date_io.y := input mod 100;
        input := input / 100;
        date_io.c := input mod 100;
        input := input /100;
        tmp := input mod 100;
        date_io.month := year_arr(Month'val(tmp-1));
        input := input / 100;
        date_io.day := input mod 100;
        if date_io.month = 13 or date_io.month = 14 then
            if date_io.y = 00 and date_io.c /= 00 then
                date_io.y := 99;
                date_io.c := date_io.c -1;
                date_io.y := date_io.y - 1;
            elsif date_io.y = 00 and date_io.c = 00 then
                date_io.bc := true;
            else
                date_io.y := date_io.y - 1;
            end if;
        end if;
        
    end userInputIntoDateRecord;
    function findDay(date_in:in Date) return Integer is
    begin
        return (date_in.day + (26*(date_in.month+1))/10+date_in.y
                +date_in.y/4+date_in.c/4-2*date_in.c) mod 7;
    end findDay;
    procedure printDay(date_in:in Date) is
    begin
            if date_in.bc then
                put_line("hey! even i cant remember that far!");
            else
                put(Day'image(Day'val(findDay(date_in))));
            end if;
    end printDay;
    procedure printDay(user_pos_in: in Positive) is
        date1:Date;
    begin
        userInputIntoDateRecord(user_pos_in,date1);
        printDay(date1);
        new_line;
    end printDay;
    num:Positive;
begin
    put_line("please insert a date using the following format: ddmmyyyy");
    get(num);
    new_line;
    printDay(num);
end q3;
