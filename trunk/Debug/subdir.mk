################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Calibration.cpp \
../ColoredObjectDetector.cpp \
../DObject.cpp \
../Frame.cpp \
../FrameAnalyser.cpp \
../FrameStack.cpp \
../Horizont.cpp \
../HorizontDetector.cpp \
../LEDdetector.cpp \
../Log.cpp \
../ObjektTracker.cpp \
../OpticalFlowDetector.cpp \
../ReadLog.cpp \
../main.cpp \
../main2.cpp \
../micromagiceye.cpp 

OBJS += \
./Calibration.o \
./ColoredObjectDetector.o \
./DObject.o \
./Frame.o \
./FrameAnalyser.o \
./FrameStack.o \
./Horizont.o \
./HorizontDetector.o \
./LEDdetector.o \
./Log.o \
./ObjektTracker.o \
./OpticalFlowDetector.o \
./ReadLog.o \
./main.o \
./main2.o \
./micromagiceye.o 

CPP_DEPS += \
./Calibration.d \
./ColoredObjectDetector.d \
./DObject.d \
./Frame.d \
./FrameAnalyser.d \
./FrameStack.d \
./Horizont.d \
./HorizontDetector.d \
./LEDdetector.d \
./Log.d \
./ObjektTracker.d \
./OpticalFlowDetector.d \
./ReadLog.d \
./main.d \
./main2.d \
./micromagiceye.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


