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
      printf(" test 2 \n" );
    res =  arm_fetch(p,&val_instr);
    if(res != 0 ){
      printf(" test 4 %d \n", res );
      return -1;
    }


    res = condCode(p,val_instr);
    if(!res  ){
        printf(" test error condCode\n" );
        return -1;
        }
        printf(" test 3 \n" );


    uint8_t code = get_bits(val_instr,27,25);
    switch(code){
        case 0b000: // traitement données 1 ou LDRH/STRH
            if(get_bit(val_instr,7)==1 && get_bit(val_instr,4)==1) //LDRH et STRH
                res = arm_load_store(p,val_instr);
            else if(get_bit(val_instr,20)==0 && get_bit(val_instr,21)==0 && get_bit(val_instr,23)==0 && get_bit(val_instr,24)==1) //MRS
                move_PSR_to_register(p,val_instr);            
            else
                res = arm_data_processing_shift(p,val_instr);
            break;
        case 0b001: // traitement données 2
            res = arm_data_processing_immediate_msr(p,val_instr);
            break;
        case 0b010: // mémoire 1
        case 0b011:
            res = arm_load_store(p,val_instr);
            break;
        case 0b100:// mémoire 2
            res = arm_load_store_multiple(p,val_instr);
            break;
        case 0b101: // branchement
            res = arm_branch(p,val_instr);
            break;
        case 0b110: // divers
            res = arm_coprocessor_load_store(p,val_instr);
            break;
        case 0b111: // divers SWI
            res = arm_coprocessor_others_swi(p,val_instr);
            break;
        default :
              res = -1;
            break;
    }
    return res;
}

int arm_step(arm_core p) {
    int result;
    printf(" test 1 \n" );

    result = arm_execute_instruction(p);
    if (!result)
        arm_exception(p, result);
    return result;
}

int condCode(arm_core p,uint32_t value){
    uint32_t cpsr = arm_read_cpsr(p);
    uint8_t n = get_bit(cpsr,N);
    uint8_t z = get_bit(cpsr,Z);
    uint8_t c = get_bit(cpsr,C);
    uint8_t v = get_bit(cpsr,V);
    uint8_t opcode = value>>28;
    switch (opcode){
      case 0: return (z==1);   // Z set
      case 1: return (z==0);  // Z clear
      case 2: return (c==1);   // C set
      case 3: return (c==0);  // C clear
      case 4: return (n==1);  // N set
      case 5: return (n==0);  // N clear
      case 6: return (v==1);  // V set
      case 7: return (v==0);  // V clear
      case 8: return ((c==1) && (z==0));  // C set Z clear
      case 9: return ((c==0) || (z==1));  // C clear or Z set
      case 10:return (n==v);// N == V
      case 11:return (n!=v);  // N != V
      case 12:return ((z==0) && (n==v));// Z clear and N == V
      case 13:return ((z==1) || (n!=v));  // Z set or N != V
      case 14:return 1;  // toujours vrai
      case 15:return -1;  // aucune idée
      default: return -1; 
    }
}
