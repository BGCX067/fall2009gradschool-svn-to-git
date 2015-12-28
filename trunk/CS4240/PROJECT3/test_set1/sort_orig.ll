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
@qsort.bb3.m = common global double 0.000000e+00
@qsort.bb3.t = common global i8* null
@qsort.bb3.i = common global double 0.000000e+00
@selectionsort.bb11.i = common global double 0.000000e+00
@selectionsort.bb13.m = common global double 0.000000e+00
@selectionsort.bb13.j = common global double 0.000000e+00
@print0 = constant [5 x i8] c"%s\09\0A\00"
@show.bb21.i = common global double 0.000000e+00
@print1 = constant [5 x i8] c"%s\09\0A\00"
@testsorts.bb25.n = common global double 0.000000e+00
@string0 = constant [9 x i8] c"original\00"
@string1 = constant [16 x i8] c"after quicksort\00"
@string2 = constant [29 x i8] c"after reverse selection sort\00"
@string3 = constant [22 x i8] c"after quicksort again\00"
@string4 = constant [4 x i8] c"Jan\00"
@string5 = constant [4 x i8] c"Feb\00"
@string6 = constant [4 x i8] c"Mar\00"
@string7 = constant [4 x i8] c"Apr\00"
@string8 = constant [4 x i8] c"May\00"
@string9 = constant [4 x i8] c"Jun\00"
@string10 = constant [4 x i8] c"Jul\00"
@string11 = constant [4 x i8] c"Aug\00"
@string12 = constant [4 x i8] c"Sep\00"
@string13 = constant [4 x i8] c"Oct\00"
@string14 = constant [4 x i8] c"Nov\00"
@string15 = constant [4 x i8] c"Dec\00"
@tab0 = common global [12 x i8*] zeroinitializer
define void @qsort([12 x i8*]* %x, double %l, double %u) {
entry:
%qsort.l = alloca double
store double %l, double* %qsort.l
%qsort.u = alloca double
store double %u, double* %qsort.u
br label %qsort.bb1
qsort.bb1:
%qsort.bb1.tmp1 = load double* %qsort.l
%qsort.bb1.tmp2 = load double* %qsort.u
%qsort.bb1.tmp0 = fcmp ult double %qsort.bb1.tmp1, %qsort.bb1.tmp2
br i1 %qsort.bb1.tmp0, label %qsort.bb3, label %qsort.bb4
qsort.bb3:
%qsort.bb3.tmp3 = load double* %qsort.l
%qsort.bb3.tmp4 = load double* @qsort.bb3.m
store double %qsort.bb3.tmp3, double* @qsort.bb3.m
%qsort.bb3.tmp9 = load double* @qsort.bb3.m
%qsort.bb3.tmp7 = sub double %qsort.bb3.tmp9, 1.000000e+00
%qsort.bb3.tmp10 = fptosi double %qsort.bb3.tmp7 to i32
%qsort.bb3.tmp5 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb3.tmp10
%qsort.bb3.tmp6 = load i8** %qsort.bb3.tmp5
%qsort.bb3.tmp15 = load double* %qsort.l
%qsort.bb3.tmp13 = sub double %qsort.bb3.tmp15, 1.000000e+00
%qsort.bb3.tmp16 = fptosi double %qsort.bb3.tmp13 to i32
%qsort.bb3.tmp11 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb3.tmp16
%qsort.bb3.tmp12 = load i8** %qsort.bb3.tmp11
%qsort.bb3.tmp21 = load double* %qsort.l
%qsort.bb3.tmp19 = sub double %qsort.bb3.tmp21, 1.000000e+00
%qsort.bb3.tmp22 = fptosi double %qsort.bb3.tmp19 to i32
%qsort.bb3.tmp17 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb3.tmp22
%qsort.bb3.tmp18 = load i8** %qsort.bb3.tmp17
%qsort.bb3.tmp27 = load double* @qsort.bb3.m
%qsort.bb3.tmp25 = sub double %qsort.bb3.tmp27, 1.000000e+00
%qsort.bb3.tmp28 = fptosi double %qsort.bb3.tmp25 to i32
%qsort.bb3.tmp23 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb3.tmp28
%qsort.bb3.tmp24 = load i8** %qsort.bb3.tmp23
store i8* %qsort.bb3.tmp6, i8** %qsort.bb3.tmp17
store i8* %qsort.bb3.tmp12, i8** %qsort.bb3.tmp23
%qsort.bb3.tmp33 = load double* %qsort.l
%qsort.bb3.tmp31 = sub double %qsort.bb3.tmp33, 1.000000e+00
%qsort.bb3.tmp34 = fptosi double %qsort.bb3.tmp31 to i32
%qsort.bb3.tmp29 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb3.tmp34
%qsort.bb3.tmp30 = load i8** %qsort.bb3.tmp29
%qsort.bb3.tmp35 = load i8** @qsort.bb3.t
store i8* %qsort.bb3.tmp30, i8** @qsort.bb3.t
%qsort.bb3.tmp36 = load double* %qsort.l
%qsort.bb3.tmp37 = load double* @qsort.bb3.m
store double %qsort.bb3.tmp36, double* @qsort.bb3.m
%qsort.bb3.tmp39 = load double* %qsort.l
%qsort.bb3.tmp40 = add double 0.000000e+00, 1.000000
%qsort.bb3.tmp38 = add double %qsort.bb3.tmp39, %qsort.bb3.tmp40
%qsort.bb3.tmp41 = load double* @qsort.bb3.i
store double %qsort.bb3.tmp38, double* @qsort.bb3.i
br label %qsort.bb5
qsort.bb5:
%qsort.bb5.tmp43 = load double* @qsort.bb3.i
%qsort.bb5.tmp44 = load double* %qsort.u
%qsort.bb5.tmp42 = fcmp ule double %qsort.bb5.tmp43, %qsort.bb5.tmp44
br i1 %qsort.bb5.tmp42, label %qsort.bb6, label %qsort.bb7
qsort.bb6:
%qsort.bb6.tmp50 = load double* @qsort.bb3.i
%qsort.bb6.tmp48 = sub double %qsort.bb6.tmp50, 1.000000e+00
%qsort.bb6.tmp51 = fptosi double %qsort.bb6.tmp48 to i32
%qsort.bb6.tmp46 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb6.tmp51
%qsort.bb6.tmp47 = load i8** %qsort.bb6.tmp46
%qsort.bb6.tmp52 = load i8** @qsort.bb3.t
%qsort.bb6.tmp45 = call i1@stringcmp(i8* %qsort.bb6.tmp47, i8* %qsort.bb6.tmp52, i32 0)
br i1 %qsort.bb6.tmp45, label %qsort.bb9, label %qsort.bb10
qsort.bb9:
%qsort.bb9.tmp54 = load double* @qsort.bb3.m
%qsort.bb9.tmp55 = add double 0.000000e+00, 1.000000
%qsort.bb9.tmp53 = add double %qsort.bb9.tmp54, %qsort.bb9.tmp55
%qsort.bb9.tmp56 = load double* @qsort.bb3.m
store double %qsort.bb9.tmp53, double* @qsort.bb3.m
%qsort.bb9.tmp61 = load double* @qsort.bb3.i
%qsort.bb9.tmp59 = sub double %qsort.bb9.tmp61, 1.000000e+00
%qsort.bb9.tmp62 = fptosi double %qsort.bb9.tmp59 to i32
%qsort.bb9.tmp57 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb9.tmp62
%qsort.bb9.tmp58 = load i8** %qsort.bb9.tmp57
%qsort.bb9.tmp67 = load double* @qsort.bb3.m
%qsort.bb9.tmp65 = sub double %qsort.bb9.tmp67, 1.000000e+00
%qsort.bb9.tmp68 = fptosi double %qsort.bb9.tmp65 to i32
%qsort.bb9.tmp63 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb9.tmp68
%qsort.bb9.tmp64 = load i8** %qsort.bb9.tmp63
%qsort.bb9.tmp73 = load double* @qsort.bb3.m
%qsort.bb9.tmp71 = sub double %qsort.bb9.tmp73, 1.000000e+00
%qsort.bb9.tmp74 = fptosi double %qsort.bb9.tmp71 to i32
%qsort.bb9.tmp69 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb9.tmp74
%qsort.bb9.tmp70 = load i8** %qsort.bb9.tmp69
%qsort.bb9.tmp79 = load double* @qsort.bb3.i
%qsort.bb9.tmp77 = sub double %qsort.bb9.tmp79, 1.000000e+00
%qsort.bb9.tmp80 = fptosi double %qsort.bb9.tmp77 to i32
%qsort.bb9.tmp75 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb9.tmp80
%qsort.bb9.tmp76 = load i8** %qsort.bb9.tmp75
store i8* %qsort.bb9.tmp58, i8** %qsort.bb9.tmp69
store i8* %qsort.bb9.tmp64, i8** %qsort.bb9.tmp75
br label %qsort.bb8
qsort.bb10:
br label %qsort.bb8
qsort.bb8:
%qsort.bb8.tmp82 = load double* @qsort.bb3.i
%qsort.bb8.tmp83 = add double 0.000000e+00, 1.000000
%qsort.bb8.tmp81 = add double %qsort.bb8.tmp82, %qsort.bb8.tmp83
%qsort.bb8.tmp84 = load double* @qsort.bb3.i
store double %qsort.bb8.tmp81, double* @qsort.bb3.i
br label %qsort.bb5
qsort.bb7:
%qsort.bb7.tmp89 = load double* @qsort.bb3.m
%qsort.bb7.tmp87 = sub double %qsort.bb7.tmp89, 1.000000e+00
%qsort.bb7.tmp90 = fptosi double %qsort.bb7.tmp87 to i32
%qsort.bb7.tmp85 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb7.tmp90
%qsort.bb7.tmp86 = load i8** %qsort.bb7.tmp85
%qsort.bb7.tmp95 = load double* %qsort.l
%qsort.bb7.tmp93 = sub double %qsort.bb7.tmp95, 1.000000e+00
%qsort.bb7.tmp96 = fptosi double %qsort.bb7.tmp93 to i32
%qsort.bb7.tmp91 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb7.tmp96
%qsort.bb7.tmp92 = load i8** %qsort.bb7.tmp91
%qsort.bb7.tmp101 = load double* %qsort.l
%qsort.bb7.tmp99 = sub double %qsort.bb7.tmp101, 1.000000e+00
%qsort.bb7.tmp102 = fptosi double %qsort.bb7.tmp99 to i32
%qsort.bb7.tmp97 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb7.tmp102
%qsort.bb7.tmp98 = load i8** %qsort.bb7.tmp97
%qsort.bb7.tmp107 = load double* @qsort.bb3.m
%qsort.bb7.tmp105 = sub double %qsort.bb7.tmp107, 1.000000e+00
%qsort.bb7.tmp108 = fptosi double %qsort.bb7.tmp105 to i32
%qsort.bb7.tmp103 = getelementptr [12 x i8*]* %x, i32 0, i32 %qsort.bb7.tmp108
%qsort.bb7.tmp104 = load i8** %qsort.bb7.tmp103
store i8* %qsort.bb7.tmp86, i8** %qsort.bb7.tmp97
store i8* %qsort.bb7.tmp92, i8** %qsort.bb7.tmp103
%qsort.bb7.tmp110 = load double* %qsort.l
%qsort.bb7.tmp112 = load double* @qsort.bb3.m
%qsort.bb7.tmp113 = add double 0.000000e+00, 1.000000
%qsort.bb7.tmp111 = sub double %qsort.bb7.tmp112, %qsort.bb7.tmp113
call void@qsort([12 x i8*]* %x, double %qsort.bb7.tmp110, double %qsort.bb7.tmp111)
%qsort.bb7.tmp117 = load double* @qsort.bb3.m
%qsort.bb7.tmp118 = add double 0.000000e+00, 1.000000
%qsort.bb7.tmp116 = add double %qsort.bb7.tmp117, %qsort.bb7.tmp118
%qsort.bb7.tmp119 = load double* %qsort.u
call void@qsort([12 x i8*]* %x, double %qsort.bb7.tmp116, double %qsort.bb7.tmp119)
br label %qsort.bb2
qsort.bb4:
br label %qsort.bb2
qsort.bb2:
br label %return
return:
ret void
}
define void @selectionsort([12 x i8*]* %x, double %n) {
entry:
%selectionsort.n = alloca double
store double %n, double* %selectionsort.n
br label %selectionsort.bb11
selectionsort.bb11:
%selectionsort.bb11.tmp121 = add double 0.000000e+00, 1.000000
%selectionsort.bb11.tmp122 = load double* @selectionsort.bb11.i
store double %selectionsort.bb11.tmp121, double* @selectionsort.bb11.i
br label %selectionsort.bb12
selectionsort.bb12:
%selectionsort.bb12.tmp124 = load double* @selectionsort.bb11.i
%selectionsort.bb12.tmp125 = load double* %selectionsort.n
%selectionsort.bb12.tmp123 = fcmp ule double %selectionsort.bb12.tmp124, %selectionsort.bb12.tmp125
br i1 %selectionsort.bb12.tmp123, label %selectionsort.bb13, label %selectionsort.bb14
selectionsort.bb13:
%selectionsort.bb13.tmp126 = load double* @selectionsort.bb11.i
%selectionsort.bb13.tmp128 = load double* @selectionsort.bb11.i
%selectionsort.bb13.tmp129 = add double 0.000000e+00, 1.000000
%selectionsort.bb13.tmp127 = add double %selectionsort.bb13.tmp128, %selectionsort.bb13.tmp129
%selectionsort.bb13.tmp130 = load double* @selectionsort.bb13.m
%selectionsort.bb13.tmp131 = load double* @selectionsort.bb13.j
store double %selectionsort.bb13.tmp126, double* @selectionsort.bb13.m
store double %selectionsort.bb13.tmp127, double* @selectionsort.bb13.j
br label %selectionsort.bb15
selectionsort.bb15:
%selectionsort.bb15.tmp133 = load double* @selectionsort.bb13.j
%selectionsort.bb15.tmp134 = load double* %selectionsort.n
%selectionsort.bb15.tmp132 = fcmp ule double %selectionsort.bb15.tmp133, %selectionsort.bb15.tmp134
br i1 %selectionsort.bb15.tmp132, label %selectionsort.bb16, label %selectionsort.bb17
selectionsort.bb16:
%selectionsort.bb16.tmp140 = load double* @selectionsort.bb13.j
%selectionsort.bb16.tmp138 = sub double %selectionsort.bb16.tmp140, 1.000000e+00
%selectionsort.bb16.tmp141 = fptosi double %selectionsort.bb16.tmp138 to i32
%selectionsort.bb16.tmp136 = getelementptr [12 x i8*]* %x, i32 0, i32 %selectionsort.bb16.tmp141
%selectionsort.bb16.tmp137 = load i8** %selectionsort.bb16.tmp136
%selectionsort.bb16.tmp146 = load double* @selectionsort.bb13.m
%selectionsort.bb16.tmp144 = sub double %selectionsort.bb16.tmp146, 1.000000e+00
%selectionsort.bb16.tmp147 = fptosi double %selectionsort.bb16.tmp144 to i32
%selectionsort.bb16.tmp142 = getelementptr [12 x i8*]* %x, i32 0, i32 %selectionsort.bb16.tmp147
%selectionsort.bb16.tmp143 = load i8** %selectionsort.bb16.tmp142
%selectionsort.bb16.tmp135 = call i1@stringcmp(i8* %selectionsort.bb16.tmp137, i8* %selectionsort.bb16.tmp143, i32 1)
br i1 %selectionsort.bb16.tmp135, label %selectionsort.bb19, label %selectionsort.bb20
selectionsort.bb19:
%selectionsort.bb19.tmp148 = load double* @selectionsort.bb13.j
%selectionsort.bb19.tmp149 = load double* @selectionsort.bb13.m
store double %selectionsort.bb19.tmp148, double* @selectionsort.bb13.m
br label %selectionsort.bb18
selectionsort.bb20:
br label %selectionsort.bb18
selectionsort.bb18:
%selectionsort.bb18.tmp151 = load double* @selectionsort.bb13.j
%selectionsort.bb18.tmp152 = add double 0.000000e+00, 1.000000
%selectionsort.bb18.tmp150 = add double %selectionsort.bb18.tmp151, %selectionsort.bb18.tmp152
%selectionsort.bb18.tmp153 = load double* @selectionsort.bb13.j
store double %selectionsort.bb18.tmp150, double* @selectionsort.bb13.j
br label %selectionsort.bb15
selectionsort.bb17:
%selectionsort.bb17.tmp158 = load double* @selectionsort.bb13.m
%selectionsort.bb17.tmp156 = sub double %selectionsort.bb17.tmp158, 1.000000e+00
%selectionsort.bb17.tmp159 = fptosi double %selectionsort.bb17.tmp156 to i32
%selectionsort.bb17.tmp154 = getelementptr [12 x i8*]* %x, i32 0, i32 %selectionsort.bb17.tmp159
%selectionsort.bb17.tmp155 = load i8** %selectionsort.bb17.tmp154
%selectionsort.bb17.tmp164 = load double* @selectionsort.bb11.i
%selectionsort.bb17.tmp162 = sub double %selectionsort.bb17.tmp164, 1.000000e+00
%selectionsort.bb17.tmp165 = fptosi double %selectionsort.bb17.tmp162 to i32
%selectionsort.bb17.tmp160 = getelementptr [12 x i8*]* %x, i32 0, i32 %selectionsort.bb17.tmp165
%selectionsort.bb17.tmp161 = load i8** %selectionsort.bb17.tmp160
%selectionsort.bb17.tmp170 = load double* @selectionsort.bb11.i
%selectionsort.bb17.tmp168 = sub double %selectionsort.bb17.tmp170, 1.000000e+00
%selectionsort.bb17.tmp171 = fptosi double %selectionsort.bb17.tmp168 to i32
%selectionsort.bb17.tmp166 = getelementptr [12 x i8*]* %x, i32 0, i32 %selectionsort.bb17.tmp171
%selectionsort.bb17.tmp167 = load i8** %selectionsort.bb17.tmp166
%selectionsort.bb17.tmp176 = load double* @selectionsort.bb13.m
%selectionsort.bb17.tmp174 = sub double %selectionsort.bb17.tmp176, 1.000000e+00
%selectionsort.bb17.tmp177 = fptosi double %selectionsort.bb17.tmp174 to i32
%selectionsort.bb17.tmp172 = getelementptr [12 x i8*]* %x, i32 0, i32 %selectionsort.bb17.tmp177
%selectionsort.bb17.tmp173 = load i8** %selectionsort.bb17.tmp172
store i8* %selectionsort.bb17.tmp155, i8** %selectionsort.bb17.tmp166
store i8* %selectionsort.bb17.tmp161, i8** %selectionsort.bb17.tmp172
%selectionsort.bb17.tmp179 = load double* @selectionsort.bb11.i
%selectionsort.bb17.tmp180 = add double 0.000000e+00, 1.000000
%selectionsort.bb17.tmp178 = add double %selectionsort.bb17.tmp179, %selectionsort.bb17.tmp180
%selectionsort.bb17.tmp181 = load double* @selectionsort.bb11.i
store double %selectionsort.bb17.tmp178, double* @selectionsort.bb11.i
br label %selectionsort.bb12
selectionsort.bb14:
br label %return
return:
ret void
}
define void @show(i8* %m, [12 x i8*]* %x) {
entry:
%show.m = alloca i8*
store i8* %m, i8** %show.m
br label %show.bb21
show.bb21:
%show.bb21.tmp182 = load i8** %show.m
%show.bb21.tmp183 = bitcast [5 x i8]* @print0 to i8*
call i32 (i8*, ...)* @printf(i8* %show.bb21.tmp183, i8* %show.bb21.tmp182)
%show.bb21.tmp184 = add double 0.000000e+00, 1.000000
store double %show.bb21.tmp184, double* @show.bb21.i
%show.bb21.tmp185 = add double 0.000000e+00, 12.000000
%show.bb21.tmp186 = add double 0.000000e+00, 1.000000e+00
br label %show.bb22
show.bb22:
%show.bb22.tmp187 = load double* @show.bb21.i
%show.bb22.tmp188 = fcmp ule double %show.bb22.tmp187, %show.bb21.tmp185
br i1 %show.bb22.tmp188, label %show.bb23, label %show.bb24
show.bb23:
%show.bb23.tmp195 = load double* @show.bb21.i
%show.bb23.tmp193 = sub double %show.bb23.tmp195, 1.000000e+00
%show.bb23.tmp196 = fptosi double %show.bb23.tmp193 to i32
%show.bb23.tmp191 = getelementptr [12 x i8*]* %x, i32 0, i32 %show.bb23.tmp196
%show.bb23.tmp192 = load i8** %show.bb23.tmp191
%show.bb23.tmp197 = bitcast [5 x i8]* @print1 to i8*
call i32 (i8*, ...)* @printf(i8* %show.bb23.tmp197, i8* %show.bb23.tmp192)
%show.bb23.tmp189 = load double* @show.bb21.i
%show.bb23.tmp190 = add double %show.bb23.tmp189, %show.bb21.tmp186
store double %show.bb23.tmp190, double* @show.bb21.i
br label %show.bb22
show.bb24:
br label %return
return:
ret void
}
define void @testsorts([12 x i8*]* %x) {
entry:
br label %testsorts.bb25
testsorts.bb25:
%testsorts.bb25.tmp198 = add double 0.000000e+00, 12.000000
%testsorts.bb25.tmp199 = load double* @testsorts.bb25.n
store double %testsorts.bb25.tmp198, double* @testsorts.bb25.n
%testsorts.bb25.tmp200 = bitcast [9 x i8]* @string0 to i8*
call void@show(i8* %testsorts.bb25.tmp200, [12 x i8*]* %x)
%testsorts.bb25.tmp204 = add double 0.000000e+00, 1.000000
%testsorts.bb25.tmp205 = load double* @testsorts.bb25.n
call void@qsort([12 x i8*]* %x, double %testsorts.bb25.tmp204, double %testsorts.bb25.tmp205)
%testsorts.bb25.tmp207 = bitcast [16 x i8]* @string1 to i8*
call void@show(i8* %testsorts.bb25.tmp207, [12 x i8*]* %x)
%testsorts.bb25.tmp211 = load double* @testsorts.bb25.n
call void@selectionsort([12 x i8*]* %x, double %testsorts.bb25.tmp211)
%testsorts.bb25.tmp213 = bitcast [29 x i8]* @string2 to i8*
call void@show(i8* %testsorts.bb25.tmp213, [12 x i8*]* %x)
%testsorts.bb25.tmp217 = add double 0.000000e+00, 1.000000
%testsorts.bb25.tmp218 = load double* @testsorts.bb25.n
call void@qsort([12 x i8*]* %x, double %testsorts.bb25.tmp217, double %testsorts.bb25.tmp218)
%testsorts.bb25.tmp220 = bitcast [22 x i8]* @string3 to i8*
call void@show(i8* %testsorts.bb25.tmp220, [12 x i8*]* %x)
br label %return
return:
ret void
}
define i32 @main() {
entry:
br label %main.bb0
main.bb0:
%main.bb0.tmp223 = bitcast [4 x i8]* @string4 to i8*
%main.bb0.tmp224 = bitcast [4 x i8]* @string5 to i8*
%main.bb0.tmp225 = bitcast [4 x i8]* @string6 to i8*
%main.bb0.tmp226 = bitcast [4 x i8]* @string7 to i8*
%main.bb0.tmp227 = bitcast [4 x i8]* @string8 to i8*
%main.bb0.tmp228 = bitcast [4 x i8]* @string9 to i8*
%main.bb0.tmp229 = bitcast [4 x i8]* @string10 to i8*
%main.bb0.tmp230 = bitcast [4 x i8]* @string11 to i8*
%main.bb0.tmp231 = bitcast [4 x i8]* @string12 to i8*
%main.bb0.tmp232 = bitcast [4 x i8]* @string13 to i8*
%main.bb0.tmp233 = bitcast [4 x i8]* @string14 to i8*
%main.bb0.tmp234 = bitcast [4 x i8]* @string15 to i8*
%main.bb0.tmp235 = getelementptr [12 x i8*]* @tab0, i32 0, i32 0
store i8* %main.bb0.tmp223, i8** %main.bb0.tmp235
%main.bb0.tmp236 = getelementptr [12 x i8*]* @tab0, i32 0, i32 1
store i8* %main.bb0.tmp224, i8** %main.bb0.tmp236
%main.bb0.tmp237 = getelementptr [12 x i8*]* @tab0, i32 0, i32 2
store i8* %main.bb0.tmp225, i8** %main.bb0.tmp237
%main.bb0.tmp238 = getelementptr [12 x i8*]* @tab0, i32 0, i32 3
store i8* %main.bb0.tmp226, i8** %main.bb0.tmp238
%main.bb0.tmp239 = getelementptr [12 x i8*]* @tab0, i32 0, i32 4
store i8* %main.bb0.tmp227, i8** %main.bb0.tmp239
%main.bb0.tmp240 = getelementptr [12 x i8*]* @tab0, i32 0, i32 5
store i8* %main.bb0.tmp228, i8** %main.bb0.tmp240
%main.bb0.tmp241 = getelementptr [12 x i8*]* @tab0, i32 0, i32 6
store i8* %main.bb0.tmp229, i8** %main.bb0.tmp241
%main.bb0.tmp242 = getelementptr [12 x i8*]* @tab0, i32 0, i32 7
store i8* %main.bb0.tmp230, i8** %main.bb0.tmp242
%main.bb0.tmp243 = getelementptr [12 x i8*]* @tab0, i32 0, i32 8
store i8* %main.bb0.tmp231, i8** %main.bb0.tmp243
%main.bb0.tmp244 = getelementptr [12 x i8*]* @tab0, i32 0, i32 9
store i8* %main.bb0.tmp232, i8** %main.bb0.tmp244
%main.bb0.tmp245 = getelementptr [12 x i8*]* @tab0, i32 0, i32 10
store i8* %main.bb0.tmp233, i8** %main.bb0.tmp245
%main.bb0.tmp246 = getelementptr [12 x i8*]* @tab0, i32 0, i32 11
store i8* %main.bb0.tmp234, i8** %main.bb0.tmp246
call void@testsorts([12 x i8*]* @tab0)
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
