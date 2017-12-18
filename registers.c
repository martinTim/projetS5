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
#include "registers.h"
#include "arm_constants.h"
#include <stdlib.h>

struct registers_data {
  uint32_t* R;
};

registers registers_create() {
    registers r = malloc(sizeof(registers));
    r->R = malloc(37*sizeof(uint32_t));
    return r;
}

void registers_destroy(registers r) {
  free(r);
}

/*
 16: mode User
 17: mode FIQ
 18: mode IRQ
 19: mode Supervisor
 23: mode Abort
 27: mode Undefined
 31: mode System
*/

uint8_t get_mode(registers r) {
  uint8_t masque = 0x1F;
  return (masque & r->R[16]);
}

int current_mode_has_spsr(registers r) {
  uint8_t mode = get_mode(r);
  return (mode != 16 && mode != 31);
}

int in_a_privileged_mode(registers r) {
  uint8_t mode = get_mode(r);
  return (mode != 16);
}

uint32_t read_register(registers r, uint8_t reg) {
    return r->R[reg];
}

uint32_t read_usr_register(registers r, uint8_t reg) {
    uint32_t value=0;
    if(! in_a_privileged_mode(reg)){
      return r->R[reg];
    }else{
      exit;
    }
}

uint32_t read_cpsr(registers r) {
    return r->R[16];
}

uint32_t read_spsr(registers r) {
  if(current_mode_has_spsr(r)){
      return r->R[17];
  }
}

void write_register(registers r, uint8_t reg, uint32_t value) {
  r->R[reg] = value;
}

void write_usr_register(registers r, uint8_t reg, uint32_t value) {
  if(! in_a_privileged_mode(reg)){
    r->R[reg] = value;
  }else{
    exit;
  }
}

void write_cpsr(registers r, uint32_t value) {
  r->R[16] = value;
}

void write_spsr(registers r, uint32_t value) {
    r->R[17] = value;
}
