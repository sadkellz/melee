.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global HSD_MulColor
HSD_MulColor:
/* 8037A780 00377360  88 E3 00 00 */	lbz r7, 0(r3)
/* 8037A784 00377364  3C C0 80 81 */	lis r6, 0x80808081@ha
/* 8037A788 00377368  88 04 00 00 */	lbz r0, 0(r4)
/* 8037A78C 0037736C  39 06 80 81 */	addi r8, r6, 0x80808081@l
/* 8037A790 00377370  7C 07 01 D6 */	mullw r0, r7, r0
/* 8037A794 00377374  7C 08 00 16 */	mulhwu r0, r8, r0
/* 8037A798 00377378  54 00 CE 3E */	rlwinm r0, r0, 0x19, 0x18, 0x1f
/* 8037A79C 0037737C  98 05 00 00 */	stb r0, 0(r5)
/* 8037A7A0 00377380  88 C3 00 01 */	lbz r6, 1(r3)
/* 8037A7A4 00377384  88 04 00 01 */	lbz r0, 1(r4)
/* 8037A7A8 00377388  7C 06 01 D6 */	mullw r0, r6, r0
/* 8037A7AC 0037738C  7C 08 00 16 */	mulhwu r0, r8, r0
/* 8037A7B0 00377390  54 00 CE 3E */	rlwinm r0, r0, 0x19, 0x18, 0x1f
/* 8037A7B4 00377394  98 05 00 01 */	stb r0, 1(r5)
/* 8037A7B8 00377398  88 C3 00 02 */	lbz r6, 2(r3)
/* 8037A7BC 0037739C  88 04 00 02 */	lbz r0, 2(r4)
/* 8037A7C0 003773A0  7C 06 01 D6 */	mullw r0, r6, r0
/* 8037A7C4 003773A4  7C 08 00 16 */	mulhwu r0, r8, r0
/* 8037A7C8 003773A8  54 00 CE 3E */	rlwinm r0, r0, 0x19, 0x18, 0x1f
/* 8037A7CC 003773AC  98 05 00 02 */	stb r0, 2(r5)
/* 8037A7D0 003773B0  88 63 00 03 */	lbz r3, 3(r3)
/* 8037A7D4 003773B4  88 04 00 03 */	lbz r0, 3(r4)
/* 8037A7D8 003773B8  7C 03 01 D6 */	mullw r0, r3, r0
/* 8037A7DC 003773BC  7C 08 00 16 */	mulhwu r0, r8, r0
/* 8037A7E0 003773C0  54 00 CE 3E */	rlwinm r0, r0, 0x19, 0x18, 0x1f
/* 8037A7E4 003773C4  98 05 00 03 */	stb r0, 3(r5)
/* 8037A7E8 003773C8  4E 80 00 20 */	blr 

