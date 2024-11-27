# Edge AI implementation on Sifive-hifive1 based VSDSquadron Pro
This repo contains Deep Neural network implementation tests for 
VSDSquadron Pro board based on SiFive-HiFive-1 FE310-G002. 

Target Specification:- 
- Development Board:- VSDSquadron Pro
- IC:- Sifive FE310-G002 
- Frequency :- 320 Mhz
- SRAM :- 16kb
- SPI Flash :- 32Mb
- Architecture:- rv32imac_zicsr_zifencei
- ToolSuit:- riscv64-unknown-elf-toolsuite-2.0.3
- Software used- Sifive Freedom Studio

## Bitnet Implementation
This approach can be used to compress the models to very small sizes, 
check out MNIST Classification project example here [sifive_bit_net_implementation](./sifive_bit_net_implementation/)

### Features:- 
- Implementaion of any dense(fully-connected) and relu layers based model can be implement using this method. 
- uses Pytorch to generate models, 
- self generated, or pretrained models with only dense and relu layers can be used. 

### Deployent Steps:- 
- Generate a model using [bitnetmcu_model_generation](sifive_bit_net_implementation\bitnetmcu_model_generation/BitNetMCU/)
- copy yhe model file to [sifive bitnet mcu project source file](sifive_bit_net_implementation\SiFive_BitNET_MCU\src) 
- update [SiFive_BitNET_MCU.c](sifive_bit_net_implementation\SiFive_BitNET_MCU\src\SiFive_BitNET_MCU.c) file to reach to correct model file
- open the project in sifive workspace and debug using inbuilt compiler


### Generated Prediction output 
![prediction output](./sifive_bit_net_implementation/images/sifive_Bitnet_nist_prediction.PNG)


## Tensorflow Lite Micro implementation
** Please not this is under development and not yet deployable

This appraoch can be used to implement prediction of models with any type of layers, usinf Tensorflow lite micro library.
check out TFLM sine wave prediction hello world example here [sifive_tensorflow_lite_micro_implementation](./sifive_tensorflow_lite_micro_implementation/) 

### Features:- 
- Implementaion of any dense(fully-connected) and relu layers based model can be implement using this method.
- uses tensorflow library in python to generate models and compress them to .tflite format for comperession
- any type of self generated, or pretrained models can be used constrained by sram and flash size

### On going Development phase
We are encountering issues with toolsuit's floating point library, complete error log can be found at [error_log](./sifive_tensorflow_lite_micro_implementation/error_log.txt)

### deployment steps
- Generate your model using tensorflow library in python
- Convert model to tflite model using [tflite-model-maker](https://ai.google.dev/edge/litert/libraries/modify)
- generate model.cc and model.h files using [tflite_to_c.py](./sifive_tensorflow_lite_micro_implementation/tflite_to_cc.py)
- copy the generated .cc and .h files to [project source folder](./sifive_tensorflow_lite_micro_implementation/sifive_hifive1_empty_1/src/)
- generate micro resolver of the model using [micro_op_resolver](https://github.com/tensorflow/tflite-micro/tree/main/tensorflow/lite/micro/tools/gen_micro_mutable_op_resolver)
- update [main.cpp](./sifive_tensorflow_lite_micro_implementation/sifive_hifive1_empty_1/src/main.cpp) file to to import correct model and implement correct resolver
- copy [tflite library directory](./sifive_tensorflow_lite_micro_implementation/sifive_hifive1_empty_1/tflite/) to your project path
- open the project in pen the project in sifive workspace update make file to resolve all imports properly in software section

example make file updates:- 

```Makefile
...
#############################################################
# Software
#############################################################

PROGRAM_ELF ?= $(SRC_DIR)/$(CONFIGURATION)/$(PROGRAM).elf
PROGRAM_HEX ?= $(SRC_DIR)/$(CONFIGURATION)/$(PROGRAM).hex
PROGRAM_LST ?= $(SRC_DIR)/$(CONFIGURATION)/$(PROGRAM).lst

.PHONY: all
all: software

.PHONY: software
software: $(PROGRAM_ELF)

software: $(PROGRAM_HEX)

tflm_dir= $(PWD)/tflite
PROGRAM_SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.h) $(wildcard $(SRC_DIR)/*.hpp) $(wildcard $(SRC_DIR)/*.S)$(wildcard $(SRC_DIR)/*.cpp)$(wildcard $(SRC_DIR)/*.cc)
TFLM_INCLUDE_DIRS := $(shell find $(tflm_dir) -type d)
#RISCV_CFLAGS += -lgcc -lc -msoft-float
RISCV_CXXFLAGS += -lgcc -lc 
RISCV_LDLIBS += -L$(tflm_dir) -ltflite 
RISCV_LDFLAGS += $(addprefix -I, $(TFLM_INCLUDE_DIRS))
RISCV_LDFLAGS += -fno-rtti 

```

- build the project

