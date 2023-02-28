# Sorting-Algorithms

## :clipboard: Introdução

A manipulação de dados de forma a ordená-los é um problema antigo e amplamente estudado na ciência da computação. Inúmeros algoritmos foram desenvolvidos ao longo dos anos, dentre eles
detacam-se algoritmos bastante difundidos na literatura, como o Selection sort, Bubble sort, Insertion sort, Merge sort, Quick sort, Counting sort, etc. O objetivo deste projeto
é fornecer um mecanismo de visualização do processo de ordenação dos algoritmos. O exemplo abaixo mostra uma ordenação feita pelo quick sort.

![](https://github.com/laskoskjoao/Sorting-Algorithms/blob/main/quick.gif)


## :bar_chart: Funcionamento

No momento, o menu exibido pelo programa é no terminal, sendo possível assim selecionar o número de elementos a serem ordenados e o algoritmo de ordenação.

![](https://github.com/laskoskjoao/Sorting-Algorithms/blob/main/menu.png)

Existe um número máximo de elementos a serem ordenados que depende da largura da janela (no caso da imagem acima, o processo só ira ser visualizado se o usuário escolher um
valor entre 1 - 400). Caso seja necessário, pode-se alterar o tamanho da janela por intermédio dos seguintes defines:

~~~ C++
#define HEIGHT_WINDOW 600
#define WIDTH_WINDOW 800
~~~

Ao final do processo, o programa ainda exibe informações do processo: Número de trocas (swaps) e Número de comparações (comparisons), que no decorrer do processo são indicados 
pelas cores vermelha e azul, respectivamente.

## :question: Como executar

O programa foi desenvolvido utilizando a biblioteca gráfica SFML 2.5.1 (versão 32 bits), portanto é necessário baixá-la e adicioná-la ao projeto para que seja possível depurar
o programa. O processo para adicionar a biblioteca se encontra descrito detalhadamente no site da [biblioteca](https://www.sfml-dev.org/tutorials/2.5/#getting-started).
