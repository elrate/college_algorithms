import serial

# Porta serial do Arduino (ajuste conforme necessário)
arduino_port = 'COM5'  # No Windows, substitua 'COM3' pela porta serial correta.
baud_rate = 9600

# Nome do arquivo de saída
output_file = 'dados.txt'

# Abre a porta serial
ser = serial.Serial(arduino_port, baud_rate)

# Abre o arquivo de saída para escrever os dados
with open(output_file, 'w') as file:
    for _ in range(4):
        # Lê uma linha da porta serial
        line = ser.readline().decode('utf-8').strip()
        
        # Imprime a linha no console
        print(line)
        
        # Escreve a linha no arquivo de saída
        file.write(line + '\n')

# Nome do arquivo de entrada
input_file = 'dados1.txt'

# Abre o arquivo de entrada para leitura
with open(input_file, 'r') as file:
    for line in file:
        ser.write(line.encode('utf-8'))  # Envie a linha pela porta serial

ser.close()