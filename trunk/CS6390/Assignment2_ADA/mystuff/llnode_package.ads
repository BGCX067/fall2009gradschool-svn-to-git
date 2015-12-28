WITH Node_Package;

PACKAGE LLNode_Package IS

    USE Node_Package;

    type LLNode;
    type LLNode_Ptr is access LLNode;

    type LLNode is record
      Data: Node;
      Next: LLNode_Ptr;
    end record;

    PROCEDURE InsertNode(item:Node;  head:  in out LLNode_Ptr);
    FUNCTION HasNode(item:Node; head:LLNode_Ptr) RETURN boolean;
END LLNode_Package;


