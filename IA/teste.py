import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.impute import SimpleImputer
from sklearn.metrics import confusion_matrix
import numpy as np

# Carregar os dados do arquivo CSV (substitua 'seuarquivo.csv' pelo caminho real)
df = pd.read_csv('C:/Codigos/IA/dados-ano-2023.csv', sep=';', decimal=',')

# Preparar os dados
X = df[['umidade', 'temperatura', 'pressao']]
y = (df['precipitacao'] > 0).astype(int)  # Se precipitação > 0, então choveu (1), senão não choveu (0)

# Preencher valores ausentes com a média da coluna
imputer = SimpleImputer(strategy='mean')
X = imputer.fit_transform(X)

# Dividir os dados em conjunto de treinamento e teste
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Criar e treinar o modelo de classificação RandomForest
modelo_rf = RandomForestClassifier(n_estimators=100, random_state=42)
modelo_rf.fit(X_train, y_train)

# Obter as probabilidades das classes com RandomForest
probabilidades_rf = modelo_rf.predict_proba(X_test)

# Formatar as probabilidades
probabilidades_formatadas = [[f'{probabilidade:.2f}' for probabilidade in linha] for linha in probabilidades_rf]

# Salvar as probabilidades formatadas em um arquivo .txt no diretório "C:/Codigos/IA"
caminho_saida = "C:/Codigos/IA/probabilidades_rf.txt"

with open(caminho_saida, "w") as arquivo:
    for linha in probabilidades_formatadas:
        arquivo.write("\t".join(linha) + "\n")
        
# Avaliar o desempenho do modelo RandomForest
matriz_confusao_rf = confusion_matrix(y_test, modelo_rf.predict(X_test))
print("Matriz de Confusão do modelo RandomForest:")
print(matriz_confusao_rf)

# Suponha que você tenha um arquivo CSV chamado 'novos_dados.csv' com as colunas 'umidade', 'temperatura' e 'pressao'.
# Carregue os novos dados em um DataFrame

novos_dados = pd.read_csv('C:/Codigos/IA/novos_dados.csv', sep=';', decimal=',')

# Pré-processe os novos dados da mesma maneira que fez com os dados de treinamento
X_novos = novos_dados[['umidade', 'temperatura', 'pressao']]
X_novos = imputer.transform(X_novos)  # Lembre-se de aplicar a mesma transformação que fez nos dados de treinamento

# Agora, você pode fazer previsões com o modelo treinado
previsoes_rf = modelo_rf.predict(X_novos)

# Exiba as previsões
print("Previsões do modelo RandomForest:")
print(previsoes_rf)