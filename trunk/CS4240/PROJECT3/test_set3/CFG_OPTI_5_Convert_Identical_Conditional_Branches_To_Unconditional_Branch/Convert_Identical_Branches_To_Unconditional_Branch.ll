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
define void @identicalToUnconditional(double %x) alwaysinline {
entry:
%identicalToUnconditional.x = alloca double
store double %x, double* %identicalToUnconditional.x
br label %identicalToUnconditional.bb2
identicalToUnconditional.bb2:
%identicalToUnconditional.bb2.tmp1 = load double* %identicalToUnconditional.x
%identicalToUnconditional.bb2.tmp2 = add double 0.000000e+00, 10.000000
%identicalToUnconditional.bb2.tmp0 = fcmp ugt double %identicalToUnconditional.bb2.tmp1, %identicalToUnconditional.bb2.tmp2
br label %return
identicalToUnconditional.bb4:
br label %return
return:
ret void
}
define i32 @main() alwaysinline {
entry:
br label %main.bb0
main.bb0:
%main.bb0.tmp3 = add double 0.000000e+00, 5.000000
call void@identicalToUnconditional(double %main.bb0.tmp3)
ret i32 0
}
