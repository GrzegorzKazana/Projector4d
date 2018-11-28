;Author: Grzegorz Kazana
;Date: 28-11-2018
;Jêzyki Asemblerowe 2018-2019

.model flat, c
includelib   msvcrtd
.data
DOUBLE_SIZE BYTE 8						; holds double size (bytes) constant
ZERO REAL8 0.0							; holds double fp 0.0 constant
ONE REAL8 1.0							; holds double fp 1.0 constant
.code 

extern malloc:proc
extern free:proc

; -------------------------------------------------------------------------------
; name: min
; parameters: 
;	a: DWORD, first number
;	b: DWORD, second number
; returns:
;	DWORD, smaller number from parameters 
; uses registers:
;	EAX
; decription:
;	picks smaller number
; -------------------------------------------------------------------------------
min proc a: DWORD, b: DWORD
	mov eax, a
	sub eax, b
	js isnegative
	mov eax, b
	jmp finished
isnegative:
	mov eax, a
finished:
	ret 8								; function is only called within asm, clear stack manually
min endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: calculateMatrixIndex
; parameters: 
;	col_index: DWORD, matrix column index
;	row_index: DWORD, matrix
;	cols: DWORD, number of columns in matrix
; returns:
;	DWORD, 1d array index, as if it was a matrix
;	uses formula (row_index*cols+col_index)
; uses registers:
;	EAX, EDX
; decription:
;	use this function when matrix is indexed by two indexes, and array is 1d
; -------------------------------------------------------------------------------
calculateMatrixIndex proc col_index: DWORD, row_index: DWORD, cols: DWORD
	mov eax, row_index
	mul cols
	add eax, col_index
	ret 12								; inner function, clear stack
calculateMatrixIndex endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: scaleMatrix
; parameters: 
;	cols: integer, number of cols of matrix
;	rows: integer, number of rows of matrix
;	arr: 32bit, adress to double array
;	scale: double, value scaling the matrix
; returns:
;	none
; uses registers:
;	EAX, EBX, ECX, EDX, XMM0
; decription:
;	scales array of doubles of given size in place
; -------------------------------------------------------------------------------
scaleMatrix proc cols: DWORD, rows: DWORD, arr: DWORD, scale: REAL8
	mov ebx, 0							; initialize row index
rowloop:
	cmp ebx, rows						; if row index == number of rows
	je finished							; loop is ended
	mov ecx, 0							; initialize column index
colloop:
	cmp ecx, cols						; if col index == number of cols
	je rowloopend						; move to next row
	push edx
	push cols
	push ebx
	push ecx
	call calculateMatrixIndex			; calc flattened 1d array index
	pop edx
	mul [DOUBLE_SIZE]					; calc offset in bytes
	add eax, arr						; add pointer to first element to offset
	movsd xmm0, REAL8 PTR [eax]			; load value
	mulsd xmm0, scale					; scale value
	movsd REAL8 PTR [eax], xmm0			; push back to array
	add ecx, 1							; increment idx
	jmp colloop
rowloopend:
	add ebx, 1							; increment idx
	jmp rowloop
finished:
	ret 20								; inner function, clear stack
scaleMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: multiplyMatrix
; parameters: 
;	cols1: DWORD, number of columns in first matrix
;	rows1: DWORD, number of rows in first matrix
;	arr1: DWORD, adress of first array
;	cols2: DWORD, number of columns in second matrix
;	rows2: DWORD, number of columns in second matrix
;	arr2: DWORD, adress of second array
;	outarr: DWORD, adress of output array
; returns:
;	none
; uses registers:
;	EAX, EBX, ECX, EDX, XMM0, XMM1
; decription:
;	multiplies two matrices, assumes given output array is correct size
; -------------------------------------------------------------------------------
multiplyMatrix proc cols1: DWORD, rows1: DWORD, arr1: DWORD, cols2: DWORD, rows2: DWORD, arr2: DWORD, outarr: DWORD
	mov ebx, 0							; initialize row index (iterates over rows of output mat)
rowloop:
	cmp ebx, rows1						; new matrix has same rows as first mat
	je finished							; loop is ended
	mov ecx, 0							; initialize column index (iterates over cols of output mat)
colloop:
	cmp ecx, cols2						; new matrix has same cols as secound mat
	je rowloopend						; move to next row
	mov edx, 0							; init depth index
	xorpd xmm1, xmm1					; zero mm1 register
