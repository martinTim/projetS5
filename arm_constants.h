/*
Armator - simulateur de jeu d'instruction ARMv5T � but p�dagogique
Copyright (C) 2011 Guillaume Huard
Ce programme est libre, vous pouvez le redistribuer et/ou le modifier selon les
termes de la Licence Publique G�n�rale GNU publi�e par la Free Software
Foundation (version 2 ou bien toute autre version ult�rieure choisie par vous).

Ce programme est distribu� car potentiellement utile, mais SANS AUCUNE
GARANTIE, ni explicite ni implicite, y compris les garanties de
commercialisation ou d'adaptation dans un but sp�cifique. Reportez-vous � la
Licence Publique G�n�rale GNU pour plus de d�tails.

Vous devez avoir re�u une copie de la Licence Publique G�n�rale GNU en m�me
temps que ce programme ; si ce n'est pas le cas, �crivez � la Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307,
�tats-Unis.

Contact: Guillaume.Huard@imag.fr
	 B�timent IMAG
	 700 avenue centrale, domaine universitaire
	 38401 Saint Martin d'H�res
*/
#ifndef __ARM_CONSTANTS_H__
#define __ARM_CONSTANTS_H__
#include <stdint.h>

/* ARM Modes */
#define USR 0x10
#define FIQ 0x11
#define IRQ 0x12
#define SVC 0x13
#define ABT 0x17
#define UND 0x1b
#define SYS 0x1f

/* ARM INSTRUCTIONS */
#define B 1
#define BL 2
#define AND 3
#define EOR 4
#define SUB 5
#define RSB 6
#define ADD 7
#define ADC 8
#define SBC 9
#define RSC 10
#define TST 11
#define TEQ 12
#define CMP 13
#define CMN 14
#define ORR 15
#define MOV 16
#define BIC 17
#define MVN 18
#define LDR 19
#define LDRB 20
#define LDRH 21
#define STR 22
#define STRB 23
#define STRH 24
#define LDM 25
#define STM 26
#define MRS 27

/* ARM Exceptions (by priority) */
#define RESET                   1
#define UNDEFINED_INSTRUCTION   2
#define SOFTWARE_INTERRUPT      3
#define PREFETCH_ABORT          4
#define DATA_ABORT              5
#define INTERRUPT               6
#define FAST_INTERRUPT          7

/* Some CPSR bits */
#define N 31
#define Z 30
#define C 29
#define V 28

/* shift operations */
#define LSL 0
#define LSR 1
#define ASR 2
#define ROR 3

/* Bit mask constants for msr */
/* We simulate architecture v5T */
#define UnallocMask 0x0FFFFF00
#define UserMask    0xF0000000
#define PrivMask    0x0000000F
#define StateMask   0x00000020

char *arm_get_exception_name(unsigned char exception);
char *arm_get_mode_name(uint8_t mode);
char *arm_get_register_name(uint8_t reg);

#endif
