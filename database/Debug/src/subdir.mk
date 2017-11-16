################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/course.cpp \
../src/database.cpp \
../src/execute.cpp \
../src/extension.cpp \
../src/preference.cpp \
../src/user.cpp \
../src/userCourse.cpp \
../src/userPreference.cpp 

OBJS += \
./src/course.o \
./src/database.o \
./src/execute.o \
./src/extension.o \
./src/preference.o \
./src/user.o \
./src/userCourse.o \
./src/userPreference.o 

CPP_DEPS += \
./src/course.d \
./src/database.d \
./src/execute.d \
./src/extension.d \
./src/preference.d \
./src/user.d \
./src/userCourse.d \
./src/userPreference.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


