import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.impute import SimpleImputer
from sklearn.metrics import confusion_matrix, accuracy_score
import joblib
import numpy as np
import os

# Caminho para o arquivo CSV (substitua pelo caminho real)
caminho_arquivo_csv = 'C:/Codigos/IA/dados/dados-ano-2023.csv'

# Verificar se o modelo já foi treinado
modelo_treinado_path = 'modelo_random_forest.pkl'
if os.path.exists(modelo_treinado_path):
    # Carregar o modelo treinado de um arquivo
    modelo_rf_carregado = joblib.load(modelo_treinado_path)

    # Carregar os dados do arquivo CSV para teste
    df = pd.read_csv(caminho_arquivo_csv, sep=';', decimal=',')
    
    # Remover a coluna precipitacao, que é a variável de saída
    X_test = df[['umidade', 'temperatura', 'pressao']]
    
    imputer = SimpleImputer(strategy='mean')
    X_test = imputer.fit_transform(X_test)
    
    y_test = (df['precipitacao'] > 0).astype(int)
else:
    # Carregar os dados do arquivo CSV
    df = pd.read_csv(caminho_arquivo_csv, sep=';', decimal=',')
    
    # Separar as características (X) e o rótulo (y)
    X = df[['umidade', 'temperatura', 'pressao']]
    y = (df['precipitacao'] > 0).astype(int)
    
    # Preencher valores ausentes com a média das características
    imputer = SimpleImputer(strategy='mean')
    X = imputer.fit_transform(X)

    # Criar e treinar o modelo de classificação RandomForest utilizando todo o conjunto de dados
    modelo_rf = RandomForestClassifier(n_estimators=100, random_state=42)
    modelo_rf.fit(X, y)

    # Salvar o modelo treinado em um arquivo
    joblib.dump(modelo_rf, modelo_treinado_path)

    # Carregar o modelo treinado
    modelo_rf_carregado = modelo_rf

# Obter as probabilidades das classes com RandomForest
probabilidades_rf = modelo_rf_carregado.predict_proba(X_test)

# As probabilidades da classe 1 (choveu) estão nas colunas 1 do array
probabilidade_choveu_rf = probabilidades_rf[:, 1]

# Calcular e exibir a precisão do modelo RandomForest
previsoes_rf = modelo_rf_carregado.predict(X_test)
precisao_rf = accuracy_score(y_test, previsoes_rf)

# Exibir a matriz de confusão do modelo RandomForest
matriz_confusao_rf = confusion_matrix(y_test, previsoes_rf)

print("Machine Learning RandomForest:")
print("Matriz de Confusão do modelo RandomForest:")
print(matriz_confusao_rf)

print("Precisão do modelo RandomForest:", precisao_rf)

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
novos_dados['umidade'] = data['Umidade']
novos_dados['temperatura'] = data['Temperatura']
novos_dados['pressao'] = data['Pressao']

# Pré-processe os novos dados da mesma maneira que fez com os dados de treinamento
X_novos = novos_dados[['umidade', 'temperatura', 'pressao']]
X_novos = imputer.transform(X_novos)

# Faça previsões para os novos dados
previsoes_novos = modelo_rf_carregado.predict(X_novos)

# Certifique-se de que as previsões estejam no intervalo de 0 a 1
previsoes_novos = np.clip(previsoes_novos, 0, 1)

# Aplicar a regra de classificação (menor ou igual a 0.5 -> 1, maior que 0.5 -> 0)
previsoes_classificadas = [1 if prob <= 0.5 else 0 for prob in previsoes_novos]

# Escrever as previsões classificadas em um arquivo "saida_ml.txt"
with open('C:/Codigos/IA/saidas/saida_ml.txt', 'w') as file:
    for prob_classificada in previsoes_classificadas:
        file.write(str(prob_classificada) + '\n')

# Exiba as previsões para a precipitação nos novos dados
print("Previsão de precipitação para os novos dados:")
print(f'Resultado = {previsoes_novos}')