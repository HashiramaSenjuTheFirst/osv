/*
 * Copyright (C) 2014 Huawei Technologies Duesseldorf GmbH
 *
 * This work is open source software, licensed under the terms of the
 * BSD license as described in the LICENSE file in the top-level directory.
 */

#include <osv/elf.hh>

namespace elf {

bool object::arch_relocate_rela(u32 type, u32 sym, void *addr,
                                Elf64_Sxword addend)
{
    switch (type) {
    case R_AARCH64_NONE:
    case R_AARCH64_NONE2:
        break;
    case R_AARCH64_ABS64:
        *static_cast<void**>(addr) = symbol(sym).relocated_addr() + addend;
        break;
    case R_AARCH64_COPY:
        abort();
        break;
    case R_AARCH64_GLOB_DAT:
    case R_AARCH64_JUMP_SLOT:
        *static_cast<void**>(addr) = symbol(sym).relocated_addr() + addend;
        break;
    case R_AARCH64_RELATIVE:
        *static_cast<void**>(addr) = _base + addend;
        break;
    case R_AARCH64_TLS_TPREL64:
        *static_cast<void**>(addr) = symbol(sym).relocated_addr() + addend;
        break;
    default:
        return false;
    }

    return true;
}

bool object::arch_relocate_jump_slot(u32 sym, void *addr, Elf64_Sxword addend)
{
    *static_cast<void**>(addr) = symbol(sym).relocated_addr() + addend;
    return true;
}

}
