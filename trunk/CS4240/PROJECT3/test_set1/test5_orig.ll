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
@print32 = constant [5 x i8] c"%f\09\0A\00"
@concat.retval = common global {i8*} zeroinitializer
@string21 = constant [48 x i8] c"This is the result from string concatenation :\0A\00"
@string22 = constant [4 x i8] c"   \00"
@string23 = constant [6 x i8] c"this \00"
@string24 = constant [4 x i8] c"is \00"
@string25 = constant [11 x i8] c"compilers \00"
@string26 = constant [12 x i8] c"assignment \00"
@print33 = constant [5 x i8] c"%s\09\0A\00"
define void @concat(i8* %a, i8* %b, i8* %c, i8* %d, double %e) {
entry:
%concat.a = alloca i8*
store i8* %a, i8** %concat.a
%concat.b = alloca i8*
store i8* %b, i8** %concat.b
%concat.c = alloca i8*
store i8* %c, i8** %concat.c
%concat.d = alloca i8*
store i8* %d, i8** %concat.d
%concat.e = alloca double
store double %e, double* %concat.e
%retval0 = alloca i8*
br label %concat.bb31
concat.bb31:
%concat.bb31.tmp275 = bitcast [48 x i8]* @string21 to i8*
%concat.bb31.tmp277 = load i8** %concat.a
%concat.bb31.tmp279 = load i8** %concat.b
%concat.bb31.tmp281 = load i8** %concat.c
%concat.bb31.tmp283 = load i8** %concat.d
%concat.bb31.tmp285 = load double* %concat.e
%concat.bb31.tmp287 = bitcast [4 x i8]* @string22 to i8*
%concat.bb31.tmp289 = add double 0.000000e+00, 1.000000
%concat.bb31.tmp291 = add double 0.000000e+00, 2.000000
%concat.bb31.tmp293 = add double 0.000000e+00, 3.000000
%concat.bb31.tmp294 = add double 0.000000e+00, 0.400000
%concat.bb31.tmp295 = call i8*@ftoa(double %concat.bb31.tmp293)
%concat.bb31.tmp296 = call i8*@ftoa(double %concat.bb31.tmp294)
%concat.bb31.tmp297 = call i8*@stringcat(i8* %concat.bb31.tmp295, i8* %concat.bb31.tmp296)
%concat.bb31.tmp298 = call i8*@ftoa(double %concat.bb31.tmp291)
%concat.bb31.tmp299 = call i8*@stringcat(i8* %concat.bb31.tmp298, i8* %concat.bb31.tmp297)
%concat.bb31.tmp300 = call i8*@ftoa(double %concat.bb31.tmp289)
%concat.bb31.tmp301 = call i8*@stringcat(i8* %concat.bb31.tmp300, i8* %concat.bb31.tmp299)
%concat.bb31.tmp302 = call i8*@stringcat(i8* %concat.bb31.tmp287, i8* %concat.bb31.tmp301)
%concat.bb31.tmp303 = call i8*@ftoa(double %concat.bb31.tmp285)
%concat.bb31.tmp304 = call i8*@stringcat(i8* %concat.bb31.tmp303, i8* %concat.bb31.tmp302)
%concat.bb31.tmp305 = call i8*@stringcat(i8* %concat.bb31.tmp283, i8* %concat.bb31.tmp304)
%concat.bb31.tmp306 = call i8*@stringcat(i8* %concat.bb31.tmp281, i8* %concat.bb31.tmp305)
%concat.bb31.tmp307 = call i8*@stringcat(i8* %concat.bb31.tmp279, i8* %concat.bb31.tmp306)
%concat.bb31.tmp308 = call i8*@stringcat(i8* %concat.bb31.tmp277, i8* %concat.bb31.tmp307)
%concat.bb31.tmp309 = call i8*@stringcat(i8* %concat.bb31.tmp275, i8* %concat.bb31.tmp308)
store i8* %concat.bb31.tmp309, i8** %retval0
br label %return
return:
%concat.return.tmp310 = load i8** %retval0
%concat.return.tmp311 = getelementptr {i8*}* @concat.retval, i32 0, i32 0
store i8* %concat.return.tmp310, i8** %concat.return.tmp311
ret void
}
define i32 @main() {
entry:
br label %main.bb30
main.bb30:
%main.bb30.tmp266 = add double 0.000000e+00, 0.400000
%main.bb30.tmp267 = load double* @global.a
store double %main.bb30.tmp266, double* @global.a
%main.bb30.tmp269 = load double* @global.a
%main.bb30.tmp270 = add double 0.000000e+00, 1.000000
%main.bb30.tmp268 = add double %main.bb30.tmp269, %main.bb30.tmp270
%main.bb30.tmp271 = load double* @global.a
store double %main.bb30.tmp268, double* @global.a
%main.bb30.tmp272 = load double* @global.a
%main.bb30.tmp273 = bitcast [5 x i8]* @print32 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb30.tmp273, double %main.bb30.tmp272)
%main.bb30.tmp312 = bitcast [6 x i8]* @string23 to i8*
%main.bb30.tmp313 = bitcast [4 x i8]* @string24 to i8*
%main.bb30.tmp314 = bitcast [11 x i8]* @string25 to i8*
%main.bb30.tmp315 = bitcast [12 x i8]* @string26 to i8*
%main.bb30.tmp316 = add double 0.000000e+00, 2.000000
call void@concat(i8* %main.bb30.tmp312, i8* %main.bb30.tmp313, i8* %main.bb30.tmp314, i8* %main.bb30.tmp315, double %main.bb30.tmp316)
%main.bb30.tmp317 = load {i8*}* @concat.retval
%main.bb30.tmp318 = extractvalue {i8*} %main.bb30.tmp317, 0
%main.bb30.tmp319 = bitcast [5 x i8]* @print33 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb30.tmp319, i8* %main.bb30.tmp318)
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
