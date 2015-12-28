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
@global.c = common global i8* null
@global.d = common global i8* null
@global.e = common global double 0.000000e+00
@ccat.retval = common global {i8*, i8*} zeroinitializer
@string4 = constant [7 x i8] c"Cellar\00"
@string5 = constant [5 x i8] c"Door\00"
@string6 = constant [40 x i8] c"***************************************\00"
@print4 = constant [5 x i8] c"%s\09\0A\00"
@string7 = constant [11 x i8] c"These are \00"
@string8 = constant [8 x i8] c"strings\00"
@print5 = constant [5 x i8] c"%s\09\0A\00"
@string9 = constant [6 x i8] c" Door\00"
@print6 = constant [5 x i8] c"%s\09\0A\00"
@string10 = constant [7 x i8] c"Cellar\00"
@string11 = constant [2 x i8] c" \00"
@print7 = constant [5 x i8] c"%s\09\0A\00"
@string12 = constant [40 x i8] c"***************************************\00"
@print8 = constant [5 x i8] c"%s\09\0A\00"
@string13 = constant [20 x i8] c"These are integers\0A\00"
@print9 = constant [8 x i8] c"%s\09%f\09\0A\00"
@print10 = constant [5 x i8] c"%f\09\0A\00"
@string14 = constant [40 x i8] c"***************************************\00"
@print11 = constant [5 x i8] c"%s\09\0A\00"
@string15 = constant [18 x i8] c"These are Boolean\00"
@print12 = constant [5 x i8] c"%s\09\0A\00"
@print13 = constant [5 x i8] c"%s\09\0A\00"
@print14 = constant [5 x i8] c"%s\09\0A\00"
@string16 = constant [40 x i8] c"***************************************\00"
@print15 = constant [5 x i8] c"%s\09\0A\00"
define void @ccat(i8* %a, i8* %b) {
entry:
%ccat.a = alloca i8*
store i8* %a, i8** %ccat.a
%ccat.b = alloca i8*
store i8* %b, i8** %ccat.b
%retval0 = alloca i8*
%retval1 = alloca i8*
br label %ccat.bb19
ccat.bb19:
%ccat.bb19.tmp93 = load i8** %ccat.a
%ccat.bb19.tmp94 = load i8** %ccat.b
store i8* %ccat.bb19.tmp93, i8** %retval0
store i8* %ccat.bb19.tmp94, i8** %retval1
br label %return
return:
%ccat.return.tmp95 = load i8** %retval0
%ccat.return.tmp96 = getelementptr {i8*, i8*}* @ccat.retval, i32 0, i32 0
store i8* %ccat.return.tmp95, i8** %ccat.return.tmp96
%ccat.return.tmp97 = load i8** %retval1
%ccat.return.tmp98 = getelementptr {i8*, i8*}* @ccat.retval, i32 0, i32 1
store i8* %ccat.return.tmp97, i8** %ccat.return.tmp98
ret void
}
define i32 @main() {
entry:
br label %main.bb18
main.bb18:
%main.bb18.tmp99 = bitcast [7 x i8]* @string4 to i8*
%main.bb18.tmp100 = bitcast [5 x i8]* @string5 to i8*
call void@ccat(i8* %main.bb18.tmp99, i8* %main.bb18.tmp100)
%main.bb18.tmp101 = load {i8*, i8*}* @ccat.retval
%main.bb18.tmp102 = extractvalue {i8*, i8*} %main.bb18.tmp101, 0
%main.bb18.tmp103 = extractvalue {i8*, i8*} %main.bb18.tmp101, 1
%main.bb18.tmp104 = load i8** @global.c
%main.bb18.tmp105 = load i8** @global.d
store i8* %main.bb18.tmp102, i8** @global.c
store i8* %main.bb18.tmp103, i8** @global.d
%main.bb18.tmp107 = add double 0.000000e+00, 10.000000
%main.bb18.tmp108 = add double 0.000000e+00, 10.000000
%main.bb18.tmp106 = mul double %main.bb18.tmp107, %main.bb18.tmp108
%main.bb18.tmp109 = load double* @global.e
store double %main.bb18.tmp106, double* @global.e
%main.bb18.tmp110 = bitcast [40 x i8]* @string6 to i8*
%main.bb18.tmp111 = bitcast [5 x i8]* @print4 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp111, i8* %main.bb18.tmp110)
%main.bb18.tmp113 = bitcast [11 x i8]* @string7 to i8*
%main.bb18.tmp114 = bitcast [8 x i8]* @string8 to i8*
%main.bb18.tmp115 = call i8*@stringcat(i8* %main.bb18.tmp113, i8* %main.bb18.tmp114)
%main.bb18.tmp116 = bitcast [5 x i8]* @print5 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp116, i8* %main.bb18.tmp115)
%main.bb18.tmp118 = load i8** @global.c
%main.bb18.tmp119 = bitcast [6 x i8]* @string9 to i8*
%main.bb18.tmp120 = call i8*@stringcat(i8* %main.bb18.tmp118, i8* %main.bb18.tmp119)
%main.bb18.tmp121 = bitcast [5 x i8]* @print6 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp121, i8* %main.bb18.tmp120)
%main.bb18.tmp123 = bitcast [7 x i8]* @string10 to i8*
%main.bb18.tmp125 = bitcast [2 x i8]* @string11 to i8*
%main.bb18.tmp126 = load i8** @global.d
%main.bb18.tmp127 = call i8*@stringcat(i8* %main.bb18.tmp125, i8* %main.bb18.tmp126)
%main.bb18.tmp128 = call i8*@stringcat(i8* %main.bb18.tmp123, i8* %main.bb18.tmp127)
%main.bb18.tmp129 = bitcast [5 x i8]* @print7 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp129, i8* %main.bb18.tmp128)
%main.bb18.tmp130 = bitcast [40 x i8]* @string12 to i8*
%main.bb18.tmp131 = bitcast [5 x i8]* @print8 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp131, i8* %main.bb18.tmp130)
%main.bb18.tmp132 = bitcast [20 x i8]* @string13 to i8*
%main.bb18.tmp133 = load double* @global.e
%main.bb18.tmp134 = bitcast [8 x i8]* @print9 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp134, i8* %main.bb18.tmp132, double %main.bb18.tmp133)
%main.bb18.tmp135 = add double 0.000000e+00, 10.000000
%main.bb18.tmp136 = bitcast [5 x i8]* @print10 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp136, double %main.bb18.tmp135)
%main.bb18.tmp137 = bitcast [40 x i8]* @string14 to i8*
%main.bb18.tmp138 = bitcast [5 x i8]* @print11 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp138, i8* %main.bb18.tmp137)
%main.bb18.tmp139 = bitcast [18 x i8]* @string15 to i8*
%main.bb18.tmp140 = bitcast [5 x i8]* @print12 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp140, i8* %main.bb18.tmp139)
%main.bb18.tmp142 = add i1 0, 1
%main.bb18.tmp141 = sub i1 1, %main.bb18.tmp142
%main.bb18.tmp143 = call i8*@btoa(i1 %main.bb18.tmp141)
%main.bb18.tmp144 = bitcast [5 x i8]* @print13 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp144, i8* %main.bb18.tmp143)
%main.bb18.tmp146 = add i1 0, 0
%main.bb18.tmp145 = sub i1 1, %main.bb18.tmp146
%main.bb18.tmp147 = call i8*@btoa(i1 %main.bb18.tmp145)
%main.bb18.tmp148 = bitcast [5 x i8]* @print14 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp148, i8* %main.bb18.tmp147)
%main.bb18.tmp149 = bitcast [40 x i8]* @string16 to i8*
%main.bb18.tmp150 = bitcast [5 x i8]* @print15 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp150, i8* %main.bb18.tmp149)
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
