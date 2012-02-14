generic
   type Structure is limited private;
   type Element is private;
   with procedure init(S:out Structure) is <>;
   with procedure Insert(S:in out Structure;E:in Element) is <>;
   with procedure remove(S:in out Structure;E:out Element) is <>;
package Any_Structure is
end Any_Structure;