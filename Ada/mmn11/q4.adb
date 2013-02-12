with Text_IO;  use Text_IO;
-- the following program takes a forest data stracture an adds an item record into it
-- the forest data structure is just an array with ColorType indexs that hosts binary trees of Item types
-- ordered by the name of the Item type data
procedure q4 is
   type State is (IN_TREE,NOT_IN_TREE);
   type ColorType is (RED,ORANGE,YELLOW,GREEN,CYAN,BLUE,INDIGO,VIOLET);
   type Word is access String;
   type Item;
   type ItemPointer is access Item;
   -- the deffenition of Item type
   -- color - the color or the object
   -- name - an accessor to a string that is the name of the object
   type Item(status:State := NOT_IN_TREE) is record
      name:Word;
      color:ColorType;
      case status is
         when IN_TREE =>
            left:ItemPointer;
            right:ItemPointer;
         when others =>
            null;
         end case;
   end record;
-- none user function that makes an item to be inserted into a tree
   function makeTreeItem(name_in:in String;color_in:in ColorType) return Item is
      itm:Item;
      n1:Word;
   begin
      n1 := new String(name_in'range);
      n1.all := name_in;
      itm := (status => IN_TREE, name => n1, color => color_in, left => null, right => null);
      return itm;
   end makeTreeItem;
   -- a function that makes an item when given a string and a color (to be used by the used to make
   --items to be inserted into forest)
   function makeItem(name_in:in String;color_in:in ColorType) return Item is
      itm:Item;
      n1:Word;
   begin
      n1 := new String(name_in'range);
      n1.all := name_in;
      itm := (status => NOT_IN_TREE, name => n1, color => color_in);
      return itm;
   end makeItem;
   -- ** tree implementation ** --
-- helper function that adds an item to a tree when given a head thats not null and an item
   procedure iterativeAddToTree(head:in ItemPointer;item_to_insert:in Item) is
      ptr,trace:ItemPointer;
   begin
      ptr := head;
      while ptr /= null loop
         if item_to_insert.name.all < ptr.all.name.all then
            trace := ptr;
            ptr := ptr.all.left;
         elsif item_to_insert.name.all > ptr.all.name.all then
            trace := ptr;
            ptr := ptr.all.right;
         elsif item_to_insert.name.all = ptr.all.name.all then
            trace := ptr;
            ptr := ptr.all.right;
         end if;
      end loop;
      if item_to_insert.name.all < trace.all.name.all then
         trace.all.left := new Item'(status => IN_TREE, name => item_to_insert.name,
                                     color => item_to_insert.color, left => item_to_insert.left,
                                     right => item_to_insert.right);
      else
         trace.all.right := new Item'(status => IN_TREE, name => item_to_insert.name,
                                      color => item_to_insert.color, left => item_to_insert.left,
                                      right => item_to_insert.right);
      end if;
   end iterativeAddToTree;
-- none user function that adds an item to a tree (it will call the iterativeAddToTree when needed)
   procedure addToTree(head:in out ItemPointer;item_in:in Item) is
      item_to_insert:Item := makeTreeItem(item_in.name.all,item_in.color);
   begin
      if head = null then
         head := new Item'(status => IN_TREE, name => item_to_insert.name,
                      color => item_to_insert.color, left => item_to_insert.left,
                      right => item_to_insert.right);
     else
            iterativeAddToTree(head,item_to_insert);
     end if;
   end addToTree;
-- a helper procedure that prints a tree when given a pointer to the root item
   procedure printTree(node:in ItemPointer) is
   begin
      if node = null then
         return;
      else
         printTree(node.left);
         put_line(node.name.all(node.name.all'range));
         printTree(node.right);
      end if;
   end printTree;

   -- *** defining the forest's root and procedures (im a lumberjack and im ok) ***--
   type Forest is array(ColorType range RED..VIOLET) of ItemPointer;
   -- a user function that adds an item made with makeItem to a forest data struct
   -- forest_in - the forest to manipulate
   -- item_in - the item to insert
   procedure addToForest(forest_in:in out Forest;item_in:in Item) is
   begin
      addToTree(forest_in(item_in.color),item_in);
   end addToForest;
   procedure printForest(forest_in:in Forest) is
   begin
      for c in forest_in'range loop
         if forest_in(c) /= null then
            printTree(forest_in(c));
         end if;
      end loop;
   end printForest;

   forest1:Forest;
begin
   -- color order: RED,ORANGE,YELLOW,GREEN,CYAN,BLUE,INDIGO,VIOLET

   -- adding a bunch of items to the forest
   addToForest(forest1,makeItem("f",RED));
   addToForest(forest1,makeItem("e",ORANGE));
   addToForest(forest1,makeItem("d",YELLOW));
   addToForest(forest1,makeItem("c",GREEN));
   addToForest(forest1,makeItem("b",CYAN));
   addToForest(forest1,makeItem("a",BLUE));
   addToForest(forest1,makeItem("b",BLUE));
   addToForest(forest1,makeItem("c",BLUE));

   --printing the forest
   printForest(forest1);
end q4;
