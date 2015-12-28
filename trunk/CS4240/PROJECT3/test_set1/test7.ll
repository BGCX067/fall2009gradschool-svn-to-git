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
@global.N = common global double 0.000000e+00
@global.n = common global double 0.000000e+00
@fib.retval = common global {double} zeroinitializer
@test.bb91.v = common global double 0.000000e+00
@print78 = constant [14 x i8] c"%s\09%f\09%f\09%f\09\0A\00"
@string50 = constant [1 x i8] c"\00"
@string51 = constant [2 x i8] c"n\00"
@string52 = constant [6 x i8] c"value\00"
@string53 = constant [6 x i8] c"evals\00"
@print79 = constant [14 x i8] c"%s\09%s\09%s\09%s\09\0A\00"
@string54 = constant [6 x i8] c"plain\00"
define void @fib(double %n) {
entry:
%fib.n = alloca double
store double %n, double* %fib.n
%retval0 = alloca double
br label %fib.bb87
fib.bb87:
%fib.bb87.tmp681 = load double* @global.N
%fib.bb87.tmp682 = add double 0.000000e+00, 1.000000
%fib.bb87.tmp680 = add double %fib.bb87.tmp681, %fib.bb87.tmp682
%fib.bb87.tmp683 = load double* @global.N
store double %fib.bb87.tmp680, double* @global.N
%fib.bb87.tmp685 = load double* %fib.n
%fib.bb87.tmp686 = add double 0.000000e+00, 2.000000
%fib.bb87.tmp684 = fcmp ult double %fib.bb87.tmp685, %fib.bb87.tmp686
br i1 %fib.bb87.tmp684, label %fib.bb89, label %fib.bb90
fib.bb89:
%fib.bb89.tmp687 = load double* %fib.n
store double %fib.bb89.tmp687, double* %retval0
br label %return
br label %fib.bb88
fib.bb90:
%fib.bb90.tmp690 = load double* %fib.n
%fib.bb90.tmp691 = add double 0.000000e+00, 1.000000
%fib.bb90.tmp689 = sub double %fib.bb90.tmp690, %fib.bb90.tmp691
call void@fib(double %fib.bb90.tmp689)
%fib.bb90.tmp692 = load {double}* @fib.retval
%fib.bb90.tmp693 = extractvalue {double} %fib.bb90.tmp692, 0
%fib.bb90.tmp695 = load double* %fib.n
%fib.bb90.tmp696 = add double 0.000000e+00, 2.000000
%fib.bb90.tmp694 = sub double %fib.bb90.tmp695, %fib.bb90.tmp696
call void@fib(double %fib.bb90.tmp694)
%fib.bb90.tmp697 = load {double}* @fib.retval
%fib.bb90.tmp698 = extractvalue {double} %fib.bb90.tmp697, 0
%fib.bb90.tmp688 = add double %fib.bb90.tmp693, %fib.bb90.tmp698
store double %fib.bb90.tmp688, double* %retval0
br label %return
br label %fib.bb88
fib.bb88:
br label %return
return:
%fib.return.tmp699 = load double* %retval0
%fib.return.tmp700 = getelementptr {double}* @fib.retval, i32 0, i32 0
store double %fib.return.tmp699, double* %fib.return.tmp700
ret void
}
define void @test(i8* %s) {
entry:
%test.s = alloca i8*
store i8* %s, i8** %test.s
br label %test.bb91
test.bb91:
%test.bb91.tmp701 = add double 0.000000e+00, 0.000000
%test.bb91.tmp702 = load double* @global.N
store double %test.bb91.tmp701, double* @global.N
%test.bb91.tmp703 = load double* @global.n
call void@fib(double %test.bb91.tmp703)
%test.bb91.tmp704 = load {double}* @fib.retval
%test.bb91.tmp705 = extractvalue {double} %test.bb91.tmp704, 0
%test.bb91.tmp706 = load double* @test.bb91.v
store double %test.bb91.tmp705, double* @test.bb91.v
%test.bb91.tmp707 = load i8** %test.s
%test.bb91.tmp708 = load double* @global.n
%test.bb91.tmp709 = load double* @test.bb91.v
%test.bb91.tmp710 = load double* @global.N
%test.bb91.tmp711 = bitcast [14 x i8]* @print78 to i8*
call i32 (i8*, ...)* @printf(i8* %test.bb91.tmp711, i8* %test.bb91.tmp707, double %test.bb91.tmp708, double %test.bb91.tmp709, double %test.bb91.tmp710)
br label %return
return:
ret void
}
define i32 @main() {
entry:
br label %main.bb86
main.bb86:
%main.bb86.tmp712 = add double 0.000000e+00, 24.000000
%main.bb86.tmp713 = load double* @global.n
store double %main.bb86.tmp712, double* @global.n
%main.bb86.tmp714 = bitcast [1 x i8]* @string50 to i8*
%main.bb86.tmp715 = bitcast [2 x i8]* @string51 to i8*
%main.bb86.tmp716 = bitcast [6 x i8]* @string52 to i8*
%main.bb86.tmp717 = bitcast [6 x i8]* @string53 to i8*
%main.bb86.tmp718 = bitcast [14 x i8]* @print79 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb86.tmp718, i8* %main.bb86.tmp714, i8* %main.bb86.tmp715, i8* %main.bb86.tmp716, i8* %main.bb86.tmp717)
%main.bb86.tmp719 = bitcast [6 x i8]* @string54 to i8*
call void@test(i8* %main.bb86.tmp719)
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
