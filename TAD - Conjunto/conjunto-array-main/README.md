# Informações do Projeto

- **Instituição:** IMD
- **Disciplina:** EDB1
- **Professor:** Prof. Eiji Adachi

  
## Implementação de Conjunto usando Array

### ✅ **O que é um Conjunto?**
Um **Conjunto** é um tipo abstrato de dados que armazena **elementos únicos**, ou seja, não permite repetições. É amplamente utilizado quando queremos realizar operações como:
- Inserção de elementos.
- Remoção de elementos.
- Verificação de existência (operação `contem`).
- Consulta do tamanho atual do conjunto.

Este projeto implementa um Conjunto utilizando **arrays** em C++, com foco em práticas de programação modular, testes automatizados e organização de código.

---

### 📂 **Estrutura de Diretórios**

```
.
├── bin/       # Executáveis gerados após a compilação
├── doc/       # Documentação do projeto
├── header/    # Arquivos de cabeçalho (.h) 
├── lib/       # Bibliotecas externas (ex: doctest.h)
├── src/       # Implementação das classes (.cpp)
├── test/      # Arquivos de teste (usando doctest)
├── .gitignore # Arquivos/diretórios ignorados pelo Git
├── makefile   # Automação da compilação e execução
└── README.md  # Este arquivo
```

---

### 🛠️ **Implementação das Operações do Conjunto**

### 📌 **Arquivo de Interface (`header/Conjunto.h`):**
Define a estrutura da classe `Conjunto` e suas operações públicas:

- `bool inserir(int elemento);`  
- `bool remover(int elemento);`  
- `bool contem(int elemento) const;`  
- `int tamanho() const;`  
- `void imprimir() const;`  

#### 📌 **Arquivo de Implementação (`src/Conjunto.cpp`):**
Deve conter a lógica completa de manipulação do conjunto e implementação dos métodos. É aqui onde você deve implementar as operações do Conjunto.

#### 📌 **Testes Automatizados (`test/teste.cpp`):**
Os testes são escritos utilizando o framework **doctest**, garantindo a validação automática de todas as operações da estrutura de dados.

---

### 📦 **Como Compilar e Executar Usando o Makefile**

O projeto inclui um `makefile` configurado para facilitar a compilação e execução. 

#### 🔧 **Comandos Disponíveis:**

| Comando        | Descrição                                   |
|----------------|---------------------------------------------|
| `make` ou `make all`  | Compila o programa principal e os testes. |
| `make run`     | Executa o programa principal (`bin/main`).  |
| `make test`    | Compila apenas os testes.                   |
| `make run-test`| Executa os testes (`bin/test`).             |
| `make clean`   | Remove arquivos objeto e executáveis.       |

#### 📌 **Exemplos de Uso:**

```bash
# Compilar o projeto
make

# Executar o programa principal
make run

# Compilar e rodar os testes
make test
make run-test

# Limpar os arquivos de build
make clean
```