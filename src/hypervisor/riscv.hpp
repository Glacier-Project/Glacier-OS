/*
 * RISCV emulator
 *
 * Copyright (c) 2016 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef RISCV_HPP
#define RISCV_HPP

#define XLEN 32

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "../api.hpp"
#include "syscall.hpp"

// uncomment this for an instruction trace and other debug outputs
//#define DEBUG_OUTPUT

// memory mapped registers
#define MTIME_ADDR 0x40000000
#define MTIMECMP_ADDR 0x40000008
#define UART_TX_ADDR 0x40002000
#define SYSCALL_ADDR 0x40004000

// emulator RAM
#define RAM_SIZE 0x8000
uint8_t ram[RAM_SIZE];

// special memory mapped registers
uint64_t mtime;
uint64_t mtimecmp;

// virtual start address for index 0 in the ram array
uint32_t ram_start;

// used when called from the compliance tests
uint32_t begin_signature = 0;
uint32_t end_signature = 0;

// is set to false to exit the emulator
bool machine_running = true;

// privilege levels
#define PRV_U 0
#define PRV_S 1
#define PRV_H 2
#define PRV_M 3

// CPU state
uint32_t pc;
uint32_t next_pc;
uint32_t insn;
uint32_t reg[32];

uint8_t priv = PRV_M; /* see PRV_x */
uint8_t mstatus_fs; /* MSTATUS_FS value */
uint8_t mxl; /* MXL field in MISA register */

uint64_t insn_counter;
int pending_exception; /* used during MMU exception handling */
uint32_t pending_tval;

/* CSRs */
uint32_t mstatus;
uint32_t mtvec;
uint32_t mscratch;
uint32_t mepc;
uint32_t mcause;
uint32_t mtval;
uint32_t mhartid; /* ro */
uint32_t misa;
uint32_t mie;
uint32_t mip;
uint32_t medeleg;
uint32_t mideleg;
uint32_t mcounteren;

uint32_t stvec;
uint32_t sscratch;
uint32_t sepc;
uint32_t scause;
uint32_t stval;
uint32_t satp;
uint32_t scounteren;
uint32_t load_res; /* for atomic LR/SC */

// exception causes
#define CAUSE_MISALIGNED_FETCH    0x0
#define CAUSE_FAULT_FETCH         0x1
#define CAUSE_ILLEGAL_INSTRUCTION 0x2
#define CAUSE_BREAKPOINT          0x3
#define CAUSE_MISALIGNED_LOAD     0x4
#define CAUSE_FAULT_LOAD          0x5
#define CAUSE_MISALIGNED_STORE    0x6
#define CAUSE_FAULT_STORE         0x7
#define CAUSE_USER_ECALL          0x8
#define CAUSE_SUPERVISOR_ECALL    0x9
#define CAUSE_HYPERVISOR_ECALL    0xa
#define CAUSE_MACHINE_ECALL       0xb
#define CAUSE_FETCH_PAGE_FAULT    0xc
#define CAUSE_LOAD_PAGE_FAULT     0xd
#define CAUSE_STORE_PAGE_FAULT    0xf
#define CAUSE_INTERRUPT  ((uint32_t)1 << 31)

/* misa CSR */
#define MCPUID_SUPER   (1 << ('S' - 'A'))
#define MCPUID_USER    (1 << ('U' - 'A'))
#define MCPUID_I       (1 << ('I' - 'A'))
#define MCPUID_M       (1 << ('M' - 'A'))
#define MCPUID_A       (1 << ('A' - 'A'))
#define MCPUID_F       (1 << ('F' - 'A'))
#define MCPUID_D       (1 << ('D' - 'A'))
#define MCPUID_Q       (1 << ('Q' - 'A'))
#define MCPUID_C       (1 << ('C' - 'A'))

#define MIP_USIP (1 << 0)
#define MIP_SSIP (1 << 1)
#define MIP_HSIP (1 << 2)
#define MIP_MSIP (1 << 3)
#define MIP_UTIP (1 << 4)
#define MIP_STIP (1 << 5)
#define MIP_HTIP (1 << 6)
#define MIP_MTIP (1 << 7)
#define MIP_UEIP (1 << 8)
#define MIP_SEIP (1 << 9)
#define MIP_HEIP (1 << 10)
#define MIP_MEIP (1 << 11)

/* mstatus CSR */

#define MSTATUS_SPIE_SHIFT 5
#define MSTATUS_MPIE_SHIFT 7
#define MSTATUS_SPP_SHIFT 8
#define MSTATUS_MPP_SHIFT 11
#define MSTATUS_mstatus_fs_SHIFT 13
#define MSTATUS_UXL_SHIFT 32
#define MSTATUS_SXL_SHIFT 34

