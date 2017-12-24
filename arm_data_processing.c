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
#include "arm_data_processing.h"
#include "arm_exception.h"
#include "arm_constants.h"
#include "arm_branch_other.h"
#include "util.h"
#include "debug.h"

/*
int* operation(uint8_t opcode,uint32_t dest ,uint32_t firstOperand ,uint32_t secondOperand ){
	int *result = 1;
	return result;
}
*/
/* Decoding functions for different classes of instructions */
int arm_data_processing_shift(arm_core p, uint32_t ins) {
	
	
	//uint8_t opcode = get_bits(ins,24,21);
	uint8_t S = get_bit(ins,20);
	


	//carry sur operation || shift
	int c = 0;


	//first operand
	//uint8_t Rn = get_bits(ins,19,16);
	//uint32_t rn_val = arm_read_register(p,Rn);	
	
	//registre de  destination
	uint8_t Register_destination = get_bits(ins,15,12);
	uint32_t rd_val =  arm_read_register(p,Register_destination);	

	//result of function
	int res;



	uint32_t registreCPSR =  arm_read_register(p,16);	

	

	if(get_bit(ins,7) && get_bit(ins,4))//instruction is not a ADD
		return -1;


	//type du shift
	uint8_t shift_type = get_bits(ins,6,5);

	uint32_t value_To_Shift;
	uint32_t val_shift;
	uint8_t register_decalage = get_bits(ins,3,0);


	if(get_bit(ins,4)){ // decalage par registre 

		
		value_To_Shift  = arm_read_register(p,register_decalage);		
	    val_shift = arm_read_register(p,get_bits(ins,11,8));		

	}else{// decalage immediat 

		uint8_t register_decalage = get_bits(ins,3,0);
		value_To_Shift  = arm_read_register(p,register_decalage);	
		val_shift = arm_read_register(p,get_bits(ins,11,7));

	}



	c = shift(&value_To_Shift,shift_type,val_shift);
	
	
	if(c){//C
		registreCPSR = set_bit(registreCPSR, 29);
	}else{
		registreCPSR = clr_bit(registreCPSR, 29);
	}


	//traiter carry shift

	/*int * result_op;
	result_op = operation(opcode,rd_val,rn_val,value_To_Shift);// (opcode,dest,fisrtOP,secOp)
	*/

	rd_val =  arm_read_register(p,Register_destination);	


	if(S == 1 && rd_val == arm_read_register(p,15)){
		if( arm_current_mode_has_spsr(p)){//=> CPSR = SPSR
			arm_write_register(p,16,arm_read_register(p,17));	
		}else{
			res = -1;
		}
	}else if(S == 1){//mise a jours des registres ZNVC
		if(get_bit(rd_val,31)){//N
			registreCPSR = set_bit(registreCPSR, 31);
		}

		if(rd_val == 0){//Z
			registreCPSR = set_bit(registreCPSR, 30);
		}else{
			 registreCPSR = clr_bit(registreCPSR, 30);
		}
		
		if(c){//C
			registreCPSR = set_bit(registreCPSR, 29);
		}else{
			registreCPSR = clr_bit(registreCPSR, 29);
		}

		//V a faire !!






	}

	

    return res;
}

int arm_data_processing_immediate_msr(arm_core p, uint32_t ins) {
    return UNDEFINED_INSTRUCTION;
}


