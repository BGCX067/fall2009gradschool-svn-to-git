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
@global.a = common global double 0.000000e+00
@global.b = common global double 0.000000e+00
@global.c = common global double 0.000000e+00
@global.i = common global double 0.000000e+00
@pythagorean.retval = common global {double} zeroinitializer
@pythagorean.bb100.c2 = common global double 0.000000e+00
@print84 = constant [5 x i8] c"%f\09\0A\00"
@main.bb99.a2 = common global double 0.000000e+00
@main.bb99.d = common global double 0.000000e+00
@print85 = constant [8 x i8] c"%f\09%f\09\0A\00"
@string55 = constant [9 x i8] c"i is now\00"
@print86 = constant [5 x i8] c"%s\09\0A\00"
@string56 = constant [6 x i8] c"small\00"
@print87 = constant [5 x i8] c"%s\09\0A\00"
@string57 = constant [7 x i8] c"medium\00"
@print88 = constant [5 x i8] c"%s\09\0A\00"
@string58 = constant [4 x i8] c"big\00"
@print89 = constant [5 x i8] c"%s\09\0A\00"
define void @pythagorean(double %a, double %b) {
entry:
%pythagorean.a = alloca double
store double %a, double* %pythagorean.a
%pythagorean.b = alloca double
store double %b, double* %pythagorean.b
%retval0 = alloca double
br label %pythagorean.bb100
pythagorean.bb100:
%pythagorean.bb100.tmp754 = load double* %pythagorean.a
%pythagorean.bb100.tmp755 = add double 0.000000e+00, 2.000000
%pythagorean.bb100.tmp756 = call double@llvm.pow.f64(double %pythagorean.bb100.tmp754, double %pythagorean.bb100.tmp755)
%pythagorean.bb100.tmp758 = load double* %pythagorean.b
%pythagorean.bb100.tmp759 = add double 0.000000e+00, 2.000000
%pythagorean.bb100.tmp760 = call double@llvm.pow.f64(double %pythagorean.bb100.tmp758, double %pythagorean.bb100.tmp759)
%pythagorean.bb100.tmp752 = add double %pythagorean.bb100.tmp756, %pythagorean.bb100.tmp760
%pythagorean.bb100.tmp761 = load double* @pythagorean.bb100.c2
store double %pythagorean.bb100.tmp752, double* @pythagorean.bb100.c2
%pythagorean.bb100.tmp762 = load double* @pythagorean.bb100.c2
store double %pythagorean.bb100.tmp762, double* %retval0
br label %return
return:
%pythagorean.return.tmp763 = load double* %retval0
%pythagorean.return.tmp764 = getelementptr {double}* @pythagorean.retval, i32 0, i32 0
store double %pythagorean.return.tmp763, double* %pythagorean.return.tmp764
ret void
}
define i32 @main() {
entry:
br label %main.bb99
main.bb99:
%main.bb99.tmp765 = add double 0.000000e+00, 3.000000
%main.bb99.tmp766 = add double 0.000000e+00, 4.000000
call void@pythagorean(double %main.bb99.tmp765, double %main.bb99.tmp766)
%main.bb99.tmp767 = load {double}* @pythagorean.retval
%main.bb99.tmp768 = extractvalue {double} %main.bb99.tmp767, 0
%main.bb99.tmp769 = bitcast [5 x i8]* @print84 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb99.tmp769, double %main.bb99.tmp768)
%main.bb99.tmp770 = add double 0.000000e+00, 1.000000
%main.bb99.tmp771 = add double 0.000000e+00, 2.000000
%main.bb99.tmp772 = add double 0.000000e+00, 3.000000
%main.bb99.tmp773 = load double* @global.a
%main.bb99.tmp774 = load double* @global.b
%main.bb99.tmp775 = load double* @global.c
store double %main.bb99.tmp770, double* @global.a
store double %main.bb99.tmp771, double* @global.b
store double %main.bb99.tmp772, double* @global.c
%main.bb99.tmp777 = add double 0.000000e+00, 2.000000
%main.bb99.tmp778 = load double* @global.a
%main.bb99.tmp776 = mul double %main.bb99.tmp777, %main.bb99.tmp778
%main.bb99.tmp779 = load double* @main.bb99.a2
store double %main.bb99.tmp776, double* @main.bb99.a2
%main.bb99.tmp782 = load double* @global.b
%main.bb99.tmp783 = add double 0.000000e+00, 2.000000
%main.bb99.tmp784 = call double@llvm.pow.f64(double %main.bb99.tmp782, double %main.bb99.tmp783)
%main.bb99.tmp787 = add double 0.000000e+00, 4.000000
%main.bb99.tmp788 = load double* @global.a
%main.bb99.tmp786 = mul double %main.bb99.tmp787, %main.bb99.tmp788
%main.bb99.tmp789 = load double* @global.c
%main.bb99.tmp785 = mul double %main.bb99.tmp786, %main.bb99.tmp789
%main.bb99.tmp780 = sub double %main.bb99.tmp784, %main.bb99.tmp785
%main.bb99.tmp790 = load double* @main.bb99.d
store double %main.bb99.tmp780, double* @main.bb99.d
%main.bb99.tmp794 = load double* @global.b
%main.bb99.tmp793 = sub double 0.000000e+00, %main.bb99.tmp794
%main.bb99.tmp795 = load double* @main.bb99.d
%main.bb99.tmp792 = add double %main.bb99.tmp793, %main.bb99.tmp795
%main.bb99.tmp796 = load double* @main.bb99.a2
%main.bb99.tmp791 = fdiv double %main.bb99.tmp792, %main.bb99.tmp796
%main.bb99.tmp797 = load double* @global.x1
store double %main.bb99.tmp791, double* @global.x1
%main.bb99.tmp801 = load double* @global.b
%main.bb99.tmp800 = sub double 0.000000e+00, %main.bb99.tmp801
%main.bb99.tmp802 = load double* @main.bb99.d
%main.bb99.tmp799 = sub double %main.bb99.tmp800, %main.bb99.tmp802
%main.bb99.tmp803 = load double* @main.bb99.a2
%main.bb99.tmp798 = fdiv double %main.bb99.tmp799, %main.bb99.tmp803
%main.bb99.tmp804 = load double* @global.x2
store double %main.bb99.tmp798, double* @global.x2
%main.bb99.tmp805 = load double* @global.x1
%main.bb99.tmp806 = load double* @global.x2
%main.bb99.tmp807 = bitcast [8 x i8]* @print85 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb99.tmp807, double %main.bb99.tmp805, double %main.bb99.tmp806)
%main.bb99.tmp808 = add double 0.000000e+00, 0.000000
%main.bb99.tmp809 = load double* @global.i
store double %main.bb99.tmp808, double* @global.i
br label %main.bb101
main.bb101:
%main.bb101.tmp811 = bitcast [9 x i8]* @string55 to i8*
%main.bb101.tmp812 = load double* @global.i
%main.bb101.tmp813 = call i8*@ftoa(double %main.bb101.tmp812)
%main.bb101.tmp814 = call i8*@stringcat(i8* %main.bb101.tmp811, i8* %main.bb101.tmp813)
%main.bb101.tmp815 = bitcast [5 x i8]* @print86 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb101.tmp815, i8* %main.bb101.tmp814)
%main.bb101.tmp817 = load double* @global.i
%main.bb101.tmp818 = add double 0.000000e+00, 2.000000
%main.bb101.tmp816 = fcmp ult double %main.bb101.tmp817, %main.bb101.tmp818
br i1 %main.bb101.tmp816, label %main.bb105, label %main.bb106
main.bb105:
%main.bb105.tmp819 = bitcast [6 x i8]* @string56 to i8*
%main.bb105.tmp820 = bitcast [5 x i8]* @print87 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb105.tmp820, i8* %main.bb105.tmp819)
br label %main.bb104
main.bb106:
%main.bb106.tmp822 = load double* @global.i
%main.bb106.tmp823 = add double 0.000000e+00, 4.000000
%main.bb106.tmp821 = fcmp ult double %main.bb106.tmp822, %main.bb106.tmp823
br i1 %main.bb106.tmp821, label %main.bb107, label %main.bb108
main.bb107:
%main.bb107.tmp824 = bitcast [7 x i8]* @string57 to i8*
%main.bb107.tmp825 = bitcast [5 x i8]* @print88 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb107.tmp825, i8* %main.bb107.tmp824)
br label %main.bb104
main.bb108:
%main.bb108.tmp826 = bitcast [4 x i8]* @string58 to i8*
%main.bb108.tmp827 = bitcast [5 x i8]* @print89 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb108.tmp827, i8* %main.bb108.tmp826)
br label %main.bb104
main.bb104:
%main.bb104.tmp829 = load double* @global.i
%main.bb104.tmp830 = add double 0.000000e+00, 1.000000
%main.bb104.tmp828 = add double %main.bb104.tmp829, %main.bb104.tmp830
%main.bb104.tmp831 = load double* @global.i
store double %main.bb104.tmp828, double* @global.i
br label %main.bb102
main.bb102:
%main.bb102.tmp833 = load double* @global.i
%main.bb102.tmp834 = add double 0.000000e+00, 5.000000
%main.bb102.tmp832 = fcmp ugt double %main.bb102.tmp833, %main.bb102.tmp834
br i1 %main.bb102.tmp832, label %main.bb103, label %main.bb101
main.bb103:
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