.global func_8037A7EC
func_8037A7EC:
/* 8037A7EC 003773CC  38 00 00 04 */	li r0, 4
/* 8037A7F0 003773D0  7C 09 03 A6 */	mtctr r0
/* 8037A7F4 003773D4  38 A0 00 00 */	li r5, 0
/* 8037A7F8 003773D8  38 C0 00 00 */	li r6, 0
/* 8037A7FC 003773DC  38 80 00 01 */	li r4, 1
lbl_8037A800:
/* 8037A800 003773E0  7C 80 30 30 */	slw r0, r4, r6
/* 8037A804 003773E4  7C 60 00 39 */	and. r0, r3, r0
/* 8037A808 003773E8  41 82 00 08 */	beq lbl_8037A810
/* 8037A80C 003773EC  38 A5 00 01 */	addi r5, r5, 1
lbl_8037A810:
/* 8037A810 003773F0  38 C6 00 01 */	addi r6, r6, 1
/* 8037A814 003773F4  7C 80 30 30 */	slw r0, r4, r6
/* 8037A818 003773F8  7C 60 00 39 */	and. r0, r3, r0
/* 8037A81C 003773FC  41 82 00 08 */	beq lbl_8037A824
/* 8037A820 00377400  38 A5 00 01 */	addi r5, r5, 1
lbl_8037A824:
/* 8037A824 00377404  38 C6 00 01 */	addi r6, r6, 1
/* 8037A828 00377408  7C 80 30 30 */	slw r0, r4, r6
/* 8037A82C 0037740C  7C 60 00 39 */	and. r0, r3, r0
/* 8037A830 00377410  41 82 00 08 */	beq lbl_8037A838
/* 8037A834 00377414  38 A5 00 01 */	addi r5, r5, 1
lbl_8037A838:
/* 8037A838 00377418  38 C6 00 01 */	addi r6, r6, 1
/* 8037A83C 0037741C  7C 80 30 30 */	slw r0, r4, r6
/* 8037A840 00377420  7C 60 00 39 */	and. r0, r3, r0
/* 8037A844 00377424  41 82 00 08 */	beq lbl_8037A84C
/* 8037A848 00377428  38 A5 00 01 */	addi r5, r5, 1
lbl_8037A84C:
/* 8037A84C 0037742C  38 C6 00 01 */	addi r6, r6, 1
/* 8037A850 00377430  7C 80 30 30 */	slw r0, r4, r6
/* 8037A854 00377434  7C 60 00 39 */	and. r0, r3, r0
/* 8037A858 00377438  41 82 00 08 */	beq lbl_8037A860
/* 8037A85C 0037743C  38 A5 00 01 */	addi r5, r5, 1
lbl_8037A860:
/* 8037A860 00377440  38 C6 00 01 */	addi r6, r6, 1
/* 8037A864 00377444  7C 80 30 30 */	slw r0, r4, r6
/* 8037A868 00377448  7C 60 00 39 */	and. r0, r3, r0
/* 8037A86C 0037744C  41 82 00 08 */	beq lbl_8037A874
/* 8037A870 00377450  38 A5 00 01 */	addi r5, r5, 1
lbl_8037A874:
/* 8037A874 00377454  38 C6 00 01 */	addi r6, r6, 1
/* 8037A878 00377458  7C 80 30 30 */	slw r0, r4, r6
/* 8037A87C 0037745C  7C 60 00 39 */	and. r0, r3, r0
/* 8037A880 00377460  41 82 00 08 */	beq lbl_8037A888
/* 8037A884 00377464  38 A5 00 01 */	addi r5, r5, 1
lbl_8037A888:
/* 8037A888 00377468  38 C6 00 01 */	addi r6, r6, 1
/* 8037A88C 0037746C  7C 80 30 30 */	slw r0, r4, r6
/* 8037A890 00377470  7C 60 00 39 */	and. r0, r3, r0
/* 8037A894 00377474  41 82 00 08 */	beq lbl_8037A89C
/* 8037A898 00377478  38 A5 00 01 */	addi r5, r5, 1
lbl_8037A89C:
/* 8037A89C 0037747C  38 C6 00 01 */	addi r6, r6, 1
/* 8037A8A0 00377480  42 00 FF 60 */	bdnz lbl_8037A800
/* 8037A8A4 00377484  7C A3 2B 78 */	mr r3, r5
/* 8037A8A8 00377488  4E 80 00 20 */	blr 

