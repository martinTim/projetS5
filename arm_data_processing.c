/*
Armator - simulateur de jeu d'instruction ARMv5T à but pédagogique
Copyright (C) 2011 Guillaume Huard
Ce programme est libre, vous pouvez le redistribuer et/ou le modifier selon les
termes de la Licence Publique Générale GNU publiée par la Free Software
Foundation (version 2 ou bien toute autre version ultérieure choisie par vous).

Ce programme est distribué car potentiellement utile, mais SANS AUCUNE
GARANTIE, ni explicite ni implicite, y compris les garanties de
commercialisation ou d'adaptation dans un but spécifique. Reportez-vous à la
Licence Publique Générale GNU pour plus de détails.

Vous devez avoir reçu une copie de la Licence Publique Générale GNU en même
temps que ce programme ; si ce n'est pas le cas, écrivez à la Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307,
États-Unis.

Contact: Guillaume.Huard@imag.fr
	 Bâtiment IMAG
	 700 avenue centrale, domaine universitaire
	 38401 Saint Martin d'Hères
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
	
	uint8_t opcode = get_bits(ins,24,21);
	uint8_t S = get_bit(ins,20);
	uint8_t Rn = get_bits(ins,19,16);
	uint32_t rn_val = p->arm_read_register(p,Rn);	
	uint8_t Rd = get_bits(ins,15,12);
	uint32_t rd_val;
	uint8_t S = get_bit(ins,25);
	int res;
	
	switch(opcode){
		case ADD:
			uint8_t shift_type = get_bits(ins,6,5);
			if(get_bit(ins,4)){ // register 
				uint8_t reg = get_bits(ins,3,0);
				uint32_t rm  = p->arm_read_register(p,reg);		
				uint32_t val_shift = p->arm_read_register(p,get_bit(ins,11,8));			
				res = shift(rm,shift_type,val_shift);
				if(!res){
					rd_val = rn_val + Rm;
					p->arm_write_register(p,Rd,rd_val);
				}else{
					return -1;
				}
			}else{//immediat
			
				uint8_t val_shift = get_bits(ins,3,0);
			
			
				if(!res){
					rd_val = rn_val + Rm;
					p->arm_write_register(p,Rd,rd_val);
				}else{
					return -1;
				}			
			}
			
		
		break;
		
		if(c){//C
			registre = set_bit(registre, 29);
		}else{
			registre = clr_bit(registre, 29);
		}


				


		//V a faire !!




	}
	
	
	
	
	
	
	
	
	
	
	

	
	
    return UNDEFINED_INSTRUCTION;
}

int arm_data_processing_immediate_msr(arm_core p, uint32_t ins) {
    return UNDEFINED_INSTRUCTION;
}

int operation(uint32_t rd*,uint8_t operande,  uint32_t rn, uint32_t shifter_operande){
	switch(operande){
		case 0: //AND  (Rd := Rn AND shifter_operande)
		case 8: //TST
			*rd := (rn & shifter_operande);
			break;
		case 1: //EOR  (Rd := Rn XOR shifter_operande) 
		case 9: //TEQ
			break;
		case 2: //SUB  (Rd := Rn - shifter_operande) 
		case 10://CMP
			break;
		case 3: //RSB reverse substract
			break;
		case 4: //ADD
		case 11://CMN
			break;
		case 5: // ADC add with carry
			break;
		case 6: // SBC sub with carry
			break;
		case 7: // RSC reverse substract with carry
			break;
		case 12: // ORR logical OR
			break;
		case 13: // MOV
			break;
		case 14: //BIC (rd = rn AND NOT shifter_operand)
			break;
		case 15: //MNV ( rd != NOT shifter_operand)
			break;
	}
	
}
