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
@global.n = common global double 0.000000e+00
@global.delta = common global double 0.000000e+00
@f.retval = common global {double} zeroinitializer
@bisect.retval = common global {double, double} zeroinitializer
@bisect.bb4.c = common global double 0.000000e+00
@string15 = constant [3 x i8] c"c=\00"
@string16 = constant [3 x i8] c"a=\00"
@string17 = constant [3 x i8] c"b=\00"
@string18 = constant [2 x i8] c"\0A\00"
@print24 = constant [26 x i8] c"%f\09%s\09%f\09%s\09%f\09%s\09%f\09%s\09\0A\00"
@bisect.bb5.fc = common global double 0.000000e+00
@solve.bb11.z = common global double 0.000000e+00
@solve.bb11.e = common global double 0.000000e+00
@string19 = constant [6 x i8] c"after\00"
@string20 = constant [15 x i8] c"steps, root is\00"
@string21 = constant [11 x i8] c"with error\00"
@string22 = constant [5 x i8] c", f=\00"
@print25 = constant [26 x i8] c"%s\09%f\09%s\09%f\09%s\09%f\09%s\09%f\09\0A\00"
define void @f(double %x) {
entry:
%f.x = alloca double
store double %x, double* %f.x
%retval0 = alloca double
br label %f.bb3
f.bb3:
%f.bb3.tmp141 = load double* %f.x
%f.bb3.tmp142 = load double* %f.x
%f.bb3.tmp140 = mul double %f.bb3.tmp141, %f.bb3.tmp142
%f.bb3.tmp143 = load double* %f.x
%f.bb3.tmp139 = mul double %f.bb3.tmp140, %f.bb3.tmp143
%f.bb3.tmp144 = load double* %f.x
%f.bb3.tmp138 = sub double %f.bb3.tmp139, %f.bb3.tmp144
%f.bb3.tmp145 = add double 0.000000e+00, 1.000000
%f.bb3.tmp137 = sub double %f.bb3.tmp138, %f.bb3.tmp145
store double %f.bb3.tmp137, double* %retval0
br label %return
return:
%f.return.tmp146 = load double* %retval0
%f.return.tmp147 = getelementptr {double}* @f.retval, i32 0, i32 0
store double %f.return.tmp146, double* %f.return.tmp147
ret void
}
define void @bisect(double %a, double %b, double %fa, double %fb) {
entry:
%bisect.a = alloca double
store double %a, double* %bisect.a
%bisect.b = alloca double
store double %b, double* %bisect.b
%bisect.fa = alloca double
store double %fa, double* %bisect.fa
%bisect.fb = alloca double
store double %fb, double* %bisect.fb
%retval0 = alloca double
%retval1 = alloca double
br label %bisect.bb4
bisect.bb4:
%bisect.bb4.tmp150 = load double* %bisect.a
%bisect.bb4.tmp151 = load double* %bisect.b
%bisect.bb4.tmp149 = add double %bisect.bb4.tmp150, %bisect.bb4.tmp151
%bisect.bb4.tmp152 = add double 0.000000e+00, 2.000000
%bisect.bb4.tmp148 = fdiv double %bisect.bb4.tmp149, %bisect.bb4.tmp152
%bisect.bb4.tmp153 = load double* @bisect.bb4.c
store double %bisect.bb4.tmp148, double* @bisect.bb4.c
%bisect.bb4.tmp154 = load double* @global.n
%bisect.bb4.tmp155 = bitcast [3 x i8]* @string15 to i8*
%bisect.bb4.tmp156 = load double* @bisect.bb4.c
%bisect.bb4.tmp157 = bitcast [3 x i8]* @string16 to i8*
%bisect.bb4.tmp158 = load double* %bisect.a
%bisect.bb4.tmp159 = bitcast [3 x i8]* @string17 to i8*
%bisect.bb4.tmp160 = load double* %bisect.b
%bisect.bb4.tmp161 = bitcast [2 x i8]* @string18 to i8*
%bisect.bb4.tmp162 = bitcast [26 x i8]* @print24 to i8*
call i32 (i8*, ...)* @printf(i8* %bisect.bb4.tmp162, double %bisect.bb4.tmp154, i8* %bisect.bb4.tmp155, double %bisect.bb4.tmp156, i8* %bisect.bb4.tmp157, double %bisect.bb4.tmp158, i8* %bisect.bb4.tmp159, double %bisect.bb4.tmp160, i8* %bisect.bb4.tmp161)
%bisect.bb4.tmp166 = load double* @bisect.bb4.c
%bisect.bb4.tmp167 = load double* %bisect.a
%bisect.bb4.tmp165 = fcmp ueq double %bisect.bb4.tmp166, %bisect.bb4.tmp167
%bisect.bb4.tmp169 = load double* @bisect.bb4.c
%bisect.bb4.tmp170 = load double* %bisect.b
%bisect.bb4.tmp168 = fcmp ueq double %bisect.bb4.tmp169, %bisect.bb4.tmp170
%bisect.bb4.tmp164 = or i1 %bisect.bb4.tmp165, %bisect.bb4.tmp168
%bisect.bb4.tmp174 = load double* %bisect.a
%bisect.bb4.tmp175 = load double* %bisect.b
%bisect.bb4.tmp173 = sub double %bisect.bb4.tmp174, %bisect.bb4.tmp175
%bisect.bb4.tmp177 = load double* @global.delta
%bisect.bb4.tmp176 = sub double 0.000000e+00, %bisect.bb4.tmp177
%bisect.bb4.tmp172 = fcmp ugt double %bisect.bb4.tmp173, %bisect.bb4.tmp176
%bisect.bb4.tmp180 = load double* %bisect.a
%bisect.bb4.tmp181 = load double* %bisect.b
%bisect.bb4.tmp179 = sub double %bisect.bb4.tmp180, %bisect.bb4.tmp181
%bisect.bb4.tmp182 = load double* @global.delta
%bisect.bb4.tmp178 = fcmp ult double %bisect.bb4.tmp179, %bisect.bb4.tmp182
%bisect.bb4.tmp171 = and i1 %bisect.bb4.tmp172, %bisect.bb4.tmp178
%bisect.bb4.tmp163 = or i1 %bisect.bb4.tmp164, %bisect.bb4.tmp171
br i1 %bisect.bb4.tmp163, label %bisect.bb6, label %bisect.bb7
bisect.bb6:
%bisect.bb6.tmp183 = load double* @bisect.bb4.c
%bisect.bb6.tmp185 = load double* %bisect.b
%bisect.bb6.tmp186 = load double* %bisect.a
%bisect.bb6.tmp184 = sub double %bisect.bb6.tmp185, %bisect.bb6.tmp186
store double %bisect.bb6.tmp183, double* %retval0
store double %bisect.bb6.tmp184, double* %retval1
br label %return
br label %bisect.bb5
bisect.bb7:
br label %bisect.bb5
bisect.bb5:
%bisect.bb5.tmp188 = load double* @global.n
%bisect.bb5.tmp189 = add double 0.000000e+00, 1.000000
%bisect.bb5.tmp187 = add double %bisect.bb5.tmp188, %bisect.bb5.tmp189
%bisect.bb5.tmp190 = load double* @global.n
store double %bisect.bb5.tmp187, double* @global.n
%bisect.bb5.tmp191 = load double* @bisect.bb4.c
call void@f(double %bisect.bb5.tmp191)
%bisect.bb5.tmp192 = load {double}* @f.retval
%bisect.bb5.tmp193 = extractvalue {double} %bisect.bb5.tmp192, 0
%bisect.bb5.tmp194 = load double* @bisect.bb5.fc
store double %bisect.bb5.tmp193, double* @bisect.bb5.fc
%bisect.bb5.tmp197 = load double* %bisect.fa
%bisect.bb5.tmp198 = load double* @bisect.bb5.fc
%bisect.bb5.tmp196 = mul double %bisect.bb5.tmp197, %bisect.bb5.tmp198
%bisect.bb5.tmp199 = add double 0.000000e+00, 0.000000
%bisect.bb5.tmp195 = fcmp ult double %bisect.bb5.tmp196, %bisect.bb5.tmp199
br i1 %bisect.bb5.tmp195, label %bisect.bb9, label %bisect.bb10
bisect.bb9:
%bisect.bb9.tmp200 = load double* %bisect.a
%bisect.bb9.tmp201 = load double* @bisect.bb4.c
%bisect.bb9.tmp202 = load double* %bisect.fa
%bisect.bb9.tmp203 = load double* @bisect.bb5.fc
call void@bisect(double %bisect.bb9.tmp200, double %bisect.bb9.tmp201, double %bisect.bb9.tmp202, double %bisect.bb9.tmp203)
%bisect.bb9.tmp204 = load {double, double}* @bisect.retval
%bisect.bb9.tmp205 = extractvalue {double, double} %bisect.bb9.tmp204, 0
%bisect.bb9.tmp206 = extractvalue {double, double} %bisect.bb9.tmp204, 1
store double %bisect.bb9.tmp205, double* %retval0
store double %bisect.bb9.tmp206, double* %retval1
br label %return
br label %bisect.bb8
bisect.bb10:
%bisect.bb10.tmp207 = load double* @bisect.bb4.c
%bisect.bb10.tmp208 = load double* %bisect.b
%bisect.bb10.tmp209 = load double* @bisect.bb5.fc
%bisect.bb10.tmp210 = load double* %bisect.fb
call void@bisect(double %bisect.bb10.tmp207, double %bisect.bb10.tmp208, double %bisect.bb10.tmp209, double %bisect.bb10.tmp210)
%bisect.bb10.tmp211 = load {double, double}* @bisect.retval
%bisect.bb10.tmp212 = extractvalue {double, double} %bisect.bb10.tmp211, 0
%bisect.bb10.tmp213 = extractvalue {double, double} %bisect.bb10.tmp211, 1
store double %bisect.bb10.tmp212, double* %retval0
store double %bisect.bb10.tmp213, double* %retval1
br label %return
br label %bisect.bb8
bisect.bb8:
br label %return
return:
%bisect.return.tmp214 = load double* %retval0
%bisect.return.tmp215 = getelementptr {double, double}* @bisect.retval, i32 0, i32 0
store double %bisect.return.tmp214, double* %bisect.return.tmp215
%bisect.return.tmp216 = load double* %retval1
%bisect.return.tmp217 = getelementptr {double, double}* @bisect.retval, i32 0, i32 1
store double %bisect.return.tmp216, double* %bisect.return.tmp217
ret void
}
define void @solve(double %a, double %b) {
entry:
%solve.a = alloca double
store double %a, double* %solve.a
%solve.b = alloca double
store double %b, double* %solve.b
br label %solve.bb11
solve.bb11:
%solve.bb11.tmp218 = add double 0.000000e+00, 0.000000
%solve.bb11.tmp219 = load double* @global.n
store double %solve.bb11.tmp218, double* @global.n
%solve.bb11.tmp220 = load double* %solve.a
%solve.bb11.tmp221 = load double* %solve.b
%solve.bb11.tmp222 = load double* %solve.a
call void@f(double %solve.bb11.tmp222)
%solve.bb11.tmp223 = load {double}* @f.retval
%solve.bb11.tmp224 = extractvalue {double} %solve.bb11.tmp223, 0
%solve.bb11.tmp225 = load double* %solve.b
call void@f(double %solve.bb11.tmp225)
%solve.bb11.tmp226 = load {double}* @f.retval
%solve.bb11.tmp227 = extractvalue {double} %solve.bb11.tmp226, 0
call void@bisect(double %solve.bb11.tmp220, double %solve.bb11.tmp221, double %solve.bb11.tmp224, double %solve.bb11.tmp227)
%solve.bb11.tmp228 = load {double, double}* @bisect.retval
%solve.bb11.tmp229 = extractvalue {double, double} %solve.bb11.tmp228, 0
%solve.bb11.tmp230 = extractvalue {double, double} %solve.bb11.tmp228, 1
%solve.bb11.tmp231 = load double* @solve.bb11.z
%solve.bb11.tmp232 = load double* @solve.bb11.e
store double %solve.bb11.tmp229, double* @solve.bb11.z
store double %solve.bb11.tmp230, double* @solve.bb11.e
%solve.bb11.tmp233 = bitcast [6 x i8]* @string19 to i8*
%solve.bb11.tmp234 = load double* @global.n
%solve.bb11.tmp235 = bitcast [15 x i8]* @string20 to i8*
%solve.bb11.tmp236 = load double* @solve.bb11.z
%solve.bb11.tmp237 = bitcast [11 x i8]* @string21 to i8*
%solve.bb11.tmp238 = load double* @solve.bb11.e
%solve.bb11.tmp239 = bitcast [5 x i8]* @string22 to i8*
%solve.bb11.tmp240 = load double* @solve.bb11.z
call void@f(double %solve.bb11.tmp240)
%solve.bb11.tmp241 = load {double}* @f.retval
%solve.bb11.tmp242 = extractvalue {double} %solve.bb11.tmp241, 0
%solve.bb11.tmp243 = bitcast [26 x i8]* @print25 to i8*
call i32 (i8*, ...)* @printf(i8* %solve.bb11.tmp243, i8* %solve.bb11.tmp233, double %solve.bb11.tmp234, i8* %solve.bb11.tmp235, double %solve.bb11.tmp236, i8* %solve.bb11.tmp237, double %solve.bb11.tmp238, i8* %solve.bb11.tmp239, double %solve.bb11.tmp242)
br label %return
return:
ret void
}
define i32 @main() {
entry:
br label %main.bb2
main.bb2:
%main.bb2.tmp135 = add double 0.000000e+00, 0.000001
%main.bb2.tmp136 = load double* @global.delta
store double %main.bb2.tmp135, double* @global.delta
%main.bb2.tmp244 = add double 0.000000e+00, 1.000000
%main.bb2.tmp245 = add double 0.000000e+00, 2.000000
call void@solve(double %main.bb2.tmp244, double %main.bb2.tmp245)
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
