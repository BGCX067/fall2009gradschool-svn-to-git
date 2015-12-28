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
@fact.retval = common global {double} zeroinitializer
@string20 = constant [21 x i8] c"Factorial of 5 is : \00"
@print31 = constant [5 x i8] c"%s\09\0A\00"
define void @fact(double %n) {
entry:
%fact.n = alloca double
store double %n, double* %fact.n
%retval0 = alloca double
br label %fact.bb26
fact.bb26:
%fact.bb26.tmp246 = load double* %fact.n
%fact.bb26.tmp247 = add double 0.000000e+00, 0.000000
%fact.bb26.tmp245 = fcmp ueq double %fact.bb26.tmp246, %fact.bb26.tmp247
br i1 %fact.bb26.tmp245, label %fact.bb28, label %fact.bb29
fact.bb28:
%fact.bb28.tmp248 = add double 0.000000e+00, 1.000000
store double %fact.bb28.tmp248, double* %retval0
br label %return
br label %fact.bb27
fact.bb29:
%fact.bb29.tmp250 = load double* %fact.n
%fact.bb29.tmp252 = load double* %fact.n
%fact.bb29.tmp253 = add double 0.000000e+00, 1.000000
%fact.bb29.tmp251 = sub double %fact.bb29.tmp252, %fact.bb29.tmp253
call void@fact(double %fact.bb29.tmp251)
%fact.bb29.tmp254 = load {double}* @fact.retval
%fact.bb29.tmp255 = extractvalue {double} %fact.bb29.tmp254, 0
%fact.bb29.tmp249 = mul double %fact.bb29.tmp250, %fact.bb29.tmp255
store double %fact.bb29.tmp249, double* %retval0
br label %return
br label %fact.bb27
fact.bb27:
br label %return
return:
%fact.return.tmp256 = load double* %retval0
%fact.return.tmp257 = getelementptr {double}* @fact.retval, i32 0, i32 0
store double %fact.return.tmp256, double* %fact.return.tmp257
ret void
}
define i32 @main() {
entry:
br label %main.bb25
main.bb25:
%main.bb25.tmp259 = bitcast [21 x i8]* @string20 to i8*
%main.bb25.tmp260 = add double 0.000000e+00, 5.000000
call void@fact(double %main.bb25.tmp260)
%main.bb25.tmp261 = load {double}* @fact.retval
%main.bb25.tmp262 = extractvalue {double} %main.bb25.tmp261, 0
%main.bb25.tmp263 = call i8*@ftoa(double %main.bb25.tmp262)
%main.bb25.tmp264 = call i8*@stringcat(i8* %main.bb25.tmp259, i8* %main.bb25.tmp263)
%main.bb25.tmp265 = bitcast [5 x i8]* @print31 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb25.tmp265, i8* %main.bb25.tmp264)
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
