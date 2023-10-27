import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.impute import SimpleImputer
from sklearn.metrics import mean_squared_error
import numpy as np
import joblib
import os

# Carregar os dados do arquivo CSV (substitua 'seuarquivo.csv' pelo caminho real)
df = pd.read_csv('C:/Codigos/IA/dados/dados-completo-2020_2023.csv', sep=';', decimal=',')

# Corrigir os valores de precipitação formatados incorretamente e converter para float
df['precipitacao'] = pd.to_numeric(df['precipitacao'], errors='coerce')
df['precipitacao'] = df['precipitacao'].fillna(0)  # Substituir valores incorretos por 0

# Converter as colunas 'temperatura' e 'pressao' em números
df['temperatura'] = pd.to_numeric(df['temperatura'], errors='coerce')
df['pressao'] = pd.to_numeric(df['pressao'], errors='coerce')

# Preparar os dados
X = df[['umidade', 'temperatura', 'pressao']]
y = df['precipitacao']  # Agora estamos prevendo a precipitação como um valor contínuo

# Preencher valores ausentes com a média da coluna
imputer = SimpleImputer(strategy='mean')
X = imputer.fit_transform(X)

# Dividir os dados em conjunto de treinamento e teste
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Verificar se o modelo já foi treinado
# Se o modelo já foi treinado, não é necessário treiná-lo novamente
if 'modelo_linear.pkl' in os.listdir():
    modelo_linear = joblib.load('modelo_linear.pkl')
    print('Sim')
else:
    print('Nao')
    # Criar e treinar o modelo de Regressão Linear
    modelo_linear = LinearRegression()
    modelo_linear.fit(X_train, y_train)  # Treine o modelo aqui
    # Salvar o modelo treinado
    joblib.dump(modelo_linear, 'modelo_linear.pkl')

# Fazer previsões no conjunto de teste
previsoes_lineares = modelo_linear.predict(X_test)

# Avaliar o desempenho do modelo usando métricas de regressão (por exemplo, Erro Quadrático Médio)
mse = mean_squared_error(y_test, previsoes_lineares)
print("Erro Quadrático Médio do modelo de Regressão Linear:", mse)

# Carregue os novos dados em um DataFrame

# Ler os valores de temperatura, umidade e pressão do arquivo .txt
with open('C:/Codigos/IA/entradas/valores_ml.txt', 'r') as file:
    data = {}
    for line in file:
        key, value = line.strip().split('=')
        value = value.strip().replace(',', '.')  # Substitui vírgula por ponto
        data[key.strip()] = float(value)
# Carregue os novos dados em um DataFrame
novos_dados = pd.read_csv('C:/Codigos/IA/dados/novos_dados.csv', sep=';', decimal=',')

# Ajustar as colunas do DataFrame com os valores lidos do arquivo .txt
novos_dados['umidade'] = data['umidade']
novos_dados['temperatura'] = data['temperatura']
novos_dados['pressao'] = data['pressao']

# Pré-processe os novos dados da mesma maneira que fez com os dados de treinamento
X_novos = novos_dados[['umidade', 'temperatura', 'pressao']]
X_novos = imputer.transform(X_novos)  # Lembre-se de aplicar a mesma transformação que fez nos dados de treinamento

# Faça previsões para os novos dados
previsoes_novos = modelo_linear.predict(X_novos)

# Certifique-se de que as previsões estejam no intervalo de 0 a 1
previsoes_novos = np.clip(previsoes_novos, 0, 1)

# Aplicar a regra de classificação (menor ou igual a 0.5 -> 1, maior que 0.5 -> 0)
previsoes_classificadas = [1 if prob <= 0.5 else 0 for prob in previsoes_novos]

# Escrever as previsões classificadas em um arquivo "saida_ml.txt"
with open('C:/Codigos/IA/saidas/saida_ml.txt', 'w') as file:
    for prob_classificada in previsoes_classificadas:
        file.write(str(prob_classificada) + '\n')

# Exiba as previsões para a precipitação nos novos dados
print("Previsões de precipitação para os novos dados:")
print(previsoes_novos)
