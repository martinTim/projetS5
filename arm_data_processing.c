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
		
	}
	
	
	
	
	
	
	
	
	
	
	

	
	
    return UNDEFINED_INSTRUCTION;
}

int arm_data_processing_immediate_msr(arm_core p, uint32_t ins) {
    return UNDEFINED_INSTRUCTION;
}
