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

	uint8_t opcode = get_bits(ins,24,21);
	uint8_t S = get_bit(ins,20);
	uint8_t Rn = get_bits(ins,19,16);
	uint32_t rn_val = arm_read_register(p,Rn);
	uint8_t Rd = get_bits(ins,15,12);
	uint8_t shift_type = get_bits(ins,6,5);
	uint8_t reg = get_bits(ins,3,0);
	uint32_t rm  = arm_read_register(p,reg);
	uint32_t val_shift;
	if(get_bit(ins,4)){ // register shift
		 val_shift = arm_read_register(p,get_bits(ins,11,8));
	}else{//immediat shift
		 val_shift = get_bits(ins,11,7);
	}
	int shifter_carry_out = shift(&rm,shift_type,val_shift);
	uint8_t nzcv = get_bits(arm_read_cpsr(p),31,28);
	uint32_t res = operation(p,opcode,Rd,rn_val,rm, &nzcv,shifter_carry_out);
	if(res){
		if((S == 1) && Rd==15){
			if(arm_current_mode_has_spsr(p)){
				arm_write_cpsr(p,(arm_read_spsr(p)));
				return 1;
			}else{
				return -1; // UNPREDICTTABLE
			}
		}else if( S == 1){
                                printf("nzcv apres : %x\n",nzcv);
                                uint32_t tmp = arm_read_cpsr(p);
                                tmp = (tmp & 0x0FFFFFFF);
                                tmp = (tmp | (nzcv <<28));
                                arm_write_cpsr(p,tmp); // update nzcv flags
		}
	}

	return res;

}

int arm_data_processing_immediate_msr(arm_core p, uint32_t ins) {

		uint8_t opcode = get_bits(ins,24,21);
		uint8_t S = get_bit(ins,20);
		uint8_t Rn = get_bits(ins,19,16);
		uint32_t rn_val = arm_read_register(p,Rn);
		uint8_t Rd = get_bits(ins,15,12);

		uint8_t rotate_imm = get_bits(ins,11,8);
		uint8_t immed_8 = get_bits(ins,7,0);
		uint32_t shifter_operande  = ror(immed_8, 2 * rotate_imm );
		
		uint8_t nzcv = get_bits(arm_read_cpsr(p),31,28);
                                printf("nzcv avant : %x\n",nzcv);


		uint32_t res = operation(p,opcode,Rd,rn_val,shifter_operande, &nzcv,0);
		if(res){
			if((S == 1) && Rd==15){
				if(arm_current_mode_has_spsr(p)){
					arm_write_cpsr(p,(arm_read_spsr(p)));
					return 1;
				}else{
					return -1; // UNPREDICTTABLE
				}
			}else if( S == 1){
                                printf("nzcv apres : %x\n",nzcv);
                                uint32_t tmp = arm_read_cpsr(p);
                                tmp = (tmp & 0x0FFFFFFF);
                                tmp = (tmp | (nzcv <<28));
                                arm_write_cpsr(p,tmp); // update nzcv flags
                                
			}
		}
    return res;
}

