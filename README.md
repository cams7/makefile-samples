# makefile-samples
Exemplo de uso do Makefile para compilar codigo C/C++

#Instalar o avr no ubuntu 14.04
sudo apt-get install avrdude binutils-avr gcc-avr avr-libc gdb-avr

#Criar o arquivo "user.mk"
gedit ~/user.mk

#Cole as linhas abaixo no arquivo "user.mk"

AVRDUDE_PROGRAMMER=arduino
AVRDUDE_PORT=/dev/ttyACM0
AVRDUDE_SPEED=115200

#Verificar portas serias
dmesg | grep tty

#Alterar permissao da porta serial 
sudo chmod a+rw /dev/ttyACM0

#Rodar os exemplos "atmega328" e "atmega328-serial"

#Limpar todos os arquivos gerados
make clean

#Compilar o programa
make all

#Compilar e carregar o programa no Arduino UNO
make flash
