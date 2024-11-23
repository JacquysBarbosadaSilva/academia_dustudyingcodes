import pandas as pd
import tkinter as tk
from tkinter import filedialog, messagebox, ttk

def validar_peca(peso, tamanho, acabamento):
    if 50 <= peso <= 100 and 10 <= tamanho <= 20 and acabamento > 7:
        return "Aprovada"
    else:
        return "Rejeitada"

def analisar_pecas(arquivo_csv):
    df = pd.read_csv(arquivo_csv)

    total_pecas = len(df)
    aprovadas = 0
    rejeitadas = 0
    pecas_rejeitadas = []

    for i, row in df.iterrows():
        resultado = validar_peca(row['Peso'], row['Tamanho'], row['Acabamento'])
        df.at[i, 'Resultado'] = resultado
        
        if resultado == "Aprovada":
            aprovadas += 1
        else:
            rejeitadas += 1
            pecas_rejeitadas.append(row)

    percentual_rejeitadas = (rejeitadas / total_pecas) * 100

    if percentual_rejeitadas > 20:
        messagebox.showwarning("Alerta", "Mais de 20% das peças foram rejeitadas! Revisar o processo.")

    if pecas_rejeitadas:
        print("Peças Rejeitadas para análise:")
        for peca in pecas_rejeitadas:
            print(peca)

    print(f"\nQuantidade de peças analisadas: {total_pecas}")
    print(f"Percentual de peças aprovadas: {(aprovadas / total_pecas) * 100:.2f}%")
    print(f"Percentual de peças rejeitadas: {(rejeitadas / total_pecas) * 100:.2f}%")
    
    return df

def abrir_arquivo():
    arquivo_csv = filedialog.askopenfilename(title="Selecionar arquivo CSV", filetypes=[("CSV Files", "*.csv")])
    
    if arquivo_csv:
        resultado_df = analisar_pecas(arquivo_csv)
        exibir_tabela(resultado_df)

def exibir_tabela(df):

    for item in tree.get_children():
        tree.delete(item)

    tree["columns"] = list(df.columns)

    for coluna in df.columns:
        tree.heading(coluna, text=coluna)
        tree.column(coluna, width=100)  


    for _, row in df.iterrows():
        tree.insert("", "end", values=list(row))

def criar_interface():
    global tree
    root = tk.Tk()
    root.title("Analisador de Peças - QualityAI Solutions")


    btn_abrir = tk.Button(root, text="Abrir Arquivo CSV", command=abrir_arquivo)
    btn_abrir.pack(pady=20)

    tree = ttk.Treeview(root, show="headings")
    tree.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
    root.mainloop()

if __name__ == "__main__":
    criar_interface()
