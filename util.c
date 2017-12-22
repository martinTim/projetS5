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
#include "util.h"

/* We implement asr because shifting a signed is non portable in ANSI C */
uint32_t asr(uint32_t value, uint8_t shift) { 
    return (value >> shift) | (get_bit(value, 31) ? ~0<<(32-shift) : 0);
}

uint32_t ror(uint32_t value, uint8_t rotation) {
    return (value >> rotation) | (value << (32-rotation));
}

int is_big_endian() {
    static uint32_t one = 1;
    return ((* (uint8_t *) &one) == 0);
}

int shift(uint32_t *rm, uint8_t shift_type, uint32_t val_shift){
	int c = 0;
	int i;
	switch(shift_type){
		case 0: // logical shift left
			for(i=0;i<val_shift;i++){
				c = c + get_bit(*rm,31);
				*rm = *rm << 1;
			}
			break;
		case 1: // logical shift right
			*rm = *rm >> val_shift;
			break;
		case 2:  // arithmetic shift right
			*rm = asr(*rm, val_shift);
			break;
		case 3: // rotation tight
			*rm = ror(*rm, val_shift);
			break;
	}
	return c;
}