#define MSTATUS_UIE (1 << 0)
#define MSTATUS_SIE (1 << 1)
#define MSTATUS_HIE (1 << 2)
#define MSTATUS_MIE (1 << 3)
#define MSTATUS_UPIE (1 << 4)
#define MSTATUS_SPIE (1 << MSTATUS_SPIE_SHIFT)
#define MSTATUS_HPIE (1 << 6)
#define MSTATUS_MPIE (1 << MSTATUS_MPIE_SHIFT)
#define MSTATUS_SPP (1 << MSTATUS_SPP_SHIFT)
#define MSTATUS_HPP (3 << 9)
#define MSTATUS_MPP (3 << MSTATUS_MPP_SHIFT)
#define MSTATUS_mstatus_fs (3 << MSTATUS_mstatus_fs_SHIFT)
#define MSTATUS_XS (3 << 15)
#define MSTATUS_MPRV (1 << 17)
#define MSTATUS_SUM (1 << 18)
#define MSTATUS_MXR (1 << 19)
#define MSTATUS_UXL_MASK ((uint64_t)3 << MSTATUS_UXL_SHIFT)
#define MSTATUS_SXL_MASK ((uint64_t)3 << MSTATUS_SXL_SHIFT)

int ctz32(uint32_t a)
{
    int i;
    if (a == 0)
        return 32;
    for(i = 0; i < 32; i++) {
        if ((a >> i) & 1)
            return i;
    }
    return 32;
}

#define SSTATUS_MASK0 (MSTATUS_UIE | MSTATUS_SIE |       \
                      MSTATUS_UPIE | MSTATUS_SPIE |     \
                      MSTATUS_SPP | \
                      MSTATUS_mstatus_fs | MSTATUS_XS | \
                      MSTATUS_SUM | MSTATUS_MXR)
#define SSTATUS_MASK SSTATUS_MASK0


#define MSTATUS_MASK (MSTATUS_UIE | MSTATUS_SIE | MSTATUS_MIE |      \
                      MSTATUS_UPIE | MSTATUS_SPIE | MSTATUS_MPIE |    \
                      MSTATUS_SPP | MSTATUS_MPP | \
                      MSTATUS_mstatus_fs | \
                      MSTATUS_MPRV | MSTATUS_SUM | MSTATUS_MXR)

/* cycle and insn counters */
#define COUNTEREN_MASK ((1 << 0) | (1 << 2))

/* return the complete mstatus with the SD bit */
uint32_t get_mstatus(uint32_t mask)
{
    uint32_t val;
    bool sd;
    val = mstatus | (mstatus_fs << MSTATUS_mstatus_fs_SHIFT);
    val &= mask;
    sd = ((val & MSTATUS_mstatus_fs) == MSTATUS_mstatus_fs) |
         ((val & MSTATUS_XS) == MSTATUS_XS);
    if (sd)
        val |= (uint32_t)1 << (XLEN - 1);
    return val;
}

void set_mstatus(uint32_t val)
{
    mstatus_fs = (val >> MSTATUS_mstatus_fs_SHIFT) & 3;

    uint32_t mask = MSTATUS_MASK & ~MSTATUS_mstatus_fs;
    mstatus = (mstatus & ~mask) | (val & mask);
}

void invalid_csr(uint32_t *pval, uint32_t csr)
{
    /* the 'time' counter is usually emulated */
    if (csr != 0xc01 && csr != 0xc81) {
#ifdef DEBUG_OUTPUT
        printf("csr_read: invalid CSR=0x%x\n", csr);
#endif
    }
    *pval = 0;
}

/* return -1 if invalid CSR. 0 if OK. 'will_write' indicate that the
   csr will be written after (used for CSR access check) */
int csr_read(uint32_t *pval, uint32_t csr,
             bool will_write)
{
    uint32_t val;

    if (((csr & 0xc00) == 0xc00) && will_write)
        return -1; /* read-only CSR */
    if (priv < ((csr >> 8) & 3))
        return -1; /* not enough priviledge */

    switch(csr) {
    case 0xc00: /* ucycle */
    case 0xc02: /* uinstret */
    {
        uint32_t counteren;
        if (priv < PRV_M) {
            if (priv < PRV_S)
                counteren = scounteren;
            else
                counteren = mcounteren;
            if (((counteren >> (csr & 0x1f)) & 1) == 0) {
                invalid_csr(pval, csr);
                return -1;
            }
        }
    }
    val = (int64_t)insn_counter;
    break;
    case 0xc80: /* mcycleh */
    case 0xc82: /* minstreth */
    {
        uint32_t counteren;
        if (priv < PRV_M) {
            if (priv < PRV_S)
                counteren = scounteren;
            else
                counteren = mcounteren;
            if (((counteren >> (csr & 0x1f)) & 1) == 0) {
                invalid_csr(pval, csr);
                return -1;
            }
        }
    }
    val = insn_counter >> 32;
    break;

    case 0x100:
        val = get_mstatus(SSTATUS_MASK);
        break;
    case 0x104: /* sie */
        val = mie & mideleg;
        break;
    case 0x105:
        val = stvec;
        break;
    case 0x106:
        val = scounteren;
        break;
    case 0x140:
        val = sscratch;
        break;
    case 0x141:
        val = sepc;
        break;
    case 0x142:
        val = scause;
        break;
    case 0x143:
        val = stval;
        break;
    case 0x144: /* sip */
        val = mip & mideleg;
        break;
    case 0x180:
        val = satp;
        break;
    case 0x300:
        val = get_mstatus((uint32_t)-1);
        break;
    case 0x301:
        val = misa;
        val |= (uint32_t)mxl << (XLEN - 2);
        break;
    case 0x302:
        val = medeleg;
        break;
    case 0x303:
        val = mideleg;
        break;
    case 0x304:
        val = mie;
        break;
    case 0x305:
        val = mtvec;
        break;
    case 0x306:
        val = mcounteren;
        break;
    case 0x340:
        val = mscratch;
        break;
    case 0x341:
        val = mepc;
        break;
    case 0x342:
        val = mcause;
        break;
    case 0x343:
        val = mtval;
        break;
    case 0x344:
        val = mip;
        break;
    case 0xb00: /* mcycle */
    case 0xb02: /* minstret */
        val = (int64_t)insn_counter;
        break;
    case 0xb80: /* mcycleh */
    case 0xb82: /* minstreth */
        val = insn_counter >> 32;
        break;
    case 0xf14:
        val = mhartid;
        break;
    default:
        invalid_csr(pval, csr);
        //return -1;
        return 0;
    }
    *pval = val;
    return 0;
}

