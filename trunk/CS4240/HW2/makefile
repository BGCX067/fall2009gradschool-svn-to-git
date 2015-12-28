

AST_SOURCES =   name_node.cpp \
				number_node.cpp \
				string_node.cpp \
				base_node.cpp \
				chunk_node.cpp \
				expression_node.cpp \
				expression_node_binary_operation.cpp \
				expression_node_bool.cpp \
				expression_node_dots.cpp \
				expression_node_nil.cpp \
				expression_node_number.cpp \
				expression_node_prefix.cpp \
				expression_node_string.cpp \
				expression_node_table_constructor.cpp \
				expression_node_unary_operation.cpp \
				field_node.cpp \
				field_node_bracket.cpp \
				field_node_expression.cpp \
				field_node_name.cpp \
				function_body_node.cpp \
				function_call_node.cpp \
				prefix_node.cpp \
				prefix_node_function_call.cpp \
				prefix_node_parenthesis.cpp \
				prefix_node_variable.cpp \
				statement_node.cpp \
				statement_node_assign.cpp \
				statement_node_break.cpp \
				statement_node_do.cpp \
				statement_node_function_definition.cpp \
				statement_node_funtion_call.cpp \
				statement_node_generic_for.cpp \
				statement_node_if.cpp \
				statement_node_local_function_definition.cpp \
				statement_node_local_variable_declaration.cpp \
				statement_node_numeric_for.cpp \
				statement_node_repeate.cpp \
				statement_node_return.cpp \
				statement_node_while.cpp \
				variable_node.cpp \
				variable_node_name.cpp \
				variable_node_prefix_bracket.cpp \
				variable_node_prefix_dot.cpp \
				\
				llvm_generator.cpp

AST_OBJECTS =   base_node.o \
				chunk_node.o \
				expression_node.o \
				expression_node_binary_operation.o \
				expression_node_bool.o \
				expression_node_dots.o \
				expression_node_nil.o \
				expression_node_number.o \
				expression_node_prefix.o \
				expression_node_string.o \
				expression_node_table_constructor.o \
				expression_node_unary_operation.o \
				field_node.o \
				field_node_bracket.o \
				field_node_expression.o \
				field_node_name.o \
				function_body_node.o \
				function_call_node.o \
				name_node.o \
				number_node.o \
				prefix_node.o \
				prefix_node_function_call.o \
				prefix_node_parenthesis.o \
				prefix_node_variable.o \
				statement_node.o \
				statement_node_assign.o \
				statement_node_break.o \
				statement_node_do.o \
				statement_node_function_definition.o \
				statement_node_funtion_call.o \
				statement_node_generic_for.o \
				statement_node_if.o \
				statement_node_local_function_definition.o \
				statement_node_local_variable_declaration.o \
				statement_node_numeric_for.o \
				statement_node_repeate.o \
				statement_node_return.o \
				statement_node_while.o \
				string_node.o \
				variable_node.o \
				variable_node_name.o \
				variable_node_prefix_bracket.o \
				variable_node_prefix_dot.o \
				\
				llvm_generator.o



all:			lua

lua:			yacc.o main.cpp symbol_table.o lex.o yyvaltype.o $(AST_OBJECTS)
				g++ -g -Wall -Werror main.cpp $(AST_OBJECTS) symbol_table.o lex.o yacc.o yyvaltype.o `llvm-config --cppflags --ldflags --libs core` -o luac

%.o:			%.cpp
				g++ -Wall -Werror -g `llvm-config --cppflags --ldflags --libs core` -c -o $@ $<

lex.o:			lex.c yyvaltype.c yacc.cpp
				cc -Wall -g -c lex.c -o lex.o

lex.c:			lua.l
				lex -s -o lex.c lua.l


yacc.cpp:		lua.y
				yacc --defines=yacc.h -o yacc.cpp lua.y

linecount:
	wc -l *.c *.cpp *.h *.y *.l *.lua

llvm: llvmOut.s
	llvm-as -f llvmOut.s && lli llvmOut.s.bc


clean:
	rm -rf *.o lex.c lex.cpp yacc.h yacc.cpp *.ast *~ luac

