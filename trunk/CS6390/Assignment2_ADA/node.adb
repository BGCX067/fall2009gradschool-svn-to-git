with Ada.Text_IO; use Ada.Text_IO;
with Ada.Exceptions; use Ada.Exceptions;

package body Node is
   -- Initializers
   function Create(Name : String) return Node_Ptr is
      tmp : Node_Ptr := new Node'(ubs.To_Unbounded_String(Name),
                                  null,
                                  null,
                                  null,
                                  false);
   begin
         return tmp;
   end Create;


   procedure Build(Item : Node_Ptr; Defs : Node_Alt_Array) is
      old : Node_Ptr;
      cur : Node_Ptr;
      tmp : Node_Ptr;
   begin
      -- Iterate over the alternatives in reverse
      for i in reverse Defs'Range(1) loop
         old := null;

         -- Iterate over the nodes of a definition in reverse
         for j in reverse Defs'Range(2) loop
            if Defs(i, j) /= null then
            	cur := Defs(i, j);

	            -- Create the node and set the name
	            tmp := Create(Get_Name(cur));
		    Set_Def(tmp, cur);
	            Set_Succ(tmp, old);


	            -- If j is the first item, then set it's alternative to Item's def
               if j = Defs'First(2) then
	               Set_Alt(tmp, Get_Def(item));
	            end if;
               old := tmp;
            end if;
         end loop;

         Set_Def(Item, old);
      end loop;
   end Build;

   -- Accessor Functions
  function Get_Name(Item : Node_Ptr) return String is
      begin
         return ubs.To_String(Item.Name);
  end Get_Name;

   function Get_Succ(Item : Node_Ptr) return Node_Ptr is
   begin
      return Item.Succ;
   end Get_Succ;

   function Get_Alt(Item : Node_Ptr) return Node_Ptr is
   begin
      return Item.Alt;
   end Get_Alt;

   function Get_Def(Item : Node_Ptr) return Node_Ptr is
      arg_error : exception;
   begin
      
      -- extra credit part
      if Item = null then
         raise arg_error with "Item is null.";
      end if;
 
      return Item.Def;
   end Get_Def;

   function Is_Visited(Item : Node_Ptr) return boolean is
      def : Node_Ptr := Get_Def(Item);
      is_vis : boolean := Item.Visited or def = null;
   begin
      if def /= null then
         -- Careful, cannot use recursive here because we are looping on a node
         if Def.Visited then
            is_vis := True;
         end if;
      end if;

      return is_vis;
   end Is_Visited;

   procedure Set_Succ(Item, Succ : Node_Ptr) is
   begin
      Item.Succ := Succ;
   end Set_Succ;

   procedure Set_Alt(Item, Alt : Node_Ptr) is
   begin
      Item.Alt := Alt;
   end Set_Alt;

   procedure Set_Def(Item, Def : Node_Ptr) is
   begin
      Item.Def := Def;
   end Set_Def;

   procedure Visit(Item : Node_Ptr) is
   begin
      Item.Visited := True;
   end Visit;


   procedure Print(Item : Node_Ptr) is
      alt : Node_Ptr := Get_Def(Item);
      cur : Node_Ptr := alt;
      arg_error : exception;
   begin
   
      -- extra credit part
      if Item = null then
         raise arg_error with "Item is null.";
      end if;
      
      Put(Get_Name(Item)); Put(": ");

         -- Print out each alternative
      	while alt /= null loop
            cur := alt;

            -- Print out the rule
            while cur /= null loop
       	     Put(Get_Name(cur)); PUT(" ");
			    cur := Get_Succ(cur);
	         end loop;

	         -- Find next alternate
	         alt := Get_Alt(alt);

	         if alt /= null then
	            Put("| ");
	         end if;
	      end loop;

      Put_Line("");
   end Print;

   procedure left_fact(Item : Node_Ptr) is
      alt : Node_Ptr := Get_Def(Item);
      cur : Node_Ptr := alt;
      defs : Node_Def_array(1..1000);
      index:INTEGER:=1;
   begin
      Put(Get_Name(Item)); Put(": ");

         -- Print out each alternative
      	while alt /= null loop
         cur := alt;

            -- Print out the rule
            defs(index):=cur;
              index:=index+1;
            while cur /= null loop
       	    Put(Get_Name(cur)); PUT(" ");
            cur := Get_Succ(cur);
            end loop;
                 -- Find next alternate
            alt := Get_Alt(alt);
            if alt /= null then
	            Put("| ");
	         end if;

         end loop;
Put_Line("");
      for i in defs'first..index-1 loop
         for j in i+1..index-1 loop
         if get_name(defs(i))=get_name(defs(j)) then
         Put(Get_name(defs(i)));
               Put_Line("  :  Left Recursion found");
               --Put_line(" ");
               index:=1;
               return;
           end if;
         end loop;
      end loop;
      index:=1;
   end Left_fact;

   -- Helpers
   procedure Walk(Item : Node_Ptr) is
      alt : Node_Ptr := Get_Def(Item);
      cur : Node_Ptr := alt;
   begin
      -- If this node hasn't been visited, visit and mark it
      if not Is_Visited(Item) then
      	 Visit(Item);
     	 f(Item);

         -- Rerun the loop to print out each rule's production
        alt := Get_Def(Item);
      	while alt /= null loop
            cur := alt;

            -- Print out the rule
            while cur /= null loop
               Walk(Get_Def(cur));
               cur := Get_Succ(cur);
            end loop;


	         -- Find next alternate
	         alt := Get_Alt(alt);
         end loop;
      end if;
   end Walk;
end node;
