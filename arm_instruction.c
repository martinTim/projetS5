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
#include "arm_instruction.h"
#include "arm_exception.h"
#include "arm_data_processing.h"
#include "arm_load_store.h"
#include "arm_branch_other.h"
#include "arm_constants.h"
#include "util.h"

static int arm_execute_instruction(arm_core p) {
    uint32_t val_instr;
    int res;
    res =  arm_fetch(p,&val_instr);
    if(!res)
      return -1;


    uint8_t code = get_bits(val_instr,27,26);
    switch(code){
        case 0b00:// traitement de données (data processing) + miscaellniounious
            uint8_t a = get_bit(val_instr,24);
            uint8_t i = get_bit(val_instr,25);
            if(i==0) {
                if(a==1) {
                    res = arm_miscellaneous(p,val_instr);
                }else{
                    res = arm_data_processing_shift(p,val_instr);
                }
            }
            else if(i==1) {
                res = arm_data_processing_immediate_msr(p,val_instr);
            }
            
        break;
      case 0b01:// accèes mémoire (LOAD_STORE)


        break;
      case 0b10:// Branchement (BRANCH)


        break;
      case 0b11:// Divers (OTHERS)
          
        break;
        default : 
            res = -1;
            break;
    }
    
    

    return res;
}

int arm_step(arm_core p) {
    int result;

    result = arm_execute_instruction(p);
    if (result)
        arm_exception(p, result);
    return result;
}

int condCode(arm_core p,uint32_t value){
    uint8_t opcode = (0xF0000000 & value)>>28;
    uint8_t NZCV = arm_read_cpsr(p)>>28;
    switch (opcode){
      case 0: return (NZCV & 0b0100); break;  // Z set
      case 1: return !(NZCV & 0b0100); break; // Z clear
      case 2: return (NZCV & 0b0010); break;  // C set
      case 3: return !(NZCV & 0b0010); break; // C clear
      case 4: return (NZCV & 0b1000); break; // N set
      case 5: return !(NZCV & 0b1000); break; // N clear
      case 6: return (NZCV & 0b0001); break; // V set
      case 7: return !(NZCV & 0b001); break; // V clear
      case 8: return ((NZCV & 0b0010) && !(NZCV & 0b0100)); break; // C set Z clear
      case 9: return (!(NZCV & 0b0010) || (NZCV & 0b0100)); break; // C clear or Z set
      case 10:return (((NZCV & 0b1000)>>3) == (NZCV & 0b0001)); break; // N == V
      case 11:return ((NZCV & 0b1000)^(NZCV & 0b0001)); break; // N != V
      case 12:return ((((NZCV & 0b1000)>>3) == (NZCV & 0b0001)) && !(NZCV & 0b0100)); break; // Z clear and N == V
      case 13:return ((NZCV & 0b0100) || (((NZCV & 0b1000)>>3) == (NZCV & 0b0001))); break;
      case 14:return 1; break; // toujours vrai
      case 15:return -1; break; // aucune idée
      default: return -1; break;
    }
}
