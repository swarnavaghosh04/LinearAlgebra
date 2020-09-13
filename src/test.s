	.file	"test.cpp"
	.text
	.section	.text$_ZNKSt5ctypeIcE8do_widenEc,"x"
	.linkonce discard
	.align 2
	.p2align 4
	.globl	_ZNKSt5ctypeIcE8do_widenEc
	.def	_ZNKSt5ctypeIcE8do_widenEc;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZNKSt5ctypeIcE8do_widenEc
_ZNKSt5ctypeIcE8do_widenEc:
.LFB1411:
	.seh_endprologue
	movl	%edx, %eax
	ret
	.seh_endproc
	.text
	.p2align 4
	.def	__tcf_0;	.scl	3;	.type	32;	.endef
	.seh_proc	__tcf_0
__tcf_0:
.LFB2182:
	.seh_endprologue
	leaq	_ZStL8__ioinit(%rip), %rcx
	jmp	_ZNSt8ios_base4InitD1Ev
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "Vector(%u) %-20s 0x%x(0x%x)\12\0"
	.text
	.p2align 4
	.def	_ZL6printfPKcz.constprop.0;	.scl	3;	.type	32;	.endef
	.seh_proc	_ZL6printfPKcz.constprop.0
_ZL6printfPKcz.constprop.0:
.LFB2190:
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	$1, %ecx
	leaq	72(%rsp), %rbx
	movq	%rdx, 72(%rsp)
	movq	%r8, 80(%rsp)
	movq	%r9, 88(%rsp)
	movq	%rbx, 40(%rsp)
	call	*__imp___acrt_iob_func(%rip)
	movq	%rbx, %r8
	leaq	.LC0(%rip), %rdx
	movq	%rax, %rcx
	call	__mingw_vfprintf
	addq	$48, %rsp
	popq	%rbx
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC1:
	.ascii "Des - No Free:\0"
.LC2:
	.ascii "Des - Free Mem:\0"
	.section	.text$_ZN6VectorIiED1Ev,"x"
	.linkonce discard
	.align 2
	.p2align 4
	.globl	_ZN6VectorIiED1Ev
	.def	_ZN6VectorIiED1Ev;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN6VectorIiED1Ev
_ZN6VectorIiED1Ev:
.LFB1923:
	subq	$72, %rsp
	.seh_stackalloc	72
	.seh_endprologue
	leaq	.LC1(%rip), %r8
	movq	%rcx, %r9
	movq	(%rcx), %rcx
	cmpb	$0, 12(%r9)
	je	.L6
	leaq	.LC2(%rip), %r8
	testq	%rcx, %rcx
	je	.L6
	movq	%r9, 80(%rsp)
	movq	%r8, 56(%rsp)
	call	_ZdaPv
	movq	80(%rsp), %r9
	movq	56(%rsp), %r8
	movq	(%r9), %rcx
.L6:
	movl	8(%r9), %edx
	movq	%rcx, 32(%rsp)
	leaq	.LC0(%rip), %rcx
	call	_ZL6printfPKcz.constprop.0
	nop
	addq	$72, %rsp
	ret
	.def	__gxx_personality_seh0;	.scl	2;	.type	32;	.endef
	.seh_handler	__gxx_personality_seh0, @unwind, @except
	.seh_handlerdata
.LLSDA1923:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1923-.LLSDACSB1923
.LLSDACSB1923:
.LLSDACSE1923:
	.section	.text$_ZN6VectorIiED1Ev,"x"
	.linkonce discard
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC3:
	.ascii "Con - No Alloc:\0"
.LC4:
	.ascii ", \0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB1674:
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$96, %rsp
	.seh_stackalloc	96
	.seh_endprologue
	call	__main
	leaq	52(%rsp), %rbx
	leaq	64(%rsp), %r12
	movabsq	$8589934593, %rax
	movq	%rbx, 32(%rsp)
	movq	%r12, %r9
	leaq	.LC3(%rip), %r8
	movl	$3, %edx
	leaq	.LC0(%rip), %rcx
	movq	%rax, 52(%rsp)
	leaq	80(%rsp), %r13
	movl	$3, 60(%rsp)
	movq	%rbx, 64(%rsp)
	movl	$3, 72(%rsp)
	movb	$0, 76(%rsp)
.LEHB0:
	call	_ZL6printfPKcz.constprop.0
.LEHE0:
	movq	%rbx, 32(%rsp)
	movq	%r13, %r9
	leaq	.LC3(%rip), %r8
	movl	$3, %edx
	leaq	.LC0(%rip), %rcx
	movq	%rbx, 80(%rsp)
	movl	$3, 88(%rsp)
	movb	$0, 92(%rsp)
