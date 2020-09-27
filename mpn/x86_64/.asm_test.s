	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 6
	.section	__TEXT,__const
	.globl	_C                      ## @C
	.p2align	2
_C:
	.long	123                     ## 0x7b

	.section	__DATA,__data
	.globl	_I                      ## @I
	.p2align	2
_I:
	.long	1                       ## 0x1

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"hi"

	.section	__DATA,__data
	.globl	_s                      ## @s
	.p2align	3
_s:
	.quad	L_.str


.subsections_via_symbols
