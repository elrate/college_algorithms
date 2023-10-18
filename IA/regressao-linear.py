import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.impute import SimpleImputer
from sklearn.metrics import mean_squared_error
import numpy as np

# Carregar os dados do arquivo CSV (substitua 'seuarquivo.csv' pelo caminho real)
df = pd.read_csv('C:/Codigos/IA/dados-completo-2020_2023.csv', sep=';', decimal=',')

# Corrigir os valores de precipitação formatados incorretamente e converter para float
df['precipitacao'] = pd.to_numeric(df['precipitacao'], errors='coerce')
df['precipitacao'] = df['precipitacao'].fillna(0)  # Substituir valores incorretos por 0

# Converter as colunas 'temperatura' e 'pressao' em números
df['temperatura'] = pd.to_numeric(df['temperatura'], errors='coerce')
df['pressao'] = pd.to_numeric(df['pressao'], errors='coerce')  # Corrigido aqui

# Preparar os dados
X = df[['umidade', 'temperatura', 'pressao']]
y = df['precipitacao']  # Agora estamos prevendo a precipitação como um valor contínuo

# Preencher valores ausentes com a média da coluna
imputer = SimpleImputer(strategy='mean')
X = imputer.fit_transform(X)

# Dividir os dados em conjunto de treinamento e teste
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Criar e treinar o modelo de Regressão Linear
modelo_linear = LinearRegression()
modelo_linear.fit(X_train, y_train)

# Fazer previsões no conjunto de teste
previsoes_linear = modelo_linear.predict(X_test)

# Aplicar a função sigmoid para ajustar os valores de saída entre 0 e 1
previsoes_linear = 1 / (1 + np.exp(-previsoes_linear))

# Avaliar o desempenho do modelo usando métricas de regressão (por exemplo, Erro Quadrático Médio)
mse = mean_squared_error(y_test, previsoes_linear)
print("Erro Quadrático Médio do modelo de Regressão Linear:", mse)

# Suponha que você tenha um arquivo CSV chamado 'novos_dados.csv' com as colunas 'umidade', 'temperatura' e 'pressao'.
# Carregue os novos dados em um DataFrame

novos_dados = pd.read_csv('C:/Codigos/IA/novos_dados.csv', sep=';', decimal=',')

# Pré-processe os novos dados da mesma maneira que fez com os dados de treinamento
X_novos = novos_dados[['umidade', 'temperatura', 'pressao']]
X_novos = imputer.transform(X_novos)  # Lembre-se de aplicar a mesma transformação que fez nos dados de treinamento

# Faça previsões para os novos dados
previsoes_novos = modelo_linear.predict(X_novos)

# Aplicar a função sigmoid para ajustar os valores de saída entre 0 e 1
previsoes_novos = 1 / (1 + np.exp(-previsoes_novos))

# Exiba as previsões para a precipitação nos novos dados
print("Previsões de precipitação para os novos dados:")
print(previsoes_novos)