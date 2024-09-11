[Link do video no Youtube](https://youtu.be/tWev-09nh78) 

### Objetivos
1. Determinar se o escalonamento de uma carga de trabalho específica é viável usando o algoritmo Rate Monotonic.
2. Sugerir um escalonamento possível para a carga de trabalho utilizando uma heurística baseada na análise das tarefas fornecidas.

### Modo de Usar

O algoritmo recebe um arquivo json contendo um array de tarefas periódicas, em que cada tarefa possuí um identificador, o período de execução e o tempo de execução. O executável busca pelo arquivo `tarefas.json`, ler as entradas e verifica se o escalonamento é possível.

#### Exemplo de entrada
```.json
{
    "tasks": [
        {
            "id": "T1",
            "period": 50,
            "execution_time": 10
        },
        {
            "id": "T2",
            "period": 100,
            "execution_time": 20
        },
    ]
}
```

### Bibliotecas Third-Party:
- [json-c](https://github.com/json-c/json-c) versão 0.17

## Instalação

### Windows
Este repositório incluí as depêndencias pré-compiladas das dependências para Windows (x64). Não é necessário instalar nenhuma biblioteca manualmente.

Requer:
  - Compilador GCC para windows (e.g: MingGW64)
    - o caminho para o g++.exe deve estar incluído na váriavel de ambiente PATH 
  - [Cmake](https://cmake.org/download/)

  Para compilar o projeto utilize abra um prompt de comando e execute:
  ```.cmd
  cmake -G "MinGW Makefiles" -Bbuild .
  cmake --build build
  ```
  Ainda no promt, execute  `build\main.exe`

  Ou instale a extensão "CMake Tools" no Visual Studio Code.
  
### Linux
  Requer:
  - gcc 9.4.0
  - make

  Execute no terminal bash `make all` para compilar o projeto.
