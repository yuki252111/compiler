@_printa = internal constant [5 x i8] c"%d  \00", align 1
@_printc = internal constant [2 x i8] c"%c", align 1
@_printn = internal constant [2 x i8] c"\0A\00", align 1
declare i32 @printf(i8*, ...)

define i32 @isLegal(i32* %K, i32 %size, i32 %index, i32 %pos) {
  %K.var = alloca i32*, align 8
  store i32* %K, i32** %K.var
  %size.var = alloca i32, align 4
  store i32 %size, i32* %size.var
  %index.var = alloca i32, align 4
  store i32 %index, i32* %index.var
  %pos.var = alloca i32, align 4
  store i32 %pos, i32* %pos.var
  %i = alloca i32, align 4
  %isLeal = alloca i32, align 4
  store i32 0, i32* %i
  store i32 1, i32* %isLeal
  br label %1

; <label>:1
  %2 = load i32* %i
  %3 = load i32* %index.var
  %4 = icmp slt i32 %2, %3
  br i1 %4, label %5, label %whileend0

; <label>:5
  %6 = load i32* %i
  %7 = load i32** %K.var
  %8 = sext i32 %6 to i64
  %9 = getelementptr inbounds i32* %7 , i64 %8
  %10 = load i32* %9
  %11 = load i32* %pos.var
  %12 = icmp eq i32 %10, %11
  br i1 %12, label %13, label %ifend0

; <label>:13
  store i32 0, i32* %isLeal
  br label %ifend0

ifend0:
  %14 = load i32* %pos.var
  %15 = load i32* %i
  %16 = load i32** %K.var
  %17 = sext i32 %15 to i64
  %18 = getelementptr inbounds i32* %16 , i64 %17
  %19 = load i32* %18
  %20 = sub nsw i32 %14, %19
  %21 = load i32* %index.var
  %22 = load i32* %i
  %23 = sub nsw i32 %21, %22
  %24 = icmp eq i32 %20, %23
  br i1 %24, label %25, label %ifend1

; <label>:25
  store i32 0, i32* %isLeal
  br label %ifend1

ifend1:
  %26 = load i32* %pos.var
  %27 = load i32* %i
  %28 = load i32** %K.var
  %29 = sext i32 %27 to i64
  %30 = getelementptr inbounds i32* %28 , i64 %29
  %31 = load i32* %30
  %32 = sub nsw i32 %26, %31
  %33 = load i32* %i
  %34 = load i32* %index.var
  %35 = sub nsw i32 %33, %34
  %36 = icmp eq i32 %32, %35
  br i1 %36, label %37, label %ifend2

; <label>:37
  store i32 0, i32* %isLeal
  br label %ifend2

ifend2:
  %38 = load i32* %i
  %39 = add nsw i32 %38, 1
  store i32 %39, i32* %i
  br label %1

whileend0:
  %40 = load i32* %isLeal
  ret i32 %40
}

define void @eightQueen(i32* %K, i32 %size, i32 %index) {
  %K.var = alloca i32*, align 8
  store i32* %K, i32** %K.var
  %size.var = alloca i32, align 4
  store i32 %size, i32* %size.var
  %index.var = alloca i32, align 4
  store i32 %index, i32* %index.var
  %i = alloca i32, align 4
  %isLeal = alloca i32, align 4
  %1 = load i32* %index.var
  %2 = load i32* %size.var
  %3 = icmp slt i32 %1, %2
  br i1 %3, label %4, label %else0

; <label>:4
  store i32 0, i32* %i
  store i32 0, i32* %isLeal
  br label %5

; <label>:5
  %6 = load i32* %i
  %7 = load i32* %size.var
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %9, label %whileend1

; <label>:9
  %10 = load i32** %K.var
  %11 = load i32* %size.var
  %12 = load i32* %index.var
  %13 = load i32* %i
  %14 = call i32 @isLegal(i32* %10, i32 %11, i32 %12, i32 %13)

  store i32 %14, i32* %isLeal
  %15 = load i32* %isLeal
  %16 = icmp eq i32 %15, 1
  br i1 %16, label %17, label %ifend4

; <label>:17
  %18 = load i32* %index.var
  %19 = load i32* %i
  %20 = load i32** %K.var
  %21 = sext i32 %18 to i64
  %22 = getelementptr inbounds i32* %20 , i64 %21
  store i32 %19, i32* %22
  %23 = load i32* %index.var
  %24 = add nsw i32 %23, 1
  store i32 %24, i32* %index.var
  %25 = load i32** %K.var
  %26 = load i32* %size.var
  %27 = load i32* %index.var
  call void @eightQueen(i32* %25, i32 %26, i32 %27)

  %28 = load i32* %index.var
  %29 = sub nsw i32 %28, 1
  store i32 %29, i32* %index.var
  br label %ifend4

ifend4:
  %30 = load i32* %i
  %31 = add nsw i32 %30, 1
  store i32 %31, i32* %i
  br label %5

whileend1:
  br label %ifend3

else0:
  %32 = load i32** %K.var
  %33 = load i32* %size.var
  call void @printa(i32* %32, i32 %33)

  br label %ifend3

ifend3:
  ret void
}

define i32 @main() {
  %K = alloca [8 x i32], align 4
  %1 = getelementptr inbounds[8 x i32]* %K, i32 0, i32 0
  %2 = getelementptr inbounds i32* %1, i64 0
  store i32 1, i32* %2
  %3 = getelementptr inbounds[8 x i32]* %K, i32 0, i32 0
  %4 = getelementptr inbounds i32* %3, i64 1
  store i32 1, i32* %4
  %5 = getelementptr inbounds[8 x i32]* %K, i32 0, i32 0
  %6 = getelementptr inbounds i32* %5, i64 2
  store i32 1, i32* %6
  %7 = getelementptr inbounds[8 x i32]* %K, i32 0, i32 0
  %8 = getelementptr inbounds i32* %7, i64 3
  store i32 1, i32* %8
  %9 = getelementptr inbounds[8 x i32]* %K, i32 0, i32 0
  %10 = getelementptr inbounds i32* %9, i64 4
  store i32 1, i32* %10
  %11 = getelementptr inbounds[8 x i32]* %K, i32 0, i32 0
  %12 = getelementptr inbounds i32* %11, i64 5
  store i32 1, i32* %12
  %13 = getelementptr inbounds[8 x i32]* %K, i32 0, i32 0
  %14 = getelementptr inbounds i32* %13, i64 6
  store i32 1, i32* %14
  %15 = getelementptr inbounds[8 x i32]* %K, i32 0, i32 0
  %16 = getelementptr inbounds i32* %15, i64 7
  store i32 1, i32* %16
  %17 = getelementptr inbounds[8 x i32]* %K, i32 0, i32 0
  call void @eightQueen(i32* %17, i32 8, i32 0)

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


