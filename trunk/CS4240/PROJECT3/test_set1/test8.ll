declare i32 @printf(i8* , ...)
declare i8* @strcat(i8* , i8* )
declare i32 @strlen(i8*)
declare double @llvm.pow.f64(double, double)
declare double @atof(i8*)
declare i32 @sprintf(i8*, i8*, ...)
declare i8* @malloc(i32)
declare void @llvm.memset.i32(i8* , i8, i32, i32)
declare i8* @strcpy(i8* , i8*)
declare i32 @strcmp(i8*, i8*)
@ftoa.str = internal constant [3 x i8] c"%f\00"
@false.str = internal constant [6 x i8] c"false\00"
@true.str = internal constant [5 x i8] c"true\00"
@global.i = common global double 0.000000e+00
@global.x = common global double 0.000000e+00
@main.bb94.x = common global double 0.000000e+00
@print80 = constant [5 x i8] c"%f\09\0A\00"
@main.bb97.x = common global double 0.000000e+00
@print81 = constant [5 x i8] c"%f\09\0A\00"
@print82 = constant [5 x i8] c"%f\09\0A\00"
@print83 = constant [5 x i8] c"%f\09\0A\00"
define i32 @main() {
entry:
br label %main.bb92
main.bb92:
%main.bb92.tmp721 = add double 0.000000e+00, 10.000000
%main.bb92.tmp722 = load double* @global.x
store double %main.bb92.tmp721, double* @global.x
%main.bb92.tmp723 = add double 0.000000e+00, 1.000000
%main.bb92.tmp724 = load double* @global.i
store double %main.bb92.tmp723, double* @global.i
br label %main.bb93
main.bb93:
%main.bb93.tmp726 = load double* @global.i
%main.bb93.tmp727 = load double* @global.x
%main.bb93.tmp725 = fcmp ule double %main.bb93.tmp726, %main.bb93.tmp727
br i1 %main.bb93.tmp725, label %main.bb94, label %main.bb95
main.bb94:
%main.bb94.tmp729 = load double* @global.i
%main.bb94.tmp730 = add double 0.000000e+00, 2.000000
%main.bb94.tmp728 = mul double %main.bb94.tmp729, %main.bb94.tmp730
%main.bb94.tmp731 = load double* @main.bb94.x
store double %main.bb94.tmp728, double* @main.bb94.x
%main.bb94.tmp732 = load double* @main.bb94.x
%main.bb94.tmp733 = bitcast [5 x i8]* @print80 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb94.tmp733, double %main.bb94.tmp732)
%main.bb94.tmp735 = load double* @global.i
%main.bb94.tmp736 = add double 0.000000e+00, 1.000000
%main.bb94.tmp734 = add double %main.bb94.tmp735, %main.bb94.tmp736
%main.bb94.tmp737 = load double* @global.i
store double %main.bb94.tmp734, double* @global.i
br label %main.bb93
main.bb95:
%main.bb95.tmp739 = load double* @global.i
%main.bb95.tmp740 = add double 0.000000e+00, 20.000000
%main.bb95.tmp738 = fcmp ugt double %main.bb95.tmp739, %main.bb95.tmp740
br i1 %main.bb95.tmp738, label %main.bb97, label %main.bb98
main.bb97:
%main.bb97.tmp741 = load double* @main.bb97.x
%main.bb97.tmp742 = add double 0.000000e+00, 20.000000
%main.bb97.tmp743 = load double* @main.bb97.x
store double %main.bb97.tmp742, double* @main.bb97.x
%main.bb97.tmp745 = load double* @main.bb97.x
%main.bb97.tmp746 = add double 0.000000e+00, 2.000000
%main.bb97.tmp744 = add double %main.bb97.tmp745, %main.bb97.tmp746
%main.bb97.tmp747 = bitcast [5 x i8]* @print81 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb97.tmp747, double %main.bb97.tmp744)
br label %main.bb96
main.bb98:
%main.bb98.tmp748 = load double* @global.x
%main.bb98.tmp749 = bitcast [5 x i8]* @print82 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb98.tmp749, double %main.bb98.tmp748)
br label %main.bb96
main.bb96:
%main.bb96.tmp750 = load double* @global.x
%main.bb96.tmp751 = bitcast [5 x i8]* @print83 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb96.tmp751, double %main.bb96.tmp750)
ret i32 0
}
define i8* @ftoa(double %num) {
entry:
%num_addr = alloca double
%retval = alloca i8*
%c = alloca i8*
%0 = alloca i8*
%"alloca point" = bitcast i32 0 to i32
store double %num, double* %num_addr
%1 = call i8* @malloc(i32 256)
store i8* %1, i8** %c
%2 = load i8** %c
call void @llvm.memset.i32(i8* %2, i8 0, i32 256, i32 1)
%3 = load i8** %c
%4 = load double* %num_addr
%5 = call i32 (i8*, i8*, ...)* @sprintf(i8* %3, i8* getelementptr ([3 x i8]* @ftoa.str, i32 0, i32 0), double %4)
%6 = load i8** %c
store i8* %6, i8** %0
%7 = load i8** %0
store i8* %7, i8** %retval
br label %return
return:
%retval1 = load i8** %retval
ret i8* %retval1
}
define i8* @stringcat(i8* %s1, i8* %s2) {
entry:
%s1_addr = alloca i8*
%s2_addr = alloca i8*
%retval = alloca i8*
%s = alloca i8*
%0 = alloca i8*
%"alloca point" = bitcast i32 0 to i32
store i8* %s1, i8** %s1_addr
store i8* %s2, i8** %s2_addr
%1 = call i8* @malloc(i32 256)
store i8* %1, i8** %s
%2 = load i8** %s
call void @llvm.memset.i32(i8* %2, i8 0, i32 256, i32 1)
%3 = load i8** %s
%4 = load i8** %s1_addr
%5 = call i8* @strcpy(i8* %3, i8* %4)
%6 = load i8** %s
%7 = load i8** %s2_addr
%8 = call i8* @strcat(i8* %6, i8* %7)
%9 = load i8** %s
store i8* %9, i8** %0
%10 = load i8** %0
store i8* %10, i8** %retval
br label %return
return:
%retval1 = load i8** %retval
ret i8* %retval1
}
define i1 @stringcmp(i8* %s1, i8* %s2, i32 %op)  {
entry:
%s1_addr = alloca i8*
%s2_addr = alloca i8*
%op_addr = alloca i32	
%retval = alloca i1
%i = alloca i32
%0 = alloca i1
%"alloca point" = bitcast i32 0 to i32
store i8* %s1, i8** %s1_addr
store i8* %s2, i8** %s2_addr
store i32 %op, i32* %op_addr
%1 = load i8** %s1_addr
%2 = load i8** %s2_addr
%3 = call i32 @strcmp(i8* %1, i8* %2)
store i32 %3, i32* %i
%4 = load i32* %op_addr
switch i32 %4, label %bb6 [
i32 0, label %bb
i32 1, label %bb1
i32 2, label %bb2
i32 3, label %bb3
i32 4, label %bb4
i32 5, label %bb5
]
bb:
%5 = load i32* %i
%6 = icmp slt i32 %5, 0
store i1 %6, i1* %0
br label %bb7
bb1:
%7 = load i32* %i
%8 = icmp sgt i32 %7, 0
store i1 %8, i1* %0
br label %bb7
bb2:
%9 = load i32* %i
%10 = icmp sle i32 %9, 0
store i1 %10, i1* %0
br label %bb7
bb3:
%11 = load i32* %i
%12 = icmp sge i32 %11, 0
store i1 %12, i1* %0
br label %bb7
bb4:
%13 = load i32* %i
%14 = icmp ne i32 %13, 0
store i1 %14, i1* %0
br label %bb7
bb5:
%15 = load i32* %i
%16 = icmp eq i32 %15, 0
store i1 %16, i1* %0
br label %bb7
bb6:
br label %return
bb7:		; preds = %bb5, %bb4, %bb3, %bb2, %bb1, %bb
%17 = load i1* %0
store i1 %17, i1* %retval
br label %return
return:
%retval8 = load i1* %retval
ret i1 %retval8
}
define i8* @btoa(i1 %i) {
entry:
%i_addr = alloca i1
%retval = alloca i8*
%0 = alloca i8*
%"alloca point" = bitcast i32 0 to i32
store i1 %i, i1* %i_addr
%1 = load i1* %i_addr
%2 = icmp eq i1 %1, 0
br i1 %2, label %bb, label %bb1
bb:
store i8* getelementptr ([6 x i8]* @false.str, i32 0, i32 0), i8** %0
br label %bb2
bb1:
store i8* getelementptr ([5 x i8]* @true.str, i32 0, i32 0), i8** %0
br label %bb2
bb2:
%3 = load i8** %0
store i8* %3, i8** %retval
br label %return
return:
%retval3 = load i8** %retval
ret i8* %retval3
}