/* return -1 if invalid CSR, 0 if OK, 1 if the interpreter loop must be
   exited (e.g. XLEN was modified), 2 if TLBs have been flushed. */
int csr_write(uint32_t csr, uint32_t val)
{
    uint32_t mask;

#if defined(DUMP_CSR)
    printf("csr_write: csr=0x%03x val=0x", csr);
    print_uint32_t(val);
    printf("\n");
#endif
    switch(csr) {
    case 0x100: /* sstatus */
        set_mstatus((mstatus & ~SSTATUS_MASK) | (val & SSTATUS_MASK));
        break;
    case 0x104: /* sie */
        mask = mideleg;
        mie = (mie & ~mask) | (val & mask);
        break;
    case 0x105:
        stvec = val & ~3;
        break;
    case 0x106:
        scounteren = val & COUNTEREN_MASK;
        break;
    case 0x140:
        sscratch = val;
        break;
    case 0x141:
        sepc = val & ~1;
        break;
    case 0x142:
        scause = val;
        break;
    case 0x143:
        stval = val;
        break;
    case 0x144: /* sip */
        mask = mideleg;
        mip = (mip & ~mask) | (val & mask);
        break;
    case 0x180:
        /* no ASID implemented */
    {
        int new_mode;
        new_mode = (val >> 31) & 1;
        satp = (val & (((uint32_t)1 << 22) - 1)) |
               (new_mode << 31);
    }
    return 2;

    case 0x300:
        set_mstatus(val);
        break;
    case 0x301: /* misa */
        break;
    case 0x302:
        mask = (1 << (CAUSE_STORE_PAGE_FAULT + 1)) - 1;
        medeleg = (medeleg & ~mask) | (val & mask);
        break;
    case 0x303:
        mask = MIP_SSIP | MIP_STIP | MIP_SEIP;
        mideleg = (mideleg & ~mask) | (val & mask);
        break;
    case 0x304:
        mask = MIP_MSIP | MIP_MTIP | MIP_SSIP | MIP_STIP | MIP_SEIP;
        mie = (mie & ~mask) | (val & mask);
        break;
    case 0x305:
        mtvec = val & ~3;
        break;
    case 0x306:
        mcounteren = val & COUNTEREN_MASK;
        break;
    case 0x340:
        mscratch = val;
        break;
    case 0x341:
        mepc = val & ~1;
        break;
    case 0x342:
        mcause = val;
        break;
    case 0x343:
        mtval = val;
        break;
    case 0x344:
        mask = MIP_SSIP | MIP_STIP;
        mip = (mip & ~mask) | (val & mask);
        break;
    default:
        return 0;
        // return -1;
    }
    return 0;
}

void handle_sret()
{
    int spp, spie;
    spp = (mstatus >> MSTATUS_SPP_SHIFT) & 1;
    /* set the IE state to previous IE state */
    spie = (mstatus >> MSTATUS_SPIE_SHIFT) & 1;
    mstatus = (mstatus & ~(1 << spp)) |
              (spie << spp);
    /* set SPIE to 1 */
    mstatus |= MSTATUS_SPIE;
    /* set SPP to U */
    mstatus &= ~MSTATUS_SPP;
    priv = spp;
    next_pc = sepc;
}

void handle_mret()
{
    int mpp, mpie;
    mpp = (mstatus >> MSTATUS_MPP_SHIFT) & 3;
    /* set the IE state to previous IE state */
    mpie = (mstatus >> MSTATUS_MPIE_SHIFT) & 1;
    mstatus = (mstatus & ~(1 << mpp)) |
              (mpie << mpp);
    /* set MPIE to 1 */
    mstatus |= MSTATUS_MPIE;
    /* set MPP to U */
    mstatus &= ~MSTATUS_MPP;
    priv = mpp;
    next_pc = mepc;
}


