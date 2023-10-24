################################################################################
# MRS Version: 1.9.0
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Resouse/SmartCar/balance\ car/libraries/sdk/Core/core_riscv.c 

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o: D:/Resouse/SmartCar/balance\ car/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\Resouse\SmartCar\balance car\Libraries\doc" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Core" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Ld" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Peripheral" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Startup" -I"D:\Resouse\SmartCar\balance car\project\user\inc" -I"D:\Resouse\SmartCar\balance car\libraries\zf_common" -I"D:\Resouse\SmartCar\balance car\libraries\zf_device" -I"D:\Resouse\SmartCar\balance car\project\code" -I"D:\Resouse\SmartCar\balance car\libraries\zf_driver" -I"C:\Users\Universe\Desktop\seekfree(勿删)\3.0Seekfree_CH32V307VCT6_Opensource_Library\project\code" -I"C:\Users\Universe\Desktop\seekfree(勿删)\3.0Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

