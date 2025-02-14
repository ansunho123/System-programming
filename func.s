	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 15, 2
	.globl	_func                           ; -- Begin function func
	.p2align	2
_func:                                  ; @func
	.cfi_startproc
; %bb.0:
	sub	w8, w0, #1
	sub	w9, w0, #2
	umull	x9, w8, w9
	lsr	x9, x9, #1
	add	w8, w8, w9
	cmp	w0, #1
	csel	w0, wzr, w8, lt
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
