; ModuleID = 'module'
@a = weak global double 0.000000e+00		; <double*> [#uses=2]
@b = weak global double 0.000000e+00		; <double*> [#uses=2]
@c = weak global double 0.000000e+00		; <double*> [#uses=3]

define i32 @string_lenght(i8* %str1) {
initblock:
	%str1Variable = alloca i32		; <i32*> [#uses=5]
	store i32 0, i32* %str1Variable
	br label %findendtest

findendtest:		; preds = %findendloop, %initblock
	%str1Loc = load i32* %str1Variable		; <i32> [#uses=1]
	%str1LocPtr = getelementptr i8* %str1, i32 %str1Loc		; <i8*> [#uses=1]
	%str1Val = load i8* %str1LocPtr		; <i8> [#uses=1]
	%0 = icmp ne i8 %str1Val, 0		; <i1> [#uses=1]
	br i1 %0, label %findendloop, label %lastblock

findendloop:		; preds = %findendtest
	%str1Loc2 = load i32* %str1Variable		; <i32> [#uses=1]
	%1 = add i32 %str1Loc2, 1		; <i32> [#uses=1]
	store i32 %1, i32* %str1Variable
	br label %findendtest

lastblock:		; preds = %findendtest
	%str1Loc3 = load i32* %str1Variable		; <i32> [#uses=1]
	ret i32 %str1Loc3
}

define void @string_concat(i8* %str1, i8* %str2, i8* %copyTo) {
initblock:
	%str1Variable = alloca i32		; <i32*> [#uses=7]
	%str2Variable = alloca i32		; <i32*> [#uses=3]
	store i32 0, i32* %str1Variable
	store i32 0, i32* %str2Variable
	br label %findendtest

findendtest:		; preds = %findendloop, %initblock
	%str1Loc = load i32* %str1Variable		; <i32> [#uses=1]
	%str1LocPtr = getelementptr i8* %str1, i32 %str1Loc		; <i8*> [#uses=1]
	%str1Val = load i8* %str1LocPtr		; <i8> [#uses=1]
	%0 = icmp ne i8 %str1Val, 0		; <i1> [#uses=1]
	br i1 %0, label %findendloop, label %copytest

findendloop:		; preds = %findendtest
	%str1Loc2 = load i32* %str1Variable		; <i32> [#uses=3]
	%str1LocPtr2 = getelementptr i8* %str1, i32 %str1Loc2		; <i8*> [#uses=1]
	%copyToLocPtr = getelementptr i8* %copyTo, i32 %str1Loc2		; <i8*> [#uses=1]
	%str1Val2 = load i8* %str1LocPtr2		; <i8> [#uses=1]
	store i8 %str1Val2, i8* %copyToLocPtr
	%1 = add i32 %str1Loc2, 1		; <i32> [#uses=1]
	store i32 %1, i32* %str1Variable
	br label %findendtest

copytest:		; preds = %copyloop, %findendtest
	%str1Loc3 = load i32* %str1Variable		; <i32> [#uses=1]
	%2 = icmp ult i32 %str1Loc3, 100		; <i1> [#uses=1]
	br i1 %2, label %copyloop, label %lastblock

copyloop:		; preds = %copytest
	%str2Loc = load i32* %str2Variable		; <i32> [#uses=2]
	%str2LocPtr = getelementptr i8* %str2, i32 %str2Loc		; <i8*> [#uses=1]
	%str2Val = load i8* %str2LocPtr		; <i8> [#uses=1]
	%str1Loc4 = load i32* %str1Variable		; <i32> [#uses=2]
	%copyToLocPtr2 = getelementptr i8* %copyTo, i32 %str1Loc4		; <i8*> [#uses=1]
	store i8 %str2Val, i8* %copyToLocPtr2
	%3 = add i32 %str1Loc4, 1		; <i32> [#uses=1]
	store i32 %3, i32* %str1Variable
	%4 = add i32 %str2Loc, 1		; <i32> [#uses=1]
	store i32 %4, i32* %str2Variable
	br label %copytest

lastblock:		; preds = %copytest
	ret void
}

define void @string_copy(i8* %from, i8* %to) {
initblock:
	%fromLocVar = alloca i32		; <i32*> [#uses=5]
	store i32 0, i32* %fromLocVar
	br label %copytest

copytest:		; preds = %copyloop, %initblock
	%fromLoc = load i32* %fromLocVar		; <i32> [#uses=1]
	%fromLocPtr = getelementptr i8* %from, i32 %fromLoc		; <i8*> [#uses=1]
	%fromLocVal = load i8* %fromLocPtr		; <i8> [#uses=1]
	%0 = icmp ne i8 %fromLocVal, 0		; <i1> [#uses=1]
	br i1 %0, label %copyloop, label %lastblock

copyloop:		; preds = %copytest
	%fromLoc2 = load i32* %fromLocVar		; <i32> [#uses=3]
	%fromLocPtr2 = getelementptr i8* %from, i32 %fromLoc2		; <i8*> [#uses=1]
	%toLocPtr = getelementptr i8* %to, i32 %fromLoc2		; <i8*> [#uses=1]
	%fromLocVal2 = load i8* %fromLocPtr2		; <i8> [#uses=1]
	store i8 %fromLocVal2, i8* %toLocPtr
	%1 = add i32 %fromLoc2, 1		; <i32> [#uses=1]
	store i32 %1, i32* %fromLocVar
	br label %copytest

lastblock:		; preds = %copytest
	%fromLoc3 = load i32* %fromLocVar		; <i32> [#uses=1]
	%toLocPtr2 = getelementptr i8* %to, i32 %fromLoc3		; <i8*> [#uses=1]
	store i8 0, i8* %toLocPtr2
	ret void
}

define void @string_print(i8* %str) {
block:
	%newLineConstant = alloca i8, i32 100		; <i8*> [#uses=3]
	%0 = getelementptr i8* %newLineConstant, i32 0		; <i8*> [#uses=1]
	store i8 10, i8* %0
	%1 = getelementptr i8* %newLineConstant, i32 1		; <i8*> [#uses=1]
	store i8 0, i8* %1
	%withNewLine = alloca i8, i32 100		; <i8*> [#uses=1]
	call void @string_concat(i8* %str, i8* %newLineConstant, i8* %withNewLine)
	br label %call_printf

call_printf:		; preds = %block
	%tmp1 = call i32 (i8*, ...)* @printf( i8* noalias  %withNewLine ) nounwind
	ret void
}

define void @string_double_to_string(double %val, i8* %str) {
block:
	%formatConstant = alloca i8, i32 100		; <i8*> [#uses=3]
	%0 = getelementptr i8* %formatConstant, i32 0		; <i8*> [#uses=1]
	store i8 37, i8* %0
	%1 = getelementptr i8* %formatConstant, i32 1		; <i8*> [#uses=1]
	store i8 102, i8* %1
	%2 = getelementptr i8* %formatConstant, i32 2		; <i8*> [#uses=1]
	store i8 0, i8* %2
	br label %call_fprintf

call_fprintf:		; preds = %block
	%tmp1 = call i32 (i8*, i8*, ...)* @sprintf( i8* noalias  %str, i8* noalias  %formatConstant, double %val ) nounwind
	ret void
}

define void @main() {
allocateLocals:
	br label %main

main:		; preds = %allocateLocals
	store double 1.000000e+00, double* @a
	br label %"main 2"

"main 2":		; preds = %main
	store double 2.000000e+00, double* @b
	br label %"main 3"

"main 3":		; preds = %"main 2"
	store double 3.000000e+00, double* @c
	br label %"main 4"

"main 4":		; preds = %"main 3"
	br label %"EVAL 1_"

"EVAL 1_":		; preds = %"main 4"
	%0 = load double* @a		; <double> [#uses=1]
	%1 = fcmp olt double %0, 1.000000e+01		; <i1> [#uses=1]
	br i1 %1, label %"IF 1_", label %"IF 2_11"

"IF 1_":		; preds = %"EVAL 1_"
	br label %"EVAL 1_2"

"EVAL 1_2":		; preds = %"IF 1_"
	%2 = load double* @b		; <double> [#uses=1]
	%3 = fcmp ogt double %2, 1.000000e+00		; <i1> [#uses=1]
	br i1 %3, label %"IF 1_3", label %"IF 2_9"

"IF 1_3":		; preds = %"EVAL 1_2"
	br label %"EVAL 1_5"

"EVAL 1_5":		; preds = %"IF 1_3"
	%4 = load double* @c		; <double> [#uses=1]
	%5 = fcmp olt double %4, 1.000000e+00		; <i1> [#uses=1]
	br i1 %5, label %"IF 1_6", label %"EVAL 2_"

"EVAL 2_":		; preds = %"EVAL 1_5"
	%6 = load double* @c		; <double> [#uses=1]
	%7 = fcmp ogt double %6, 5.000000e+00		; <i1> [#uses=1]
	br i1 %7, label %"IF 2_", label %"IF 3_"

"IF 1_6":		; preds = %"EVAL 1_5"
	%stringConstant = alloca i8, i32 100		; <i8*> [#uses=5]
	%8 = getelementptr i8* %stringConstant, i32 0		; <i8*> [#uses=1]
	store i8 66, i8* %8
	%9 = getelementptr i8* %stringConstant, i32 1		; <i8*> [#uses=1]
	store i8 65, i8* %9
	%10 = getelementptr i8* %stringConstant, i32 2		; <i8*> [#uses=1]
	store i8 68, i8* %10
	%11 = getelementptr i8* %stringConstant, i32 3		; <i8*> [#uses=1]
	store i8 0, i8* %11
	call void @string_print(i8* %stringConstant)
	br label %AfterIfBlock4

"IF 2_":		; preds = %"EVAL 2_"
	%stringConstant7 = alloca i8, i32 100		; <i8*> [#uses=5]
	%12 = getelementptr i8* %stringConstant7, i32 0		; <i8*> [#uses=1]
	store i8 66, i8* %12
	%13 = getelementptr i8* %stringConstant7, i32 1		; <i8*> [#uses=1]
	store i8 65, i8* %13
	%14 = getelementptr i8* %stringConstant7, i32 2		; <i8*> [#uses=1]
	store i8 68, i8* %14
	%15 = getelementptr i8* %stringConstant7, i32 3		; <i8*> [#uses=1]
	store i8 0, i8* %15
	call void @string_print(i8* %stringConstant7)
	br label %AfterIfBlock4

"IF 3_":		; preds = %"EVAL 2_"
	%stringConstant8 = alloca i8, i32 100		; <i8*> [#uses=6]
	%16 = getelementptr i8* %stringConstant8, i32 0		; <i8*> [#uses=1]
	store i8 71, i8* %16
	%17 = getelementptr i8* %stringConstant8, i32 1		; <i8*> [#uses=1]
	store i8 79, i8* %17
	%18 = getelementptr i8* %stringConstant8, i32 2		; <i8*> [#uses=1]
	store i8 79, i8* %18
	%19 = getelementptr i8* %stringConstant8, i32 3		; <i8*> [#uses=1]
	store i8 68, i8* %19
	%20 = getelementptr i8* %stringConstant8, i32 4		; <i8*> [#uses=1]
	store i8 0, i8* %20
	call void @string_print(i8* %stringConstant8)
	br label %AfterIfBlock4

AfterIfBlock4:		; preds = %"IF 3_", %"IF 2_", %"IF 1_6"
	br label %AfterIfBlock1

"IF 2_9":		; preds = %"EVAL 1_2"
	%stringConstant10 = alloca i8, i32 100		; <i8*> [#uses=5]
	%21 = getelementptr i8* %stringConstant10, i32 0		; <i8*> [#uses=1]
	store i8 66, i8* %21
	%22 = getelementptr i8* %stringConstant10, i32 1		; <i8*> [#uses=1]
	store i8 65, i8* %22
	%23 = getelementptr i8* %stringConstant10, i32 2		; <i8*> [#uses=1]
	store i8 68, i8* %23
	%24 = getelementptr i8* %stringConstant10, i32 3		; <i8*> [#uses=1]
	store i8 0, i8* %24
	call void @string_print(i8* %stringConstant10)
	br label %AfterIfBlock1

AfterIfBlock1:		; preds = %"IF 2_9", %AfterIfBlock4
	br label %AfterIfBlock

"IF 2_11":		; preds = %"EVAL 1_"
	%stringConstant12 = alloca i8, i32 100		; <i8*> [#uses=5]
	%25 = getelementptr i8* %stringConstant12, i32 0		; <i8*> [#uses=1]
	store i8 66, i8* %25
	%26 = getelementptr i8* %stringConstant12, i32 1		; <i8*> [#uses=1]
	store i8 65, i8* %26
	%27 = getelementptr i8* %stringConstant12, i32 2		; <i8*> [#uses=1]
	store i8 68, i8* %27
	%28 = getelementptr i8* %stringConstant12, i32 3		; <i8*> [#uses=1]
	store i8 0, i8* %28
	call void @string_print(i8* %stringConstant12)
	br label %AfterIfBlock

AfterIfBlock:		; preds = %"IF 2_11", %AfterIfBlock1
	ret void
}

declare i32 @printf(i8* noalias , ...) nounwind
declare i32 @sprintf(i8* noalias , i8* noalias , ...) nounwind 