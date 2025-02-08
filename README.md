# 📚 Gerenciamento de Biblioteca

Este projeto implementa um sistema de gerenciamento de biblioteca utilizando **Estruturas de Dados em C**.

## 🛠️ Compilação e Execução

### 1️⃣ Acesse o diretório do projeto:
```bash
cd /c/example/biblioteca
```

### 2️⃣ Compile o programa:
```bash
    gcc biblioteca.c main.c -lm -o biblioteca.bin

```

### 3️⃣ Execute o programa:
```bash
./biblioteca.bin <entrada> <saida>
```
Exemplo de uso:
```bash
./biblioteca.bin entrada.txt saida.txt
```

## 📜 Formato do Arquivo de Entrada
O arquivo de entrada deve seguir o formato abaixo:
```
I 10001 OSenhorDosAneis,JRRRTolkien,1954,Fantasia
I 10002 DomCasmurro,MachadoDeAssis,1899,Romance
R 10001
B 10002
F
```
- `I <ID> <Título>,<Autor>,<Ano>,<Gênero>` → Insere um novo livro na biblioteca.  
- `R <ID>` → Remove o livro com o ID informado.  
- `B <ID>` → Busca e exibe as informações do livro com o ID informado.  
- `F` → Finaliza a leitura do arquivo.  


---

📌 **Autor:** Yasmim Stefane Faria  e Maria Eduarda Siqueira
📌 **Disciplina:** Estruturas de Dados  

---

