# TP-AedsIII-UFSJ
# Projeto de Análise de Grafo de Fluxo de Controle

Este é um projeto que envolve a análise de um grafo de fluxo de controle de um programa. O código apresentado é responsável por ler um arquivo de texto contendo as instruções do programa e construir um grafo representando o fluxo de controle do programa.

## Estrutura do Projeto

O projeto está estruturado da seguinte forma:

1. **Estruturas de Dados:** O projeto faz uso de duas principais estruturas de dados: `No` e `Grafo`. A estrutura `No` representa um nó do grafo e contém o número do bloco (vertice) e um ponteiro para o próximo nó. A estrutura `Grafo` representa o grafo em si e contém o número de vértices e uma matriz de listas de adjacência.

2. **Função de Criação de Nós (`criarNo`):** Essa função aloca memória para um novo nó e inicializa suas propriedades, incluindo o número do bloco e o ponteiro para o próximo nó.

3. **Função de Criação do Grafo (`criarGrafo`):** Essa função cria um grafo inicial contendo um vértice. Ela aloca memória para o grafo, inicializa o número de vértices como 1 e aloca memória para a matriz de lista de adjacência, definindo a primeira posição como NULL.

4. **Função de Adição de Ligação (`addLig`):** Essa função é responsável por adicionar uma ligação entre dois blocos no grafo. Ela verifica se o bloco de destino já existe no grafo, caso contrário, redimensiona a matriz de lista de adjacência. Em seguida, cria um novo nó e o insere na lista de adjacência do bloco de origem, garantindo que a lista permaneça ordenada.

5. **Função de Impressão do Grafo (`imprimir`):** Essa função imprime o grafo, mostrando as ligações entre os blocos.

6. **Função de Leitura do Arquivo (`readArq`):** Esta função é responsável por ler as instruções de um arquivo de texto e construir o grafo de fluxo de controle com base nessas instruções. Ela identifica blocos de código, ligações condicionais (if-goto) e ligações por meio de labels (goto).

## Funcionamento do Projeto

O projeto lê um arquivo chamado "arq1.txt", que contém as instruções do programa. Ele identifica os blocos de código com base nas instruções e cria as ligações no grafo. Os blocos são representados por números (B1, B2, etc.). As ligações condicionais (if-goto) entre blocos são identificadas, e as ligações por meio de labels (goto) são estabelecidas.

## Como Executar o Projeto

Para executar o projeto, basta compilar o código fornecido em um ambiente que suporta a linguagem C. Certifique-se de ter um arquivo chamado "arq1.txt" no mesmo diretório do código-fonte, contendo as instruções do programa que deseja analisar. Após a compilação e execução do programa, ele lerá o arquivo, construirá o grafo de fluxo de controle e o imprimirá na saída padrão.

## Contribuições

Este projeto pode ser expandido e aprimorado de várias maneiras. Você pode adicionar recursos para identificar mais tipos de instruções ou melhorar a visualização do grafo. Sinta-se à vontade para contribuir e personalizar o projeto de acordo com suas necessidades.
