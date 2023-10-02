import numpy as np
import skfuzzy as fuzz
from skfuzzy import control as ctrl
import matplotlib.pyplot as plt

# Definindo os antecedentes (sensores)
sensor1 = ctrl.Antecedent(np.arange(0, 10001, 1), 'Sensor 1')  # Luz (intensidade de luz em lux)
sensor2 = ctrl.Antecedent(np.arange(0, 51, 1), 'Sensor 2')   # Temperatura (em graus Celsius)
sensor3 = ctrl.Antecedent(np.arange(0, 101, 1), 'Sensor 3')    # Umidade relativa do ar (%)
sensor4 = ctrl.Antecedent(np.arange(0, 21, 1), 'Sensor 4')     # Velocidade do vento (em km/h)
sensor5 = ctrl.Antecedent(np.arange(900, 1101, 1), 'Sensor 5') # Barômetro (hPa)

# Definindo o consequente (probabilidade de chuva)
probabilidade_chuva = ctrl.Consequent(np.arange(0, 101, 1), 'Probabilidade Chuva')

# Definindo funções de pertinência para os antecedentes e o consequente
# Funções de pertinência para o Sensor 1 (Luz em lux)
sensor1['muito_baixo'] = fuzz.trapmf(sensor1.universe, [0, 0, 1000, 2000])
sensor1['baixo'] = fuzz.trimf(sensor1.universe, [1000, 2000, 3000])
sensor1['medio'] = fuzz.gaussmf(sensor1.universe, 5000, 1000)
sensor1['alto'] = fuzz.trimf(sensor1.universe, [7000, 8000, 9000])
sensor1['muito_alto'] = fuzz.trapmf(sensor1.universe, [8000, 9000, 10000, 10000])

# Funções de pertinência para o Sensor 2 (Temperatura em graus Celsius)
sensor2['muito_baixo'] = fuzz.trapmf(sensor2.universe, [0, 0, 5, 10])
sensor2['baixo'] = fuzz.trimf(sensor2.universe, [5, 12, 20])
sensor2['medio'] = fuzz.gaussmf(sensor2.universe, 25, 3)
sensor2['alto'] = fuzz.trimf(sensor2.universe, [25, 32, 40])
sensor2['muito_alto'] = fuzz.trapmf(sensor2.universe, [35, 40, 50, 50])

# Funções de pertinência para o Sensor 3 (Umidade relativa do ar em %)
sensor3['muito_baixo'] = fuzz.trapmf(sensor3.universe, [0, 0, 10, 20])
sensor3['baixo'] = fuzz.trimf(sensor3.universe, [15, 28, 40])
sensor3['medio'] = fuzz.gaussmf(sensor3.universe, 50, 10)
sensor3['alto'] = fuzz.trimf(sensor3.universe, [60, 73, 85])
sensor3['muito_alto'] = fuzz.trapmf(sensor3.universe, [80, 90, 100, 100])

# Funções de pertinência para o Sensor 4 (Velocidade do vento em km/h)
sensor4['muito_baixo'] = fuzz.trapmf(sensor4.universe, [0, 0, 3, 5])
sensor4['baixo'] = fuzz.trimf(sensor4.universe, [3, 5, 7])
sensor4['medio'] = fuzz.gaussmf(sensor4.universe, 10, 2)
sensor4['alto'] = fuzz.trimf(sensor4.universe, [13, 15, 17])
sensor4['muito_alto'] = fuzz.trapmf(sensor4.universe, [15, 17, 20, 20])

# Funções de pertinência para o Sensor 5 (Pressão atmosférica em hpa)
sensor5['muito_baixo'] = fuzz.trapmf(sensor5.universe, [900, 900, 925, 950])
sensor5['baixo'] = fuzz.trimf(sensor5.universe, [935, 955, 975])
sensor5['medio'] = fuzz.gaussmf(sensor5.universe, 1000, 10)
sensor5['alto'] = fuzz.trimf(sensor5.universe, [1025, 1045, 1065])
sensor5['muito_alto'] = fuzz.trapmf(sensor5.universe, [1050, 1075, 1100, 1100])

probabilidade_chuva['sim'] = fuzz.trimf(probabilidade_chuva.universe, [0, 0, 50])
probabilidade_chuva['nao'] = fuzz.trimf(probabilidade_chuva.universe, [30, 100, 100])


