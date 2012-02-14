generic
   -- these are the generic formal arguments that are passed in the first initialization of our function before usage.
   -- the LIndex is the index type of the first vector
   -- IMPORTANT: if the 2 vectors are not of the same size the portion of the bigger vector that exceeds the mutual
   -- length of the 2 will be ignored. i.e: if vectror 1 is shorter than vector 2 then vector 2's length will be sliced from
   -- the end to fit the multiplication and the result will be returned only for that part.
   -- eg: [1,2,3] * [1,1,1,1] will be calculated as [1,2,3] * [1,1,1] and will return 6
   -- thats how i chose to deal with such cases , the same goes for other permutations of different size cases
   type LIndex is (<>);
   -- the type of the items in the first verctor
   type LItem is limited private;
   -- the vector type itself
   type LVec is array(LIndex range <>) of LItem;
   -- the index of the second vector to multiply
   type RIndex is (<>);
   -- the type of items that will reside in the second vector
   type RItem is limited private;
   -- the second vector's type
   type RVec is array(RIndex range <>) of RItem;
   -- the result type
   type Result(<>) is private;
   -- the multiplication function between the 2 items LItem and RItem defined above
   with function "*"(left: LItem; right: RItem) return Result;
   -- the addition function between the 2 items LItem and RItem defined above
   with function "+"(left,right:Result) return Result;
   -- a generic function that gets any 2 arrays of any size with any type of items and indexes and
   -- the does a vector multiplcation on them
   -- leftv - the vector on the left side of the real world (ink and paper) vector multiplication operand
   -- rightv - the vector on the right side of the real world (ink and paper) vector multiplication operand
   -- Result - the result of the verctor multiplication
function dot_product(leftv: LVec;rightv: RVec) return Result;