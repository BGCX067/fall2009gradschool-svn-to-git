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
@global.i = common global double 0.000000e+00
@global.value = common global i8* null
@global.number = common global double 0.000000e+00
@print30 = constant [5 x i8] c"%f\09\0A\00"
@print31 = constant [5 x i8] c"%f\09\0A\00"
@print32 = constant [5 x i8] c"%f\09\0A\00"
@print33 = constant [5 x i8] c"%f\09\0A\00"
@main.bb37.count = common global double 0.000000e+00
@print34 = constant [5 x i8] c"%f\09\0A\00"
@string25 = constant [7 x i8] c"bigger\00"
@print35 = constant [5 x i8] c"%s\09\0A\00"
@string26 = constant [7 x i8] c"bigger\00"
@print36 = constant [5 x i8] c"%s\09\0A\00"
@string27 = constant [8 x i8] c"smaller\00"
@print37 = constant [5 x i8] c"%s\09\0A\00"
@string28 = constant [17 x i8] c"smaller than one\00"
@string29 = constant [4 x i8] c"one\00"
@string30 = constant [4 x i8] c"two\00"
@string31 = constant [6 x i8] c"three\00"
@string32 = constant [18 x i8] c"bigger than three\00"
@print38 = constant [5 x i8] c"%s\09\0A\00"
@main.bb50.i = common global double 0.000000e+00
@print39 = constant [5 x i8] c"%f\09\0A\00"
@main.bb61.i = common global double 0.000000e+00
@print40 = constant [5 x i8] c"%f\09\0A\00"
@main.bb64.i = common global double 0.000000e+00
@print41 = constant [5 x i8] c"%f\09\0A\00"
@main.bb67.i = common global double 0.000000e+00
@print42 = constant [5 x i8] c"%f\09\0A\00"
define i32 @main() {
entry:
br label %main.bb22
main.bb22:
%main.bb22.tmp301 = add double 0.000000e+00, 3.000000
%main.bb22.tmp302 = load double* @global.i
store double %main.bb22.tmp301, double* @global.i
br label %main.bb23
main.bb23:
%main.bb23.tmp304 = load double* @global.i
%main.bb23.tmp305 = add double 0.000000e+00, 0.000000
%main.bb23.tmp303 = fcmp ugt double %main.bb23.tmp304, %main.bb23.tmp305
br i1 %main.bb23.tmp303, label %main.bb24, label %main.bb25
main.bb24:
%main.bb24.tmp306 = load double* @global.i
%main.bb24.tmp307 = bitcast [5 x i8]* @print30 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb24.tmp307, double %main.bb24.tmp306)
%main.bb24.tmp309 = load double* @global.i
%main.bb24.tmp310 = add double 0.000000e+00, 1.000000
%main.bb24.tmp308 = sub double %main.bb24.tmp309, %main.bb24.tmp310
%main.bb24.tmp311 = load double* @global.i
store double %main.bb24.tmp308, double* @global.i
br label %main.bb23
main.bb25:
%main.bb25.tmp312 = add double 0.000000e+00, 0.000000
%main.bb25.tmp313 = add double 0.000000e+00, 1.000000
%main.bb25.tmp314 = load double* @global.a
%main.bb25.tmp315 = load double* @global.b
store double %main.bb25.tmp312, double* @global.a
store double %main.bb25.tmp313, double* @global.b
br label %main.bb26
main.bb26:
%main.bb26.tmp316 = add i1 0, 1
br i1 %main.bb26.tmp316, label %main.bb27, label %main.bb28
main.bb27:
%main.bb27.tmp317 = load double* @global.b
%main.bb27.tmp318 = bitcast [5 x i8]* @print31 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb27.tmp318, double %main.bb27.tmp317)
%main.bb27.tmp319 = load double* @global.b
%main.bb27.tmp321 = load double* @global.a
%main.bb27.tmp322 = load double* @global.b
%main.bb27.tmp320 = add double %main.bb27.tmp321, %main.bb27.tmp322
%main.bb27.tmp323 = load double* @global.a
%main.bb27.tmp324 = load double* @global.b
store double %main.bb27.tmp319, double* @global.a
store double %main.bb27.tmp320, double* @global.b
%main.bb27.tmp326 = load double* @global.a
%main.bb27.tmp327 = add double 0.000000e+00, 500.000000
%main.bb27.tmp325 = fcmp ugt double %main.bb27.tmp326, %main.bb27.tmp327
br i1 %main.bb27.tmp325, label %main.bb30, label %main.bb31
main.bb30:
br label %main.bb28
br label %main.bb29
main.bb31:
br label %main.bb29
main.bb29:
br label %main.bb26
main.bb28:
%main.bb28.tmp328 = add double 0.000000e+00, 3.000000
%main.bb28.tmp329 = load double* @global.i
store double %main.bb28.tmp328, double* @global.i
br label %main.bb32
main.bb32:
%main.bb32.tmp330 = load double* @global.i
%main.bb32.tmp331 = bitcast [5 x i8]* @print32 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb32.tmp331, double %main.bb32.tmp330)
%main.bb32.tmp333 = load double* @global.i
%main.bb32.tmp334 = add double 0.000000e+00, 1.000000
%main.bb32.tmp332 = sub double %main.bb32.tmp333, %main.bb32.tmp334
%main.bb32.tmp335 = load double* @global.i
store double %main.bb32.tmp332, double* @global.i
br label %main.bb33
main.bb33:
%main.bb33.tmp337 = load double* @global.i
%main.bb33.tmp338 = add double 0.000000e+00, 0.000000
%main.bb33.tmp336 = fcmp ueq double %main.bb33.tmp337, %main.bb33.tmp338
br i1 %main.bb33.tmp336, label %main.bb34, label %main.bb32
main.bb34:
%main.bb34.tmp339 = add double 0.000000e+00, 1.000000
%main.bb34.tmp340 = load double* @global.i
store double %main.bb34.tmp339, double* @global.i
br label %main.bb35
main.bb35:
%main.bb35.tmp341 = load double* @global.i
%main.bb35.tmp342 = bitcast [5 x i8]* @print33 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb35.tmp342, double %main.bb35.tmp341)
%main.bb35.tmp344 = load double* @global.i
%main.bb35.tmp345 = add double 0.000000e+00, 1.000000
%main.bb35.tmp343 = add double %main.bb35.tmp344, %main.bb35.tmp345
%main.bb35.tmp346 = load double* @global.i
store double %main.bb35.tmp343, double* @global.i
%main.bb35.tmp348 = load double* @global.i
%main.bb35.tmp349 = add double 0.000000e+00, 3.000000
%main.bb35.tmp347 = fcmp ugt double %main.bb35.tmp348, %main.bb35.tmp349
br i1 %main.bb35.tmp347, label %main.bb39, label %main.bb40
main.bb39:
br label %main.bb37
br label %main.bb38
main.bb40:
br label %main.bb38
main.bb38:
br label %main.bb36
main.bb36:
%main.bb36.tmp350 = add i1 0, 0
br i1 %main.bb36.tmp350, label %main.bb37, label %main.bb35
main.bb37:
%main.bb37.tmp351 = add double 0.000000e+00, 1.000000
store double %main.bb37.tmp351, double* @main.bb37.count
%main.bb37.tmp352 = add double 0.000000e+00, 3.000000
%main.bb37.tmp353 = add double 0.000000e+00, 1.000000e+00
br label %main.bb41
main.bb41:
%main.bb41.tmp354 = load double* @main.bb37.count
%main.bb41.tmp355 = fcmp ule double %main.bb41.tmp354, %main.bb37.tmp352
br i1 %main.bb41.tmp355, label %main.bb42, label %main.bb43
main.bb42:
%main.bb42.tmp358 = load double* @main.bb37.count
%main.bb42.tmp359 = bitcast [5 x i8]* @print34 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb42.tmp359, double %main.bb42.tmp358)
%main.bb42.tmp356 = load double* @main.bb37.count
%main.bb42.tmp357 = add double %main.bb42.tmp356, %main.bb37.tmp353
store double %main.bb42.tmp357, double* @main.bb37.count
br label %main.bb41
main.bb43:
%main.bb43.tmp361 = add double 0.000000e+00, 10.000000
%main.bb43.tmp362 = add double 0.000000e+00, 2.000000
%main.bb43.tmp360 = fcmp ugt double %main.bb43.tmp361, %main.bb43.tmp362
br i1 %main.bb43.tmp360, label %main.bb45, label %main.bb46
main.bb45:
%main.bb45.tmp363 = bitcast [7 x i8]* @string25 to i8*
%main.bb45.tmp364 = bitcast [5 x i8]* @print35 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb45.tmp364, i8* %main.bb45.tmp363)
br label %main.bb44
main.bb46:
br label %main.bb44
main.bb44:
%main.bb44.tmp366 = add double 0.000000e+00, 1.000000
%main.bb44.tmp367 = add double 0.000000e+00, 10.000000
%main.bb44.tmp365 = fcmp ugt double %main.bb44.tmp366, %main.bb44.tmp367
br i1 %main.bb44.tmp365, label %main.bb48, label %main.bb49
main.bb48:
%main.bb48.tmp368 = bitcast [7 x i8]* @string26 to i8*
%main.bb48.tmp369 = bitcast [5 x i8]* @print36 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb48.tmp369, i8* %main.bb48.tmp368)
br label %main.bb47
main.bb49:
%main.bb49.tmp370 = bitcast [8 x i8]* @string27 to i8*
%main.bb49.tmp371 = bitcast [5 x i8]* @print37 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb49.tmp371, i8* %main.bb49.tmp370)
br label %main.bb47
main.bb47:
%main.bb47.tmp372 = add double 0.000000e+00, 3.000000
%main.bb47.tmp373 = load double* @global.number
store double %main.bb47.tmp372, double* @global.number
%main.bb47.tmp375 = load double* @global.number
%main.bb47.tmp376 = add double 0.000000e+00, 1.000000
%main.bb47.tmp374 = fcmp ult double %main.bb47.tmp375, %main.bb47.tmp376
br i1 %main.bb47.tmp374, label %main.bb51, label %main.bb52
main.bb51:
%main.bb51.tmp377 = bitcast [17 x i8]* @string28 to i8*
%main.bb51.tmp378 = load i8** @global.value
store i8* %main.bb51.tmp377, i8** @global.value
br label %main.bb50
main.bb52:
%main.bb52.tmp380 = load double* @global.number
%main.bb52.tmp381 = add double 0.000000e+00, 1.000000
%main.bb52.tmp379 = fcmp ueq double %main.bb52.tmp380, %main.bb52.tmp381
br i1 %main.bb52.tmp379, label %main.bb53, label %main.bb54
main.bb53:
%main.bb53.tmp382 = bitcast [4 x i8]* @string29 to i8*
%main.bb53.tmp383 = load i8** @global.value
store i8* %main.bb53.tmp382, i8** @global.value
br label %main.bb50
main.bb54:
%main.bb54.tmp385 = load double* @global.number
%main.bb54.tmp386 = add double 0.000000e+00, 2.000000
%main.bb54.tmp384 = fcmp ueq double %main.bb54.tmp385, %main.bb54.tmp386
br i1 %main.bb54.tmp384, label %main.bb55, label %main.bb56
main.bb55:
%main.bb55.tmp387 = bitcast [4 x i8]* @string30 to i8*
%main.bb55.tmp388 = load i8** @global.value
store i8* %main.bb55.tmp387, i8** @global.value
br label %main.bb50
main.bb56:
%main.bb56.tmp390 = load double* @global.number
%main.bb56.tmp391 = add double 0.000000e+00, 3.000000
%main.bb56.tmp389 = fcmp ueq double %main.bb56.tmp390, %main.bb56.tmp391
br i1 %main.bb56.tmp389, label %main.bb57, label %main.bb58
main.bb57:
%main.bb57.tmp392 = bitcast [6 x i8]* @string31 to i8*
%main.bb57.tmp393 = load i8** @global.value
store i8* %main.bb57.tmp392, i8** @global.value
br label %main.bb50
main.bb58:
%main.bb58.tmp394 = bitcast [18 x i8]* @string32 to i8*
%main.bb58.tmp395 = load i8** @global.value
store i8* %main.bb58.tmp394, i8** @global.value
br label %main.bb50
main.bb50:
%main.bb50.tmp396 = load i8** @global.value
%main.bb50.tmp397 = bitcast [5 x i8]* @print38 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb50.tmp397, i8* %main.bb50.tmp396)
%main.bb50.tmp398 = add double 0.000000e+00, 1.000000
store double %main.bb50.tmp398, double* @main.bb50.i
%main.bb50.tmp399 = add double 0.000000e+00, 3.000000
%main.bb50.tmp400 = add double 0.000000e+00, 1.000000e+00
br label %main.bb59
main.bb59:
%main.bb59.tmp401 = load double* @main.bb50.i
%main.bb59.tmp402 = fcmp ule double %main.bb59.tmp401, %main.bb50.tmp399
br i1 %main.bb59.tmp402, label %main.bb60, label %main.bb61
main.bb60:
%main.bb60.tmp405 = load double* @main.bb50.i
%main.bb60.tmp406 = bitcast [5 x i8]* @print39 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb60.tmp406, double %main.bb60.tmp405)
%main.bb60.tmp403 = load double* @main.bb50.i
%main.bb60.tmp404 = add double %main.bb60.tmp403, %main.bb50.tmp400
store double %main.bb60.tmp404, double* @main.bb50.i
br label %main.bb59
main.bb61:
%main.bb61.tmp407 = add double 0.000000e+00, 3.000000
store double %main.bb61.tmp407, double* @main.bb61.i
%main.bb61.tmp408 = add double 0.000000e+00, 1.000000
%main.bb61.tmp409 = add double 0.000000e+00, 1.000000e+00
br label %main.bb62
main.bb62:
%main.bb62.tmp410 = load double* @main.bb61.i
%main.bb62.tmp411 = fcmp ule double %main.bb62.tmp410, %main.bb61.tmp408
br i1 %main.bb62.tmp411, label %main.bb63, label %main.bb64
main.bb63:
%main.bb63.tmp414 = load double* @main.bb61.i
%main.bb63.tmp415 = bitcast [5 x i8]* @print40 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb63.tmp415, double %main.bb63.tmp414)
%main.bb63.tmp412 = load double* @main.bb61.i
%main.bb63.tmp413 = add double %main.bb63.tmp412, %main.bb61.tmp409
store double %main.bb63.tmp413, double* @main.bb61.i
br label %main.bb62
main.bb64:
%main.bb64.tmp416 = add double 0.000000e+00, 3.000000
store double %main.bb64.tmp416, double* @main.bb64.i
%main.bb64.tmp417 = add double 0.000000e+00, 1.000000
%main.bb64.tmp419 = add double 0.000000e+00, 1.000000
%main.bb64.tmp418 = sub double 0.000000e+00, %main.bb64.tmp419
br label %main.bb65
main.bb65:
%main.bb65.tmp420 = load double* @main.bb64.i
%main.bb65.tmp422 = fcmp ugt double %main.bb64.tmp418, 0.000000e+00
%main.bb65.tmp423 = fcmp ule double %main.bb65.tmp420, %main.bb64.tmp417
%main.bb65.tmp424 = and i1 %main.bb65.tmp422, %main.bb65.tmp423
%main.bb65.tmp425 = fcmp ule double %main.bb64.tmp418, 0.000000e+00
%main.bb65.tmp426 = fcmp uge double %main.bb65.tmp420, %main.bb64.tmp417
%main.bb65.tmp427 = and i1 %main.bb65.tmp425, %main.bb65.tmp426
%main.bb65.tmp421 = or i1 %main.bb65.tmp424, %main.bb65.tmp427
br i1 %main.bb65.tmp421, label %main.bb66, label %main.bb67
main.bb66:
%main.bb66.tmp430 = load double* @main.bb64.i
%main.bb66.tmp431 = bitcast [5 x i8]* @print41 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb66.tmp431, double %main.bb66.tmp430)
%main.bb66.tmp428 = load double* @main.bb64.i
%main.bb66.tmp429 = add double %main.bb66.tmp428, %main.bb64.tmp418
store double %main.bb66.tmp429, double* @main.bb64.i
br label %main.bb65
main.bb67:
%main.bb67.tmp432 = add double 0.000000e+00, 1.000000
store double %main.bb67.tmp432, double* @main.bb67.i
%main.bb67.tmp433 = add double 0.000000e+00, 0.000000
%main.bb67.tmp435 = add double 0.000000e+00, 0.250000
%main.bb67.tmp434 = sub double 0.000000e+00, %main.bb67.tmp435
br label %main.bb68
main.bb68:
%main.bb68.tmp436 = load double* @main.bb67.i
%main.bb68.tmp438 = fcmp ugt double %main.bb67.tmp434, 0.000000e+00
%main.bb68.tmp439 = fcmp ule double %main.bb68.tmp436, %main.bb67.tmp433
%main.bb68.tmp440 = and i1 %main.bb68.tmp438, %main.bb68.tmp439
%main.bb68.tmp441 = fcmp ule double %main.bb67.tmp434, 0.000000e+00
%main.bb68.tmp442 = fcmp uge double %main.bb68.tmp436, %main.bb67.tmp433
%main.bb68.tmp443 = and i1 %main.bb68.tmp441, %main.bb68.tmp442
%main.bb68.tmp437 = or i1 %main.bb68.tmp440, %main.bb68.tmp443
br i1 %main.bb68.tmp437, label %main.bb69, label %main.bb70
main.bb69:
%main.bb69.tmp446 = load double* @main.bb67.i
%main.bb69.tmp447 = bitcast [5 x i8]* @print42 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb69.tmp447, double %main.bb69.tmp446)
%main.bb69.tmp444 = load double* @main.bb67.i
%main.bb69.tmp445 = add double %main.bb69.tmp444, %main.bb67.tmp434
store double %main.bb69.tmp445, double* @main.bb67.i
br label %main.bb68
main.bb70:
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
