# Sorting-Algorithms

## :clipboard: Introduction

Manipulating data to classify it is an old and widely studied problem in computer science. Numerous algorithms have been developed over the years, including
algorithms widely disseminated in the literature, such as Selection sort, Bubble sort, Insertion sort, Merge sort, Quick sort, Counting sort, etc. The aim of this project
is to provide a mechanism for visualizing the algorithm's sorting process. The example below shows a quick sort order.

![](https://github.com/laskoskjoao/Sorting-Algorithms/blob/main/quick.gif)


## :bar_chart: Operation

At the moment, the menu displayed by the program is in the terminal, making it possible to select the number of elements to be sorted and the sorting algorithm.

![](https://github.com/laskoskjoao/Sorting-Algorithms/blob/main/menu.png)

There is a maximum number of elements to be sorted that depends on the width of the window (in the case of the image above, the process will only be visualized if the user chooses a value between 1 - 400). If necessary, you can change the size of the window using the following defines:

~~~ C++
#define HEIGHT_WINDOW 600
#define WIDTH_WINDOW 800
~~~

## :heavy_exclamation_mark: Observations

* Currently, Heap Sort uses the Heap data structure provided by the STL library. Therefore, the algorithm in the visual sorting process seems faster than others **n*logn** algorithms, since there are no delays (as in the other implemented algorithms) due to the comparison and exchange of elements during the manipulation of the Heap structure. Furthermore, as we do not have information on the number of exchanges and comparisons, the option to view this information is not available for this algorithm.
A solution to be implemented for this problem is to develop the Heap structure itself and thus properly add the delays.

* It is still necessary to review whether the calculations of the number of exchanges and comparisons are correct for all algorithms. Therefore, at the moment, it is not possible to clearly state the consistency of these data.

The issues described in the notes above are marked to be resolved in the next commits.

## :question: How to test 

The program was developed using the SFML 2.5.1 graphic library (32-bit version), therefore it is necessary to [download it](https://www.sfml-dev.org/download/sfml/2.5.1/) and add it to the project in order to be able to debug the program. The process for adding the library is described in detail on the library's [website](https://www.sfml-dev.org/tutorials/2.5/#getting-started).
