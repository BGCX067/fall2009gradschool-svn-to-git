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
@global.f = common global double 0.000000e+00
@main.bb12.c0 = common global double 0.000000e+00
@string23 = constant [2 x i8] c"C\00"
@print26 = constant [5 x i8] c"%s\09\0A\00"
@main.bb14.c = common global double 0.000000e+00
@print27 = constant [5 x i8] c"%f\09\0A\00"
@string24 = constant [2 x i8] c"F\00"
@print28 = constant [5 x i8] c"%s\09\0A\00"
@main.bb18.c = common global double 0.000000e+00
@print29 = constant [5 x i8] c"%f\09\0A\00"
define i32 @main() {
entry:
br label %main.bb12
main.bb12:
%main.bb12.tmp248 = add double 0.000000e+00, 20.000000
%main.bb12.tmp247 = sub double 0.000000e+00, %main.bb12.tmp248
store double %main.bb12.tmp247, double* @main.bb12.c0
%main.bb12.tmp250 = add double 0.000000e+00, 50.000000
%main.bb12.tmp251 = add double 0.000000e+00, 1.000000
%main.bb12.tmp249 = sub double %main.bb12.tmp250, %main.bb12.tmp251
%main.bb12.tmp252 = add double 0.000000e+00, 10.000000
br label %main.bb13
main.bb13:
%main.bb13.tmp253 = load double* @main.bb12.c0
%main.bb13.tmp255 = fcmp ugt double %main.bb12.tmp252, 0.000000e+00
%main.bb13.tmp256 = fcmp ule double %main.bb13.tmp253, %main.bb12.tmp249
%main.bb13.tmp257 = and i1 %main.bb13.tmp255, %main.bb13.tmp256
%main.bb13.tmp258 = fcmp ule double %main.bb12.tmp252, 0.000000e+00
%main.bb13.tmp259 = fcmp uge double %main.bb13.tmp253, %main.bb12.tmp249
%main.bb13.tmp260 = and i1 %main.bb13.tmp258, %main.bb13.tmp259
%main.bb13.tmp254 = or i1 %main.bb13.tmp257, %main.bb13.tmp260
br i1 %main.bb13.tmp254, label %main.bb14, label %main.bb15
main.bb14:
%main.bb14.tmp263 = bitcast [2 x i8]* @string23 to i8*
%main.bb14.tmp264 = bitcast [5 x i8]* @print26 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb14.tmp264, i8* %main.bb14.tmp263)
%main.bb14.tmp265 = load double* @main.bb12.c0
store double %main.bb14.tmp265, double* @main.bb14.c
%main.bb14.tmp268 = load double* @main.bb12.c0
%main.bb14.tmp269 = add double 0.000000e+00, 10.000000
%main.bb14.tmp267 = add double %main.bb14.tmp268, %main.bb14.tmp269
%main.bb14.tmp270 = add double 0.000000e+00, 1.000000
%main.bb14.tmp266 = sub double %main.bb14.tmp267, %main.bb14.tmp270
%main.bb14.tmp271 = add double 0.000000e+00, 1.000000e+00
br label %main.bb16
main.bb16:
%main.bb16.tmp272 = load double* @main.bb14.c
%main.bb16.tmp273 = fcmp ule double %main.bb16.tmp272, %main.bb14.tmp266
br i1 %main.bb16.tmp273, label %main.bb17, label %main.bb18
main.bb17:
%main.bb17.tmp276 = load double* @main.bb14.c
%main.bb17.tmp277 = bitcast [5 x i8]* @print27 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb17.tmp277, double %main.bb17.tmp276)
%main.bb17.tmp274 = load double* @main.bb14.c
%main.bb17.tmp275 = add double %main.bb17.tmp274, %main.bb14.tmp271
store double %main.bb17.tmp275, double* @main.bb14.c
br label %main.bb16
main.bb18:
%main.bb18.tmp278 = bitcast [2 x i8]* @string24 to i8*
%main.bb18.tmp279 = bitcast [5 x i8]* @print28 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb18.tmp279, i8* %main.bb18.tmp278)
%main.bb18.tmp280 = load double* @main.bb12.c0
store double %main.bb18.tmp280, double* @main.bb18.c
%main.bb18.tmp283 = load double* @main.bb12.c0
%main.bb18.tmp284 = add double 0.000000e+00, 10.000000
%main.bb18.tmp282 = add double %main.bb18.tmp283, %main.bb18.tmp284
%main.bb18.tmp285 = add double 0.000000e+00, 1.000000
%main.bb18.tmp281 = sub double %main.bb18.tmp282, %main.bb18.tmp285
%main.bb18.tmp286 = add double 0.000000e+00, 1.000000e+00
br label %main.bb19
main.bb19:
%main.bb19.tmp287 = load double* @main.bb18.c
%main.bb19.tmp288 = fcmp ule double %main.bb19.tmp287, %main.bb18.tmp281
br i1 %main.bb19.tmp288, label %main.bb20, label %main.bb21
main.bb20:
%main.bb20.tmp294 = add double 0.000000e+00, 9.000000
%main.bb20.tmp295 = add double 0.000000e+00, 5.000000
%main.bb20.tmp293 = fdiv double %main.bb20.tmp294, %main.bb20.tmp295
%main.bb20.tmp296 = load double* @main.bb18.c
%main.bb20.tmp292 = mul double %main.bb20.tmp293, %main.bb20.tmp296
%main.bb20.tmp297 = add double 0.000000e+00, 32.000000
%main.bb20.tmp291 = add double %main.bb20.tmp292, %main.bb20.tmp297
%main.bb20.tmp298 = load double* @global.f
store double %main.bb20.tmp291, double* @global.f
%main.bb20.tmp299 = load double* @global.f
%main.bb20.tmp300 = bitcast [5 x i8]* @print29 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb20.tmp300, double %main.bb20.tmp299)
%main.bb20.tmp289 = load double* @main.bb18.c
%main.bb20.tmp290 = add double %main.bb20.tmp289, %main.bb18.tmp286
store double %main.bb20.tmp290, double* @main.bb18.c
br label %main.bb19
main.bb21:
%main.bb14.tmp261 = load double* @main.bb12.c0
%main.bb14.tmp262 = add double %main.bb14.tmp261, %main.bb12.tmp252
store double %main.bb14.tmp262, double* @main.bb12.c0
br label %main.bb13
main.bb15:
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
