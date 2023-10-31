import serial
import time

# Porta serial do Arduino (ajuste conforme necessário)
arduino_port = 'COM5'  # No Windows, substitua 'COM3' pela porta serial correta.
baud_rate = 9600

# Atraso para dar tempo ao Arduino para inicializar (em segundos)
initialization_delay = 2

# Abre a porta serial
ser = serial.Serial(arduino_port, baud_rate)

# Atraso no início do código
time.sleep(initialization_delay)

# Nome do arquivo de entrada
input_file = 'saidas/saida_fuzzy.txt'

# Abre o arquivo de entrada para leitura
with open(input_file, 'r') as file:
    for line in file:
        print(line)
        ser.write(line.encode('utf-8'))  # Envie a linha pela porta serial