void raise_exception(uint32_t cause,
                     uint32_t tval)
{
    bool deleg;

    // exit for Zephyr applications
    if (cause == CAUSE_ILLEGAL_INSTRUCTION) {
        machine_running = false;
        return;
    }

    if (priv <= PRV_S) {
        /* delegate the exception to the supervisor priviledge */
        if (cause & CAUSE_INTERRUPT)
            deleg = (mideleg >> (cause & (XLEN - 1))) & 1;
        else
            deleg = (medeleg >> cause) & 1;
    } else {
        deleg = 0;
    }

    if (deleg) {
        scause = cause;
        sepc = pc;
        stval = tval;
        mstatus = (mstatus & ~MSTATUS_SPIE) |
                  (((mstatus >> priv) & 1) << MSTATUS_SPIE_SHIFT);
        mstatus = (mstatus & ~MSTATUS_SPP) |
                  (priv << MSTATUS_SPP_SHIFT);
        mstatus &= ~MSTATUS_SIE;
        priv = PRV_S;
        next_pc = stvec;
    } else {
        mcause = cause;
        mepc = pc;
        mtval = tval;
        mstatus = (mstatus & ~MSTATUS_MPIE) |
                  (((mstatus >> priv) & 1) << MSTATUS_MPIE_SHIFT);
        mstatus = (mstatus & ~MSTATUS_MPP) |
                  (priv << MSTATUS_MPP_SHIFT);
        mstatus &= ~MSTATUS_MIE;
        priv = PRV_M;
        next_pc = mtvec;
    }
}

uint32_t get_pending_irq_mask()
{
    uint32_t pending_ints, enabled_ints;

    pending_ints = mip & mie;
    if (pending_ints == 0)
        return 0;

    enabled_ints = 0;
    switch(priv) {
    case PRV_M:
        if (mstatus & MSTATUS_MIE)
            enabled_ints = ~mideleg;
        break;
    case PRV_S:
        enabled_ints = ~mideleg;
        if (mstatus & MSTATUS_SIE)
            enabled_ints |= mideleg;
        break;
    default:
    case PRV_U:
        enabled_ints = -1;
        break;
    }
    return pending_ints & enabled_ints;
}

int raise_interrupt()
{
    uint32_t mask;
    int irq_num;

    mask = get_pending_irq_mask();
    if (mask == 0)
        return 0;
    irq_num = ctz32(mask);
    raise_exception(irq_num | CAUSE_INTERRUPT, 0);
    return -1;
}

uint32_t get_insn32(uint32_t pc)
{
    uint32_t ptr = pc - ram_start;
    if (ptr > RAM_SIZE) return 1;
    uint8_t* p = ram + ptr;
    return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
}

int target_read_u8(uint8_t *pval, uint32_t addr)
{
    addr -= ram_start;
    if (addr > RAM_SIZE) {
        *pval = 0;
        printf("illegal read 8, PC: 0x%08x, address: 0x%08x\n", pc, addr + ram_start);
        return 1;
    } else {
        uint8_t* p = ram + addr;
        *pval = p[0];
    }
    return 0;
}

int target_read_u16(uint16_t *pval, uint32_t addr)
{
    if (addr & 1) {
        pending_exception = CAUSE_MISALIGNED_LOAD;
        pending_tval = addr;
        return 1;
    }
    addr -= ram_start;
    if (addr > RAM_SIZE)  {
        *pval = 0;
        printf("illegal read 16, PC: 0x%08x, address: 0x%08x\n", pc, addr + ram_start);
        return 1;
    } else {
        uint8_t* p = ram + addr;
        *pval = p[0] | (p[1] << 8);
    }
    return 0;
}

int target_read_u32(uint32_t *pval, uint32_t addr)
{
    if (addr & 3) {
        pending_exception = CAUSE_MISALIGNED_LOAD;
        pending_tval = addr;
        return 1;
    }
    if (addr == MTIMECMP_ADDR) {
        *pval = (uint32_t) mtimecmp;
    } else if (addr == MTIMECMP_ADDR + 4) {
        *pval = (uint32_t) (mtimecmp >> 32);
    } else if (addr == MTIME_ADDR) {
        *pval = (uint32_t) mtime;
    } else if (addr == MTIME_ADDR + 4) {
        *pval = (uint32_t) (mtime >> 32);
    } else {
        addr -= ram_start;
        if (addr > RAM_SIZE) {
            *pval = 0;
            printf("illegal read 32, PC: 0x%08x, address: 0x%08x\n", pc, addr + ram_start);
            return 1;
        } else {
            uint8_t* p = ram + addr;
            *pval = p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
        }
    }
    return 0;
}

int target_write_u8(uint32_t addr, uint8_t val)
{
    if (addr == UART_TX_ADDR) {
        // test for UART output, compatible with QEMU
        printf("%c", val);
    } else {
        addr -= ram_start;
        if (addr > RAM_SIZE - 1) {
            printf("illegal write 8, PC: 0x%08x, address: 0x%08x\n", pc, addr + ram_start);
            return 1;
        } else {
            uint8_t* p = ram + addr;
            p[0] = val & 0xff;
        }
    }
    return 0;
}

