################################################################################
# MRS Version: 1.9.0
# ×Ô¶¯Éú³ÉµÄÎÄ¼þ¡£²»Òª±à¼­£¡
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Resouse/SmartCar/balance\ car/project/code/My_Math.c \
D:/Resouse/SmartCar/balance\ car/project/code/SeekLine4.0.c \
D:/Resouse/SmartCar/balance\ car/project/code/Servo.c \
D:/Resouse/SmartCar/balance\ car/project/code/cam_preprocess.c \
D:/Resouse/SmartCar/balance\ car/project/code/motor.c \
D:/Resouse/SmartCar/balance\ car/project/code/pid.c 

OBJS += \
./code/My_Math.o \
./code/SeekLine4.0.o \
./code/Servo.o \
./code/cam_preprocess.o \
./code/motor.o \
./code/pid.o 

C_DEPS += \
./code/My_Math.d \
./code/SeekLine4.0.d \
./code/Servo.d \
./code/cam_preprocess.d \
./code/motor.d \
./code/pid.d 


# Each subdirectory must supply rules for building sources it contributes
code/My_Math.o: D:/Resouse/SmartCar/balance\ car/project/code/My_Math.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\Resouse\SmartCar\balance car\Libraries\doc" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Core" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Ld" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Peripheral" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Startup" -I"D:\Resouse\SmartCar\balance car\project\user\inc" -I"D:\Resouse\SmartCar\balance car\libraries\zf_common" -I"D:\Resouse\SmartCar\balance car\libraries\zf_device" -I"D:\Resouse\SmartCar\balance car\project\code" -I"D:\Resouse\SmartCar\balance car\libraries\zf_driver" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\project\code" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/SeekLine4.0.o: D:/Resouse/SmartCar/balance\ car/project/code/SeekLine4.0.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\Resouse\SmartCar\balance car\Libraries\doc" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Core" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Ld" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Peripheral" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Startup" -I"D:\Resouse\SmartCar\balance car\project\user\inc" -I"D:\Resouse\SmartCar\balance car\libraries\zf_common" -I"D:\Resouse\SmartCar\balance car\libraries\zf_device" -I"D:\Resouse\SmartCar\balance car\project\code" -I"D:\Resouse\SmartCar\balance car\libraries\zf_driver" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\project\code" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/Servo.o: D:/Resouse/SmartCar/balance\ car/project/code/Servo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\Resouse\SmartCar\balance car\Libraries\doc" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Core" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Ld" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Peripheral" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Startup" -I"D:\Resouse\SmartCar\balance car\project\user\inc" -I"D:\Resouse\SmartCar\balance car\libraries\zf_common" -I"D:\Resouse\SmartCar\balance car\libraries\zf_device" -I"D:\Resouse\SmartCar\balance car\project\code" -I"D:\Resouse\SmartCar\balance car\libraries\zf_driver" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\project\code" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/cam_preprocess.o: D:/Resouse/SmartCar/balance\ car/project/code/cam_preprocess.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\Resouse\SmartCar\balance car\Libraries\doc" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Core" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Ld" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Peripheral" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Startup" -I"D:\Resouse\SmartCar\balance car\project\user\inc" -I"D:\Resouse\SmartCar\balance car\libraries\zf_common" -I"D:\Resouse\SmartCar\balance car\libraries\zf_device" -I"D:\Resouse\SmartCar\balance car\project\code" -I"D:\Resouse\SmartCar\balance car\libraries\zf_driver" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\project\code" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/motor.o: D:/Resouse/SmartCar/balance\ car/project/code/motor.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\Resouse\SmartCar\balance car\Libraries\doc" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Core" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Ld" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Peripheral" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Startup" -I"D:\Resouse\SmartCar\balance car\project\user\inc" -I"D:\Resouse\SmartCar\balance car\libraries\zf_common" -I"D:\Resouse\SmartCar\balance car\libraries\zf_device" -I"D:\Resouse\SmartCar\balance car\project\code" -I"D:\Resouse\SmartCar\balance car\libraries\zf_driver" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\project\code" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/pid.o: D:/Resouse/SmartCar/balance\ car/project/code/pid.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\Resouse\SmartCar\balance car\Libraries\doc" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Core" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Ld" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Peripheral" -I"D:\Resouse\SmartCar\balance car\libraries\sdk\Startup" -I"D:\Resouse\SmartCar\balance car\project\user\inc" -I"D:\Resouse\SmartCar\balance car\libraries\zf_common" -I"D:\Resouse\SmartCar\balance car\libraries\zf_device" -I"D:\Resouse\SmartCar\balance car\project\code" -I"D:\Resouse\SmartCar\balance car\libraries\zf_driver" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\project\code" -I"C:\Users\Universe\Desktop\seekfree(ÎðÉ¾)\3.0Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

