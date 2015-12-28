; ModuleID = 'module'
@a = weak global double 0.000000e+00		; <double*> [#uses=5]
@b = weak global [100 x i8] zeroinitializer		; <[100 x i8]*> [#uses=1]
@c = weak global [100 x i8] zeroinitializer		; <[100 x i8]*> [#uses=1]
@d = weak global double 0.000000e+00		; <double*> [#uses=2]
@e = weak global double 0.000000e+00		; <double*> [#uses=2]

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
	store double 5.000000e+00, double* @a
	br label %"main 2"

"main 2":		; preds = %main
	%stringConstant = alloca i8, i32 100		; <i8*> [#uses=9]
	%0 = getelementptr i8* %stringConstant, i32 0		; <i8*> [#uses=1]
	store i8 102, i8* %0
	%1 = getelementptr i8* %stringConstant, i32 1		; <i8*> [#uses=1]
	store i8 111, i8* %1
	%2 = getelementptr i8* %stringConstant, i32 2		; <i8*> [#uses=1]
	store i8 111, i8* %2
	%3 = getelementptr i8* %stringConstant, i32 3		; <i8*> [#uses=1]
	store i8 98, i8* %3
	%4 = getelementptr i8* %stringConstant, i32 4		; <i8*> [#uses=1]
	store i8 97, i8* %4
	%5 = getelementptr i8* %stringConstant, i32 5		; <i8*> [#uses=1]
	store i8 114, i8* %5
	%6 = getelementptr i8* %stringConstant, i32 6		; <i8*> [#uses=1]
	store i8 32, i8* %6
	%7 = getelementptr i8* %stringConstant, i32 7		; <i8*> [#uses=1]
	store i8 0, i8* %7
	call void @string_copy(i8* %stringConstant, i8* getelementptr ([100 x i8]* @b, i32 0, i32 0))
	br label %"main 3"

"main 3":		; preds = %"main 2"
	%8 = load double* @a		; <double> [#uses=1]
	%9 = alloca i8, i32 100		; <i8*> [#uses=2]
	call void @string_double_to_string(double %8, i8* %9)
	%10 = alloca i8, i32 100		; <i8*> [#uses=2]
	call void @string_concat(i8* getelementptr ([100 x i8]* @b, i32 0, i32 0), i8* %9, i8* %10)
	call void @string_copy(i8* %10, i8* getelementptr ([100 x i8]* @c, i32 0, i32 0))
	br label %"main 4"

"main 4":		; preds = %"main 3"
	call void @string_print(i8* getelementptr ([100 x i8]* @c, i32 0, i32 0))
	br label %"main 5"

"main 5":		; preds = %"main 4"
	%11 = load double* @a		; <double> [#uses=1]
	%12 = load double* @a		; <double> [#uses=1]
	%13 = mul double 1.000000e+01, %12		; <double> [#uses=1]
	%14 = add double %11, %13		; <double> [#uses=1]
	store double %14, double* @d
	br label %"main 6"

"main 6":		; preds = %"main 5"
	%15 = load double* @d		; <double> [#uses=1]
	%16 = alloca i8, i32 100		; <i8*> [#uses=2]
	call void @string_double_to_string(double %15, i8* %16)
	call void @string_print(i8* %16)
	br label %"main 7"

"main 7":		; preds = %"main 6"
	%17 = load double* @a		; <double> [#uses=1]
	%18 = fdiv double %17, 3.140000e+00		; <double> [#uses=1]
	store double %18, double* @e
	br label %"main 8"

"main 8":		; preds = %"main 7"
	%19 = load double* @e		; <double> [#uses=1]
	%20 = alloca i8, i32 100		; <i8*> [#uses=2]
	call void @string_double_to_string(double %19, i8* %20)
	call void @string_print(i8* %20)
	ret void
}

declare i32 @printf(i8* noalias , ...) nounwind
declare i32 @sprintf(i8* noalias , i8* noalias , ...) nounwind 