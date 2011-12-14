--isprime.adb

with Ada.Numerics.Aux;
use Ada.Numerics.Aux;

function is_prime(n: in integer) return boolean is
    n_sqrt: double := sqrt(double(n));
    factor_not_found: boolean := true;
    i: integer := 2;
begin
    while factor_not_found and i <= integer(n_sqrt) loop
        if n mod i = 0 then
            factor_not_found := false;
        else
            i := i + 1;
        end if;
    end loop;
    return factor_not_found;
end is_prime;
