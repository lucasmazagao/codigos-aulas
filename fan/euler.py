import pandas as pd
import numpy as np

def euler(x0, y0, h, objetivo_c):
    passos = []
    x, y = x0, y0
    contagem = 0
    
    # inicial
    passos.append({
        "n": contagem,
        "x_n": round(x, 8),
        "y_n": round(y, 8),
        "f(x,y)": round(x/y, 8),
        "y_n+1": round(y + h*(x/y), 8),
        "c": round(x*y, 8)
    })
    
    while (x * y) < objetivo_c:
        dxdy = x / y
        y_k = y + h * dxdy
        x_k = x + h
        
        x = x_k
        y = y_k
        contagem += 1
        
        dxdy = x/y
        y_prox = y + h*dxdy
        
        passos.append({
            "n": contagem,
            "x_n": round(x, 8),
            "y_n": round(y, 8),
            "f(x,y)": round(dxdy, 8),
            "y_n+1": round(y_prox, 8),
            "c": round(x*y, 8)
        })
        
    return pd.DataFrame(passos)

# gerar tabelas para diferentes condições iniciais
df1 = euler(0.5, 2.0, 0.1, 4.0)
df2 = euler(1.0, 1.0, 0.1, 4.0)
df3 = euler(2.0, 0.5, 0.1, 4.0)

print("Tabela 1 Inicio (0.5, 2.0)")
print(df1)
print("\nTabela 2 Inicio (1.0, 1.0)")
print(df2)
print("\nTabela 3 Inicio (2.0, 0.5)")
print(df3)

import matplotlib.pyplot as plt
import numpy as np

def metodo_euler(x0, y0, h, c_alvo):
    """
    Calcula a trajetória usando o Método de Euler até que x*y >= c_alvo
    """
    xs = [x0]
    ys = [y0]
    
    x = x0
    y = y0
    
    # Limite de passos para evitar loop infinito
    max_steps = 50 
    step = 0
    
    while (x * y) < c_alvo and step < max_steps:
        # Inclinação da ortogonal: dy/dx = x/y
        slope = x / y
        
        # Euler: y_prox = y_atual + h * inclinação
        y_new = y + h * slope
        x_new = x + h
        
        # Atualiza variáveis
        x = x_new
        y = y_new
        
        # Armazena
        xs.append(x)
        ys.append(y)
        step += 1
        
    return xs, ys

# --- Configurações ---
h = 0.1
c_final = 4.0

x1, y1 = metodo_euler(0.5, 2.0, h, c_final)

x2, y2 = metodo_euler(1.0, 1.0, h, c_final)

x3, y3 = metodo_euler(2.0, 0.5, h, c_final)

plt.figure(figsize=(8, 8))

# 1. Desenhar as curvas de fundo (xy=c) para referência
x_grid = np.linspace(0.2, 3.5, 400)
y_c1 = 1.0 / x_grid  # Curva xy=1
y_c4 = 4.0 / x_grid  # Curva xy=4

plt.plot(x_grid, y_c1, 'b--', linewidth=1.5, label='Curva Inicial - C = 1')
plt.plot(x_grid, y_c4, 'g--', linewidth=1.5, label='Curva Final - C = 4')

# 2. Desenhar as trajetórias de Euler
plt.plot(x1, y1, color='red', markersize=5, label='Ponto 1: (0.5, 2.0)')
plt.plot(x2, y2, color='yellow', markersize=5, label='Ponto 2: (1.0, 1.0)')
plt.plot(x3, y3, color='blue', markersize=5, label='Ponto 3: (2.0, 0.5)')

# 3. Formatação
plt.title('Trajetórias Ortogonais')
plt.xlabel('X')
plt.ylabel('Y')
plt.xlim(0, 3.0)
plt.ylim(0, 3.0)
plt.legend()
plt.grid(True, linestyle=':', alpha=0.6)

# Exibir o gráfico
plt.show()
