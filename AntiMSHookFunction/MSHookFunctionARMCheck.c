//
//  MSHookFunctionARMCheck.c
//  AntiMSHook
//
//  Created by jintao on 2019/9/18.
//  Copyright © 2019 jintao. All rights reserved.
//

#include "MSHookFunctionARMCheck.h"

__attribute__ ((always_inline))
_Bool MSHookARMCheck(void *symbol_addr) {
    uint32_t *arms = (uint32_t *)symbol_addr;
        
    // first_instruction (C4.4.5 and C6.2.84, ARM® Architecture Reference Manual)
    uint32_t first_instruction = *arms;
    int ldr = (first_instruction & (255 << 24)) >> 24;
    int rt = first_instruction & 31;
    int imm19Mask = ((1 << 19) - 1) << 5;
    int imm19 = (first_instruction & imm19Mask) >> 5;
    
    _Bool ldr_x16 = 0;
    if ((ldr == 0b01011000) && (rt == 16) && ((imm19 << 2) == 8)) {
        ldr_x16 = 1;
    }
    
    // second_instruction
    uint32_t second_instruction = *(arms+1);
    int br = second_instruction >> 10;
    int br_rn = (second_instruction & (31 << 5)) >> 5;
    
    _Bool br_x16 = 0;
    if (br == 0b1101011000011111000000 && br_rn == 16) {
        br_x16 = 1;
    }
    
    return ldr_x16 && br_x16;
}