.LEHB1:
	call	_ZL6printfPKcz.constprop.0
.LEHE1:
	movl	72(%rsp), %eax
	cmpl	88(%rsp), %eax
	jne	.L13
	testl	%eax, %eax
	je	.L13
	movq	64(%rsp), %rdx
	movq	80(%rsp), %r8
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L14:
	movl	(%r8,%rax,4), %ecx
	addl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpl	%eax, 72(%rsp)
	ja	.L14
.L13:
	movq	.refptr._ZSt4cout(%rip), %r14
	leaq	.LC4(%rip), %rsi
.L12:
	movl	(%rbx), %edx
	movq	%r14, %rcx
.LEHB2:
	call	_ZNSolsEi
	movq	%rax, %rcx
	movl	$2, %r8d
	movq	%rsi, %rdx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_x
	addq	$4, %rbx
	cmpq	%rbx, %r12
	jne	.L12
	movq	.refptr._ZSt4cout(%rip), %rax
	movq	(%rax), %rdx
	movq	-24(%rdx), %rdx
	movq	240(%rdx,%rax), %r14
	testq	%r14, %r14
	je	.L29
	cmpb	$0, 56(%r14)
	je	.L16
	movsbl	67(%r14), %edx
.L17:
	movq	.refptr._ZSt4cout(%rip), %rcx
	call	_ZNSo3putEc
	movq	%rax, %rcx
	call	_ZNSo5flushEv
	movq	%r13, %rcx
	call	_ZN6VectorIiED1Ev
	movq	%r12, %rcx
	call	_ZN6VectorIiED1Ev
	xorl	%eax, %eax
	addq	$96, %rsp
	popq	%rbx
	popq	%rsi
	popq	%r12
	popq	%r13
	popq	%r14
	ret
.L16:
	movq	%r14, %rcx
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%r14), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rcx
	movl	$10, %edx
	movq	48(%rax), %rax
	cmpq	%rcx, %rax
	je	.L17
	movl	$10, %edx
	movq	%r14, %rcx
	call	*%rax
	movsbl	%al, %edx
	jmp	.L17
.L29:
	call	_ZSt16__throw_bad_castv
.LEHE2:
.L21:
	movq	%rax, %r13
.L19:
	movq	%r12, %rcx
	call	_ZN6VectorIiED1Ev
	movq	%r13, %rcx
.LEHB3:
	call	_Unwind_Resume
.LEHE3:
.L22:
	movq	%rax, %rbx
	movq	%r13, %rcx
	call	_ZN6VectorIiED1Ev
	movq	%rbx, %r13
	jmp	.L19
	.seh_handler	__gxx_personality_seh0, @unwind, @except
	.seh_handlerdata
.LLSDA1674:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1674-.LLSDACSB1674
.LLSDACSB1674:
	.uleb128 .LEHB0-.LFB1674
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1674
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L21-.LFB1674
	.uleb128 0
	.uleb128 .LEHB2-.LFB1674
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L22-.LFB1674
	.uleb128 0
	.uleb128 .LEHB3-.LFB1674
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSE1674:
	.section	.text.startup,"x"
	.seh_endproc
	.p2align 4
	.def	_GLOBAL__sub_I_main;	.scl	3;	.type	32;	.endef
	.seh_proc	_GLOBAL__sub_I_main
_GLOBAL__sub_I_main:
.LFB2183:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	leaq	_ZStL8__ioinit(%rip), %rcx
	call	_ZNSt8ios_base4InitC1Ev
	leaq	__tcf_0(%rip), %rcx
	addq	$40, %rsp
	jmp	atexit
	.seh_endproc
	.section	.ctors,"w"
	.align 8
	.quad	_GLOBAL__sub_I_main
.lcomm _ZStL8__ioinit,1,1
	.ident	"GCC: (Rev1, Built by MSYS2 project) 10.2.0"
	.def	_ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	_ZdaPv;	.scl	2;	.type	32;	.endef
	.def	_ZNSolsEi;	.scl	2;	.type	32;	.endef
	.def	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_x;	.scl	2;	.type	32;	.endef
	.def	_ZNSo3putEc;	.scl	2;	.type	32;	.endef
	.def	_ZNSo5flushEv;	.scl	2;	.type	32;	.endef
	.def	_ZNKSt5ctypeIcE13_M_widen_initEv;	.scl	2;	.type	32;	.endef
	.def	_ZSt16__throw_bad_castv;	.scl	2;	.type	32;	.endef
	.def	_Unwind_Resume;	.scl	2;	.type	32;	.endef
	.def	_ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	atexit;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr._ZSt4cout, "dr"
	.globl	.refptr._ZSt4cout
	.linkonce	discard
.refptr._ZSt4cout:
	.quad	_ZSt4cout
