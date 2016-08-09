@_printa = internal constant [5 x i8] c"%d  \00", align 1
@_printc = internal constant [2 x i8] c"%c", align 1
@_printn = internal constant [2 x i8] c"\0A\00", align 1
declare i32 @printf(i8*, ...)

define i32 @main() {
  %a = alloca i32, align 4
  %b = alloca [11 x i8], align 1
  store i32 11, i32* %a
  %1 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  %2 = getelementptr inbounds i8* %1, i64 0
  store i8 104, i8* %2
  %3 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  %4 = getelementptr inbounds i8* %3, i64 1
  store i8 101, i8* %4
  %5 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  %6 = getelementptr inbounds i8* %5, i64 2
  store i8 108, i8* %6
  %7 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  %8 = getelementptr inbounds i8* %7, i64 3
  store i8 108, i8* %8
  %9 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  %10 = getelementptr inbounds i8* %9, i64 4
  store i8 111, i8* %10
  %11 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  %12 = getelementptr inbounds i8* %11, i64 5
  store i8 44, i8* %12
  %13 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  %14 = getelementptr inbounds i8* %13, i64 6
  store i8 119, i8* %14
  %15 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  %16 = getelementptr inbounds i8* %15, i64 7
  store i8 111, i8* %16
  %17 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  %18 = getelementptr inbounds i8* %17, i64 8
  store i8 114, i8* %18
  %19 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  %20 = getelementptr inbounds i8* %19, i64 9
  store i8 108, i8* %20
  %21 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  %22 = getelementptr inbounds i8* %21, i64 10
  store i8 100, i8* %22
  %23 = getelementptr inbounds[11 x i8]* %b, i32 0, i32 0
  call void @printc(i8* %23, i32 11)

  ret i32 0
}


;link
define void @printa(i32* %arr, i32 %n) nounwind {
entry:
  %arr.var = alloca i32*, align 4
  store i32* %arr, i32** %arr.var, align 4
  %n.var = alloca i32, align 4
  store i32 %n, i32* %n.var, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  br label %0

  %1 = load i32* %i, align 4
  %2 = load i32* %n.var, align 4
  %3 = icmp slt i32 %1, %2
  br i1 %3, label %4, label %12

; <label> : %4
  %5 = load i32* %i, align 4
  %6 = load i32** %arr.var, align 4
  %7 = getelementptr inbounds i32* %6, i32 %5
  %8 = load i32* %7, align 4
  call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([5 x i8]* @_printa, i32 0, i32 0), i32 %8)
  %10 = load i32* %i, align 4
  %11 = add nsw i32 %10, 1
  store i32 %11, i32* %i, align 4
  br label %0

; <label> : %12
  call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @_printn, i32 0, i32 0), i32 %8)
  ret void
}

define void @printc(i8* %arr, i32 %n) nounwind {
entry:
  %arr.var = alloca i8*, align 1
  store i8* %arr, i8** %arr.var, align 1
  %n.var = alloca i32, align 4
  store i32 %n, i32* %n.var, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  br label %0

  %1 = load i32* %i, align 4
  %2 = load i32* %n.var, align 4
  %3 = icmp slt i32 %1, %2
  br i1 %3, label %4, label %12

; <label> : %4
  %5 = load i32* %i, align 4
  %6 = load i8** %arr.var, align 1
  %7 = getelementptr inbounds i8* %6, i32 %5
  %8 = load i8* %7
  call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @_printc, i32 0, i32 0), i8 %8)
  %10 = load i32* %i, align 4
  %11 = add nsw i32 %10, 1
  store i32 %11, i32* %i, align 4
  br label %0

; <label> : %12
  call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @_printn, i32 0, i32 0), i8 %8)
  ret void
}

