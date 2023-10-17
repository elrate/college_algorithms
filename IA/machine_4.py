import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.impute import SimpleImputer
from sklearn.metrics import confusion_matrix

# Carregar os dados do arquivo CSV (substitua 'seuarquivo.csv' pelo caminho real)
df = pd.read_csv('C:/Codigos/IA/dados-ano-2023.csv', sep=';', decimal=',')

# Preparar os dados
X = df[['umidade', 'temperatura', 'pressao', 'precipitacao']]

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

# Exibir as probabilidades do modelo RandomForest em um arquivo
print("Salvando as probabilidades do modelo RandomForest em um arquivo...")
with open('probabilidades_random_forest.txt', 'w') as f:
    for prob in probabilidade_choveu_rf:
        f.write(str(prob) + '\n')

# Exibir as probabilidades do modelo SVM em um arquivo
print("Salvando as probabilidades do modelo SVM em um arquivo...")
with open('probabilidades_svm.txt', 'w') as f:
    for prob in probabilidade_choveu_svm:
        f.write(str(prob) + '\n')

# Avalie o desempenho do modelo SVM com uma matriz de confusão
matriz_confusao_svm = confusion_matrix(y_test, modelo_svm.predict(X_test))
print("Matriz de Confusão do modelo SVM:")
print(matriz_confusao_svm)
