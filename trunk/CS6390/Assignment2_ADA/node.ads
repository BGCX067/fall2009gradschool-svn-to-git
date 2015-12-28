with Ada.Strings.Unbounded;

package Node is
   package ubs renames Ada.Strings.Unbounded;

   type Node;
   type Node_Ptr is access Node;

   type Node is record
      Name : ubs.Unbounded_String;
      Def  : Node_Ptr;
      Succ : Node_Ptr;
      Alt  : Node_Ptr;
      Visited : Boolean;
   end record;

   type Node_Alt_Array is array (Positive range <>, Positive range <>) of Node_Ptr;
   type Node_Def_Array is array (Positive range <>) of Node_Ptr;
   -- Constructors
   function Create(Name : String) return Node_Ptr;
   procedure Build(Item : Node_Ptr; Defs : Node_Alt_Array);

   -- Accessors
   function Is_Visited(Item : Node_Ptr) return boolean;
   function Get_Name(Item : Node_Ptr) return String;
   function Get_Succ(Item : Node_Ptr) return Node_Ptr;
   function Get_Alt(Item : Node_Ptr) return Node_Ptr;
   function Get_Def(Item : Node_Ptr) return Node_Ptr;
   procedure Set_Succ(Item, Succ : Node_Ptr);
   procedure Set_Alt(Item, Alt : Node_Ptr);
   procedure Set_Def(Item, Def : Node_Ptr);
   procedure Visit(Item : Node_Ptr);

   -- Helper functions
   procedure Print(Item : Node_Ptr);
   procedure left_fact(Item: Node_ptr);
   generic with procedure f(Item : Node_Ptr);
   procedure Walk(Item : Node_Ptr);
end node;
