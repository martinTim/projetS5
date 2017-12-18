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
#include "memory.h"
#include "util.h"

struct memory_data {
  uint32_t *memoire;
  size_t size;
  int is_big_endian;
};

memory memory_create(size_t size, int is_big_endian) {
    memory mem= malloc(sizeof(memory));
    if(mem){
      mem->memoire = malloc(size*sizeof(uint32_t));
      mem->size = size;
      mem->is_big_endian = is_big_endian;
      return mem;
    }else{
      exit;
    }
}

size_t memory_get_size(memory mem) {
  return mem->size;
}

void memory_destroy(memory mem) {
  free(mem);
}

int memory_read_byte(memory mem, uint32_t address, uint8_t *value) {
    if(mem->memoire + address <=  ( mem->memoire + mem->size - sizeof(uint8_t) ) ) {
        uint8_t * result = mem->memoire + address;
        value = result;
        return 0;
    }else{
      return -1;
    }
}

int memory_read_half(memory mem, uint32_t address, uint16_t *value) {
  if(mem->memoire + address <=  ( mem->memoire + mem->size - sizeof(uint16_t) ) ) {
    uint16_t * result;
    if( mem->is_big_endian){
      result = mem->memoire + address;
    }else{
      result = ((uint16_t)(mem->memoire + address)<<8) | ((uint16_t)(mem->memoire + address)>>8);
    }
      value = result;
      return 0;
  }else{
    return -1;
  }

}

int memory_read_word(memory mem, uint32_t address, uint32_t *value) {
  if(mem->memoire + address <=  ( mem->memoire + mem->size - sizeof(uint32_t) ) ) {
      uint32_t * result;
    if( mem->is_big_endian){
      result = mem->memoire + address;
    }else{
      uint32_t masque = 0x000000FF;
      uint32_t * tmp = mem->memoire + address;
     result= (masque & (uint32_t)tmp>>24)
      + ((masque<<8) & (uint32_t)tmp>>8)
      + ((masque<<8) & (uint32_t)tmp<<8)
      + ((masque<<8) & (uint32_t)tmp<< 24);
    }
      value = result;
      return 0;
  }else{
    return -1;
  }
}

int memory_write_byte(memory mem, uint32_t address, uint8_t value) {
  if(mem->memoire + address <=  ( mem->memoire + mem->size - sizeof(uint8_t) ) ) {
      uint8_t * result = mem->memoire + address;
      result = value;
      return 0;
  }else{
    return -1;
  }
}

int memory_write_half(memory mem, uint32_t address, uint16_t value) {
  if(mem->memoire + address <=  ( mem->memoire + mem->size - sizeof(uint16_t) ) ) {
      uint16_t * result = mem->memoire + address;
      result = value;
      return 0;
  }else{
    return -1;
  }
}

int memory_write_word(memory mem, uint32_t address, uint32_t value) {
  if(mem->memoire + address <=  ( mem->memoire + mem->size - sizeof(uint32_t) ) ) {
      uint32_t * result = mem->memoire + address;
      result = value;
      return 0;
  }else{
    return -1;
  }
}
