import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.impute import SimpleImputer
import schedule
import time

# Carregar os dados do arquivo CSV para treinamento
df = pd.read_csv('C:/Codigos/IA/dados_tempo_2.csv', sep=';')

# Corrigir as vírgulas nos valores de todas as colunas numéricas e converter para float
colunas_numericas = ['umidade', 'temperatura', 'velocidade', 'precipitacao']
df[colunas_numericas] = df[colunas_numericas].apply(lambda x: x.str.replace(',', '.').astype(float))

# Preencher valores ausentes com a média da coluna
imputer = SimpleImputer(strategy='mean')
X = df[['umidade', 'temperatura', 'velocidade', 'precipitacao']]
X = imputer.fit_transform(X)
y = (df['precipitacao'] > 0).astype(int)

# Treinar o modelo de classificação
modelo = RandomForestClassifier(n_estimators=100, random_state=42)
modelo.fit(X, y)

# Função para analisar dados de um arquivo TXT
def analisar_dados_arquivo():
    # Carregar os dados do arquivo TXT (substitua 'seuarquivo.txt' pelo caminho real)
    df = pd.read_csv('C:/Caminho/Para/Seu/Arquivo.txt', sep=';')

    # Corrigir as vírgulas nos valores de todas as colunas numéricas e converter para float
    colunas_numericas = ['umidade', 'temperatura', 'velocidade', 'precipitacao']
    df[colunas_numericas] = df[colunas_numericas].apply(lambda x: x.str.replace(',', '.').astype(float))

    # Preparar os dados
    X = df[['umidade', 'temperatura', 'velocidade', 'precipitacao']]

    # Preencher valores ausentes com a média da coluna
    imputer = SimpleImputer(strategy='mean')
    X = imputer.fit_transform(X)

    # Realizar a análise usando o modelo
    probabilidades = modelo.predict_proba(X)
    probabilidade_choveu = probabilidades[:, 1]

    print(f'Probabilidade de chuva: {probabilidade_choveu}')

# Agendar a análise a cada 1 hora
schedule.every(1).hours.do(analisar_dados_arquivo)

# Loop infinito para manter o agendamento em execução
while True:
    schedule.run_pending()
    time.sleep(1)  # Pequena pausa para economizar recursos
