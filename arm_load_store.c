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
#include "arm_load_store.h"
#include "arm_exception.h"
#include "arm_constants.h"
#include "util.h"
#include "debug.h"

int arm_load_store(arm_core p, uint32_t ins) {
    uint8_t pBit = get_bit(ins,24);
    uint8_t w = get_bit(ins,21);
 
    uint8_t imm_offset = get_bit(ins,25);
    uint8_t u = get_bit(ins,23);
    uint8_t l = get_bit(ins,20);
    uint8_t b = get_bit(ins,22);
    uint8_t h = get_bit(ins,26);

    uint8_t rn = get_bits(ins,19,16); 
    uint32_t rn_val = arm_read_register(p,rn);
    uint8_t rd = get_bits(ins,15,12); 
    uint32_t offset = get_bits(ins,11,0);
    uint32_t address =0 ;
    
    printf("load / store \n");
   

    if(!imm_offset && h){// Feuille 1
     printf("load / store test 1 \n");
        if(!pBit && !w ){
            address = rn_val;
        }

        if(u){
            address = rn_val + offset;
        }else{
            address = rn_val - offset;
        }
      
    //CONDCODE ici

        if(pBit && w ){
            arm_write_register(p,rn,address);
        }


      /*  if(rn == 15 && ( pBit && !w )) {
            return -1; // UNPREDICTTABLE
        }
        }else{
             address += 8;
        }
        */


    }else{// feuille 2 ET 3
        printf("load / store test 2\n ");
        uint8_t shift_imm = get_bits(ins,11,7);
        uint32_t val_shift = arm_read_register(p,shift_imm);
        uint8_t shift_type = get_bits(ins,6,5);
        uint8_t rm = get_bits(ins,3,0);
        offset = arm_read_register(p,rm);
        if(!pBit && !w ){
            address = rn_val;
        }

        shift(&offset,shift_type,val_shift);

        if(u){
            address = rn_val + offset;
        }else{
            address = rn_val - offset;
        }
        //CONDCODE ici
        if(pBit && w ){
            arm_write_register(p,rn,address);
        }

    }
            printf(" offset ---- %x \n",offset);



    if(!h){//LOAD OUR STORE HALF WORD
        uint16_t data;
        printf("load / str un 1/2 mot  \n ");
        if(l){//load
            arm_read_half(p,address,&data);
            arm_write_register(p,rd,data);
        }else{//store
            printf(" address ---- %x \n",address);
            data =  arm_read_register(p,rd);
            arm_write_half(p,address,data);
        }

    }else if(b){//LOAD OU STORE 1 octet 
        printf("load / str un octet \n ");
        uint8_t data; 

        if(l){//load
            arm_read_byte(p,address,&data);
            arm_write_register(p,rd,data);
        }else{//store
            data =  arm_read_register(p,rd);
        //     printf(" st ---- %d\n",data);
            arm_write_byte(p,address,data);
        }

    }else{//LOAD OU STORE 1 MOT
    //    printf("load / str un mot \n ");
        uint32_t data;
        if(l){//load
            arm_read_word(p,address,&data);
            arm_write_register(p,rd,data);
        }else{//store
            data =  arm_read_register(p,rd);
            arm_write_word(p,address,data);
        }

    }

    return 0;
}

int arm_load_store_multiple(arm_core p, uint32_t ins) {


    uint8_t pBit            = get_bit(ins,24);
    uint8_t u               = get_bit(ins,23);
    uint8_t w               = get_bit(ins,21);
    uint8_t l               = get_bit(ins,20);
    uint8_t rn              = get_bits(ins,19,16); 
    uint32_t rn_val         = arm_read_register(p,rn);
    uint16_t register_list  = get_bits(ins,15,0);
    uint32_t start_address;
    uint32_t end_address; 
    uint32_t address; 
    uint32_t data;
    int res = 0;
    int i;
    int cpt = 0;
    //conde code !!!!!!!

    for(i = 0; i <= 15; i++ ){
        if (get_bit(register_list, i)){
           cpt ++;
        }        
    }

    if(pBit){
        if(u){
            start_address = rn_val + 4;
            end_address   = rn_val + (cpt * 4);
            if(w){
                rn_val  = rn_val + (cpt * 4);
            }

        }else{
            start_address = rn_val - (cpt * 4);
            end_address   = rn_val - 4 ;
            if(w){
                rn_val  = rn_val - (cpt * 4);
            }
        }
    }else{
         if(u){
            start_address = rn_val;
            end_address  = rn_val + (cpt * 4) - 4;
            if(w){
                rn_val = rn_val + (cpt * 4);
            }
         }else{
            start_address = rn_val -(cpt * 4) + 4;
            end_address  = rn_val;
            if(w){
                rn_val = rn_val - (cpt * 4);
            }
         }

    }

    arm_write_register(p,rn,rn_val);


   
    address = start_address;

    if(l){//load 
        for(i = 0; i <= 14; i++ ){
            if (get_bit(register_list, i)){
                arm_read_word(p,address,&data);
                arm_write_register(p,i,data);
                address = address + 4;
            }
        }

        if(get_bit(register_list,15)){
            arm_read_word(p,address,&data);
            arm_write_register(p,15,data & 0xFFFFFFFE);
            address = address + 4;
        }

        res = end_address == (address - 4);

    }else{//store

        for(i = 0; i <= 15; i++ ){
            if (get_bit(register_list, i)){
                data = arm_read_register(p,i);
                arm_write_word(p,address,data);
                address = address + 4;
            }        
        }

        res = end_address == (address - 4);

    }
    return res;
}

int arm_coprocessor_load_store(arm_core p, uint32_t ins) {
    /* Not implemented */
    return UNDEFINED_INSTRUCTION;
}
