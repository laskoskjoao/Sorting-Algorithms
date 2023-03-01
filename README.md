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

## :heavy_exclamation_mark: Observações

* No momento, o Heap Sort utiliza a estrutura de dados Heap fornecida pela biblioteca STL. Sendo assim, o algoritmo no processo visual de ordenação parece mais rápido que outros
algoritmos **n*logn**, uma vez que não existem atrasos (como nos outros algoritmos implementados) em decorrência da comparação e troca de elementos durante a manipulação da estrutura Heap. Além disso, por não possuírmos informações no número de trocas e comparações, a opção da visualização dessas informações não fica disponível para esse algoritmo. 
Uma solução à ser implementada para esse problema é desenvolver a própria estrutura Heap e assim adicionar devidamente os atrasos.

* Ainda é necessário revisar se os cálculos do número de trocas e de comparações estão corretos para todos os algoritmos. Por isso no momento não é possível afirmar com clareza a consistência desses dados.

As pendências descritas nas observações acima estão marcadas para serem resolvidas nos próximos commits.

## :question: Como testar

O programa foi desenvolvido utilizando a biblioteca gráfica SFML 2.5.1 (versão 32 bits), portanto é necessário [baixá-la](https://www.sfml-dev.org/download/sfml/2.5.1/) e adicioná-la ao projeto para que seja possível depurar o programa. O processo para adicionar a biblioteca se encontra descrito detalhadamente no site da [biblioteca](https://www.sfml-dev.org/tutorials/2.5/#getting-started).
