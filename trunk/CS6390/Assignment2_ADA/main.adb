with Ada.Text_IO; use Ada.Text_IO;
with Node; use Node;

procedure Main is
   LPAREN : Node_Ptr := Create("(");
   RPAREN : Node_Ptr := Create(")");
   PLUS : Node_Ptr := Create("+");
   MINUS : Node_Ptr := Create("-");
   MULT : Node_Ptr := Create("*");
   DIV : Node_Ptr := Create("/");
   IDENT : Node_Ptr := Create("IDENTIFIER_TOKEN");
   MOP : Node_Ptr := Create("MOP");
   AOP : Node_Ptr := Create("AOP");
   FACTOR : Node_Ptr := Create("FACTOR");
   EXPRESSION : Node_Ptr := Create("EXPRESSION");
   TERM : Node_Ptr := Create("TERM");
   procedure Print_Op is new Walk(Print);

   F:Node_Ptr:=Create("F");
   E:Node_Ptr:=Create("E");
   D:Node_Ptr:=Create("D");
   C:Node_Ptr:=Create("C");
   B3:Node_Ptr:=Create("B");
   B2:Node_Ptr:=Create("B");
   B1:Node_Ptr:=Create("B");
   B4:Node_Ptr:=Create("B");
   B5:Node_Ptr:=Create("B");
   A:Node_Ptr:=Create("A");
   procedure check_lf is new Walk(left_fact);
begin
   -- Extra Credit Test
   -- print(null);
   Build(AOP, Defs => ((1=>PLUS), (1=>MINUS)));
   Build(MOP, Defs => ((1=>MULT), (1=>DIV)));
   Build(FACTOR, ((LPAREN, EXPRESSION, RPAREN), (IDENT, null, null)));
   Build(TERM, ((TERM, MOP, FACTOR), (FACTOR, null, null)));
   Build(EXPRESSION, ((EXPRESSION, AOP, TERM), (EXPRESSION, null, null)));
   --Print_Op(expression);
   Check_lf(Expression);

   put_line(" ");
   Build(A,((B1,C),(B2,D),(B3,E),(B4,F)));
   Check_lf(A);


end Main;
