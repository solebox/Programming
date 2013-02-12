with Text_IO; use Text_IO;
procedure main is
    subtype Max is Positive range 1..100;
    type Matrix is array(Positive range <>,Positive range <>) of Integer;
    type Smatrix(size:Max := 4) is record
        m:Matrix(1..size,1..size);
    end record;
    mat1:Smatrix;
begin
   mat1 := (size => 2);
    put("kaka");
end main;