# Exemplo de regras para todas as combinações de sensores
regra1 = ctrl.Rule(
    sensor1['baixo'] & sensor2['baixo'] & sensor3['baixo'] & sensor4['baixo'] & sensor5['baixo'],
    probabilidade_chuva['sim']
)

regra2 = ctrl.Rule(
    sensor1['medio'] & sensor2['baixo'] & sensor3['alto'] & sensor4['alto'] & sensor5['baixo'],
    probabilidade_chuva['nao']
)

regra3 = ctrl.Rule(
    sensor1['alto'] & sensor2['medio'] & sensor3['medio'] & sensor4['alto'] & sensor5['alto'],
    probabilidade_chuva['nao']
)

# Criando um sistema de controle fuzzy
sistema_ctrl = ctrl.ControlSystem([regra1, regra2, regra3])

# Criando uma simulação
simulacao = ctrl.ControlSystemSimulation(sistema_ctrl)

# Valores dos sensores
valor_sensor1 = 2500  # Intensidade de luz em lux (dentro do intervalo de 0 a 10000)
valor_sensor2 = 12    # Temperatura em graus Celsius (dentro do intervalo de 0 a 50)
valor_sensor3 = 26    # Umidade relativa do ar em % (dentro do intervalo de 0 a 100)
valor_sensor4 = 6    # Velocidade do vento em km/h (dentro do intervalo de 0 a 20)
valor_sensor5 = 960   # Leitura do sensor de barômetro em hPa (dentro do intervalo definido)

# Atribuindo os valores aos antecedentes do sistema de controle
simulacao.input['Sensor 1'] = valor_sensor1
simulacao.input['Sensor 2'] = valor_sensor2
simulacao.input['Sensor 3'] = valor_sensor3
simulacao.input['Sensor 4'] = valor_sensor4
simulacao.input['Sensor 5'] = valor_sensor5

# Computando a saída
simulacao.compute()

# Obtendo a saída (nível de acionamento do varal)
porcentagem_chuva = simulacao.output['Probabilidade Chuva']
print(f'Probabilidade de Chuva: {porcentagem_chuva:.2f}%')

# Visualizando as funções de pertinência
# Visualização do Sensor 1
sensor1.view()
plt.xlabel('Intensidade de Luz (lux)')
plt.ylabel('Pertinência')
plt.title('Funções de Pertinência - Sensor de Luz')
plt.show()

# Visualização do Sensor 2
sensor2.view()
plt.xlabel('Temperatura (°C)')
plt.ylabel('Pertinência')
plt.title('Funções de Pertinência - Sensor de Temperatura')
plt.show()

# Visualização do Sensor 3
sensor3.view()
plt.xlabel('Umidade Relativa do Ar (%)')
plt.ylabel('Pertinência')
plt.title('Funções de Pertinência - Sensor de Umidade')
plt.show()

# Visualização do Sensor 4
sensor4.view()
plt.xlabel('Velocidade do Vento (km/h)')
plt.ylabel('Pertinência')
plt.title('Funções de Pertinência - Sensor de Vento')
plt.show()

# Visualização do Sensor 5
sensor5.view()
plt.xlabel('Pressão Atmosférica (hPa)')
plt.ylabel('Pertinência')
plt.title('Funções de Pertinência - Sensor de Barômetro')
plt.show()

# Probabilidade Chuva
probabilidade_chuva.view()
plt.xlabel('Probabilidade de Chuva (%)')
plt.ylabel('Pertinência')
plt.title('Funções de Pertinência - Probabilidade de chuva')
plt.show()

# Obtendo a saída (porcentagem de chuva)
porcentagem_chuva = simulacao.output['Probabilidade Chuva']

# Plotando as funções de probabilidade chuva
probabilidade_chuva.view(sim=simulacao)

# Adicionando uma linha vertical indicando o ponto de acionamento
plt.axvline(x=porcentagem_chuva, color='red', linestyle='--', label=f'Nível: {porcentagem_chuva:.2f}%')

# Configurando o gráfico
plt.legend()
plt.xlabel('Probabilidade De Chuva')
plt.ylabel('Pertinência')
plt.title('Funções de Pertinência da Probabilidade de Chuva')


# Exibindo o gráfico
plt.show()
