################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cycle_detector.cpp \
../src/image.cpp \
../src/lodepng.cpp \
../src/main.cpp 

OBJS += \
./src/cycle_detector.o \
./src/image.o \
./src/lodepng.o \
./src/main.o 

CPP_DEPS += \
./src/cycle_detector.d \
./src/image.d \
./src/lodepng.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/sam/Coding_Projects/Edge_Detection/Image_Edge_Detection/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


