ICBODY       := AT8B62D
CLIENT_NAME  := "c-matrixtech"
CB_FILE      := test01.cb
CB_FILE_SP   := test01.cb
HOST_TOOL	 := ATW IDE 3.12
USER_C       := main.c 
USER_ASM     := 
OUT_NAME	 := test01
ATWCC_PATH   := d:\ATW\ATWIDE\CCompiler\ATWCC

MODEL	:= bank2_8b

ENABLE_INIT_BSS := 1

##################################################

CC := sdcc
AS := atwas
LD := atwlinker

LDFLAGS		:= -p $(ICBODY) --client $(CLIENT_NAME) -g -M --riffbin --elf --disasm --host "$(HOST_TOOL)" --cinit --no-programchecksum --codechecksum --opt-banksel
CFLAGS 		:= -mny8 --errfmt-ny -p$(ICBODY) -D__CPU_$(ICBODY) --debug -I"$(ATWCC_PATH)/include" -I"d:\ATW\ATWIDE\\include"  -MD --stack-size 16  --backup-stk 2
ASFLAGS 	:= -p $(ICBODY) -g -l -I "$(ATWCC_PATH)/inc" 

DEPS		:= $(patsubst %.c,%.d, $(USER_C))
ASM_SRC		:= $(USER_ASM) $(patsubst %.c,%.s, $(USER_C))
USER_OBJ	:= $(patsubst %.s,%.o, $(ASM_SRC))
USER_OBJ	:= $(patsubst %.asm,%.o, $(USER_OBJ))
USER_OBJ	:= $(sort $(USER_OBJ))

IC_LIB		:= $(ATWCC_PATH)/lib/$(ICBODY).a
BIN_FILE	:= $(strip $(OUT_NAME)).bin

ifneq (,$(findstring small,$(MODEL)))
	COMMON_LIB	:= $(ATWCC_PATH)/lib/libsdcc_small.a
	CFG_FILE	:= $(ATWCC_PATH)/cfg/small/$(ICBODY).cfg
else
	COMMON_LIB	:= $(ATWCC_PATH)/lib/libsdcc_bankram.a
	CFG_FILE	:= $(ATWCC_PATH)/cfg/bankram/$(ICBODY).cfg
	ASFLAGS		+= -D ENABLE_RAM_BANK=1
endif

ifeq ($(ENABLE_INIT_BSS),1)
	LIB_STARTUP		:= $(ATWCC_PATH)/lib/startup/$(strip $(MODEL)).a
else
	LIB_STARTUP		:= $(ATWCC_PATH)/lib/startup/no-bss/$(strip $(MODEL)).a
endif

.SUFFIXES:
.SECONDARY:
.PHONY: all clean

all: $(BIN_FILE)

$(BIN_FILE): $(USER_OBJ) $(CB_FILE)
	$(LD) $(USER_OBJ) "$(IC_LIB)" "$(COMMON_LIB)" "$(LIB_STARTUP)" "$(CB_FILE_SP)" -s "$(CFG_FILE)" -o "$(OUT_NAME)" $(LDFLAGS)

%.s: %.c
	$(CC) -S $< -o $@ $(CFLAGS)

%.o: %.s
	$(AS) $< $(ASFLAGS)

%.o: %.asm
	$(AS) $< $(ASFLAGS)
	
-include $(DEPS)

rebuild: clean all

clean:
	-@1>nul 2>nul del "$(OUT_NAME).bin" "$(OUT_NAME).fpga" "$(OUT_NAME).elf" "$(OUT_NAME).link.lst" "$(OUT_NAME).map"
	-@1>nul 2>nul del $(patsubst %.c, %.adb, $(USER_C))
	-@1>nul 2>nul del $(patsubst %.c, %.p, $(USER_C))
	-@1>nul 2>nul del $(patsubst %.c, %.d, $(USER_C))
	-@1>nul 2>nul del $(patsubst %.c, %.s, $(USER_C))
	-@1>nul 2>nul del $(addsuffix .o, $(basename $(ASM_SRC)))
	-@1>nul 2>nul del $(addsuffix .lst, $(basename $(ASM_SRC)))

