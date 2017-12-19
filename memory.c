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
#include <stdlib.h>
#include <stdio.h>

#include "memory.h"
#include "util.h"

struct memory_data {
  uint8_t *memoire;
  size_t size;
  int is_big_endian;
};

memory memory_create(size_t size, int is_big_endian) {
    memory mem = malloc(sizeof(memory));
    if(mem){
      mem->memoire = malloc(size*sizeof(uint8_t));
      mem->size = size;
      mem->is_big_endian = is_big_endian;
      return mem;
    }else{
      return NULL;
    }

}

size_t memory_get_size(memory mem) {
  return mem->size;
}

void memory_destroy(memory mem) {
  free(mem);
}

int memory_read_byte(memory mem, uint32_t address, uint8_t *value) {
    if(address <=  (mem->size - sizeof(uint8_t) ) ) {
        *value = mem->memoire[address];
        return 0;
    }else{
      return -1;
    }
}

int memory_read_half(memory mem, uint32_t address, uint16_t *value) {
  if(mem->size < address - sizeof(uint16_t)) {
    uint16_t result;
    if( mem->is_big_endian){
      result = mem->memoire[address]<<8 | mem->memoire[address+1];
    }else{
      result = mem->memoire[address+1]<<8 | mem->memoire[address];
    }
      *value = result;
      return 0;
  }else{
    return -1;
  }

}

int memory_read_word(memory mem, uint32_t address, uint32_t *value) {
  if(address <=  (mem->size - sizeof(uint32_t) ) ) {
      uint32_t result;
    if( mem->is_big_endian){
        result = mem->memoire[address]<<24 | mem->memoire[address+1] << 16 |
         mem->memoire[address+2] << 8  | mem->memoire[address+3] ;
    }else{
      result = mem->memoire[address+3]<<24 | mem->memoire[address+2] << 16 |
       mem->memoire[address+1] << 8  | mem->memoire[address] ;
    }
      *value = result;
      return 0;
  }else{
    return -1;
  }
}

int memory_write_byte(memory mem, uint32_t address, uint8_t value) {
  if(address <=  (  mem->size - sizeof(uint8_t) ) ) {
      mem->memoire[address] = value;
      return 0;
  }else{
    return -1;
  }
}

int memory_write_half(memory mem, uint32_t address, uint16_t value) {
  if(address <=  (mem->size - sizeof(uint16_t) ) ) {
      
    if(mem->is_big_endian){
      value = reverse_2(value);
      
    }

      mem->memoire[address+1] = (((value) & 0xFF00)>>8) ;
      mem->memoire[address] = (value & 0xFF) ;
      return 0;
  }else{
    return -1;
  }
}

int memory_write_word(memory mem, uint32_t address, uint32_t value) {
  if( address <=  (mem->size - sizeof(uint32_t) ) ) {


    if(mem->is_big_endian){
      value = reverse_4(value);
    }
    mem->memoire[address+3] = (value >>24 )& 0xFF ;
    mem->memoire[address+2] = (value >>16 )& 0xFF ;
    mem->memoire[address+1] = (value >>8 )& 0xFF ;
    mem->memoire[address] = (value & 0xFF) ;
    return 0;
  }else{
    return -1;
  }
}
