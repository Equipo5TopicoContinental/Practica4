################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/app/Buttons.c" \
"../Sources/app/Player.c" \
"../Sources/app/Player_Fsm.c" \
"../Sources/app/RGB_LEDs.c" \
"../Sources/app/UartFsm.c" \

C_SRCS += \
../Sources/app/Buttons.c \
../Sources/app/Player.c \
../Sources/app/Player_Fsm.c \
../Sources/app/RGB_LEDs.c \
../Sources/app/UartFsm.c \

OBJS += \
./Sources/app/Buttons.o \
./Sources/app/Player.o \
./Sources/app/Player_Fsm.o \
./Sources/app/RGB_LEDs.o \
./Sources/app/UartFsm.o \

OBJS_QUOTED += \
"./Sources/app/Buttons.o" \
"./Sources/app/Player.o" \
"./Sources/app/Player_Fsm.o" \
"./Sources/app/RGB_LEDs.o" \
"./Sources/app/UartFsm.o" \

C_DEPS += \
./Sources/app/Buttons.d \
./Sources/app/Player.d \
./Sources/app/Player_Fsm.d \
./Sources/app/RGB_LEDs.d \
./Sources/app/UartFsm.d \

OBJS_OS_FORMAT += \
./Sources/app/Buttons.o \
./Sources/app/Player.o \
./Sources/app/Player_Fsm.o \
./Sources/app/RGB_LEDs.o \
./Sources/app/UartFsm.o \

C_DEPS_QUOTED += \
"./Sources/app/Buttons.d" \
"./Sources/app/Player.d" \
"./Sources/app/Player_Fsm.d" \
"./Sources/app/RGB_LEDs.d" \
"./Sources/app/UartFsm.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/app/Buttons.o: ../Sources/app/Buttons.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/Buttons.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/Buttons.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/Player.o: ../Sources/app/Player.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/Player.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/Player.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/Player_Fsm.o: ../Sources/app/Player_Fsm.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/Player_Fsm.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/Player_Fsm.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/RGB_LEDs.o: ../Sources/app/RGB_LEDs.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/RGB_LEDs.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/RGB_LEDs.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/UartFsm.o: ../Sources/app/UartFsm.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/UartFsm.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/UartFsm.o"
	@echo 'Finished building: $<'
	@echo ' '