depthloop:
	cmp edx, cols1						; iterate over cols of first mat and rows of second
	je colloopend
	push edx							; hide edx on stack (mul in called func may overwritte)
	push cols1							; read element from first matrix
	push ebx
	push edx
	call calculateMatrixIndex		
	pop edx								; get edx back
	mul [DOUBLE_SIZE]
	add eax, arr1
	movsd xmm0, REAL8 PTR [eax]			; write it to mm0
	push edx
	push cols2							; read element from second matrix
	push edx
	push ecx
	call calculateMatrixIndex		
	pop edx
	mul [DOUBLE_SIZE]
	add eax, arr2
	mulsd xmm0, REAL8 PTR [eax]			; multiply it to previous value
	addsd xmm1, xmm0					; aggregate in mm1	
	add edx, 1
	jmp depthloop
colloopend:
	push cols2
	push ebx
	push ecx
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, outarr
	movsd REAL8 PTR [eax], xmm1			; write aggregated sum to output matrix
	add ecx, 1							; increment idx
	jmp colloop
rowloopend:
	add ebx, 1							; increment idx
	jmp rowloop
finished:
	ret 28								; clear stack, inner function
multiplyMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: fillZerosMatrix
; parameters: 
;	cols: DWORD, number of columns in matrix
;	rows: DWORD, number of rows in matrix
;	arr: DWORD, address of matrix
; returns:
;	none
; uses registers:
;	EAX, EBX, ECX, XMM0
; decription:
;	fills given matrix with zeros, by scaling it by 0
; -------------------------------------------------------------------------------
fillZerosMatrix proc cols: DWORD, rows: DWORD, arr: DWORD
	push 00000000h
	push arr
	push rows
	push cols
	call scaleMatrix		; scale by 0
	ret 12								; clear stack
fillZerosMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: fillIdentityMatrix
; parameters: 
;	cols: DWORD, number of columns in matrix
;	rows: DWORD, number of rows in matrix
;	arr: DWORD, address of matrix
; returns:
;	none
; uses registers:
;	EAX, EBX, ECX, EDX, XMM0
; decription:
;	fills given matrix with identity matrix
; -------------------------------------------------------------------------------
fillIdentityMatrix proc cols: DWORD, rows: DWORD, arr: DWORD
	push arr
	push rows
	push cols
	call fillZerosMatrix				; fill w/ zeros
	movsd xmm0, [ONE]
	mov ebx, 0
dataloop:
	cmp ebx, cols						; iterate over diagonal, assuming cols==rows
	je finished
	push cols
	push ebx
	push ebx
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr						; get addres
	movsd REAL8 PTR [eax], xmm0			; write one
	add ebx, 1
	jmp dataloop
finished:
	ret 12
fillIdentityMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: fillOrtographicProjectionMatrix
; parameters: 
;	cols: DWORD, number of columns in matrix
;	rows: DWORD, number of rows in matrix
;	arr: DWORD, address of matrix
; returns:
;	none
; uses registers:
;	EAX, EBX, ECX, EDX, XMM0
; decription:
;	fills given matrix with projection matrix
; -------------------------------------------------------------------------------
fillOrtographicProjectionMatrix proc cols: DWORD, rows: DWORD, arr: DWORD
	push arr
	push rows
	push cols
	call fillZerosMatrix				; fill w/ zeros
	movsd xmm0, [ONE]
	push rows
	push cols
	call min
	mov ecx, eax
	mov ebx, 0
dataloop:
	cmp ebx, ecx						; iterate over pseudo-diagonal projected by smaller index
	je finished
	push cols
	push ebx
	push ebx
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr						; get addres
	movsd REAL8 PTR [eax], xmm0			; write one
	add ebx, 1
	jmp dataloop
finished:
	ret 12
fillOrtographicProjectionMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: allocateMatrix
; parameters: 
;	cols: DWORD, number of columns in matrix
;	rows: DWORD, number of rows in matrix
; returns:
;	DWORD, address of matrix
; uses registers:
;	EAX, ECX, EDX, XMM0
; decription:
;	allocate matrix
; -------------------------------------------------------------------------------
allocateMatrix proc cols: DWORD, rows: DWORD
	mov eax, 1
	mul [DOUBLE_SIZE]
	mul cols
	mul rows
	push eax
	call malloc
	ret 8
allocateMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: deallocateMatrix
; parameters: 
;	arr: DWORD, adress to array
; returns:
;	none
; uses registers:
;	EAX, ECX, EDX, XMM0
; decription:
;	free matrix
; -------------------------------------------------------------------------------
deallocateMatrix proc arr: DWORD
	push arr
	call free
	ret 4
deallocateMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: projectOrtographicImplementation
; parameters: 
;	cols: DWORD, number of columns in matrix
;	rows: DWORD, number of rows in matrix
;	arr: DWORD, address to matrix
;	outarr: DWORD, address to output matrix
;	goal_dim: DWORD, output dimention
; returns:
;	none
; uses registers:
;	EAX, EBX, ECX, EDX, XMM0, XMM1
; decription:
;	projects matrix to specified dimension without perspective
; -------------------------------------------------------------------------------
projectOrtographicImplementation proc cols: DWORD, rows: DWORD, arr: DWORD, outarr: DWORD, goal_dim: DWORD
	push goal_dim
	push rows
	call allocateMatrix
	push eax
	push eax
	push goal_dim
	push rows
	call fillOrtographicProjectionMatrix	; generate projection matrix
	pop eax

	push eax
	push outarr
	push arr
	push rows
	push cols
	push eax
	push goal_dim
	push rows
	call multiplyMatrix					; perform projection
	pop eax

	push eax
	call deallocateMatrix
	ret
projectOrtographicImplementation endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: projectPerspectiveImplementation
; parameters: 
;	cols: DWORD, number of columns in matrix
;	rows: DWORD, number of rows in matrix
;	arr: DWORD, address to matrix
;	outarr: DWORD, address to output matrix
;	goal_dim: DWORD, output dimention
;	distance: REAL8, distance from 'camera' to objects
; returns:
;	none
; uses registers:
;	EAX, EBX, ECX, EDX, XMM0, XMM1
; decription:
;	project matrix with perspective
; -------------------------------------------------------------------------------
projectPerspectiveImplementation proc cols: DWORD, rows: DWORD, arr: DWORD, outarr: DWORD, goal_dim: DWORD, distance: REAL8
	push goal_dim
	push rows
	call allocateMatrix
	push eax
	push eax
	push goal_dim
	push rows
	call fillOrtographicProjectionMatrix	; generate default projection matrix

	push 1
	push 0
	push goal_dim
	call calculateMatrixIndex							; get Z coordinate ofarr
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd xmm1, REAL8 PTR [eax]
	subsd xmm1, distance
	movsd xmm0, [ONE]
	divsd xmm0, xmm1									; calculate perspective scaler

	pop eax												; retrive addres of allocated projection mat
	push eax											; hide it again

	sub esp, 8											; equal to
	movsd REAL8 PTR [esp], xmm0							; push xmm0
	push eax
	push goal_dim
	push rows
	call scaleMatrix						; scale by perspective
	
	pop eax
	push eax

	push outarr
	push arr
	push rows
	push cols
	push eax
	push goal_dim
	push rows
	call multiplyMatrix					; perform projection

	pop eax

	push eax
	call deallocateMatrix
	ret
projectPerspectiveImplementation endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: fillRotationMatrix
; parameters: 
;	cols: DWORD, number of columns in matrix
;	rows: DWORD, number of rows in matrix
;	arr: DWORD, address to matrix
;	angle: REAL8, angle of rotation
;	axis1: DWORD, first axis modified by rotation
;	axis2: DWORD, second axis modified by rotation
; returns:
;	none
; uses registers:
;	EAX, EBX, ECX, EDX, XMM0, XMM1, ST7, MM7
; decription:
;	fills rotation matrix
; -------------------------------------------------------------------------------
fillRotationMatrix proc cols: DWORD, rows: DWORD, arr: DWORD, angle: REAL8, axis1: DWORD, axis2: DWORD
	push arr
	push rows
	push cols
	call fillIdentityMatrix			; prepare matrix

	push cols
	push axis1
	push axis1
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	fld angle
	fcos
	fstp REAL8 PTR [eax]							; write cos(angle)
	movsd xmm0, REAL8 PTR [eax]

	push cols
	push axis2
	push axis2
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd REAL8 PTR [eax], xmm0

	push cols
	push axis2
	push axis1
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd xmm0, angle
	movsd REAL8 PTR [eax], xmm0
	fld angle
	fsin
	fstp REAL8 PTR [eax]							; write sin(angle)
	movsd xmm0, REAL8 PTR [eax]

	push cols
	push axis1
	push axis2
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd xmm1, xmm0								; calculate -sin, given sin
	subsd xmm0, xmm1
	subsd xmm0, xmm1
	movsd REAL8 PTR [eax], xmm0						; write -sin(angle)
	ret
fillRotationMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: rotateImplementation
; parameters: 
;	cols: DWORD, number of columns in matrix
;	rows: DWORD, number of rows in matrix
;	arr: DWORD, address to matrix
;	outarr: DWORD, address of output matrix, assuming size is correct - equal to arr size
;	angle: REAL8, angle of rotation
;	axis1: DWORD, first axis modified by rotation
;	axis2: DWORD, second axis modified by rotation
; returns:
;	none
; uses registers:
;	EAX, EBX, ECX, EDX, XMM0, ST7, MM7
; decription:
;	rotates vector by specified angle
; -------------------------------------------------------------------------------
rotateImplementation proc cols: DWORD, rows: DWORD, arr: DWORD, outarr: DWORD, angle: REAL8, axis0: DWORD, axis1: DWORD
	push rows
	push rows
	call allocateMatrix
	push eax											; allocate rotation matrix

	movsd xmm0, angle
	push axis1
	push axis0
	sub esp, 8											; equal to
	movsd REAL8 PTR [esp], xmm0							; push angle
	push eax
	push rows
	push rows
	call fillRotationMatrix				; filling rotation matrix
	add esp, 28
	pop eax
	push eax

	push outarr
	push arr
	push rows
	push cols
	push eax
	push rows
	push rows
	call multiplyMatrix					; performing rotation

	pop eax
	push eax
	call deallocateMatrix
	ret
rotateImplementation endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: fillDoubleRotationMatrix
; parameters: 
;	cols: DWORD, number of columns in matrix
;	rows: DWORD, number of rows in matrix
;	arr: DWORD, address to matrix
;	angle: REAL8, angle of rotation
; returns:
;	none
; uses registers:
;	EAX, EBX, ECX, EDX, XMM0, ST7, MM7
; decription:
;	fills double rotation matrix
; -------------------------------------------------------------------------------
fillDoubleRotationMatrix proc cols: DWORD, rows: DWORD, arr: DWORD, angle: REAL8
	push arr
	push rows
	push cols
	call fillIdentityMatrix			; prepare matrix

	push cols
	push 0
	push 0
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	fld angle
	fcos
	fstp REAL8 PTR [eax]							; write cos(angle)
	movsd xmm0, REAL8 PTR [eax]

	push cols
	push 1
	push 1
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd REAL8 PTR [eax], xmm0

	push cols
	push 2
	push 2
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd REAL8 PTR [eax], xmm0

	push cols
	push 3
	push 3
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd REAL8 PTR [eax], xmm0

	push cols
	push 1
	push 0
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd xmm0, angle
	movsd REAL8 PTR [eax], xmm0
	fld angle
	fsin
	fstp REAL8 PTR [eax]								; write sin(angle)
	movsd xmm0, REAL8 PTR [eax]

	push cols
	push 3
	push 2
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd REAL8 PTR [eax], xmm0

	push cols
	push 0
	push 1
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd xmm1, xmm0								; calculate -sin, given sin
	subsd xmm0, xmm1
	subsd xmm0, xmm1
	movsd REAL8 PTR [eax], xmm0						; write -sin(angle

	push cols
	push 2
	push 3
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd REAL8 PTR [eax], xmm0

	ret
fillDoubleRotationMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; name: rotateWImplementation
; parameters: 
;	cols: DWORD, number of columns in matrix
;	rows: DWORD, number of rows in matrix
;	arr: DWORD, address to matrix
;	outarr: DWORD, address of output matrix
;	angle: REAL8, angle of rotation
; returns:
;	none
; uses registers:
;	EAX, EBX, ECX, EDX, XMM0, ST7, MM7
; decription:
;	double rotation implrmrntation only
; -------------------------------------------------------------------------------
rotateWImplementation proc cols: DWORD, rows: DWORD, arr: DWORD, outarr: DWORD, angle: REAL8
	push rows
	push rows
	call allocateMatrix
	push eax											; allocate rotation matrix

	movsd xmm0, angle
	sub esp, 8											; equal to
	movsd REAL8 PTR [esp], xmm0							; push angle
	push eax
	push rows
	push rows
	call fillDoubleRotationMatrix			; filling rotation matrix
	add esp, 20
	pop eax
	push eax

	push outarr
	push arr
	push rows
	push cols
	push eax
	push rows
	push rows
	call multiplyMatrix					; performing rotation

	pop eax
	push eax
	call deallocateMatrix
	ret
rotateWImplementation endp
; -------------------------------------------------------------------------------
end