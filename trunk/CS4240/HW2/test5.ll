; ModuleID = 'module'

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
	%a = alloca double		; <double*> [#uses=2]
	br label %main

main:		; preds = %allocateLocals
	br label %"main 2"

"main 2":		; preds = %main
	br label %"main 3"

"main 3":		; preds = %"main 2"
	store double 1.100000e+01, double* %a
	br label %"main 4"

"main 4":		; preds = %"main 3"
	%0 = load double* %a		; <double> [#uses=1]
	call void @count(double %0)
	br label %"main 5"

"main 5":		; preds = %"main 4"
	%stringConstant = alloca i8, i32 100		; <i8*> [#uses=4]
	%1 = getelementptr i8* %stringConstant, i32 0		; <i8*> [#uses=1]
	store i8 97, i8* %1
	%2 = getelementptr i8* %stringConstant, i32 1		; <i8*> [#uses=1]
	store i8 97, i8* %2
	%3 = getelementptr i8* %stringConstant, i32 2		; <i8*> [#uses=1]
	store i8 0, i8* %3
	call void @testStrCount(i8* %stringConstant)
	ret void
}

define void @count(double %num) {
allocateLocals:
	%num1 = alloca double		; <double*> [#uses=3]
	store double %num, double* %num1
	%nextCount = alloca double		; <double*> [#uses=3]
	br label %count

count:		; preds = %allocateLocals
	%0 = load double* %num1		; <double> [#uses=1]
	%1 = alloca i8, i32 100		; <i8*> [#uses=2]
	call void @string_double_to_string(double %0, i8* %1)
	call void @string_print(i8* %1)
	br label %"count 2"

"count 2":		; preds = %count
	%2 = load double* %num1		; <double> [#uses=1]
	%3 = add double %2, 1.000000e+00		; <double> [#uses=1]
	store double %3, double* %nextCount
	br label %"count 3"

"count 3":		; preds = %"count 2"
	br label %"EVAL 1_"

"EVAL 1_":		; preds = %"count 3"
	%4 = load double* %nextCount		; <double> [#uses=1]
	%5 = fcmp olt double %4, 2.000000e+01		; <i1> [#uses=1]
	br i1 %5, label %"IF 1_", label %AfterIfBlock

"IF 1_":		; preds = %"EVAL 1_"
	%6 = load double* %nextCount		; <double> [#uses=1]
	call void @count(double %6)
	br label %AfterIfBlock

AfterIfBlock:		; preds = %"EVAL 1_", %"IF 1_"
	ret void
}

define void @testStrCount(i8* %myStr) {
allocateLocals:
	%myStr1 = alloca i8, i32 100		; <i8*> [#uses=3]
	call void @string_copy(i8* %myStr, i8* %myStr1)
	%newStr = alloca i8, i32 100		; <i8*> [#uses=3]
	%newStrLen = alloca double		; <double*> [#uses=2]
	br label %testStrCount

testStrCount:		; preds = %allocateLocals
	%stringConstant = alloca i8, i32 100		; <i8*> [#uses=4]
	%0 = getelementptr i8* %stringConstant, i32 0		; <i8*> [#uses=1]
	store i8 104, i8* %0
	%1 = getelementptr i8* %stringConstant, i32 1		; <i8*> [#uses=1]
	store i8 105, i8* %1
	%2 = getelementptr i8* %stringConstant, i32 2		; <i8*> [#uses=1]
	store i8 0, i8* %2
	%3 = alloca i8, i32 100		; <i8*> [#uses=2]
	call void @string_concat(i8* %myStr1, i8* %stringConstant, i8* %3)
	call void @string_copy(i8* %3, i8* %newStr)
	br label %"testStrCount 2"

"testStrCount 2":		; preds = %testStrCount
	call void @string_print(i8* %myStr1)
	br label %"testStrCount 3"

"testStrCount 3":		; preds = %"testStrCount 2"
	%4 = call i32 @string_lenght(i8* %newStr)		; <i32> [#uses=1]
	%5 = sitofp i32 %4 to double		; <double> [#uses=1]
	store double %5, double* %newStrLen
	br label %"testStrCount 4"

"testStrCount 4":		; preds = %"testStrCount 3"
	br label %"EVAL 1_"

"EVAL 1_":		; preds = %"testStrCount 4"
	%6 = load double* %newStrLen		; <double> [#uses=1]
	%7 = fcmp olt double %6, 5.000000e+01		; <i1> [#uses=1]
	br i1 %7, label %"IF 1_", label %AfterIfBlock

"IF 1_":		; preds = %"EVAL 1_"
	call void @testStrCount(i8* %newStr)
	br label %AfterIfBlock

AfterIfBlock:		; preds = %"EVAL 1_", %"IF 1_"
	ret void
}

declare i32 @printf(i8* noalias , ...) nounwind
declare i32 @sprintf(i8* noalias , i8* noalias , ...) nounwind 