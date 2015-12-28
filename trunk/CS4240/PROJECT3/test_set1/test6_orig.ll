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
@global.a = common global i8* null
@global.b = common global i8* null
@global.x = common global i8* null
@string27 = constant [14 x i8] c"local scope 1\00"
@string28 = constant [13 x i8] c"global scope\00"
@string29 = constant [16 x i8] c"Value of X is: \00"
@print34 = constant [5 x i8] c"%s\09\0A\00"
@string30 = constant [15 x i8] c"local sccope 2\00"
@string31 = constant [16 x i8] c"Value of X is: \00"
@print35 = constant [5 x i8] c"%s\09\0A\00"
@string32 = constant [16 x i8] c"Value of X is: \00"
@print36 = constant [5 x i8] c"%s\09\0A\00"
define void @first() {
entry:
br label %first.bb33
first.bb33:
%first.bb33.tmp322 = bitcast [14 x i8]* @string27 to i8*
%first.bb33.tmp323 = load i8** @global.a
store i8* %first.bb33.tmp322, i8** @global.a
%first.bb33.tmp324 = bitcast [13 x i8]* @string28 to i8*
%first.bb33.tmp325 = load i8** @global.x
store i8* %first.bb33.tmp324, i8** @global.x
%first.bb33.tmp326 = load i8** @global.x
%first.bb33.tmp327 = load i8** @global.a
%first.bb33.tmp328 = load i8** @global.a
%first.bb33.tmp329 = load i8** @global.x
store i8* %first.bb33.tmp326, i8** @global.a
store i8* %first.bb33.tmp327, i8** @global.x
br label %return
return:
ret void
}
define void @second() {
entry:
br label %second.bb34
second.bb34:
%second.bb34.tmp336 = load i8** @global.x
%second.bb34.tmp337 = load i8** @global.a
%second.bb34.tmp338 = load i8** @global.a
%second.bb34.tmp339 = load i8** @global.x
store i8* %second.bb34.tmp336, i8** @global.a
store i8* %second.bb34.tmp337, i8** @global.x
%second.bb34.tmp340 = bitcast [15 x i8]* @string30 to i8*
%second.bb34.tmp341 = load i8** @global.b
store i8* %second.bb34.tmp340, i8** @global.b
br label %return
return:
ret void
}
define i32 @main() {
entry:
br label %main.bb32
main.bb32:
%main.bb32.tmp320 = add double 0.000000e+00, 1.000000
%main.bb32.tmp321 = load double* @global.x
store double %main.bb32.tmp320, double* @global.x
call void@first()
%main.bb32.tmp332 = bitcast [16 x i8]* @string29 to i8*
%main.bb32.tmp333 = load i8** @global.x
%main.bb32.tmp334 = call i8*@stringcat(i8* %main.bb32.tmp332, i8* %main.bb32.tmp333)
%main.bb32.tmp335 = bitcast [5 x i8]* @print34 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb32.tmp335, i8* %main.bb32.tmp334)
call void@second()
%main.bb32.tmp344 = bitcast [16 x i8]* @string31 to i8*
%main.bb32.tmp345 = load i8** @global.x
%main.bb32.tmp346 = call i8*@stringcat(i8* %main.bb32.tmp344, i8* %main.bb32.tmp345)
%main.bb32.tmp347 = bitcast [5 x i8]* @print35 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb32.tmp347, i8* %main.bb32.tmp346)
%main.bb32.tmp348 = load i8** @global.b
%main.bb32.tmp349 = load i8** @global.a
%main.bb32.tmp350 = load i8** @global.a
%main.bb32.tmp351 = load i8** @global.b
store i8* %main.bb32.tmp348, i8** @global.a
store i8* %main.bb32.tmp349, i8** @global.b
%main.bb32.tmp352 = load i8** @global.b
%main.bb32.tmp353 = load i8** @global.a
%main.bb32.tmp354 = load i8** @global.x
%main.bb32.tmp355 = load i8** @global.a
%main.bb32.tmp356 = load i8** @global.x
%main.bb32.tmp357 = load i8** @global.b
store i8* %main.bb32.tmp352, i8** @global.a
store i8* %main.bb32.tmp353, i8** @global.x
store i8* %main.bb32.tmp354, i8** @global.b
%main.bb32.tmp359 = bitcast [16 x i8]* @string32 to i8*
%main.bb32.tmp360 = load i8** @global.x
%main.bb32.tmp361 = call i8*@stringcat(i8* %main.bb32.tmp359, i8* %main.bb32.tmp360)
%main.bb32.tmp362 = bitcast [5 x i8]* @print36 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb32.tmp362, i8* %main.bb32.tmp361)
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
