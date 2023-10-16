import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.neighbors import KNeighborsClassifier
from sklearn.impute import SimpleImputer
from sklearn.metrics import confusion_matrix, accuracy_score, recall_score, f1_score
from sklearn.model_selection import GridSearchCV

# Carregar os dados do arquivo CSV (substitua 'seuarquivo.csv' pelo caminho real)
df = pd.read_csv('/content/dados_tempo_2.csv', sep=';')

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

# Defina uma grade de valores para os hiperparâmetros do Random Forest
param_grid_rf = {
    'n_estimators': [100, 200, 300],
    'max_depth': [None, 10, 20, 30],
    'min_samples_split': [2, 5, 10],
    'min_samples_leaf': [1, 2, 4]
}

# Crie um objeto GridSearchCV com o classificador Random Forest e a grade de hiperparâmetros
grid_search_rf = GridSearchCV(RandomForestClassifier(random_state=42), param_grid_rf, cv=5)

# Realize a pesquisa em grade no conjunto de treinamento
grid_search_rf.fit(X_train, y_train)

# Obtenha os melhores hiperparâmetros encontrados
best_params_rf = grid_search_rf.best_params_
print("Melhores hiperparâmetros encontrados para o Random Forest:", best_params_rf)

# Avalie o modelo Random Forest com os melhores hiperparâmetros no conjunto de teste
best_model_rf = grid_search_rf.best_estimator_
best_model_rf.fit(X_train, y_train)

# Obter as probabilidades das classes com K-NN
modelo_knn = KNeighborsClassifier(n_neighbors=5)
modelo_knn.fit(X_train, y_train)
probabilidades_knn = modelo_knn.predict_proba(X_test)

# Obter as probabilidades das classes com RandomForest
probabilidades_rf = best_model_rf.predict_proba(X_test)

# Obtenha as probabilidades das classes com SVM
param_grid_svm = {
    'C': [0.1, 1, 10, 100],
    'kernel': ['linear', 'poly', 'rbf'],
    'degree': [2, 3, 4],
}

# Crie um objeto GridSearchCV com o classificador SVM e a grade de hiperparâmetros
grid_search_svm = GridSearchCV(SVC(probability=True), param_grid_svm, cv=5)

# Realize a pesquisa em grade no conjunto de treinamento
grid_search_svm.fit(X_train, y_train)

# Obtenha os melhores hiperparâmetros encontrados
best_params_svm = grid_search_svm.best_params_
print("Melhores hiperparâmetros encontrados para o SVM:", best_params_svm)

# Avalie o modelo SVM com os melhores hiperparâmetros no conjunto de teste
best_model_svm = grid_search_svm.best_estimator_
best_model_svm.fit(X_train, y_train)

# Obtenha as probabilidades das classes com SVM
probabilidades_svm = best_model_svm.predict_proba(X_test)

# As probabilidades da classe 1 (choveu) estão nas colunas 1 do array
probabilidade_choveu_knn = probabilidades_knn[:, 1]
probabilidade_choveu_rf = probabilidades_rf[:, 1]
probabilidade_choveu_svm = probabilidades_svm[:, 1]

# Exibir as probabilidades do modelo K-NN
print("Probabilidades do modelo K-NN:")
print(probabilidade_choveu_knn)

# Exibir as probabilidades do modelo RandomForest
print("Probabilidades do modelo Random Forest:")
print(probabilidade_choveu_rf)

# Exibir as probabilidades do modelo SVM
print("Probabilidades do modelo SVM:")
print(probabilidade_choveu_svm)

# Realize previsões no conjunto de teste para K-NN
y_pred_knn = modelo_knn.predict(X_test)

# Exibir as métricas de avaliação para K-NN
print("Métricas de avaliação do modelo K-NN:")
print("Precisão (K-NN):", accuracy_score(y_test, y_pred_knn))
print("Revocação (K-NN):", recall_score(y_test, y_pred_knn))
print("F1-Score (K-NN):", f1_score(y_test, y_pred_knn))

# Exibir a matriz de confusão para K-NN
matriz_confusao_knn = confusion_matrix(y_test, y_pred_knn)
print("Matriz de Confusão do modelo K-NN:")
print(matriz_confusao_knn)

# Realize previsões no conjunto de teste para Random Forest
y_pred_rf = best_model_rf.predict(X_test)

# Exibir as métricas de avaliação para Random Forest
print("Métricas de avaliação do modelo Random Forest:")
print("Precisão (Random Forest):", accuracy_score(y_test, y_pred_rf))
print("Revocação (Random Forest):", recall_score(y_test, y_pred_rf))
print("F1-Score (Random Forest):", f1_score(y_test, y_pred_rf))

# Exibir a matriz de confusão para Random Forest
matriz_confusao_rf = confusion_matrix(y_test, y_pred_rf)
print("Matriz de Confusão do modelo Random Forest:")
print(matriz_confusao_rf)

# Realize previsões no conjunto de teste para SVM
y_pred_svm = best_model_svm.predict(X_test)

# Exibir as métricas de avaliação para SVM
print("Métricas de avaliação do modelo SVM:")
print("Precisão (SVM):", accuracy_score(y_test, y_pred_svm))
print("Revocação (SVM):", recall_score(y_test, y_pred_svm))
print("F1-Score (SVM):", f1_score(y_test, y_pred_svm))

# Exibir a matriz de confusão para SVM
matriz_confusao_svm = confusion_matrix(y_test, y_pred_svm)
print("Matriz de Confusão do modelo SVM:")
print(matriz_confusao_svm)