.global func_8037A8AC
func_8037A8AC:
/* 8037A8AC 0037748C  7C 08 02 A6 */	mflr r0
/* 8037A8B0 00377490  28 03 00 09 */	cmplwi r3, 9
/* 8037A8B4 00377494  90 01 00 04 */	stw r0, 4(r1)
/* 8037A8B8 00377498  94 21 FF F8 */	stwu r1, -8(r1)
/* 8037A8BC 0037749C  41 81 00 6C */	bgt lbl_8037A928
/* 8037A8C0 003774A0  3C 80 80 40 */	lis r4, jtbl_80406E20@ha
/* 8037A8C4 003774A4  38 84 6E 20 */	addi r4, r4, jtbl_80406E20@l
/* 8037A8C8 003774A8  54 60 10 3A */	slwi r0, r3, 2
/* 8037A8CC 003774AC  7C 04 00 2E */	lwzx r0, r4, r0
/* 8037A8D0 003774B0  7C 09 03 A6 */	mtctr r0
/* 8037A8D4 003774B4  4E 80 04 20 */	bctr 
.global lbl_8037A8D8
lbl_8037A8D8:
/* 8037A8D8 003774B8  38 60 00 00 */	li r3, 0
/* 8037A8DC 003774BC  48 00 00 60 */	b lbl_8037A93C
.global lbl_8037A8E0
lbl_8037A8E0:
/* 8037A8E0 003774C0  38 60 00 03 */	li r3, 3
/* 8037A8E4 003774C4  48 00 00 58 */	b lbl_8037A93C
.global lbl_8037A8E8
lbl_8037A8E8:
/* 8037A8E8 003774C8  38 60 00 06 */	li r3, 6
/* 8037A8EC 003774CC  48 00 00 50 */	b lbl_8037A93C
.global lbl_8037A8F0
lbl_8037A8F0:
/* 8037A8F0 003774D0  38 60 00 09 */	li r3, 9
/* 8037A8F4 003774D4  48 00 00 48 */	b lbl_8037A93C
.global lbl_8037A8F8
lbl_8037A8F8:
/* 8037A8F8 003774D8  38 60 00 0C */	li r3, 0xc
/* 8037A8FC 003774DC  48 00 00 40 */	b lbl_8037A93C
.global lbl_8037A900
lbl_8037A900:
/* 8037A900 003774E0  38 60 00 0F */	li r3, 0xf
/* 8037A904 003774E4  48 00 00 38 */	b lbl_8037A93C
.global lbl_8037A908
lbl_8037A908:
/* 8037A908 003774E8  38 60 00 12 */	li r3, 0x12
/* 8037A90C 003774EC  48 00 00 30 */	b lbl_8037A93C
.global lbl_8037A910
lbl_8037A910:
/* 8037A910 003774F0  38 60 00 15 */	li r3, 0x15
/* 8037A914 003774F4  48 00 00 28 */	b lbl_8037A93C
.global lbl_8037A918
lbl_8037A918:
/* 8037A918 003774F8  38 60 00 18 */	li r3, 0x18
/* 8037A91C 003774FC  48 00 00 20 */	b lbl_8037A93C
.global lbl_8037A920
lbl_8037A920:
/* 8037A920 00377500  38 60 00 1B */	li r3, 0x1b
/* 8037A924 00377504  48 00 00 18 */	b lbl_8037A93C
lbl_8037A928:
/* 8037A928 00377508  38 6D A8 00 */	addi r3, r13, lbl_804D5EA0@sda21
/* 8037A92C 0037750C  38 80 00 84 */	li r4, 0x84
/* 8037A930 00377510  38 AD A8 08 */	addi r5, r13, lbl_804D5EA8@sda21
/* 8037A934 00377514  48 00 D8 ED */	bl __assert
/* 8037A938 00377518  38 60 00 00 */	li r3, 0
lbl_8037A93C:
/* 8037A93C 0037751C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8037A940 00377520  38 21 00 08 */	addi r1, r1, 8
/* 8037A944 00377524  7C 08 03 A6 */	mtlr r0
/* 8037A948 00377528  4E 80 00 20 */	blr 


.section .data

.global lbl_80406DF0
lbl_80406DF0:
    .4byte 0x3F800000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x3F800000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x3F800000
    .4byte NULL
.global jtbl_80406E20
jtbl_80406E20:
	.4byte lbl_8037A8D8
	.4byte lbl_8037A8E0
	.4byte lbl_8037A8E8
	.4byte lbl_8037A8F0
	.4byte lbl_8037A8F8
	.4byte lbl_8037A900
	.4byte lbl_8037A908
	.4byte lbl_8037A910
	.4byte lbl_8037A918
	.4byte lbl_8037A920


.section .sdata

.global lbl_804D5EA0
lbl_804D5EA0:
    .asciz "util.c"
    .balign 4
.global lbl_804D5EA8
lbl_804D5EA8:
    .asciz "0"
    .balign 4
    .4byte NULL
