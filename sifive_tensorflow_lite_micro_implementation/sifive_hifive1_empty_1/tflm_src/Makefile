PROGRAM = tflm
TARGET = sifive-hifive1

###################################################
# Build Flags for the Debug Configuration
###################################################

# Set the optimization level
RISCV_ASFLAGS += -O0
RISCV_CFLAGS += -O0
RISCV_CXXFLAGS += -O0

# Enable debug
RISCV_ASFLAGS += -g
RISCV_CFLAGS += -g
RISCV_CXXFLAGS += -g


# The configuration defaults to Debug. Valid choices are:
#   - debug
#   - release
CONFIGURATION ?= release

RISCV_ARCH = rv32imac_zicsr_zifencei
RISCV_ABI = ilp32
RISCV_CMODEL = medlow
RISCV_SERIES = sifive-3-series

TARGET_TAGS = board openocd
TARGET_DHRY_ITERS = 20000000
TARGET_CORE_ITERS = 5000
TARGET_FREERTOS_WAIT_MS = 1000
TARGET_INTR_WAIT_CYCLE  = 0

ifeq ($(RISCV_LIBC),)
RISCV_LIBC=nano
endif

#############################################################
# Toolchain
#############################################################

# Allow users to select a different cross compiler.
CROSS_COMPILE ?= riscv64-unknown-elf

# If users don't specify RISCV_PATH then assume that the tools will just be in
# their path.
ifeq ($(RISCV_PATH),)
RISCV_GCC     := $(CROSS_COMPILE)-gcc
RISCV_GXX     := $(CROSS_COMPILE)-g++
RISCV_OBJDUMP := $(CROSS_COMPILE)-objdump
RISCV_OBJCOPY := $(CROSS_COMPILE)-objcopy
RISCV_GDB     := $(CROSS_COMPILE)-gdb
RISCV_AR      := $(CROSS_COMPILE)-ar
RISCV_SIZE    := $(CROSS_COMPILE)-size
else
RISCV_GCC     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-gcc)
RISCV_GXX     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-g++)
RISCV_OBJDUMP := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-objdump)
RISCV_OBJCOPY := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-objcopy)
RISCV_GDB     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-gdb)
RISCV_AR      := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-ar)
RISCV_SIZE    := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-size)
PATH          := $(abspath $(RISCV_PATH)/bin):$(PATH)
endif

SEGGER_JLINK_EXE := JLinkExe
SEGGER_JLINK_GDB_SERVER := JLinkGDBServer

QEMU_RISCV32 = qemu-system-riscv32
QEMU_RISCV64 = qemu-system-riscv64

#############################################################
# Software Flags
#############################################################

# Set the arch, ABI, and code model
RISCV_CCASFLAGS += -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=$(RISCV_CMODEL)
RISCV_CFLAGS    += -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=$(RISCV_CMODEL)
RISCV_CXXFLAGS  += -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=$(RISCV_CMODEL)
RISCV_ASFLAGS   += -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=$(RISCV_CMODEL)
# Prune unused functions and data
ifeq ($(RISCV_SERIES),sifive-8-series)
ifeq ($(PROGRAM),dhrystone)
RISCV_CFLAGS   += -fno-function-sections -fno-data-sections
RISCV_CXXFLAGS += -fno-function-sections -fno-data-sections
else
RISCV_CFLAGS   += -ffunction-sections -fdata-sections
RISCV_CXXFLAGS += -ffunction-sections -fdata-sections
endif
else
RISCV_CFLAGS   += -ffunction-sections -fdata-sections
RISCV_CXXFLAGS += -ffunction-sections -fdata-sections
endif
# Include the Metal headers
RISCV_CCASFLAGS += -I$(abspath $(BSP_DIR)/install/include/)
RISCV_CFLAGS    += -I$(abspath $(BSP_DIR)/install/include/)
RISCV_CXXFLAGS  += -I$(abspath $(BSP_DIR)/install/include/)
# Reference selected library
RISCV_ASFLAGS   += --specs=$(SPEC).specs
RISCV_CCASFLAGS += --specs=$(SPEC).specs
RISCV_CFLAGS    += --specs=$(SPEC).specs
RISCV_CXXFLAGS  += --specs=$(SPEC).specs
# Set the MTIME frequency
RISCV_CFLAGS    += -DMTIME_RATE_HZ_DEF=$(MTIME_RATE_HZ_DEF)
RISCV_CXXFLAGS  += -DMTIME_RATE_HZ_DEF=$(MTIME_RATE_HZ_DEF)

RISCV_CFLAGS    += -fcommon