int target_write_u16(uint32_t addr, uint16_t val)
{
    if (addr & 1) {
        pending_exception = CAUSE_MISALIGNED_STORE;
        pending_tval = addr;
        return 1;
    }
    addr -= ram_start;
    if (addr > RAM_SIZE - 2) {
        printf("illegal write 16, PC: 0x%08x, address: 0x%08x\n", pc, addr + ram_start);
        return 1;
    } else {
        uint8_t* p = ram + addr;
        p[0] = val & 0xff;
        p[1] = (val >> 8) & 0xff;
    }
    return 0;
}

void write_mtimecmp(uint64_t value)
{
    mtimecmp = value;
    mip &= ~MIP_MTIP;
}

int target_write_u32(uint32_t addr, uint32_t val)
{
    if (addr & 3) {
        pending_exception = CAUSE_MISALIGNED_STORE;
        pending_tval = addr;
        return 1;
    }
    if (addr == MTIMECMP_ADDR) {
        write_mtimecmp((mtimecmp & 0xffffffff00000000ll) | val);
    } else if (addr == MTIMECMP_ADDR + 4) {
        write_mtimecmp((mtimecmp & 0xffffffffll) | (((uint64_t)val) << 32));
    } else if (addr == SYSCALL_ADDR) {
        system_call(val);
    } else {
        addr -= ram_start;
        if (addr > RAM_SIZE - 4)  {
            return 1;
        } else {
            uint8_t* p = ram + addr;
            p[0] = val & 0xff;
            p[1] = (val >> 8) & 0xff;
            p[2] = (val >> 16) & 0xff;
            p[3] = (val >> 24) & 0xff;
        }
    }
    return 0;
}

int32_t div32(int32_t a, int32_t b)
{
    if (b == 0) {
        return -1;
    } else if (a == ((int32_t)1 << (XLEN - 1)) && b == -1) {
        return a;
    } else {
        return a / b;
    }
}

uint32_t divu32(uint32_t a, uint32_t b)
{
    if (b == 0) {
        return -1;
    } else {
        return a / b;
    }
}

int32_t rem32(int32_t a, int32_t b)
{
    if (b == 0) {
        return a;
    } else if (a == ((int32_t)1 << (XLEN - 1)) && b == -1) {
        return 0;
    } else {
        return a % b;
    }
}

uint32_t remu32(uint32_t a, uint32_t b)
{
    if (b == 0) {
        return a;
    } else {
        return a % b;
    }
}

static uint32_t mulh32(int32_t a, int32_t b)
{
    return ((int64_t)a * (int64_t)b) >> 32;
}

static uint32_t mulhsu32(int32_t a, uint32_t b)
{
    return ((int64_t)a * (int64_t)b) >> 32;
}

static uint32_t mulhu32(uint32_t a, uint32_t b)
{
    return ((int64_t)a * (int64_t)b) >> 32;
}

/*
// dumps all registers, useful for in-depth debugging
static void dump_regs()
{
    printf("x0 zero: %08x\n", reg[0]);
    printf("x1 ra:   %08x\n", reg[1]);
    printf("x2 sp:   %08x\n", reg[2]);
    printf("x3 gp:   %08x\n", reg[3]);
    printf("x4 tp:   %08x\n", reg[4]);
    printf("x5 t0:   %08x\n", reg[5]);
    printf("x6 t1:   %08x\n", reg[6]);
    printf("x7 t2:   %08x\n", reg[7]);
    printf("x8 s0:   %08x\n", reg[8]);
    printf("x9 s1:   %08x\n", reg[9]);
    printf("x10 a0:  %08x\n", reg[10]);
    printf("x11 a1:  %08x\n", reg[11]);
    printf("x12 a2:  %08x\n", reg[12]);
    printf("x13 a3:  %08x\n", reg[13]);
    printf("x14 a4:  %08x\n", reg[14]);
    printf("x15 a5:  %08x\n", reg[15]);
    printf("x16 a6:  %08x\n", reg[16]);
    printf("x17 a7:  %08x\n", reg[17]);
    printf("x18 s2:  %08x\n", reg[18]);
    printf("x19 s3:  %08x\n", reg[19]);
    printf("x20 s4:  %08x\n", reg[20]);
    printf("x21 s5:  %08x\n", reg[21]);
    printf("x22 s6:  %08x\n", reg[22]);
    printf("x23 s7:  %08x\n", reg[23]);
    printf("x24 s8:  %08x\n", reg[24]);
    printf("x25 s9:  %08x\n", reg[25]);
    printf("x26 s10: %08x\n", reg[26]);
    printf("x27 s11: %08x\n", reg[27]);
    printf("x28 t3:  %08x\n", reg[28]);
    printf("x29 t4:  %08x\n", reg[29]);
    printf("x30 t5:  %08x\n", reg[30]);
    printf("x31 t6:  %08x\n", reg[31]);
}
*/

