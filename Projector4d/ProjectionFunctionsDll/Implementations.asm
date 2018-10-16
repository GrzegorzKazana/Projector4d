PUBLIC Dej5Asm

.model flat, c

includelib   msvcrtd

.data
DOUBLE_SIZE BYTE 8
ZERO REAL8 0.0
ONE REAL8 1.0
.code  

Dej5Asm proc
	mov eax, 5
	ret
Dej5Asm endp

; -------------------------------------------------------------------------------
; picks smaller number
min proc a: DWORD, b: DWORD
	mov eax, a
	sub eax, b
	test eax, eax
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
; use this function when matrix is indexed by two indexes, and array is 1d
calculateMatrixIndex proc col_index: DWORD, row_index: DWORD, cols: DWORD
	mov eax, row_index
	mul cols
	add eax, col_index
	ret 12								; inner function, clear stack
calculateMatrixIndex endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; scales array of doubles of given size in place
scaleMatrixImplementation proc cols: DWORD, rows: DWORD, arr: DWORD, scale: REAL8
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
	ret
scaleMatrixImplementation endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; multiplies two matrices, assumes given output array is correct size
multiplyMatrixImplementation proc cols1: DWORD, rows1: DWORD, arr1: DWORD, cols2: DWORD, rows2: DWORD, arr2: DWORD, outarr: DWORD
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
	ret
multiplyMatrixImplementation endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; fills given matrix with zeros
fillZerosMatrix proc cols: DWORD, rows: DWORD, arr: DWORD
	push 00000000h
	push arr
	push rows
	push cols
	call scaleMatrixImplementation		; scale by 0
	add esp, 20							; clear stack manually, since scaleMatrixImplementation is called from asm
	ret 12
fillZerosMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; fills given matrix with identity matrix
fillIdentityMatrixImplementation proc cols: DWORD, rows: DWORD, arr: DWORD
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
	ret
fillIdentityMatrixImplementation endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; fills given matrix with projection matrix
fillOrtographicProjectionMatrixImplementation proc cols: DWORD, rows: DWORD, arr: DWORD
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
	ret
fillOrtographicProjectionMatrixImplementation endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; allocate matrix
allocateMatrix proc cols: DWORD, rows: DWORD
	mov eax, 1
	mul [DOUBLE_SIZE]
	mul cols
	mul rows
	push eax
	call malloc
	ret
allocateMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; free matrix
deallocateMatrix proc arr: DWORD
	push arr
	call free
	ret
deallocateMatrix endp
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
; project matrix (outarr has dimensions: cols x 2)
projectOrtographicImplementation proc cols: DWORD, rows: DWORD, arr: DWORD, outarr: DWORD, goal_dim: DWORD
	push goal_dim
	push rows
	call allocateMatrix
	add esp, 8
	push eax
	push eax
	push goal_dim
	push rows
	call fillOrtographicProjectionMatrixImplementation	; generate projection matrix
	add esp, 12
	pop eax

	push eax
	push outarr
	push arr
	push rows
	push cols
	push eax
	push goal_dim
	push rows
	call multiplyMatrixImplementation					; perform projection
	add esp, 28
	pop eax

	push eax
	call deallocateMatrix
	add esp, 4
	ret
projectOrtographicImplementation endp
; -------------------------------------------------------------------------------


; -------------------------------------------------------------------------------
; project matrix (arr has dimentions 1 x 3, outarr has dimensions: 1 x 2)
projectPerspectiveImplementation proc cols: DWORD, rows: DWORD, arr: DWORD, outarr: DWORD, goal_dim: DWORD, distance: REAL8
	push goal_dim
	push rows
	call allocateMatrix
	add esp, 8
	push eax
	push eax
	push goal_dim
	push rows
	call fillOrtographicProjectionMatrixImplementation	; generate default projection matrix
	add esp, 12

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
	call scaleMatrixImplementation						; scale by perspective
	add esp, 20
	
	pop eax
	push eax

	push outarr
	push arr
	push rows
	push cols
	push eax
	push goal_dim
	push rows
	call multiplyMatrixImplementation					; perform projection
	add esp, 28
	pop eax

	push eax
	call deallocateMatrix
	add esp, 4
	ret
projectPerspectiveImplementation endp
; -------------------------------------------------------------------------------

; fills rotation matrix, which rotates specified axis
; -------------------------------------------------------------------------------
fillRotationMatrixImplementation proc cols: DWORD, rows: DWORD, arr: DWORD, angle: REAL8, axis1: DWORD, axis2: DWORD
	push arr
	push rows
	push cols
	call fillIdentityMatrixImplementation			; prepare matrix
	add esp, 12

	push cols
	push axis1
	push axis1
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	fld angle
	fcos
	fst REAL8 PTR [eax]								; write cos(angle)

	push cols
	push axis2
	push axis2
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	fst REAL8 PTR [eax]								; write cos(angle)

	push cols
	push axis2
	push axis1
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	fld angle
	fsin
	fst REAL8 PTR [eax]								; write sin(angle)
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
fillRotationMatrixImplementation endp
; -------------------------------------------------------------------------------


; rotates 2d vector
; -------------------------------------------------------------------------------
rotateImplementation proc cols: DWORD, rows: DWORD, arr: DWORD, outarr: DWORD, angle: REAL8
	movsd xmm0, angle
	push 2
	push 2
	call allocateMatrix
	add esp, 8
	push eax											; allocate rotation matrix

	push 1
	push 0
	sub esp, 8											; equal to
	movsd REAL8 PTR [esp], xmm0							; push angle
	push eax
	push 2
	push 2
	call fillRotationMatrixImplementation				; filling rotation matrix
	add esp, 28
	pop eax
	push eax

	push outarr
	push arr
	push rows
	push cols
	push eax
	push 2
	push 2
	call multiplyMatrixImplementation					; performing rotation
	add esp, 28

	pop eax
	push eax
	call deallocateMatrix
	add esp, 4
	ret
rotateImplementation endp
; -------------------------------------------------------------------------------


extern malloc:proc
extern free:proc
testIMP proc i: DWORD
	push i
	call malloc
	ret
testIMP endp

end