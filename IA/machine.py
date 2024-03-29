import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC  # Importar o SVM (Support Vector Machine)
from sklearn.impute import SimpleImputer
from sklearn.metrics import confusion_matrix

# Carregar os dados do arquivo CSV (substitua 'seuarquivo.csv' pelo caminho real)
df = pd.read_csv('C:/Codigos/IA/dados_tempo_2.csv', sep=';')

# Corrigir as vírgulas nos valores de todas as colunas numéricas e converter para float
colunas_numericas = ['umidade', 'temperatura', 'velocidade', 'precipitacao']
df[colunas_numericas] = df[colunas_numericas].apply(lambda x: x.str.replace(',', '.').astype(float))

# Preparar os dados
X = df[['umidade', 'temperatura', 'velocidade', 'precipitacao']]

# Preencher valores ausentes com a média da coluna
imputer = SimpleImputer(strategy='mean')
X = imputer.fit_transform(X)

y = (df['precipitacao'] > 0).astype(int)  # Se precipitação > 0, então choveu (1), senão não choveu (0)

# Dividir os dados em conjunto de treinamento e teste
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Criar e treinar o modelo de classificação RandomForest
modelo_rf = RandomForestClassifier(n_estimators=100, random_state=42)
modelo_rf.fit(X_train, y_train)

# Obter as probabilidades das classes com RandomForest
probabilidades_rf = modelo_rf.predict_proba(X_test)

# As probabilidades da classe 1 (choveu) estão nas colunas 1 do array
probabilidade_choveu_rf = probabilidades_rf[:, 1]

# Criar e treinar o modelo SVM para classificação
modelo_svm = SVC(probability=True)
modelo_svm.fit(X_train, y_train)

# Obter as probabilidades das classes com SVM
probabilidades_svm = modelo_svm.predict_proba(X_test)

# As probabilidades da classe 1 (choveu) estão nas colunas 1 do array
probabilidade_choveu_svm = probabilidades_svm[:, 1]

# Verificar o número de probabilidades
numero_de_probabilidades = probabilidades_rf.shape[0]
print(f'Número de probabilidades: {numero_de_probabilidades}')

# Exibir as probabilidades do modelo RandomForest
print("Probabilidades do modelo RandomForest:")
print(probabilidade_choveu_rf)

# Exibir as probabilidades do modelo SVM
print("Probabilidades do modelo SVM:")
print(probabilidade_choveu_svm)

# Avalie o desempenho do modelo SVM com uma matriz de confusão
matriz_confusao_svm = confusion_matrix(y_test, modelo_svm.predict(X_test))
print("Matriz de Confusão do modelo SVM:")
print(matriz_confusao_svm)