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
@unconditionalBranch.retval = common global {double} zeroinitializer
@string0 = constant [5 x i8] c"What\00"
@print0 = constant [5 x i8] c"%s\09\0A\00"
define void @unconditionalBranch(double %x) alwaysinline {
entry:
%unconditionalBranch.x = alloca double
store double %x, double* %unconditionalBranch.x
%retval0 = alloca double
br label %unconditionalBranch.bb2
unconditionalBranch.bb1:
br label %unconditionalBranch.bb2
unconditionalBranch.bb2:
%unconditionalBranch.bb2.tmp1 = load double* %unconditionalBranch.x
%unconditionalBranch.bb2.tmp2 = add double 0.000000e+00, 1.000000
%unconditionalBranch.bb2.tmp0 = fcmp ugt double %unconditionalBranch.bb2.tmp1, %unconditionalBranch.bb2.tmp2
br i1 %unconditionalBranch.bb2.tmp0, label %unconditionalBranch.bb3, label %unconditionalBranch.bb4
unconditionalBranch.bb3:
%unconditionalBranch.bb3.tmp4 = load double* %unconditionalBranch.x
%unconditionalBranch.bb3.tmp5 = add double 0.000000e+00, 1.000000
%unconditionalBranch.bb3.tmp3 = fcmp ugt double %unconditionalBranch.bb3.tmp4, %unconditionalBranch.bb3.tmp5
br i1 %unconditionalBranch.bb3.tmp3, label %unconditionalBranch.bb6, label %unconditionalBranch.bb2
unconditionalBranch.bb6:
%unconditionalBranch.bb6.tmp6 = bitcast [5 x i8]* @string0 to i8*
%unconditionalBranch.bb6.tmp7 = bitcast [5 x i8]* @print0 to i8*
call i32 (i8*, ...)* @printf(i8* %unconditionalBranch.bb6.tmp7, i8* %unconditionalBranch.bb6.tmp6)
br label %unconditionalBranch.bb2
unconditionalBranch.bb7:
br label %unconditionalBranch.bb5
unconditionalBranch.bb5:
br label %unconditionalBranch.bb2
unconditionalBranch.bb4:
%unconditionalBranch.bb4.tmp8 = load double* %unconditionalBranch.x
store double %unconditionalBranch.bb4.tmp8, double* %retval0
br label %return
return:
%unconditionalBranch.return.tmp9 = load double* %retval0
%unconditionalBranch.return.tmp10 = getelementptr {double}* @unconditionalBranch.retval, i32 0, i32 0
store double %unconditionalBranch.return.tmp9, double* %unconditionalBranch.return.tmp10
ret void
}
define i32 @main() alwaysinline {
entry:
br label %main.bb0
main.bb0:
%main.bb0.tmp11 = add double 0.000000e+00, 10.000000
call void@unconditionalBranch(double %main.bb0.tmp11)
%main.bb0.tmp12 = load {double}* @unconditionalBranch.retval
%main.bb0.tmp13 = extractvalue {double} %main.bb0.tmp12, 0
ret i32 0
}
