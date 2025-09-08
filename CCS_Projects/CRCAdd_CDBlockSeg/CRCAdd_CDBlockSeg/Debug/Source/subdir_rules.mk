################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Source/%.obj: ../Source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c6000_8.3.13/bin/cl6x" -mv6600 --big_endian --abi=eabi -g --include_path="D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c6000_8.3.13/include" --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="Source/$(basename $(<F)).d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


