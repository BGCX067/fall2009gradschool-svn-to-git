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
@global.x1 = common global double 0.000000e+00
@global.x2 = common global double 0.000000e+00
@global.y1 = common global i8* null
@global.a = common global double 0.000000e+00
@global.b = common global double 0.000000e+00
@global.c = common global double 0.000000e+00
@global.d = common global double 0.000000e+00
@global.e = common global i8* null
@global.i = common global double 0.000000e+00
@global.x = common global double 0.000000e+00
@global.y = common global i8* null
@global.aa = common global double 0.000000e+00
@global.bb = common global i8* null
@string11 = constant [6 x i8] c"hello\00"
@print16 = constant [8 x i8] c"%f\09%s\09\0A\00"
@string12 = constant [6 x i8] c"there\00"
@print17 = constant [8 x i8] c"%f\09%s\09\0A\00"
@string13 = constant [4 x i8] c"two\00"
@string14 = constant [4 x i8] c"foo\00"
@print18 = constant [17 x i8] c"%f\09%s\09%f\09%f\09%s\09\0A\00"
@print19 = constant [8 x i8] c"%f\09%f\09\0A\00"
@print20 = constant [8 x i8] c"%f\09%f\09\0A\00"
@print21 = constant [8 x i8] c"%f\09%f\09\0A\00"
@print22 = constant [8 x i8] c"%f\09%f\09\0A\00"
@print23 = constant [11 x i8] c"%f\09%f\09%f\09\0A\00"
define i32 @main() {
entry:
br label %main.bb1
main.bb1:
%main.bb1.tmp60 = add double 0.000000e+00, 1.000000
%main.bb1.tmp61 = load double* @global.x
store double %main.bb1.tmp60, double* @global.x
%main.bb1.tmp62 = bitcast [6 x i8]* @string11 to i8*
%main.bb1.tmp63 = load i8** @global.y
store i8* %main.bb1.tmp62, i8** @global.y
%main.bb1.tmp64 = load double* @global.x
%main.bb1.tmp65 = load i8** @global.y
%main.bb1.tmp66 = bitcast [8 x i8]* @print16 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb1.tmp66, double %main.bb1.tmp64, i8* %main.bb1.tmp65)
%main.bb1.tmp67 = add double 0.000000e+00, 2.000000
%main.bb1.tmp68 = bitcast [6 x i8]* @string12 to i8*
%main.bb1.tmp69 = load double* @global.x1
%main.bb1.tmp70 = load i8** @global.y1
store double %main.bb1.tmp67, double* @global.x1
store i8* %main.bb1.tmp68, i8** @global.y1
%main.bb1.tmp71 = load double* @global.x1
%main.bb1.tmp72 = load i8** @global.y1
%main.bb1.tmp73 = bitcast [8 x i8]* @print17 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb1.tmp73, double %main.bb1.tmp71, i8* %main.bb1.tmp72)
%main.bb1.tmp74 = add double 0.000000e+00, 1.000000
%main.bb1.tmp75 = bitcast [4 x i8]* @string13 to i8*
%main.bb1.tmp76 = add double 0.000000e+00, 3.000000
%main.bb1.tmp77 = add double 0.000000e+00, 3.141590
%main.bb1.tmp78 = bitcast [4 x i8]* @string14 to i8*
%main.bb1.tmp79 = load double* @global.aa
%main.bb1.tmp80 = load i8** @global.bb
%main.bb1.tmp81 = load double* @global.c
%main.bb1.tmp82 = load double* @global.d
%main.bb1.tmp83 = load i8** @global.e
store double %main.bb1.tmp74, double* @global.aa
store i8* %main.bb1.tmp75, i8** @global.bb
store double %main.bb1.tmp76, double* @global.c
store double %main.bb1.tmp77, double* @global.d
store i8* %main.bb1.tmp78, i8** @global.e
%main.bb1.tmp84 = load double* @global.aa
%main.bb1.tmp85 = load i8** @global.bb
%main.bb1.tmp86 = load double* @global.c
%main.bb1.tmp87 = load double* @global.d
%main.bb1.tmp88 = load i8** @global.e
%main.bb1.tmp89 = bitcast [17 x i8]* @print18 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb1.tmp89, double %main.bb1.tmp84, i8* %main.bb1.tmp85, double %main.bb1.tmp86, double %main.bb1.tmp87, i8* %main.bb1.tmp88)
%main.bb1.tmp90 = add double 0.000000e+00, 7.000000
%main.bb1.tmp91 = load double* @global.i
store double %main.bb1.tmp90, double* @global.i
%main.bb1.tmp93 = load double* @global.i
%main.bb1.tmp94 = add double 0.000000e+00, 1.000000
%main.bb1.tmp92 = add double %main.bb1.tmp93, %main.bb1.tmp94
%main.bb1.tmp95 = load double* @global.i
%main.bb1.tmp96 = load double* @global.i
%main.bb1.tmp97 = load double* @global.x2
store double %main.bb1.tmp92, double* @global.i
store double %main.bb1.tmp95, double* @global.x2
%main.bb1.tmp98 = load double* @global.i
%main.bb1.tmp99 = load double* @global.x2
%main.bb1.tmp100 = bitcast [8 x i8]* @print19 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb1.tmp100, double %main.bb1.tmp98, double %main.bb1.tmp99)
%main.bb1.tmp101 = add double 0.000000e+00, 1.000000
%main.bb1.tmp102 = add double 0.000000e+00, 2.000000
%main.bb1.tmp103 = load double* @global.a
%main.bb1.tmp104 = load double* @global.b
store double %main.bb1.tmp101, double* @global.a
store double %main.bb1.tmp102, double* @global.b
%main.bb1.tmp105 = load double* @global.a
%main.bb1.tmp106 = load double* @global.b
%main.bb1.tmp107 = bitcast [8 x i8]* @print20 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb1.tmp107, double %main.bb1.tmp105, double %main.bb1.tmp106)
%main.bb1.tmp108 = load double* @global.b
%main.bb1.tmp109 = load double* @global.a
%main.bb1.tmp110 = load double* @global.a
%main.bb1.tmp111 = load double* @global.b
store double %main.bb1.tmp108, double* @global.a
store double %main.bb1.tmp109, double* @global.b
%main.bb1.tmp112 = load double* @global.a
%main.bb1.tmp113 = load double* @global.b
%main.bb1.tmp114 = bitcast [8 x i8]* @print21 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb1.tmp114, double %main.bb1.tmp112, double %main.bb1.tmp113)
%main.bb1.tmp115 = load double* @global.b
%main.bb1.tmp116 = load double* @global.a
%main.bb1.tmp117 = load double* @global.a
%main.bb1.tmp118 = load double* @global.b
store double %main.bb1.tmp115, double* @global.a
store double %main.bb1.tmp116, double* @global.b
%main.bb1.tmp119 = load double* @global.a
%main.bb1.tmp120 = load double* @global.b
%main.bb1.tmp121 = bitcast [8 x i8]* @print22 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb1.tmp121, double %main.bb1.tmp119, double %main.bb1.tmp120)
%main.bb1.tmp122 = add double 0.000000e+00, 1.000000
%main.bb1.tmp123 = add double 0.000000e+00, 2.000000
%main.bb1.tmp124 = add double 0.000000e+00, 3.000000
%main.bb1.tmp125 = add double 0.000000e+00, 4.000000
%main.bb1.tmp126 = add double 0.000000e+00, 5.000000
%main.bb1.tmp127 = add double 0.000000e+00, 6.000000
%main.bb1.tmp128 = load double* @global.a
%main.bb1.tmp129 = load double* @global.b
%main.bb1.tmp130 = load double* @global.c
store double %main.bb1.tmp122, double* @global.a
store double %main.bb1.tmp123, double* @global.b
store double %main.bb1.tmp124, double* @global.c
%main.bb1.tmp131 = load double* @global.a
%main.bb1.tmp132 = load double* @global.b
%main.bb1.tmp133 = load double* @global.c
%main.bb1.tmp134 = bitcast [11 x i8]* @print23 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb1.tmp134, double %main.bb1.tmp131, double %main.bb1.tmp132, double %main.bb1.tmp133)
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
