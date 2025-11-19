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