# Turn on garbage collection for unused sections
RISCV_LDFLAGS += -Wl,--gc-sections
# Turn on linker map file generation
RISCV_LDFLAGS += -Wl,-Map,$(PROGRAM).map
# Turn off the C standard library
RISCV_LDFLAGS += -nostartfiles -nostdlib
# Find the archive files and linker scripts
RISCV_LDFLAGS += -L$(sort $(dir $(abspath $(filter %.a,$^)))) -T$(abspath $(filter %.lds,$^))

# Link to the relevant libraries
RISCV_LDLIBS += -Wl,--start-group -lc -lgcc -lm -lmetal $(LIBMETAL_EXTRA) -Wl,--end-group

# Load the configuration Makefile
CONFIGURATION_FILE = $(wildcard $(CONFIGURATION).mk)
ifeq ($(words $(CONFIGURATION_FILE)),0)
$(error Unable to find the Makefile $(CONFIGURATION).mk for CONFIGURATION=$(CONFIGURATION))
endif
include $(CONFIGURATION).mk

# Load the instantiation Makefile
INSTANTIATION_FILE = $(wildcard $(SRC_DIR)/options.mk)
ifneq ($(words $(INSTANTIATION_FILE)),0)
include $(SRC_DIR)/options.mk
endif

# Benchmark CFLAGS go after loading the CONFIGURATION so that they can override the optimization level

# Checking if we use gcc-10 or not, which need different compiler options for better benchmark scores
GCC_VER_GTE10 := $(shell echo `${RISCV_GCC} -dumpversion | cut -f1-2 -d.` \>= 10 | bc )

ifeq ($(PROGRAM),dhrystone)
ifeq ($(DHRY_OPTION),)
# Ground rules (default)
RISCV_XCFLAGS += -mexplicit-relocs -fno-inline
else ifeq ($(DHRY_OPTION),fast)
# With inline and without lto
RISCV_XCFLAGS += -mexplicit-relocs -finline
else ifeq ($(DHRY_OPTION),best)
# Best Score
RISCV_XCFLAGS += -finline -flto -fwhole-program
endif
RISCV_XCFLAGS += -DDHRY_ITERS=$(TARGET_DHRY_ITERS)
endif

ifeq ($(PROGRAM),coremark)
ifeq ($(RISCV_SERIES),$(filter $(RISCV_SERIES),sifive-7-series sifive-8-series))
# 8-series currently uses 7-series mtune, but this may change
RISCV_XCFLAGS += -O2 -fno-common -funroll-loops -finline-functions -funroll-all-loops -falign-functions=8 -falign-jumps=8 -falign-loops=8 -finline-limit=1000 -mtune=sifive-7-series -ffast-math
else
ifeq ($(RISCV_XLEN),32)
RISCV_XCFLAGS += -O2 -fno-common -funroll-loops -finline-functions -falign-functions=16 -falign-jumps=4 -falign-loops=4 -finline-limit=1000 -fno-if-conversion2 -fselective-scheduling -fno-tree-dominator-opts -fno-reg-struct-return -fno-rename-registers --param case-values-threshold=8 -fno-crossjumping -freorder-blocks-and-partition -fno-tree-loop-if-convert -fno-tree-sink -fgcse-sm -fno-strict-overflow
else
RISCV_XCFLAGS += -O2 -fno-common -funroll-loops -finline-functions -falign-functions=16 -falign-jumps=4 -falign-loops=4 -finline-limit=1000 -fno-if-conversion2 -fselective-scheduling -fno-tree-dominator-opts
endif # RISCV_XLEN==32
endif # RISCV_SERIES==sifive-7-series|sifive-8-series
RISCV_XCFLAGS += -DITERATIONS=$(TARGET_CORE_ITERS)
ifeq ($(GCC_VER_GTE10),1)
# additional options for gcc-10 to get better performance
RISCV_XCFLAGS += -fno-tree-loop-distribute-patterns --param fsm-scale-path-stmts=3
endif # GCC_VER_GTE10==1
endif # PROGRAM==coremark

ifeq ($(findstring freertos,$(PROGRAM)),freertos)
RISCV_XCFLAGS += -DWAIT_MS=$(TARGET_FREERTOS_WAIT_MS)
endif

ifneq ($(filter rtl,$(TARGET_TAGS)),)
RISCV_XCFLAGS += -DHCA_BYPASS_TRNG
endif

# A method to pass cycle delay
RISCV_XCFLAGS += -DMETAL_WAIT_CYCLE=$(TARGET_INTR_WAIT_CYCLE)