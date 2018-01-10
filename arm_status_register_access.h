/* 
 * File:   arm_status_register_access.h
 * Author: liakopog
 *
 * Created on 9 janvier 2018, 14:12
 */

#ifndef ARM_STATUS_REGISTER_ACCESS_H
#define	ARM_STATUS_REGISTER_ACCESS_H
#include "arm_core.h"
#include "util.h"
#include "trace_location.h"

int move_PSR_to_register(arm_core p, uint32_t ins);

#endif	/* ARM_STATUS_REGISTER_ACCESS_H */

