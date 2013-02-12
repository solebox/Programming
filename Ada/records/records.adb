-- records.adb
with Text_IO; use Text_IO;
procedure records is
   type Kaka is record
      age:Integer;
      scent:String(1..100);
   end record;
   laka:Kaka;
begin
   laka.age := 3;
   laka.scent(1..5) := "musty";
   Put("laka's age is: ");
   Put_Line(integer'image(laka.age));
   Put("laka's scent is: ");
   Put_Line(laka.scent(1..5));
end records;
