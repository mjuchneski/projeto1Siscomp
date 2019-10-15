# QtCacheSim – Simulador de Algoritmos de Substituição de Página de Memória em Cache

<div style="display: flex; justify-content: center;">
    <img src="QtCacheSim.png" alt="QtCacheSim" text-align="center" height="50%" width="50%" style="margin:30px 0px">
</div>

Projeto apresentado como componente avaliativo na disciplina de Sistemas de Computação do Programa de Pós-Graduação (PGC) do Instituto de Computação/Universidade Federal Fluminense (IC/UFF).

## Descrição

Pelo fato da memória cache possuir menos espaço que a memória principal, é necessário que seja implementado um mecanismo que permita que os endereços da memória principal sejam de alguma forma associados a endereços da cache, além de uma política de substituição desses dados caso seja necessária a atualização pelo processador. Dessa maneira, esse simulador se propõe a demonstrar de forma didática como pode ocorrer a escolha e a substituição de uma posição de memória na cache em três modelos diferentes de mapeamento – direto, associativo e associativo por conjuntos – e quatro diferentes algoritmos de ordenação – FIFO, LRU, LFU e RANDOM.

## Implementação

Em seu desenvolvimento foi utilizada a linguagem de programação C++ em combinação com o Qt (framework para desenvolvimento de interfaces gráficas) em sua versão 5.12.4 através da IDE (ambiente de desenvolvimento integrado) QtCreator. Mais informações sobre como instalar tanto em Windows, Linux ou macOS podem ser vistas [aqui](https://doc.qt.io/qt-5/gettingstarted.html).

## Execução

Já para sua execução basta utilizar como entrada o caminho e nome de um arquivo de extensão `.txt` a ser lido e que possua a sequência de referências às páginas de memória principal (endereços) no formato de um número inteiro por linha e então informar como parâmetros a capacidade total da memória cache, o esquema de mapeamento - direto, associativo ou associativo por conjuntos (no caso do mapeamento associativo por conjuntos deve-se informar também o número de conjuntos pretendidos) e por fim selecionar o algoritmo de ordenação dos dados - FIFO, LRU, LFU ou RANDOM.

Assim sendo, são simuladas as substituições e exibidas como saídas na tabela ao lado todas as páginas armazenadas na memória cache de acordo com o mapeamento e algoritmo escolhidos, além do número de hits, misses e sua consequente taxa de acertos às referências de memória.