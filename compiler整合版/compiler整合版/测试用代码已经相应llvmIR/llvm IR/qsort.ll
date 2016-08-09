@_printa = internal constant [5 x i8] c"%d  \00", align 1
@_printc = internal constant [2 x i8] c"%c", align 1
@_printn = internal constant [2 x i8] c"\0A\00", align 1
declare i32 @printf(i8*, ...)

define void @_QuickSort(i32* %A, i32 %iLo, i32 %iHi) {
  %A.var = alloca i32*, align 8
  store i32* %A, i32** %A.var
  %iLo.var = alloca i32, align 4
  store i32 %iLo, i32* %iLo.var
  %iHi.var = alloca i32, align 4
  store i32 %iHi, i32* %iHi.var
  %Lo = alloca i32, align 4
  %Hi = alloca i32, align 4
  %Mid = alloca i32, align 4
  %temp = alloca i32, align 4
  %1 = load i32* %iLo.var
  store i32 %1, i32* %Lo
  %2 = load i32* %iHi.var
  store i32 %2, i32* %Hi
  %3 = load i32* %Lo
  %4 = load i32* %Hi
  %5 = add nsw i32 %3, %4
  %6 = sdiv i32 %5, 2
  %7 = load i32** %A.var
  %8 = sext i32 %6 to i64
  %9 = getelementptr inbounds i32* %7 , i64 %8
  %10 = load i32* %9
  store i32 %10, i32* %Mid
  br label %11

; <label>:11
  %12 = load i32* %Lo
  %13 = load i32* %Hi
  %14 = icmp slt i32 %12, %13
  br i1 %14, label %15, label %whileend0

; <label>:15
  br label %16

; <label>:16
  %17 = load i32* %Lo
  %18 = load i32** %A.var
  %19 = sext i32 %17 to i64
  %20 = getelementptr inbounds i32* %18 , i64 %19
  %21 = load i32* %20
  %22 = load i32* %Mid
  %23 = icmp slt i32 %21, %22
  br i1 %23, label %24, label %whileend1

; <label>:24
  %25 = load i32* %Lo
  %26 = add nsw i32 %25, 1
  store i32 %26, i32* %Lo
  br label %16

whileend1:
  br label %27

; <label>:27
  %28 = load i32* %Hi
  %29 = load i32** %A.var
  %30 = sext i32 %28 to i64
  %31 = getelementptr inbounds i32* %29 , i64 %30
  %32 = load i32* %31
  %33 = load i32* %Mid
  %34 = icmp sgt i32 %32, %33
  br i1 %34, label %35, label %whileend2

; <label>:35
  %36 = load i32* %Hi
  %37 = sub nsw i32 %36, 1
  store i32 %37, i32* %Hi
  br label %27

whileend2:
  %38 = load i32* %Lo
  %39 = load i32* %Hi
  %40 = icmp sle i32 %38, %39
  br i1 %40, label %41, label %ifend0

; <label>:41
  %42 = load i32* %Lo
  %43 = load i32** %A.var
  %44 = sext i32 %42 to i64
  %45 = getelementptr inbounds i32* %43 , i64 %44
  %46 = load i32* %45
  store i32 %46, i32* %temp
  %47 = load i32* %Lo
  %48 = load i32* %Hi
  %49 = load i32** %A.var
  %50 = sext i32 %48 to i64
  %51 = getelementptr inbounds i32* %49 , i64 %50
  %52 = load i32* %51
  %53 = load i32** %A.var
  %54 = sext i32 %47 to i64
  %55 = getelementptr inbounds i32* %53 , i64 %54
  store i32 %52, i32* %55
  %56 = load i32* %Hi
  %57 = load i32* %temp
  %58 = load i32** %A.var
  %59 = sext i32 %56 to i64
  %60 = getelementptr inbounds i32* %58 , i64 %59
  store i32 %57, i32* %60
  %61 = load i32* %Lo
  %62 = add nsw i32 %61, 1
  store i32 %62, i32* %Lo
  %63 = load i32* %Hi
  %64 = sub nsw i32 %63, 1
  store i32 %64, i32* %Hi
  br label %ifend0

ifend0:
  br label %11

whileend0:
  %65 = load i32* %Hi
  %66 = load i32* %iLo.var
  %67 = icmp sgt i32 %65, %66
  br i1 %67, label %68, label %ifend1

; <label>:68
  %69 = load i32** %A.var
  %70 = load i32* %iLo.var
  %71 = load i32* %Hi
  call void @_QuickSort(i32* %69, i32 %70, i32 %71)

  br label %ifend1

ifend1:
  %72 = load i32* %Lo
  %73 = load i32* %iHi.var
  %74 = icmp slt i32 %72, %73
  br i1 %74, label %75, label %ifend2

; <label>:75
  %76 = load i32** %A.var
  %77 = load i32* %Lo
  %78 = load i32* %iHi.var
  call void @_QuickSort(i32* %76, i32 %77, i32 %78)

  br label %ifend2

ifend2:
  ret void
}

define void @QuickSort(i32* %A, i32 %size) {
  %A.var = alloca i32*, align 8
  store i32* %A, i32** %A.var
  %size.var = alloca i32, align 4
  store i32 %size, i32* %size.var
  %1 = load i32** %A.var
  %2 = load i32* %size.var
  %3 = sub nsw i32 %2, 1
  call void @_QuickSort(i32* %1, i32 0, i32 %3)

  ret void
}

define i32 @main() {
  %a = alloca i32, align 4
  %K = alloca [10 x i32], align 4
  %b = alloca i32, align 4
  store i32 1, i32* %a
  store i32 10, i32* %b
  %1 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %2 = getelementptr inbounds i32* %1, i64 0
  store i32 4, i32* %2
  %3 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %4 = getelementptr inbounds i32* %3, i64 1
  store i32 2, i32* %4
  %5 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %6 = getelementptr inbounds i32* %5, i64 2
  store i32 4, i32* %6
  %7 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %8 = getelementptr inbounds i32* %7, i64 3
  store i32 6, i32* %8
  %9 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %10 = getelementptr inbounds i32* %9, i64 4
  store i32 1, i32* %10
  %11 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %12 = getelementptr inbounds i32* %11, i64 5
  store i32 3, i32* %12
  %13 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %14 = getelementptr inbounds i32* %13, i64 6
  store i32 9, i32* %14
  %15 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %16 = getelementptr inbounds i32* %15, i64 7
  store i32 1, i32* %16
  %17 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %18 = getelementptr inbounds i32* %17, i64 8
  store i32 10, i32* %18
  %19 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %20 = getelementptr inbounds i32* %19, i64 9
  store i32 11, i32* %20
  %21 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  call void @QuickSort(i32* %21, i32 10)

  %22 = getelementptr inbounds[10 x i32]* %K, i32 0, i32 0
  %23 = load i32* %b
  call void @printa(i32* %22, i32 %23)

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


