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
@global.b = common global double 0.000000e+00
@global.c = common global double 0.000000e+00
@global.x = common global double 0.000000e+00
@global.y = common global double 0.000000e+00
@global.z = common global double 0.000000e+00
@string17 = constant [19 x i8] c"Integer Operations\00"
@print16 = constant [5 x i8] c"%s\09\0A\00"
@print17 = constant [5 x i8] c"%f\09\0A\00"
@print18 = constant [5 x i8] c"%f\09\0A\00"
@print19 = constant [5 x i8] c"%f\09\0A\00"
@print20 = constant [5 x i8] c"%f\09\0A\00"
@print21 = constant [5 x i8] c"%f\09\0A\00"
@print22 = constant [5 x i8] c"%f\09\0A\00"
@string18 = constant [26 x i8] c"Floating point Operations\00"
@print23 = constant [5 x i8] c"%s\09\0A\00"
@print24 = constant [5 x i8] c"%f\09\0A\00"
@print25 = constant [5 x i8] c"%f\09\0A\00"
@print26 = constant [5 x i8] c"%f\09\0A\00"
@print27 = constant [5 x i8] c"%f\09\0A\00"
@print28 = constant [5 x i8] c"%f\09\0A\00"
define i32 @main() {
entry:
br label %main.bb20
main.bb20:
%main.bb20.tmp151 = bitcast [19 x i8]* @string17 to i8*
%main.bb20.tmp152 = bitcast [5 x i8]* @print16 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp152, i8* %main.bb20.tmp151)
%main.bb20.tmp153 = add double 0.000000e+00, 5.000000
%main.bb20.tmp154 = load double* @global.b
store double %main.bb20.tmp153, double* @global.b
%main.bb20.tmp155 = add double 0.000000e+00, 10.000000
%main.bb20.tmp156 = load double* @global.c
store double %main.bb20.tmp155, double* @global.c
%main.bb20.tmp158 = load double* @global.b
%main.bb20.tmp159 = load double* @global.c
%main.bb20.tmp157 = mul double %main.bb20.tmp158, %main.bb20.tmp159
%main.bb20.tmp160 = load double* @global.a
store double %main.bb20.tmp157, double* @global.a
%main.bb20.tmp161 = load double* @global.a
%main.bb20.tmp162 = bitcast [5 x i8]* @print17 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp162, double %main.bb20.tmp161)
%main.bb20.tmp164 = load double* @global.a
%main.bb20.tmp165 = add double 0.000000e+00, 10.000000
%main.bb20.tmp163 = mul double %main.bb20.tmp164, %main.bb20.tmp165
%main.bb20.tmp166 = bitcast [5 x i8]* @print18 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp166, double %main.bb20.tmp163)
%main.bb20.tmp168 = load double* @global.a
%main.bb20.tmp169 = add double 0.000000e+00, 10.000000
%main.bb20.tmp167 = add double %main.bb20.tmp168, %main.bb20.tmp169
%main.bb20.tmp170 = bitcast [5 x i8]* @print19 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp170, double %main.bb20.tmp167)
%main.bb20.tmp172 = load double* @global.a
%main.bb20.tmp173 = add double 0.000000e+00, 10.000000
%main.bb20.tmp171 = sub double %main.bb20.tmp172, %main.bb20.tmp173
%main.bb20.tmp174 = bitcast [5 x i8]* @print20 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp174, double %main.bb20.tmp171)
%main.bb20.tmp176 = load double* @global.a
%main.bb20.tmp177 = add double 0.000000e+00, 10.000000
%main.bb20.tmp175 = fdiv double %main.bb20.tmp176, %main.bb20.tmp177
%main.bb20.tmp178 = bitcast [5 x i8]* @print21 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp178, double %main.bb20.tmp175)
%main.bb20.tmp180 = load double* @global.a
%main.bb20.tmp181 = add double 0.000000e+00, 10.000000
%main.bb20.tmp179 = frem double %main.bb20.tmp180, %main.bb20.tmp181
%main.bb20.tmp182 = bitcast [5 x i8]* @print22 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp182, double %main.bb20.tmp179)
%main.bb20.tmp183 = bitcast [26 x i8]* @string18 to i8*
%main.bb20.tmp184 = bitcast [5 x i8]* @print23 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp184, i8* %main.bb20.tmp183)
%main.bb20.tmp185 = add double 0.000000e+00, 10.500000
%main.bb20.tmp186 = load double* @global.x
store double %main.bb20.tmp185, double* @global.x
%main.bb20.tmp187 = add double 0.000000e+00, 20.354560
%main.bb20.tmp188 = load double* @global.y
store double %main.bb20.tmp187, double* @global.y
%main.bb20.tmp190 = load double* @global.x
%main.bb20.tmp191 = load double* @global.y
%main.bb20.tmp189 = mul double %main.bb20.tmp190, %main.bb20.tmp191
%main.bb20.tmp192 = load double* @global.z
store double %main.bb20.tmp189, double* @global.z
%main.bb20.tmp193 = load double* @global.z
%main.bb20.tmp194 = bitcast [5 x i8]* @print24 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp194, double %main.bb20.tmp193)
%main.bb20.tmp196 = load double* @global.z
%main.bb20.tmp197 = add double 0.000000e+00, 10.000000
%main.bb20.tmp195 = mul double %main.bb20.tmp196, %main.bb20.tmp197
%main.bb20.tmp198 = bitcast [5 x i8]* @print25 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp198, double %main.bb20.tmp195)
%main.bb20.tmp200 = load double* @global.z
%main.bb20.tmp201 = add double 0.000000e+00, 10.000000
%main.bb20.tmp199 = add double %main.bb20.tmp200, %main.bb20.tmp201
%main.bb20.tmp202 = bitcast [5 x i8]* @print26 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp202, double %main.bb20.tmp199)
%main.bb20.tmp204 = load double* @global.z
%main.bb20.tmp205 = add double 0.000000e+00, 10.000000
%main.bb20.tmp203 = sub double %main.bb20.tmp204, %main.bb20.tmp205
%main.bb20.tmp206 = bitcast [5 x i8]* @print27 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp206, double %main.bb20.tmp203)
%main.bb20.tmp208 = load double* @global.z
%main.bb20.tmp209 = add double 0.000000e+00, 10.000000
%main.bb20.tmp207 = fdiv double %main.bb20.tmp208, %main.bb20.tmp209
%main.bb20.tmp210 = bitcast [5 x i8]* @print28 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp210, double %main.bb20.tmp207)
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
