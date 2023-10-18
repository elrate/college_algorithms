import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.metrics import confusion_matrix
from sklearn.impute import SimpleImputer

# Carregar os dados do arquivo CSV (substitua 'seuarquivo.csv' pelo caminho real)
df = pd.read_csv('C:/Codigos/IA/dados-completo-2020_2023.csv', sep=';', decimal=',')

# Corrigir os valores de precipitação formatados incorretamente e converter para float
df['precipitacao'] = pd.to_numeric(df['precipitacao'], errors='coerce')
df['precipitacao'] = df['precipitacao'].fillna(0)  # Substituir valores incorretos por 0

# Converter as colunas 'temperatura' e 'pressao' em números
df['temperatura'] = pd.to_numeric(df['temperatura'], errors='coerce')
df['pressao'] = pd.to_numeric(df['pressao'], errors='coerce')

# Preparar os dados
X = df[['umidade', 'temperatura', 'pressao']]
y = (df['precipitacao'] > 0).astype(int)  # Se precipitação > 0, então choveu (1), senão não choveu (0)

# Preencher valores ausentes com a média da coluna
imputer = SimpleImputer(strategy='mean')
X = imputer.fit_transform(X)

# Dividir os dados em conjunto de treinamento e teste
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Criar e treinar o modelo SVM
modelo_svm = SVC(kernel='linear', random_state=42)  # Usamos um kernel linear para classificação
modelo_svm.fit(X_train, y_train)

# Avaliar o desempenho do modelo SVM
matriz_confusao_svm = confusion_matrix(y_test, modelo_svm.predict(X_test))
print("Matriz de Confusão do modelo SVM:")
print(matriz_confusao_svm)

# Suponha que você tenha um arquivo CSV chamado 'novos_dados.csv' com as colunas 'umidade', 'temperatura' e 'pressao'.
# Carregue os novos dados em um DataFrame

novos_dados = pd.read_csv('C:/Codigos/IA/novos_dados.csv', sep=';', decimal=',')

# Pré-processe os novos dados da mesma maneira que fez com os dados de treinamento
X_novos = novos_dados[['umidade', 'temperatura', 'pressao']]
X_novos = imputer.transform(X_novos)  # Lembre-se de aplicar a mesma transformação que fez nos dados de treinamento

# Agora, você pode fazer previsões com o modelo treinado
previsoes_svm = modelo_svm.predict(X_novos)

# Exiba as previsões
print("Previsões do modelo SVM:")
print(previsoes_svm)