-- dynamic_descreminant.adb
with Text_IO;use Text_IO;
procedure dynamic_descreminant is
    type AssWipe is (backwards,front,circular);
    type Preson(wipe:AssWipe := backwards) is record
        age:Natural;
        weigh:Natural;
    end record;
    p:Preson;
begin
    p := (wipe => front, age => 12,weigh => 6);
end dynamic_descreminant;
