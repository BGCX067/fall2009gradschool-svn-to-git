; ModuleID = 'module'
@i = weak global double 0.000000e+00		; <double*> [#uses=0]
@j = weak global double 0.000000e+00		; <double*> [#uses=0]

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
	%i = alloca double		; <double*> [#uses=5]
	%j = alloca double		; <double*> [#uses=6]
	%k = alloca double		; <double*> [#uses=3]
	br label %main

main:		; preds = %allocateLocals
	store double 2.000000e+01, double* %i
	br label %"main 2"

"main 2":		; preds = %"WhileBlock 2", %main
	%0 = load double* %i		; <double> [#uses=1]
	%1 = fcmp ogt double %0, 0.000000e+00		; <i1> [#uses=1]
	br i1 %1, label %WhileBlock, label %WhileBreakBlock

WhileBlock:		; preds = %"main 2"
	%2 = load double* %i		; <double> [#uses=1]
	%3 = alloca i8, i32 100		; <i8*> [#uses=2]
	call void @string_double_to_string(double %2, i8* %3)
	call void @string_print(i8* %3)
	br label %"WhileBlock 2"

"WhileBlock 2":		; preds = %WhileBlock
	%4 = load double* %i		; <double> [#uses=1]
	%5 = sub double %4, 1.000000e+00		; <double> [#uses=1]
	store double %5, double* %i
	br label %"main 2"

WhileBreakBlock:		; preds = %"main 2"
	br label %"main 3"

"main 3":		; preds = %WhileBreakBlock
	store double 1.000000e+00, double* %j
	br label %"main 4"

"main 4":		; preds = %RepeateTestBlock, %"main 3"
	%6 = load double* %j		; <double> [#uses=1]
	%7 = alloca i8, i32 100		; <i8*> [#uses=2]
	call void @string_double_to_string(double %6, i8* %7)
	call void @string_print(i8* %7)
	br label %"main 4 2"

"main 4 2":		; preds = %"main 4"
	%8 = load double* %j		; <double> [#uses=1]
	%9 = add double %8, 1.000000e+00		; <double> [#uses=1]
	store double %9, double* %j
	br label %RepeateTestBlock

RepeateTestBlock:		; preds = %"main 4 2"
	%10 = load double* %j		; <double> [#uses=1]
	%11 = fcmp ogt double %10, 2.000000e+01		; <i1> [#uses=1]
	br i1 %11, label %RepeateBreakBlock, label %"main 4"

RepeateBreakBlock:		; preds = %RepeateTestBlock
	br label %"main 5"

"main 5":		; preds = %RepeateBreakBlock
	%stringConstant = alloca i8, i32 100		; <i8*> [#uses=4]
	%12 = getelementptr i8* %stringConstant, i32 0		; <i8*> [#uses=1]
	store i8 106, i8* %12
	%13 = getelementptr i8* %stringConstant, i32 1		; <i8*> [#uses=1]
	store i8 61, i8* %13
	%14 = getelementptr i8* %stringConstant, i32 2		; <i8*> [#uses=1]
	store i8 0, i8* %14
	%15 = load double* %j		; <double> [#uses=1]
	%16 = alloca i8, i32 100		; <i8*> [#uses=2]
	call void @string_double_to_string(double %15, i8* %16)
	%17 = alloca i8, i32 100		; <i8*> [#uses=2]
	call void @string_concat(i8* %stringConstant, i8* %16, i8* %17)
	call void @string_print(i8* %17)
	br label %"main 6"

"main 6":		; preds = %"main 5"
	store double 1.000000e+00, double* %k
	br label %"main 7"

"main 7":		; preds = %RepeateTestBlock3, %"main 6"
	%stringConstant2 = alloca i8, i32 100		; <i8*> [#uses=6]
	%18 = getelementptr i8* %stringConstant2, i32 0		; <i8*> [#uses=1]
	store i8 71, i8* %18
	%19 = getelementptr i8* %stringConstant2, i32 1		; <i8*> [#uses=1]
	store i8 79, i8* %19
	%20 = getelementptr i8* %stringConstant2, i32 2		; <i8*> [#uses=1]
	store i8 79, i8* %20
	%21 = getelementptr i8* %stringConstant2, i32 3		; <i8*> [#uses=1]
	store i8 68, i8* %21
	%22 = getelementptr i8* %stringConstant2, i32 4		; <i8*> [#uses=1]
	store i8 0, i8* %22
	call void @string_print(i8* %stringConstant2)
	br label %RepeateTestBlock3

RepeateTestBlock3:		; preds = %"main 7"
	%23 = load double* %k		; <double> [#uses=1]
	%24 = fcmp oeq double %23, 1.000000e+00		; <i1> [#uses=1]
	br i1 %24, label %RepeateBreakBlock1, label %"main 7"

RepeateBreakBlock1:		; preds = %RepeateTestBlock3
	br label %"main 8"

"main 8":		; preds = %WhileBlock4, %RepeateBreakBlock1
	%25 = load double* %k		; <double> [#uses=1]
	%26 = fcmp one double %25, 1.000000e+00		; <i1> [#uses=1]
	br i1 %26, label %WhileBlock4, label %WhileBreakBlock5

WhileBlock4:		; preds = %"main 8"
	%stringConstant6 = alloca i8, i32 100		; <i8*> [#uses=5]
	%27 = getelementptr i8* %stringConstant6, i32 0		; <i8*> [#uses=1]
	store i8 66, i8* %27
	%28 = getelementptr i8* %stringConstant6, i32 1		; <i8*> [#uses=1]
	store i8 65, i8* %28
	%29 = getelementptr i8* %stringConstant6, i32 2		; <i8*> [#uses=1]
	store i8 68, i8* %29
	%30 = getelementptr i8* %stringConstant6, i32 3		; <i8*> [#uses=1]
	store i8 0, i8* %30
	call void @string_print(i8* %stringConstant6)
	br label %"main 8"

WhileBreakBlock5:		; preds = %"main 8"
	ret void
}

declare i32 @printf(i8* noalias , ...) nounwind
declare i32 @sprintf(i8* noalias , i8* noalias , ...) nounwind 