void execute_instruction()
{
    uint32_t opcode, rd, rs1, rs2, funct3;
    int32_t imm, cond, err;
    uint32_t addr, val, val2;

    opcode = insn & 0x7f;
    rd = (insn >> 7) & 0x1f;
    rs1 = (insn >> 15) & 0x1f;
    rs2 = (insn >> 20) & 0x1f;

    switch(opcode) {
    case 0x37: /* lui */
        if (rd != 0)
            reg[rd] = (int32_t)(insn & 0xfffff000);
        break;
    case 0x17: /* auipc */
        if (rd != 0)
            reg[rd] = (int32_t)(pc + (int32_t)(insn & 0xfffff000));
        break;
    case 0x6f: /* jal */
        imm = ((insn >> (31 - 20)) & (1 << 20)) |
              ((insn >> (21 - 1)) & 0x7fe) |
              ((insn >> (20 - 11)) & (1 << 11)) |
              (insn & 0xff000);
        imm = (imm << 11) >> 11;
        if (rd != 0)
            reg[rd] = pc + 4;
        next_pc = (int32_t)(pc + imm);
        break;
    case 0x67: /* jalr */
        imm = (int32_t)insn >> 20;
        val = pc + 4;
        next_pc = (int32_t)(reg[rs1] + imm) & ~1;
        if (rd != 0)
            reg[rd] = val;
        break;
    case 0x63:
        funct3 = (insn >> 12) & 7;
        switch(funct3 >> 1) {
        case 0: /* beq/bne */
            cond = (reg[rs1] == reg[rs2]);
            break;
        case 2: /* blt/bge */
            cond = ((int32_t)reg[rs1] < (int32_t)reg[rs2]);
            break;
        case 3: /* bltu/bgeu */
            cond = (reg[rs1] < reg[rs2]);
            break;
        default:
            raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
            return;
        }
        cond ^= (funct3 & 1);
        if (cond) {
            imm = ((insn >> (31 - 12)) & (1 << 12)) |
                  ((insn >> (25 - 5)) & 0x7e0) |
                  ((insn >> (8 - 1)) & 0x1e) |
                  ((insn << (11 - 7)) & (1 << 11));
            imm = (imm << 19) >> 19;
            next_pc = (int32_t)(pc + imm);
            break;
        }
        break;
    case 0x03: /* load */
        funct3 = (insn >> 12) & 7;
        imm = (int32_t)insn >> 20;
        addr = reg[rs1] + imm;
        switch(funct3) {
        case 0: /* lb */
        {
            uint8_t rval;
            if (target_read_u8(&rval, addr)) {
                raise_exception(pending_exception, pending_tval);
                return;
            }
            val = (int8_t)rval;
        }
        break;
        case 1: /* lh */
        {
            uint16_t rval;
            if (target_read_u16(&rval, addr)) {
                raise_exception(pending_exception, pending_tval);
                return;
            }
            val = (int16_t)rval;
        }
        break;
        case 2: /* lw */
        {
            uint32_t rval;
            if (target_read_u32(&rval, addr)) {
                raise_exception(pending_exception, pending_tval);
                return;
            }
            val = (int32_t)rval;
        }
        break;
        case 4: /* lbu */
        {
            uint8_t rval;
            if (target_read_u8(&rval, addr)) {
                raise_exception(pending_exception, pending_tval);
                return;
            }
            val = rval;
        }
        break;
        case 5: /* lhu */
        {
            uint16_t rval;
            if (target_read_u16(&rval, addr)) {
                raise_exception(pending_exception, pending_tval);
                return;
            }
            val = rval;
        }
        break;
        default:
            raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
            return;
        }
        if (rd != 0)
            reg[rd] = val;
        break;
    case 0x23: /* store */
        funct3 = (insn >> 12) & 7;
        imm = rd | ((insn >> (25 - 5)) & 0xfe0);
        imm = (imm << 20) >> 20;
        addr = reg[rs1] + imm;
        val = reg[rs2];
        switch(funct3) {
        case 0: /* sb */
            if (target_write_u8(addr, val)) {
                raise_exception(pending_exception, pending_tval);
                return;
            }
            break;
        case 1: /* sh */
            if (target_write_u16(addr, val)) {
                raise_exception(pending_exception, pending_tval);
                return;
            }
            break;
        case 2: /* sw */
            if (target_write_u32(addr, val)) {
                raise_exception(pending_exception, pending_tval);
                return;
            }
            break;
        default:
            raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
            return;
        }
        break;
    case 0x13:
        funct3 = (insn >> 12) & 7;
        imm = (int32_t)insn >> 20;
        switch(funct3) {
        case 0: /* addi */
            val = (int32_t)(reg[rs1] + imm);
            break;
        case 1: /* slli */
            if ((imm & ~(XLEN - 1)) != 0) {
                raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                return;
            }
            val = (int32_t)(reg[rs1] << (imm & (XLEN - 1)));
            break;
        case 2: /* slti */
            val = (int32_t)reg[rs1] < (int32_t)imm;
            break;
        case 3: /* sltiu */
            val = reg[rs1] < (uint32_t)imm;
            break;
        case 4: /* xori */
            val = reg[rs1] ^ imm;
            break;
        case 5: /* srli/srai */
            if ((imm & ~((XLEN - 1) | 0x400)) != 0) {
                raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                return;
            }
            if (imm & 0x400)
                val = (int32_t)reg[rs1] >> (imm & (XLEN - 1));
            else
                val = (int32_t)((uint32_t)reg[rs1] >> (imm & (XLEN - 1)));
            break;
        case 6: /* ori */
            val = reg[rs1] | imm;
            break;
        default:
        case 7: /* andi */
            val = reg[rs1] & imm;
            break;
        }
        if (rd != 0)
            reg[rd] = val;
        break;
    case 0x33:
        imm = insn >> 25;
        val = reg[rs1];
        val2 = reg[rs2];
        if (imm == 1) {
            funct3 = (insn >> 12) & 7;
            switch(funct3) {
            case 0: /* mul */
                val = (int32_t)((int32_t)val * (int32_t)val2);
                break;
            case 1: /* mulh */
                val = (int32_t)mulh32(val, val2);
                break;
            case 2:/* mulhsu */
                val = (int32_t)mulhsu32(val, val2);
                break;
            case 3:/* mulhu */
                val = (int32_t)mulhu32(val, val2);
                break;
            case 4:/* div */
                val = div32(val, val2);
                break;
            case 5:/* divu */
                val = (int32_t)divu32(val, val2);
                break;
            case 6:/* rem */
                val = rem32(val, val2);
                break;
            case 7:/* remu */
                val = (int32_t)remu32(val, val2);
                break;
            default:
                raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                return;
            }
        } else {
            if (imm & ~0x20) {
                raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                return;
            }
            funct3 = ((insn >> 12) & 7) | ((insn >> (30 - 3)) & (1 << 3));
            switch(funct3) {
            case 0: /* add */
                val = (int32_t)(val + val2);
                break;
            case 0 | 8: /* sub */
                val = (int32_t)(val - val2);
                break;
            case 1: /* sll */
                val = (int32_t)(val << (val2 & (XLEN - 1)));
                break;
            case 2: /* slt */
                val = (int32_t)val < (int32_t)val2;
                break;
            case 3: /* sltu */
                val = val < val2;
                break;
            case 4: /* xor */
                val = val ^ val2;
                break;
            case 5: /* srl */
                val = (int32_t)((uint32_t)val >> (val2 & (XLEN - 1)));
                break;
            case 5 | 8: /* sra */
                val = (int32_t)val >> (val2 & (XLEN - 1));
                break;
            case 6: /* or */
                val = val | val2;
                break;
            case 7: /* and */
                val = val & val2;
                break;
            default:
                raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                return;
            }
        }
        if (rd != 0)
            reg[rd] = val;
        break;
    case 0x73:
        funct3 = (insn >> 12) & 7;
        imm = insn >> 20;
        if (funct3 & 4)
            val = rs1;
        else
            val = reg[rs1];
        funct3 &= 3;
        switch(funct3) {
        case 1: /* csrrw */
            if (csr_read(&val2, imm, true)) {
                raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                return;
            }
            val2 = (int32_t)val2;
            err = csr_write(imm, val);
            if (err < 0) {
                raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                return;
            }
            if (rd != 0)
                reg[rd] = val2;
            if (err > 0) {
                //pc = pc + 4;
            }
            break;
        case 2: /* csrrs */
        case 3: /* csrrc */
            if (csr_read(&val2, imm, (rs1 != 0))) {
                raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                return;
            }
            val2 = (int32_t)val2;
            if (rs1 != 0) {
                if (funct3 == 2)
                    val = val2 | val;
                else
                    val = val2 & ~val;
                err = csr_write(imm, val);
                if (err < 0) {
                    raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                    return;
                }
            } else {
                err = 0;
            }
            if (rd != 0)
                reg[rd] = val2;
            break;
        case 0:
            switch(imm) {
            case 0x000: /* ecall */
                if (insn & 0x000fff80) {
                    raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                    return;
                }
                // compliance test specific: if bit 0 of gp (x3) is 0, it is a syscall,
                // otherwise it is the program end, with the exit code in the bits 31:1
                if (begin_signature) {
                    if (reg[3] & 1) {
#ifdef DEBUG_OUTPUT
                        printf("program end, result: %04x\n", reg[3] >> 1);
#endif
                        machine_running = false;
                        return;
                    } else {
#ifdef DEBUG_OUTPUT
                        printf("syscall: %04x\n", reg[3]);
#endif
                        raise_exception(CAUSE_USER_ECALL + priv, 0);
                    }
                } else {
                    // on real hardware, an exception is raised, the I-ECALL-01 compliance test tests this as well
                    raise_exception(CAUSE_USER_ECALL + priv, 0);
                    return;
                }
                break;

            case 0x001: /* ebreak */
                if (insn & 0x000fff80) {
                    raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                    return;
                }
                raise_exception(CAUSE_BREAKPOINT, 0);
                return;
            case 0x102: /* sret */
            {
                if ((insn & 0x000fff80) || (priv < PRV_S)) {
                    raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                    return;
                }
                handle_sret();
                return;
            }
            break;
            case 0x105: /* wfi */
                // wait for interrupt: it is allowed to execute it as nop
                break;
            case 0x302: /* mret */
            {
                if ((insn & 0x000fff80) || (priv < PRV_M)) {
                    raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                    return;
                }
                handle_mret();
                return;
            }
            break;
            default:
                if ((imm >> 5) == 0x09) {
                    /* sfence.vma */
                    if ((insn & 0x00007f80) || (priv == PRV_U)) {
                        raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                        return;
                    }
                } else {
                    raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                    return;
                }
                break;
            }
            break;
        default:
            raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
            return;
        }
        break;
    case 0x0f: /* misc-mem */
        funct3 = (insn >> 12) & 7;
        switch(funct3) {
        case 0: /* fence */
            if (insn & 0xf00fff80) {
                raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                return;
            }
            break;
        case 1: /* fence.i */
            if (insn != 0x0000100f) {
                raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                return;
            }
            break;
        default:
            raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
            return;
        }
        break;
    case 0x2f:
        funct3 = (insn >> 12) & 7;
        switch(funct3) {
        case 2:
        {
            uint32_t rval;

            addr = reg[rs1];
            funct3 = insn >> 27;
            switch(funct3) {
            case 2: /* lr.w */
                if (rs2 != 0) {
                    raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                    return;
                }
                if (target_read_u32(&rval, addr)) {
                    raise_exception(pending_exception, pending_tval);
                    return;
                }
                val = (int32_t)rval;
                load_res = addr;
                break;
            case 3: /* sc.w */
                if (load_res == addr) {
                    if (target_write_u32(addr, reg[rs2])) {
                        raise_exception(pending_exception, pending_tval);
                        return;
                    }
                    val = 0;
                } else {
                    val = 1;
                }
                break;
            case 1: /* amiswap.w */
            case 0: /* amoadd.w */
            case 4: /* amoxor.w */
            case 0xc: /* amoand.w */
            case 0x8: /* amoor.w */
            case 0x10: /* amomin.w */
            case 0x14: /* amomax.w */
            case 0x18: /* amominu.w */
            case 0x1c: /* amomaxu.w */
                if (target_read_u32(&rval, addr)) {
                    raise_exception(pending_exception, pending_tval);
                    return;
                }
                val = (int32_t)rval;
                val2 = reg[rs2];
                switch(funct3) {
                case 1: /* amiswap.w */
                    break;
                case 0: /* amoadd.w */
                    val2 = (int32_t)(val + val2);
                    break;
                case 4: /* amoxor.w */
                    val2 = (int32_t)(val ^ val2);
                    break;
                case 0xc: /* amoand.w */
                    val2 = (int32_t)(val & val2);
                    break;
                case 0x8: /* amoor.w */
                    val2 = (int32_t)(val | val2);
                    break;
                case 0x10: /* amomin.w */
                    if ((int32_t)val < (int32_t)val2)
                        val2 = (int32_t)val;
                    break;
                case 0x14: /* amomax.w */
                    if ((int32_t)val > (int32_t)val2)
                        val2 = (int32_t)val;
                    break;
                case 0x18: /* amominu.w */
                    if ((uint32_t)val < (uint32_t)val2)
                        val2 = (int32_t)val;
                    break;
                case 0x1c: /* amomaxu.w */
                    if ((uint32_t)val > (uint32_t)val2)
                        val2 = (int32_t)val;
                    break;
                default:
                    raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                    return;
                }
                if (target_write_u32(addr, val2)) {
                    raise_exception(pending_exception, pending_tval);
                    return;
                }
                break;
            default:
                raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
                return;
            }
        }
        break;
        default:
            raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
            return;
        }
        if (rd != 0)
            reg[rd] = val;
        break;
    default:
        raise_exception(CAUSE_ILLEGAL_INSTRUCTION, insn);
        return;
    }
}

