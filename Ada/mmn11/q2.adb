--q2.adb
with Text_IO; use Text_IO;
procedure q2 is
    package POS_IO is new Integer_IO(Positive);
    use POS_IO;
    type PLANET is(MERCURY,VENUS,EARTH,MARS,JUPITER,SATURN,URANUS,NEPTUN,PLUTO);
    type SIZE is(SMALL,GIANT);
    type SOLAR_SIZE is array(PLANET range <>) of SIZE;
    type SOLAR_SYSTEM is array (PLANET range <>) of NATURAL;
    DATA:SOLAR_SIZE(PLANET):=(JUPITER..NEPTUN => GIANT, others => SMALL);
    INNER:SOLAR_SYSTEM(MERCURY..MARS):=(4880,12103,12756,6794);
    OUTER:SOLAR_SYSTEM(JUPITER..PLUTO):=(142984,120536,5118,49532,2274);
begin
   -- put(planet'image(INNER'last));
    --new_line;
   put(size'image(DATA(DATA'FIRST)));
   new_line;
   -- put(DATA'LAST);
   -- new_line;
   -- put(OUTER'LENGTH);
   -- new_line;
   -- PLANET'SUCC(INNER'FIRST);
   -- new_line;
   -- PLANET'PRED(OUTER'LAST);
   -- new_line;
   -- INNER(PLANET'PRED(INNER'LAST);
   -- new_line;
   -- PLANET'VAL(PLANET'POS(VENUS));
   -- new_line;
   -- DATA(DATA'FIRST);
end q2;
