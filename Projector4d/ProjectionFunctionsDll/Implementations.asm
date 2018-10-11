PUBLIC Dej5Asm

.model flat, c

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
calculateMatrixIndex proc col_index: DWORD, row_index: DWORD, cols: DWORD
	mov eax, row_index
	mul cols
	add eax, col_index
	ret 12						; clear stack
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
	call fillZerosMatrix
	movsd xmm0, [ONE]
	mov ebx, 0
dataloop:
	cmp ebx, cols
	je finished
	push cols
	push ebx
	push ebx
	call calculateMatrixIndex
	mul [DOUBLE_SIZE]
	add eax, arr
	movsd REAL8 PTR [eax], xmm0
	add ebx, 1
	jmp dataloop
finished:
	ret
fillIdentityMatrixImplementation endp
; -------------------------------------------------------------------------------

testIMP proc i: DWORD
	mov eax, i
	mov eax, [eax]
	ret 4
testIMP endp

end