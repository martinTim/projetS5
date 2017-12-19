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
#include <stdio.h>
#include <stdlib.h>
#include "registers.h"
#include "util.h"


int main() {

    registers r = registers_create();


    write_register(r,16,16);

    uint8_t mode = get_mode(r);

    if(mode == 16 ){
        printf("MODE OK\n");
    }else{
        printf("MODE NOK\n");
    }

    uint32_t lecture = read_register(r,16);

    if( lecture == 16){
        printf("LECTURE OK\n");
    }else{
        printf("LECTURE NOK\n");
    }

    uint32_t cpsr = read_cpsr(r);

    if( cpsr == lecture){
        printf("read cpsr OK\n");
    }else{
        printf("read cpsr NOK %x \n",cpsr);
    }






    registers_destroy(r);
    return 0;
}
