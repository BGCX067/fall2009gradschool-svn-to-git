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
@global.y = common global double 0.000000e+00
@print0 = constant [5 x i8] c"%f\09\0A\00"
define void @MergeBasicBlocksWithOnlyOneBranch(double %x) alwaysinline {
entry:
%MergeBasicBlocksWithOnlyOneBranch.x = alloca double
store double %x, double* %MergeBasicBlocksWithOnlyOneBranch.x
%MergeBasicBlocksWithOnlyOneBranch.bb1.tmp0 = add double 0.000000e+00, 5.000000
%MergeBasicBlocksWithOnlyOneBranch.bb1.tmp1 = load double* @global.y
store double %MergeBasicBlocksWithOnlyOneBranch.bb1.tmp0, double* @global.y
%MergeBasicBlocksWithOnlyOneBranch.bb1.tmp3 = load double* %MergeBasicBlocksWithOnlyOneBranch.x
%MergeBasicBlocksWithOnlyOneBranch.bb1.tmp4 = load double* @global.y
%MergeBasicBlocksWithOnlyOneBranch.bb1.tmp2 = add double %MergeBasicBlocksWithOnlyOneBranch.bb1.tmp3, %MergeBasicBlocksWithOnlyOneBranch.bb1.tmp4
%MergeBasicBlocksWithOnlyOneBranch.bb1.tmp5 = bitcast [5 x i8]* @print0 to i8*
call i32 (i8*, ...)* @printf(i8* %MergeBasicBlocksWithOnlyOneBranch.bb1.tmp5, double %MergeBasicBlocksWithOnlyOneBranch.bb1.tmp2)
br label %return
return:
ret void
}
define i32 @main() alwaysinline {
entry:
%main.bb0.tmp6 = add double 0.000000e+00, 6.000000
call void@MergeBasicBlocksWithOnlyOneBranch(double %main.bb0.tmp6)
ret i32 0
}
