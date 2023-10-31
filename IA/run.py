import schedule
import subprocess
import time

def execute_code1():
    # Substitua 'code1.py' pelo nome do seu primeiro arquivo Python
    subprocess.run(['python', 'C:/Codigos/IA/entrada.py'])

def execute_code2():
    # Substitua 'code1.py' pelo nome do seu primeiro arquivo Python
    subprocess.run(['python', 'C:/Codigos/IA/algoritmos/fuzzy.py'])
def execute_code3():
    # Substitua 'code2.py' pelo nome do seu segundo arquivo Python
    subprocess.run(['python', 'C:/Codigos/IA/algoritmos/regressao-linear.py'])

def execute_code4():
    # Substitua 'code2.py' pelo nome do seu segundo arquivo Python
    subprocess.run(['python', 'C:/Codigos/IA/saida.py'])  

# Agende a execução de code1 e code2 a cada 1 minuto
schedule.every().minutes.do(execute_code1)
schedule.every().minutes.do(execute_code2)
schedule.every().minutes.do(execute_code3)
schedule.every().minutes.do(execute_code4)

while True:
    schedule.run_pending()
    time.sleep(1)