int operation(arm_core p, uint8_t operande, uint32_t rd, uint32_t rn, uint32_t shifter_operande, uint8_t * nzcv, int shifter_carry_out){
	uint32_t val;
	int res = -1;
	switch(operande){
		case 0: //AND  (Rd := Rn AND shifter_operande)
			val = (rn & shifter_operande);
			*nzcv=*nzcv & (shifter_carry_out<<1 | 0b1101); // set C flag
			arm_write_register(p,rd,val); //V flag unaffected
			res = 1;
			break;

		case 1:  //EOR  (Rd := Rn XOR shifter_operande)
			val = (rn ^ shifter_operande);
			*nzcv=*nzcv & (shifter_carry_out<<1 | 0b1101); // set C flag
			arm_write_register(p,rd,val); //V flag unaffected
			res = 1;
			break;

		case 2: //SUB  (Rd := Rn - shifter_operande)
			val =  (rn - shifter_operande);
			*nzcv= *nzcv & ((~((~rn & ~shifter_operande) & val) >> 30)| 0b1101); // set C flag
			*nzcv= *nzcv & (((((rn & shifter_operande) & ~val) | ((~rn & ~shifter_operande) & val)) >> 31)| 0b1110); // set V flag
			arm_write_register(p,rd,val);
			res = 1;
			break;
		case 3: //RSB reverse substract
			val =  (shifter_operande - rn);
			*nzcv= *nzcv & ((~( (~rn & ~shifter_operande) & val) >> 30)| 0b1101); // set C flag
			*nzcv= *nzcv & (((((rn & shifter_operande) & ~val) | ((~rn & ~shifter_operande) & val)) >> 31)| 0b1110); // set V flag
			arm_write_register(p,rd,val);
			res = 1;
			break;

		case 4:  //ADD
			val =  (rn + shifter_operande);
			*nzcv= *nzcv & ((((rn | shifter_operande) & ~val) >> 30)| 0b1101); // set C flag
			*nzcv= *nzcv & (((((rn & shifter_operande) & ~val) | ((~rn & ~shifter_operande) & val)) >> 31)| 0b1110); // set V flag			arm_write_register(p,rd,val);
			arm_write_register(p,rd,val);
			res = 1;
			break;

		case 5 : // ADC
			val =  (rn + shifter_operande + (*nzcv & (0b0010>>1)));
			*nzcv= *nzcv & ((((rn | shifter_operande) & ~val) >> 30)| 0b1101); // set C flag
			*nzcv= *nzcv & (((((rn & shifter_operande) & ~val) | ((~rn & ~shifter_operande) & val)) >> 31)| 0b1110); // set V flag
			arm_write_register(p,rd,val);
			res = 1;
			break;

		case 6: // SBC sub with carry
			val =  (rn - shifter_operande - (*nzcv & (0b0010>>1)));
			*nzcv= *nzcv & ((~((~rn & ~shifter_operande) & val) >> 30)| 0b1101); // set C flag
			*nzcv= *nzcv & (((((rn & shifter_operande) & ~val) | ((~rn & ~shifter_operande) & val)) >> 31)| 0b1110); // set V flag
			arm_write_register(p,rd,val);
			res = 1;
			break;

		case 7: // RSC reverse substract with carry
			val =  (shifter_operande - rn - (*nzcv & (0b0010>>1)));
			*nzcv= *nzcv & ((((~rn & ~shifter_operande) & val) >> 30)| 0b1101); // set C flag
			*nzcv= *nzcv & ((((rn & shifter_operande) & ~val) | ((~rn & ~shifter_operande) & val) >> 31)| 0b1110); // set V flag
			arm_write_register(p,rd,val);
			res = 1;
			break;

		case 8: //TST
			val = (rn & shifter_operande);
			*nzcv=*nzcv & ( (shifter_carry_out<<1) | 0b1101); // set C flag
			res = 1;	//V flag unaffected
			break;

		case 9: //TEQ
			val = (rn ^ shifter_operande);
			*nzcv=*nzcv & ( (shifter_carry_out<<1) | 0b1101); // set C flag
			res = 1;	//V flag unaffected
			break;

		case 10://CMP
			val =  (rn - shifter_operande);
			*nzcv= *nzcv & ((~( (~rn & ~shifter_operande) & val) >> 30)| 0b1101); // set C flag
			*nzcv= *nzcv & (((((rn & shifter_operande) & ~val) | ((~rn & ~shifter_operande) & val)) >> 31)| 0b1110); // set V flag
			res = 1;
			break;

		case 11://CMN
			val =  (rn + shifter_operande);
			*nzcv= *nzcv & ((((rn | shifter_operande) & ~val) >> 30)| 0b1101); // set C flag
			*nzcv= *nzcv & (((((rn & shifter_operande) & ~val) | ((~rn & ~shifter_operande) & val)) >> 31)| 0b1110); // set V flag
			res = 1;
			break;
		
		case 12: // ORR logical OR
			val =  (rn | shifter_operande);
			*nzcv=*nzcv & ((shifter_carry_out<<1) | 0b1101); // set C flag
			res = 1;	//V flag unaffected
			arm_write_register(p,rd,val);
			break;

		case 13: // MOV
			val =  shifter_operande;
			*nzcv=*nzcv & ((shifter_carry_out<<1) | 0b1101); // set C flag
			res = 1;	//V flag unaffected
			arm_write_register(p,rd,val);
			break;

		case 14: //BIC (rd = rn AND NOT shifter_operand)
			val =  (rn & ~shifter_operande);
			*nzcv=*nzcv & ((shifter_carry_out<<1) | 0b1101); // set C flag
			res = 1;	//V flag unaffected
			arm_write_register(p,rd,val);
			break;

		case 15: //MVN ( rd != NOT shifter_operand)
			val =  ~shifter_operande;
			*nzcv=*nzcv & ((shifter_carry_out<<1) | 0b1101); // set C flag
			res = 1;	//V flag unaffected
			arm_write_register(p,rd,val);
			break;

		default :
			res = -1;
			break;
	}
	*nzcv = (get_bit(val,31)<<3 | *nzcv); 	// set N flag
	if (val == 0){ 							// set Z flag
		*nzcv= (*nzcv | 0b0100); 
	}else{ 
		*nzcv= (*nzcv & 0b1011);
	}
	return res;

}
