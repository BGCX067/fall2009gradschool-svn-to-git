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
@global.a = common global double 0.000000e+00
@fact.retval = common global {double} zeroinitializer
@print0 = constant [5 x i8] c"%s\09\0A\00"
@string0 = constant [12 x i8] c"factorial (\00"
@string1 = constant [3 x i8] c") \00"
@print1 = constant [5 x i8] c"%s\09\0A\00"
@string2 = constant [4 x i8] c" = \00"
@string3 = constant [17 x i8] c"\0ARandom numbers:\00"
@print2 = constant [5 x i8] c"%s\09\0A\00"
@main.bb8.i = common global double 0.000000e+00
@main.bb10.j = common global double 0.000000e+00
@print3 = constant [5 x i8] c"%f\09\0A\00"
define void @factorial(double %m, i8* %c) {
entry:
%factorial.m = alloca double
store double %m, double* %factorial.m
%factorial.c = alloca i8*
store i8* %c, i8** %factorial.c
br label %factorial.bb1
factorial.bb1:
%factorial.bb1.tmp16 = load i8** %factorial.c
%factorial.bb1.tmp17 = load double* %factorial.m
call void@fact(double %factorial.bb1.tmp17)
%factorial.bb1.tmp18 = load {double}* @fact.retval
%factorial.bb1.tmp19 = extractvalue {double} %factorial.bb1.tmp18, 0
%factorial.bb1.tmp20 = call i8*@ftoa(double %factorial.bb1.tmp19)
%factorial.bb1.tmp21 = call i8*@stringcat(i8* %factorial.bb1.tmp16, i8* %factorial.bb1.tmp20)
%factorial.bb1.tmp22 = bitcast [5 x i8]* @print0 to i8*
call i32 (i8*, ...)* @printf(i8* %factorial.bb1.tmp22, i8* %factorial.bb1.tmp21)
br label %return
return:
ret void
}
define void @fact(double %n) {
entry:
%fact.n = alloca double
store double %n, double* %fact.n
%retval0 = alloca double
br label %fact.bb2
fact.bb2:
%fact.bb2.tmp3 = load double* %fact.n
%fact.bb2.tmp4 = add double 0.000000e+00, 0.000000
%fact.bb2.tmp2 = fcmp ueq double %fact.bb2.tmp3, %fact.bb2.tmp4
br i1 %fact.bb2.tmp2, label %fact.bb4, label %fact.bb5
fact.bb4:
%fact.bb4.tmp5 = add double 0.000000e+00, 1.000000
store double %fact.bb4.tmp5, double* %retval0
br label %return
br label %fact.bb3
fact.bb5:
%fact.bb5.tmp7 = load double* %fact.n
%fact.bb5.tmp9 = load double* %fact.n
%fact.bb5.tmp10 = add double 0.000000e+00, 1.000000
%fact.bb5.tmp8 = sub double %fact.bb5.tmp9, %fact.bb5.tmp10
call void@fact(double %fact.bb5.tmp8)
%fact.bb5.tmp11 = load {double}* @fact.retval
%fact.bb5.tmp12 = extractvalue {double} %fact.bb5.tmp11, 0
%fact.bb5.tmp6 = mul double %fact.bb5.tmp7, %fact.bb5.tmp12
store double %fact.bb5.tmp6, double* %retval0
br label %return
br label %fact.bb3
fact.bb3:
br label %return
return:
%fact.return.tmp13 = load double* %retval0
%fact.return.tmp14 = getelementptr {double}* @fact.retval, i32 0, i32 0
store double %fact.return.tmp13, double* %fact.return.tmp14
ret void
}
define i32 @main() {
entry:
br label %main.bb0
main.bb0:
%main.bb0.tmp0 = add double 0.000000e+00, 5.000000
%main.bb0.tmp1 = load double* @global.a
store double %main.bb0.tmp0, double* @global.a
br label %main.bb6
main.bb6:
%main.bb6.tmp24 = load double* @global.a
%main.bb6.tmp25 = add double 0.000000e+00, 1.000000
%main.bb6.tmp23 = sub double %main.bb6.tmp24, %main.bb6.tmp25
%main.bb6.tmp26 = load double* @global.a
store double %main.bb6.tmp23, double* @global.a
%main.bb6.tmp28 = bitcast [12 x i8]* @string0 to i8*
%main.bb6.tmp30 = load double* @global.a
%main.bb6.tmp31 = bitcast [3 x i8]* @string1 to i8*
%main.bb6.tmp32 = call i8*@ftoa(double %main.bb6.tmp30)
%main.bb6.tmp33 = call i8*@stringcat(i8* %main.bb6.tmp32, i8* %main.bb6.tmp31)
%main.bb6.tmp34 = call i8*@stringcat(i8* %main.bb6.tmp28, i8* %main.bb6.tmp33)
%main.bb6.tmp35 = bitcast [5 x i8]* @print1 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb6.tmp35, i8* %main.bb6.tmp34)
%main.bb6.tmp36 = load double* @global.a
%main.bb6.tmp37 = bitcast [4 x i8]* @string2 to i8*
call void@factorial(double %main.bb6.tmp36, i8* %main.bb6.tmp37)
br label %main.bb7
main.bb7:
%main.bb7.tmp40 = load double* @global.a
%main.bb7.tmp42 = load double* @global.a
%main.bb7.tmp43 = add double 0.000000e+00, 1.000000
%main.bb7.tmp41 = sub double %main.bb7.tmp42, %main.bb7.tmp43
%main.bb7.tmp44 = add i1 0, 1
br i1 %main.bb7.tmp44, label %main.bb8, label %main.bb6
main.bb8:
%main.bb8.tmp45 = bitcast [17 x i8]* @string3 to i8*
%main.bb8.tmp46 = bitcast [5 x i8]* @print2 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb8.tmp46, i8* %main.bb8.tmp45)
%main.bb8.tmp47 = add double 0.000000e+00, 1.000000
store double %main.bb8.tmp47, double* @main.bb8.i
%main.bb8.tmp48 = add double 0.000000e+00, 5.000000
%main.bb8.tmp49 = add double 0.000000e+00, 1.000000
br label %main.bb9
main.bb9:
%main.bb9.tmp50 = load double* @main.bb8.i
%main.bb9.tmp52 = fcmp ugt double %main.bb8.tmp49, 0.000000e+00
%main.bb9.tmp53 = fcmp ule double %main.bb9.tmp50, %main.bb8.tmp48
%main.bb9.tmp54 = and i1 %main.bb9.tmp52, %main.bb9.tmp53
%main.bb9.tmp55 = fcmp ule double %main.bb8.tmp49, 0.000000e+00
%main.bb9.tmp56 = fcmp uge double %main.bb9.tmp50, %main.bb8.tmp48
%main.bb9.tmp57 = and i1 %main.bb9.tmp55, %main.bb9.tmp56
%main.bb9.tmp51 = or i1 %main.bb9.tmp54, %main.bb9.tmp57
br i1 %main.bb9.tmp51, label %main.bb10, label %main.bb11
main.bb10:
%main.bb10.tmp60 = add double 0.000000e+00, 1.000000
store double %main.bb10.tmp60, double* @main.bb10.j
%main.bb10.tmp61 = load double* @main.bb8.i
%main.bb10.tmp62 = add double 0.000000e+00, 1.000000
br label %main.bb12
main.bb12:
%main.bb12.tmp63 = load double* @main.bb10.j
%main.bb12.tmp65 = fcmp ugt double %main.bb10.tmp62, 0.000000e+00
%main.bb12.tmp66 = fcmp ule double %main.bb12.tmp63, %main.bb10.tmp61
%main.bb12.tmp67 = and i1 %main.bb12.tmp65, %main.bb12.tmp66
%main.bb12.tmp68 = fcmp ule double %main.bb10.tmp62, 0.000000e+00
%main.bb12.tmp69 = fcmp uge double %main.bb12.tmp63, %main.bb10.tmp61
%main.bb12.tmp70 = and i1 %main.bb12.tmp68, %main.bb12.tmp69
%main.bb12.tmp64 = or i1 %main.bb12.tmp67, %main.bb12.tmp70
br i1 %main.bb12.tmp64, label %main.bb13, label %main.bb14
main.bb13:
%main.bb13.tmp76 = load double* @main.bb8.i
%main.bb13.tmp77 = load double* @main.bb10.j
%main.bb13.tmp75 = mul double %main.bb13.tmp76, %main.bb13.tmp77
%main.bb13.tmp78 = load double* @main.bb8.i
%main.bb13.tmp74 = add double %main.bb13.tmp75, %main.bb13.tmp78
%main.bb13.tmp81 = load double* @main.bb10.j
%main.bb13.tmp82 = load double* @main.bb10.j
%main.bb13.tmp80 = fdiv double %main.bb13.tmp81, %main.bb13.tmp82
%main.bb13.tmp84 = load double* @global.a
%main.bb13.tmp85 = add double 0.000000e+00, 2.000000
%main.bb13.tmp86 = call double@llvm.pow.f64(double %main.bb13.tmp84, double %main.bb13.tmp85)
%main.bb13.tmp79 = frem double %main.bb13.tmp80, %main.bb13.tmp86
%main.bb13.tmp73 = sub double %main.bb13.tmp74, %main.bb13.tmp79
%main.bb13.tmp87 = bitcast [5 x i8]* @print3 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb13.tmp87, double %main.bb13.tmp73)
%main.bb13.tmp90 = load double* @main.bb8.i
%main.bb13.tmp91 = load double* @main.bb10.j
%main.bb13.tmp89 = mul double %main.bb13.tmp90, %main.bb13.tmp91
%main.bb13.tmp92 = add double 0.000000e+00, 100.000000
%main.bb13.tmp88 = fcmp ueq double %main.bb13.tmp89, %main.bb13.tmp92
br i1 %main.bb13.tmp88, label %main.bb16, label %main.bb17
main.bb16:
br label %main.bb14
br label %main.bb15
main.bb17:
br label %main.bb15
main.bb15:
%main.bb13.tmp71 = load double* @main.bb10.j
%main.bb13.tmp72 = add double %main.bb13.tmp71, %main.bb10.tmp62
store double %main.bb13.tmp72, double* @main.bb10.j
br label %main.bb12
main.bb14:
%main.bb10.tmp58 = load double* @main.bb8.i
%main.bb10.tmp59 = add double %main.bb10.tmp58, %main.bb8.tmp49
store double %main.bb10.tmp59, double* @main.bb8.i
br label %main.bb9
main.bb11:
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
