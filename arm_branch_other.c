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
#include "arm_branch_other.h"
#include "arm_constants.h"
#include "util.h"
#include "arm_instruction.h"
#include <debug.h>
#include <stdlib.h>

int arm_branch(arm_core p, uint32_t ins) {

    if (condCode(p, ins)) {

        uint8_t L = get_bit(ins, 24);
        uint8_t mode = get_mode_registers(p);
        uint8_t bit = get_bit(ins, 23);
        uint32_t target_address;
        uint32_t pc = arm_read_register(p, 15);

        //In case L=1 we have to preserve the return address
        if (L == 1) {
            if (mode == USR) {
                arm_write_usr_register(p, 14, pc - 0x4);
            } else if (mode == SYS) {
                arm_write_register(p, 14, pc - 0x4);
            } else
                arm_write_register(p, 14, pc - 0x4); //Apparemment on est dans le mode superviseur
        }

        //Sign extending to 30 bits
        if (bit) {
            target_address = 0b111111000000000000000000000000 | get_bits(ins, 23, 0);
        } else {
            target_address = 0b000000000000000000000000000000 | get_bits(ins, 23, 0);
        }

        target_address = target_address << 2;
        pc = pc + target_address;
        arm_write_register(p, 15, pc);

        return 1;
    } else return 1; //Condition not satisfied, no branch done.
}

int arm_coprocessor_others_swi(arm_core p, uint32_t ins) {
    if (get_bit(ins, 24)) {
        /* Here we implement the end of the simulation as swi 0x123456 */
        if ((ins & 0xFFFFFF) == 0x123456)
            exit(0);
        return SOFTWARE_INTERRUPT;
    }
    return UNDEFINED_INSTRUCTION;
}

int arm_miscellaneous(arm_core p, uint32_t ins) {
    return UNDEFINED_INSTRUCTION;
}
