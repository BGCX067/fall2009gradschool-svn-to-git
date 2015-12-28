WITH Node_Package;

PACKAGE BODY LLNode_Package IS
   USE Node_Package;

   PROCEDURE InsertNode(item:Node;  head:  in out LLNode_Ptr) IS
      NewLLNode: LLNode_Ptr;
   BEGIN
      NewLLNode := new LLNode'(item, null);
      NewLLNode.Next := head;
      head := NewLLNode;
   END InsertNode;

   FUNCTION HasNode(item:Node;  head:LLNode_Ptr) RETURN boolean IS
      CurrentNode:      LLNode_Ptr;
   BEGIN
      CurrentNode := Head;
      
      loop
         exit when CurrentNode = null;
         
         if item = CurrentNode.Data then
            return true;
         end if;
         
         CurrentNode := CurrentNode.Next;
      end loop;
      
      return false;
      
   END HasNode;
   
END LLNode_Package;
