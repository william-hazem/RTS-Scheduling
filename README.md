Bibliotecas Third-Party:
- [json-c](https://github.com/json-c/json-c) versão 0.17

## Instalação
Este repositório incluí as depêndencias pré-compiladas das dependências para Windows (x64) e Linux. Não é necessário instalar nenhuma biblioteca manualmente.

### Windows
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
