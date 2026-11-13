# PSE Sonora: Saúde Auditiva nas Escolas

Projeto acadêmico (AEP 2026) do curso de Análise e Desenvolvimento de Sistemas.

## Integrantes

| Nome | RA |
|---|---|
| Henrique Lorenzato Santana | 26008322-2 |
| Matheus Marins | 26004875-2 |
| João Vitor S. Varini | 26000305-2 |

## Sobre o projeto

O PSE Sonora é um sistema em linguagem C, executado pelo terminal, que apoia a organização de ações educativas sobre saúde auditiva no ambiente escolar. O foco das ações é a conscientização sobre o uso responsável de fones de ouvido, dentro da proposta do Programa Saúde na Escola (PSE).

O sistema permite cadastrar, buscar, listar e acompanhar as ações realizadas pela iniciativa fictícia PSE Sonora, além de gerar um resumo com a participação dos estudantes.

> O projeto tem caráter educativo e utiliza apenas dados fictícios. O sistema não realiza diagnósticos nem armazena informações pessoais ou clínicas de estudantes.

## Funcionalidades

| Opção do menu | Funcionalidade | Requisito |
|---|---|---|
| 1 - Cadastro acao | Cadastra uma ação com nome, escola, tema, data, público-alvo, responsáveis e quantidade prevista de participantes. O código é gerado automaticamente. | RF01 |
| 2 - Buscar acao | Busca uma ação por **código**, **escola** ou **tema**. A busca por escola e tema aceita parte do texto e não diferencia maiúsculas de minúsculas. | RF03 |
| 3 - Listar acao | Lista todas as ações cadastradas. | RF02 |
| 4 - Atualizar acao | Edita os dados de uma ação ou altera sua situação para **Planejada**, **Realizada** ou **Cancelada**. Ao marcar como Realizada, o sistema pede a quantidade real de participantes. | RF04 |
| 5 - Resumo das acoes | Mostra o total de ações, a quantidade por situação, o total de participantes e o percentual de participação (reais ÷ previstos das ações realizadas). | RF05 |
| 0 - Sair | Salva os dados e encerra o programa. | — |

### Validações (RNF02)

- Códigos únicos, gerados automaticamente pelo sistema.
- Campos de texto não podem ficar vazios nem ultrapassar o tamanho máximo.
- Datas no formato `DD/MM/AAAA`, com checagem de dias por mês e anos bissextos.
- Quantidades de participantes não podem ser negativas.
- Opções de menu inválidas e entradas não numéricas são recusadas.

## Como executar

### Pré-requisito

Um compilador C:

- **Windows:** [MinGW-w64](https://www.mingw-w64.org/), ou uma IDE que já o inclua, como Dev-C++ ou Code::Blocks.
- **Linux:** `gcc` (no Ubuntu/Debian: `sudo apt install gcc`).
- **macOS:** `gcc`/`clang`, instalados com `xcode-select --install`.

### Compilar e executar pelo terminal

1. Baixe o repositório (botão **Code → Download ZIP**) ou clone:
```bash
   git clone https://github.com/Olorenzatoo/Entrega_AEP_2026.git
   cd Entrega_AEP_2026
```
2. Compile:
```bash
   gcc mainAEP.c -o pse_sonora
```
3. Execute:
   - **Windows:** `pse_sonora.exe`
   - **Linux/macOS:** `./pse_sonora`

### Pela IDE (Dev-C++ / Code::Blocks)

Abra o arquivo `mainAEP.c` e use a opção **Compilar e Executar** (no Dev-C++, a tecla `F11`).

## Como usar

1. No menu principal, digite o número da opção desejada e pressione **ENTER**.
2. Comece cadastrando uma ação (opção 1). Ela inicia com a situação **Planejada**.
3. Depois que a ação acontecer, use a opção 4 → 2 para marcá-la como **Realizada** e informar quantos participantes compareceram.
4. Use a opção 5 para ver o resumo e o percentual de participação.

## Armazenamento dos dados

As ações ficam salvas no arquivo `acoes.dat`, criado automaticamente na pasta em que o programa é executado. O arquivo é atualizado a cada cadastro ou alteração e lido ao abrir o programa. Assim, os dados continuam disponíveis entre uma execução e outra.

Para começar do zero, basta apagar o `acoes.dat`.

## Estrutura do repositório

```
Entrega_AEP_2026/
├── mainAEP.c        # Código-fonte do sistema
├── README.md        # Este arquivo
├── .gitignore       # Evita enviar executáveis e o arquivo de dados
└── Docs/
    └── AEP_final_1B.pdf   # Documentação da 1ª etapa (requisitos, fluxograma, pseudocódigo)
```

## Vídeo de apresentação

🎥 [Assistir à apresentação do projeto](https://youtu.be/V1IljfnvDk4)
