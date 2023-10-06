import numpy as np
import skfuzzy as fuzz
from skfuzzy import control as ctrl
import matplotlib.pyplot as plt

# Definindo os antecedentes (sensores)
sensor1 = ctrl.Antecedent(np.arange(0, 10001, 1), 'Sensor 1')  # Luz (intensidade de luz em lux)
sensor2 = ctrl.Antecedent(np.arange(0, 51, 1), 'Sensor 2')   # Temperatura (em graus Celsius)
sensor3 = ctrl.Antecedent(np.arange(0, 101, 1), 'Sensor 3')    # Umidade relativa do ar (%)
sensor4 = ctrl.Antecedent(np.arange(900, 1101, 1), 'Sensor 4') # Barômetro (hPa)

# Definindo o consequente (previsão do tempo)
previsao = ctrl.Consequent(np.arange(0, 101, 1), 'Previsao Tempo')

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

# Funções de pertinência para o Sensor 5 (Pressão atmosférica em hpa)
sensor4['muito_baixo'] = fuzz.trapmf(sensor4.universe, [900, 900, 925, 950])
sensor4['baixo'] = fuzz.trimf(sensor4.universe, [935, 955, 975])
sensor4['medio'] = fuzz.gaussmf(sensor4.universe, 1000, 10)
sensor4['alto'] = fuzz.trimf(sensor4.universe, [1025, 1045, 1065])
sensor4['muito_alto'] = fuzz.trapmf(sensor4.universe, [1050, 1075, 1100, 1100])

previsao['desativado'] = fuzz.trimf(previsao.universe, [0, 0, 50])
previsao['ativado'] = fuzz.trimf(previsao.universe, [30, 100, 100])


# Regras para todas as combinações de sensores

regra1 = ctrl.Rule(
    (sensor1['medio'] | sensor1['alto'] | sensor1['muito_alto']) &
    (sensor2['muito_baixo'] | sensor2['baixo']) &
    (sensor3['medio'] | sensor3['alto'] | sensor3['muito_alto']) &
    (sensor4['muito_baixo'] | sensor4['baixo']),
    previsao['desativado']
) # Condição Perfeita de Chuva
regra2 = ctrl.Rule(
    (sensor1['medio'] | sensor1['alto'] | sensor1['muito_alto'])  &
    (sensor2['medio']) &
    (sensor3['alto'] | sensor3['muito_alto']) &
    (sensor4['medio']),
    previsao['desativado']
) # Umidade muita alta de dia com temperatura e pressão media
regra3 = ctrl.Rule(
    (sensor1['muito_baixo'] | sensor1['baixo']),
    previsao['desativado']
) # De noite
regra4 = ctrl.Rule(
    (sensor1['medio'] | sensor1['alto'] | sensor1['muito_alto']) &
    (sensor2['medio'] | sensor2['alto'] | sensor2['muito_alto']) &
    (sensor3['muito_baixo'] | sensor3['baixo']) &
    (sensor4['medio'] | sensor4['alto'] | sensor4['muito_alto']),
    previsao['ativado']
) # Condições Perfeita de Sol
regra5 = ctrl.Rule(
    (sensor1['medio'] | sensor1['alto'] | sensor1['muito_alto']) &
    (sensor2['muito_alto']) &
    (sensor3['medio']) &
    (sensor4['muito_alto']),
    previsao['ativado']
) # Temperatura e pressão muito alta, umidade media
regra6 = ctrl.Rule(
    (sensor1['alto'] | sensor1['muito_alto']) &
    (sensor2['alto'] | sensor2['muito_alto']) &
    (sensor3['alto'] | sensor3['muito_alto']) &
    (sensor4['alto'] | sensor4['muito_alto']),
    previsao['ativado']
) # Tudo alto e muito alto
regra7 = ctrl.Rule(
    (sensor1['medio'] | sensor1['alto'] | sensor1['muito_alto']) &
    (sensor2['baixo'] | sensor2['muito_baixo']) &
    (sensor3['baixo'] | sensor3['muito_baixo']) &
    (sensor4['baixo'] | sensor4['muito_baixo']),
    previsao['ativado']
) # Tudo baixo e muito baixo
regra8 = ctrl.Rule(
    (sensor1['medio'] | sensor1['alto'] | sensor1['muito_alto']) &
    (sensor2['medio']) &
    (sensor3['medio']) &
    (sensor4['medio']),
    previsao['ativado']
) # Tudo Médio

# Criando um sistema de controle fuzzy
sistema_ctrl = ctrl.ControlSystem([regra1,regra2,regra3,regra4,regra5,regra6,regra7,regra8])

# Criando uma simulação
simulacao = ctrl.ControlSystemSimulation(sistema_ctrl)

# Valores dos sensores
valor_sensor1 = 7000  # Intensidade de luz em lux (dentro do intervalo de 0 a 10000)
valor_sensor2 = 25    # Temperatura em graus Celsius (dentro do intervalo de 0 a 50)
valor_sensor3 = 50    # Umidade relativa do ar em % (dentro do intervalo de 0 a 100)
valor_sensor4 = 1000   # Leitura do sensor de barômetro em hPa (dentro do intervalo definido)

# Atribuindo os valores aos antecedentes do sistema de controle
simulacao.input['Sensor 1'] = valor_sensor1
simulacao.input['Sensor 2'] = valor_sensor2
simulacao.input['Sensor 3'] = valor_sensor3
simulacao.input['Sensor 4'] = valor_sensor4

# Computando a saída
simulacao.compute()

# Obtendo a saída
probabilidade_tempo = simulacao.output['Previsao Tempo']
print(f'Previsão do tempo(%): {probabilidade_tempo:.2f}%')

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
plt.xlabel('Pressão Atmosférica (hPa)')
plt.ylabel('Pertinência')
plt.title('Funções de Pertinência - Sensor de Barômetro')
plt.show()

# Probabilidade Do Tempo
previsao.view()
plt.xlabel('Previsão do Tempo (%)')
plt.ylabel('Pertinência')
plt.title('Funções de Pertinência - Probabilidade de sol e chuva')
plt.show()

# Obtendo a saída (porcentagem da probabilidade do tempo)
probabilidade_tempo = simulacao.output['Previsao Tempo']

# Plotando as funções de previsao do tempo
previsao.view(sim=simulacao)

# Adicionando uma linha vertical indicando o ponto de acionamento
plt.axvline(x=probabilidade_tempo, color='red', linestyle='--', label=f'Nível: {probabilidade_tempo:.2f}%')

# Configurando o gráfico
plt.legend()
plt.xlabel('Probabilidade da Previsão do Tempo')
plt.ylabel('Pertinência')
plt.title('Funções de Pertinência da Previsão do Tempo')


# Exibindo o gráfico
plt.show()