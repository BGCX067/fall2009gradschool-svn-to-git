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
@global.y = common global double 0.000000e+00
@global.z = common global double 0.000000e+00
@add.retval = common global {double} zeroinitializer
@addition.retval = common global {double} zeroinitializer
@string19 = constant [11 x i8] c"Answer is:\00"
@print29 = constant [5 x i8] c"%s\09\0A\00"
@print30 = constant [5 x i8] c"%f\09\0A\00"
define void @add(double %a, double %b) {
entry:
%add.a = alloca double
store double %a, double* %add.a
%add.b = alloca double
store double %b, double* %add.b
%retval0 = alloca double
br label %add.bb22
add.bb22:
%add.bb22.tmp214 = load double* %add.a
%add.bb22.tmp215 = load double* %add.b
%add.bb22.tmp213 = add double %add.bb22.tmp214, %add.bb22.tmp215
store double %add.bb22.tmp213, double* %retval0
br label %return
return:
%add.return.tmp216 = load double* %retval0
%add.return.tmp217 = getelementptr {double}* @add.retval, i32 0, i32 0
store double %add.return.tmp216, double* %add.return.tmp217
ret void
}
define void @addition(double %a, double %b, double %c) {
entry:
%addition.a = alloca double
store double %a, double* %addition.a
%addition.b = alloca double
store double %b, double* %addition.b
%addition.c = alloca double
store double %c, double* %addition.c
%retval0 = alloca double
br label %addition.bb23
addition.bb23:
%addition.bb23.tmp219 = load double* %addition.a
%addition.bb23.tmp220 = load double* %addition.b
%addition.bb23.tmp218 = add double %addition.bb23.tmp219, %addition.bb23.tmp220
%addition.bb23.tmp221 = load double* %addition.c
call void@add(double %addition.bb23.tmp218, double %addition.bb23.tmp221)
%addition.bb23.tmp222 = load {double}* @add.retval
%addition.bb23.tmp223 = extractvalue {double} %addition.bb23.tmp222, 0
%addition.bb23.tmp224 = load double* @global.y
store double %addition.bb23.tmp223, double* @global.y
%addition.bb23.tmp225 = load double* @global.y
store double %addition.bb23.tmp225, double* %retval0
br label %return
return:
%addition.return.tmp226 = load double* %retval0
%addition.return.tmp227 = getelementptr {double}* @addition.retval, i32 0, i32 0
store double %addition.return.tmp226, double* %addition.return.tmp227
ret void
}
define void @doAddition() {
entry:
br label %doAddition.bb24
doAddition.bb24:
%doAddition.bb24.tmp228 = add double 0.000000e+00, 1.000000
%doAddition.bb24.tmp229 = load double* @global.a
store double %doAddition.bb24.tmp228, double* @global.a
%doAddition.bb24.tmp230 = add double 0.000000e+00, 2.000000
%doAddition.bb24.tmp231 = load double* @global.b
store double %doAddition.bb24.tmp230, double* @global.b
%doAddition.bb24.tmp232 = add double 0.000000e+00, 3.000000
%doAddition.bb24.tmp233 = load double* @global.c
store double %doAddition.bb24.tmp232, double* @global.c
%doAddition.bb24.tmp234 = load double* @global.a
%doAddition.bb24.tmp235 = load double* @global.b
%doAddition.bb24.tmp236 = load double* @global.c
call void@addition(double %doAddition.bb24.tmp234, double %doAddition.bb24.tmp235, double %doAddition.bb24.tmp236)
%doAddition.bb24.tmp237 = load {double}* @addition.retval
%doAddition.bb24.tmp238 = extractvalue {double} %doAddition.bb24.tmp237, 0
%doAddition.bb24.tmp239 = load double* @global.z
store double %doAddition.bb24.tmp238, double* @global.z
br label %return
return:
ret void
}
define i32 @main() {
entry:
br label %main.bb21
main.bb21:
%main.bb21.tmp211 = add double 0.000000e+00, 0.000000
%main.bb21.tmp212 = load double* @global.z
store double %main.bb21.tmp211, double* @global.z
call void@doAddition()
%main.bb21.tmp241 = bitcast [11 x i8]* @string19 to i8*
%main.bb21.tmp242 = bitcast [5 x i8]* @print29 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb21.tmp242, i8* %main.bb21.tmp241)
%main.bb21.tmp243 = load double* @global.z
%main.bb21.tmp244 = bitcast [5 x i8]* @print30 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb21.tmp244, double %main.bb21.tmp243)
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
