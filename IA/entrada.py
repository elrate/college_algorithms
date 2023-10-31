import serial

# Porta serial do Arduino (ajuste conforme necessário)
arduino_port = 'COM5'  # No Windows, substitua 'COM3' pela porta serial correta.
baud_rate = 9600

# Nome do arquivo de saída para os valores 'fuzzy'
output_file_fuzzy = 'entradas/valores_fuzzy.txt'
# Nome do arquivo de saída para os valores 'ml'
output_file_ml = 'entradas/valores_ml.txt'

# Abre a porta serial
ser = serial.Serial(arduino_port, baud_rate)

# Abre o arquivo de saída para escrever os valores 'fuzzy'
with open(output_file_fuzzy, 'w') as file_fuzzy:
    print('Valores:')
    for _ in range(4):
        # Lê uma linha da porta serial
        line = ser.readline().decode('utf-8').strip()
        
        # Imprime a linha no console
        print(line)
        
        # Escreve a linha no arquivo de saída 'fuzzy'
        file_fuzzy.write(line + '\n')

# Nome do arquivo de entrada (valores 'fuzzy')
input_file = 'entradas/valores_fuzzy.txt'

# Lista de chaves que você deseja manter
chaves_desejadas = ['Temperatura', 'Umidade', 'Pressao']

# Dicionário para armazenar os valores 'fuzzy'
valores_fuzzy = {}

# Abre o arquivo de entrada para leitura
with open(input_file, 'r') as file_fuzzy:
    for line in file_fuzzy:
        key, value = line.strip().split(' = ')
        valores_fuzzy[key] = value

# Abre o arquivo de saída para escrever os valores 'ml'
with open(output_file_ml, 'w') as file_ml:
    for chave in chaves_desejadas:
        if chave in valores_fuzzy:
            # Escreve os valores 'ml' no arquivo
            file_ml.write(f"{chave} = {valores_fuzzy[chave]}\n")