// returns realtime in nanoseconds
int64_t get_clock()
{
    return get_nanos();
}


void riscv_cpu_interp_x32()
{
    /* we use a single execution loop to keep a simple control flow
       for emscripten */
    while (machine_running) {
        // update timer, assuming 10 MHz clock (100 ns period) for the mtime counter
        mtime = get_clock() / 100ll;

        // for reproducible debug runs, you can use a fixed fixed increment per instruction
        //mtime += 10;

        // default value for next PC is next instruction, can be changed by branches or exceptions
        next_pc = pc + 4;

        // test for timer interrupt
        if (mtimecmp <= mtime) {
            mip |= MIP_MTIP;
        }
        if ((mip & mie) != 0 && (mstatus & MSTATUS_MIE)) {
            raise_interrupt();
        } else {
            // normal instruction execution
            insn = get_insn32(pc);
            insn_counter++;

#ifdef DEBUG_OUTPUT
            printf("%08x, mtime: %08x, mtimecmp: %08x\n", pc, mtime, mtimecmp);
#endif
            execute_instruction();
        }

        // test for misaligned fetches
        if (next_pc & 3) {
            raise_exception(CAUSE_MISALIGNED_FETCH, next_pc);
        }

        // update current PC
        pc = next_pc;
    }

#ifdef DEBUG_OUTPUT
    printf("done interp %lx int=%x mstatus=%lx prv=%d\n",
           (uint64_t)insn_counter, mip & mie, (uint64_t)mstatus,
           priv);
#endif
}

#endif