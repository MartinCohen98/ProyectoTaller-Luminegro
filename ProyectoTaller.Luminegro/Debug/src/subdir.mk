################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Encuadre.cpp \
../src/EstadoJugador.cpp \
../src/EstadoJugadorAvanzando.cpp \
../src/EstadoJugadorFrenado.cpp \
../src/Imagen.cpp \
../src/Parallax.cpp \
../src/Protagonista.cpp \
../src/Renderizador.cpp \
../src/Textura.cpp \
../src/VentanaDeJuego.cpp \
../src/logger.cpp \
../src/main.cpp 

OBJS += \
./src/Encuadre.o \
./src/EstadoJugador.o \
./src/EstadoJugadorAvanzando.o \
./src/EstadoJugadorFrenado.o \
./src/Imagen.o \
./src/Parallax.o \
./src/Protagonista.o \
./src/Renderizador.o \
./src/Textura.o \
./src/VentanaDeJuego.o \
./src/logger.o \
./src/main.o 

CPP_DEPS += \
./src/Encuadre.d \
./src/EstadoJugador.d \
./src/EstadoJugadorAvanzando.d \
./src/EstadoJugadorFrenado.d \
./src/Imagen.d \
./src/Parallax.d \
./src/Protagonista.d \
./src/Renderizador.d \
./src/Textura.d \
./src/VentanaDeJuego.d \
./src/logger.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


