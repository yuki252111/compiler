@_printa = internal constant [5 x i8] c"%d  \00", align 1
@_printc = internal constant [2 x i8] c"%c", align 1
@_printn = internal constant [2 x i8] c"\0A\00", align 1
declare i32 @printf(i8*, ...)

define i32 @deleteD(i32* %A, i32 %size, i32 %ele) {
  %A.var = alloca i32*, align 8
  store i32* %A, i32** %A.var
  %size.var = alloca i32, align 4
  store i32 %size, i32* %size.var
  %ele.var = alloca i32, align 4
  store i32 %ele, i32* %ele.var
  %i = alloca i32, align 4
  %newsize = alloca i32, align 4
  store i32 0, i32* %i
  store i32 0, i32* %newsize
  br label %1

; <label>:1
  %2 = load i32* %i
  %3 = load i32* %size.var
  %4 = icmp slt i32 %2, %3
  br i1 %4, label %5, label %whileend0

; <label>:5
  %6 = load i32* %i
  %7 = load i32** %A.var
  %8 = sext i32 %6 to i64
  %9 = getelementptr inbounds i32* %7 , i64 %8
  %10 = load i32* %9
  %11 = load i32* %ele.var
  %12 = icmp ne i32 %10, %11
  br i1 %12, label %13, label %ifend0

; <label>:13
  %14 = load i32* %newsize
  %15 = add nsw i32 %14, 1
  store i32 %15, i32* %newsize
  br label %ifend0

ifend0:
  %16 = load i32* %i
  %17 = add nsw i32 %16, 1
  store i32 %17, i32* %i
  br label %1

whileend0:
  %18 = load i32* %newsize
  ret i32 %18
}

define i32 @main() {
  %K = alloca [10 x i32], align 4
  %D = alloca [1 x i32], align 4
  %size = alloca i32, align 4
  store i32 0, i32* %size
  %1 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %2 = getelementptr inbounds i32* %1, i64 0
  store i32 1, i32* %2
  %3 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %4 = getelementptr inbounds i32* %3, i64 1
  store i32 1, i32* %4
  %5 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %6 = getelementptr inbounds i32* %5, i64 2
  store i32 2, i32* %6
  %7 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %8 = getelementptr inbounds i32* %7, i64 3
  store i32 3, i32* %8
  %9 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %10 = getelementptr inbounds i32* %9, i64 4
  store i32 3, i32* %10
  %11 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %12 = getelementptr inbounds i32* %11, i64 5
  store i32 3, i32* %12
  %13 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %14 = getelementptr inbounds i32* %13, i64 6
  store i32 9, i32* %14
  %15 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %16 = getelementptr inbounds i32* %15, i64 7
  store i32 10, i32* %16
  %17 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %18 = getelementptr inbounds i32* %17, i64 8
  store i32 10, i32* %18
  %19 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %20 = getelementptr inbounds i32* %19, i64 9
  store i32 11, i32* %20
  %21 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %22 = call i32 @deleteD(i32* %21, i32 10, i32 3)

  store i32 %22, i32* %size
  %23 = load i32* %size
  %24 = getelementptr inbounds[1 x i32]* %D, i32 0, i32 0
  %25 = getelementptr inbounds i32* %24, i64 0
  store i32 %23, i32* %25
  %26 = getelementptr inbounds[1 x i32]* %D, i32 0, i32 0
  call void @printa(i32* %26, i32 1)

  %27 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %28 = call i32 @deleteD(i32* %27, i32 10, i32 13)

  store i32 %28, i32* %size
  %29 = load i32* %size
  %30 = getelementptr inbounds[1 x i32]* %D, i32 0, i32 0
  %31 = getelementptr inbounds i32* %30, i64 0
  store i32 %29, i32* %31
  %32 = getelementptr inbounds[1 x i32]* %D, i32 0, i32 0
  call void @printa(i32* %32, i32 1)

  %33 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %34 = getelementptr inbounds i32* %33, i64 0
  store i32 1, i32* %34
  %35 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %36 = getelementptr inbounds i32* %35, i64 1
  store i32 1, i32* %36
  %37 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %38 = getelementptr inbounds i32* %37, i64 2
  store i32 1, i32* %38
  %39 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %40 = getelementptr inbounds i32* %39, i64 3
  store i32 1, i32* %40
  %41 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %42 = getelementptr inbounds i32* %41, i64 4
  store i32 1, i32* %42
  %43 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %44 = getelementptr inbounds i32* %43, i64 5
  store i32 1, i32* %44
  %45 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %46 = getelementptr inbounds i32* %45, i64 6
  store i32 1, i32* %46
  %47 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %48 = getelementptr inbounds i32* %47, i64 7
  store i32 1, i32* %48
  %49 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %50 = getelementptr inbounds i32* %49, i64 8
  store i32 1, i32* %50
  %51 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %52 = getelementptr inbounds i32* %51, i64 9
  store i32 1, i32* %52
  %53 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %54 = call i32 @deleteD(i32* %53, i32 10, i32 3)

  store i32 %54, i32* %size
  %55 = load i32* %size
  %56 = getelementptr inbounds[1 x i32]* %D, i32 0, i32 0
  %57 = getelementptr inbounds i32* %56, i64 0
  store i32 %55, i32* %57
  %58 = getelementptr inbounds[1 x i32]* %D, i32 0, i32 0
  call void @printa(i32* %58, i32 1)

  %59 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %60 = call i32 @deleteD(i32* %59, i32 10, i32 1)

  store i32 %60, i32* %size
  %61 = load i32* %size
  %62 = getelementptr inbounds[1 x i32]* %D, i32 0, i32 0
  %63 = getelementptr inbounds i32* %62, i64 0
  store i32 %61, i32* %63
  %64 = getelementptr inbounds[1 x i32]* %D, i32 0, i32 0
  call void @printa(i32* %64, i32 1)

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

