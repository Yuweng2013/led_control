################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
IR_check.obj: ../IR_check.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="H:/ti/ccsv7/ccs_base/msp430/include" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl/driverlib/MSP430F5xx_6xx" --include_path="H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="IR_check.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

crc.obj: ../crc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="H:/ti/ccsv7/ccs_base/msp430/include" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl/driverlib/MSP430F5xx_6xx" --include_path="H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="crc.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

data_pack.obj: ../data_pack.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="H:/ti/ccsv7/ccs_base/msp430/include" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl/driverlib/MSP430F5xx_6xx" --include_path="H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="data_pack.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

flash.obj: ../flash.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="H:/ti/ccsv7/ccs_base/msp430/include" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl/driverlib/MSP430F5xx_6xx" --include_path="H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="flash.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

led.obj: ../led.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="H:/ti/ccsv7/ccs_base/msp430/include" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl/driverlib/MSP430F5xx_6xx" --include_path="H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="led.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="H:/ti/ccsv7/ccs_base/msp430/include" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl/driverlib/MSP430F5xx_6xx" --include_path="H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rs485.obj: ../rs485.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="H:/ti/ccsv7/ccs_base/msp430/include" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl/driverlib/MSP430F5xx_6xx" --include_path="H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="rs485.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rtc.obj: ../rtc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="H:/ti/ccsv7/ccs_base/msp430/include" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl" --include_path="G:/ti_file/Fog_light_Prj/led_ctrl/driverlib/MSP430F5xx_6xx" --include_path="H:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="rtc.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


