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
@global.page = common global i8* null
@string0 = constant [44 x i8] c"one line\0Anext line\0A\22in quotes\22, 'in quotes'\00"
@print0 = constant [5 x i8] c"%s\09\0A\00"
@string1 = constant [31 x i8] c"a backslash inside quotes: '\5C'\00"
@print1 = constant [5 x i8] c"%s\09\0A\00"
@string2 = constant [19 x i8] c"a simpler way: '\5C'\00"
@print2 = constant [5 x i8] c"%s\09\0A\00"
@string3 = constant [113 x i8] c"<HTML>\0A<HEAD>\0A<TITLE>An HTML Page</TITLE>\0A</HEAD>\0A<BODY>\0ALua\0A[[a text between double brackets]]\0A</BODY>\0A</HTML>\0A\00"
@print3 = constant [5 x i8] c"%s\09\0A\00"
@string4 = constant [3 x i8] c"10\00"
@print4 = constant [5 x i8] c"%f\09\0A\00"
@string5 = constant [7 x i8] c"10 + 1\00"
@print5 = constant [5 x i8] c"%s\09\0A\00"
@string6 = constant [8 x i8] c"-5.3e-2\00"
@string7 = constant [2 x i8] c"2\00"
@print6 = constant [5 x i8] c"%f\09\0A\00"
@string8 = constant [6 x i8] c"hello\00"
@string9 = constant [6 x i8] c"world\00"
@print7 = constant [5 x i8] c"%s\09\0A\00"
@print8 = constant [5 x i8] c"%f\09\0A\00"
@print9 = constant [5 x i8] c"%f\09\0A\00"
@print10 = constant [5 x i8] c"%s\09\0A\00"
@print11 = constant [5 x i8] c"%s\09\0A\00"
@print12 = constant [5 x i8] c"%s\09\0A\00"
@print13 = constant [5 x i8] c"%s\09\0A\00"
@string10 = constant [6 x i8] c"hello\00"
@print14 = constant [5 x i8] c"%f\09\0A\00"
@print15 = constant [5 x i8] c"%f\09\0A\00"
define i32 @main() {
entry:
br label %main.bb0
main.bb0:
%main.bb0.tmp0 = bitcast [44 x i8]* @string0 to i8*
%main.bb0.tmp1 = bitcast [5 x i8]* @print0 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp1, i8* %main.bb0.tmp0)
%main.bb0.tmp2 = bitcast [31 x i8]* @string1 to i8*
%main.bb0.tmp3 = bitcast [5 x i8]* @print1 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp3, i8* %main.bb0.tmp2)
%main.bb0.tmp4 = bitcast [19 x i8]* @string2 to i8*
%main.bb0.tmp5 = bitcast [5 x i8]* @print2 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp5, i8* %main.bb0.tmp4)
%main.bb0.tmp6 = bitcast [113 x i8]* @string3 to i8*
%main.bb0.tmp7 = load i8** @global.page
store i8* %main.bb0.tmp6, i8** @global.page
%main.bb0.tmp8 = load i8** @global.page
%main.bb0.tmp9 = bitcast [5 x i8]* @print3 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp9, i8* %main.bb0.tmp8)
%main.bb0.tmp11 = bitcast [3 x i8]* @string4 to i8*
%main.bb0.tmp12 = add double 0.000000e+00, 1.000000
%main.bb0.tmp13 = call double@atof(i8* %main.bb0.tmp11)
%main.bb0.tmp10 = add double %main.bb0.tmp13, %main.bb0.tmp12
%main.bb0.tmp14 = bitcast [5 x i8]* @print4 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp14, double %main.bb0.tmp10)
%main.bb0.tmp15 = bitcast [7 x i8]* @string5 to i8*
%main.bb0.tmp16 = bitcast [5 x i8]* @print5 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp16, i8* %main.bb0.tmp15)
%main.bb0.tmp18 = bitcast [8 x i8]* @string6 to i8*
%main.bb0.tmp19 = bitcast [2 x i8]* @string7 to i8*
%main.bb0.tmp20 = call double@atof(i8* %main.bb0.tmp18)
%main.bb0.tmp21 = call double@atof(i8* %main.bb0.tmp19)
%main.bb0.tmp17 = mul double %main.bb0.tmp20, %main.bb0.tmp21
%main.bb0.tmp22 = bitcast [5 x i8]* @print6 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp22, double %main.bb0.tmp17)
%main.bb0.tmp24 = bitcast [6 x i8]* @string8 to i8*
%main.bb0.tmp25 = bitcast [6 x i8]* @string9 to i8*
%main.bb0.tmp26 = call i8*@stringcat(i8* %main.bb0.tmp24, i8* %main.bb0.tmp25)
%main.bb0.tmp27 = bitcast [5 x i8]* @print7 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp27, i8* %main.bb0.tmp26)
%main.bb0.tmp29 = add double 0.000000e+00, 4.000000
%main.bb0.tmp30 = add double 0.000000e+00, 5.000000
%main.bb0.tmp31 = bitcast [5 x i8]* @print8 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp31, double %main.bb0.tmp30)
%main.bb0.tmp33 = add double 0.000000e+00, 4.000000
%main.bb0.tmp34 = add double 0.000000e+00, 5.000000
%main.bb0.tmp35 = bitcast [5 x i8]* @print9 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp35, double %main.bb0.tmp33)
%main.bb0.tmp37 = add i1 0, 0
%main.bb0.tmp36 = sub i1 1, %main.bb0.tmp37
%main.bb0.tmp38 = call i8*@btoa(i1 %main.bb0.tmp36)
%main.bb0.tmp39 = bitcast [5 x i8]* @print10 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp39, i8* %main.bb0.tmp38)
%main.bb0.tmp41 = add i1 0, 0
%main.bb0.tmp40 = sub i1 1, %main.bb0.tmp41
%main.bb0.tmp42 = call i8*@btoa(i1 %main.bb0.tmp40)
%main.bb0.tmp43 = bitcast [5 x i8]* @print11 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp43, i8* %main.bb0.tmp42)
%main.bb0.tmp45 = add double 0.000000e+00, 0.000000
%main.bb0.tmp44 = add i1 0, 0
%main.bb0.tmp46 = call i8*@btoa(i1 %main.bb0.tmp44)
%main.bb0.tmp47 = bitcast [5 x i8]* @print12 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp47, i8* %main.bb0.tmp46)
%main.bb0.tmp50 = add i1 0, 0
%main.bb0.tmp49 = sub i1 1, %main.bb0.tmp50
%main.bb0.tmp48 = sub i1 1, %main.bb0.tmp49
%main.bb0.tmp51 = call i8*@btoa(i1 %main.bb0.tmp48)
%main.bb0.tmp52 = bitcast [5 x i8]* @print13 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp52, i8* %main.bb0.tmp51)
%main.bb0.tmp54 = bitcast [6 x i8]* @string10 to i8*
%main.bb0.tmp55 = call i32@strlen(i8* %main.bb0.tmp54)
%main.bb0.tmp56 = sitofp i32 %main.bb0.tmp55 to double
%main.bb0.tmp57 = bitcast [5 x i8]* @print14 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp57, double %main.bb0.tmp56)
%main.bb0.tmp58 = add double 0.000000e+00, 10.000000
%main.bb0.tmp59 = bitcast [5 x i8]* @print15 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb0.tmp59, double %main.bb0.tmp58)
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
