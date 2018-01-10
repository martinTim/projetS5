
#include "arm_status_register_access.h"

int move_PSR_to_register(arm_core p, uint32_t ins) {

    if (condCode(p, ins)) {
        uint8_t rd = get_bits(ins, 15, 12);
        uint8_t r = get_bit(ins, 22);
        if (r) {
            arm_write_register(p, rd, arm_read_spsr(p));
        } else
            arm_write_register(p, rd, arm_read_cpsr(p));
    }
    return 1;
}
