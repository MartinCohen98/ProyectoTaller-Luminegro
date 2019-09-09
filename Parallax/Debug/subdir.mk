################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Imagen.cpp \
../Parallax.cpp \
../Renderizador.cpp \
../Textura.cpp \
../VentanaDeJuego.cpp \
../mainParallax.cpp 

OBJS += \
./Imagen.o \
./Parallax.o \
./Renderizador.o \
./Textura.o \
./VentanaDeJuego.o \
./mainParallax.o 

CPP_DEPS += \
./Imagen.d \
./Parallax.d \
./Renderizador.d \
./Textura.d \
./VentanaDeJuego.d \
./mainParallax.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


