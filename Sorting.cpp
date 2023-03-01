#include "Sorting.h"
#include <thread>

#define DELAY 2   //microsegundos

Sorting::Sorting(int width, int height): lastIndexesSwap(-1, -1), lastInsertedIndex(-1), comparisons(0), swaps(0), lastViewedElement(-1), lastElementsCompared(-1, -1) {
	running = true;
    endSorting = true;
    swaps = 0;
    comparisons = 0;

    this->width = width;
    this->heigth = height;
}

Sorting::~Sorting() {
    for (int i = 0; i < elements.size(); i++) { //Uma forma mais eficiente seria liberara a memoria de uma posicao e ja dar erase da posicao no vector.
        if (elements[i].second)
            delete elements[i].second;
    }
    elements.clear();
}

void Sorting::run() {
	while (running) {
		if (!endSorting) {
			switch (algorithm)
			{
			case Selection:
                selectionSort();
				break;
			case Bubble:
                bubbleSort();
				break;
			case Insertion:
                insertionSort();
				break;
			case My:
                swapSort();
				break;
            case Shell:
                shellSort();
                break;
			case Merge:
                mergeSort(0,elements.size()-1);
				break;
			case Quick:
                quickSort(0, elements.size() - 1);
				break;
            case Heap:
                heapSort();
                break;
			case Counting:
                countingSort();
				break;
			default:
				break;
			}
            endSort();          //pinta os elementos ordenados de verde
			endSorting = true;
		}
	}
}

void Sorting::endExecution() {
	running = false;
}

void Sorting::setAlgorithm(Algorithm algorithm) {
    this->algorithm = algorithm;
}

void Sorting::startSorting() {
    endSorting = false;
}

bool Sorting::getEndSorting() {
    return endSorting;
}

void Sorting::generateData(int size) {
    srand(time(NULL));  //alterando a semente do rand

    int elementWidth = width / size;
    //gerando dados aleatórios
    for (int i = 0; i < size; i++) {
        int currentData = rand() % heigth;

        sf::RectangleShape* currentShape = new sf::RectangleShape();
        currentShape->setSize(sf::Vector2f(elementWidth - 1, currentData - 1));       //-1 pois considera o outlinethickness de 1 no tamanho. 
        currentShape->setOutlineColor(sf::Color::Black);
        currentShape->setOutlineThickness(1);
        currentShape->setPosition(i * elementWidth, heigth - currentData);

        std::pair<int, sf::RectangleShape*> currentElement(currentData, currentShape);
        elements.push_back(currentElement);
    }
}

void Sorting::setElements(std::vector<std::pair<int, sf::RectangleShape*>> elements) {
    this->elements = elements;
}

std::vector<std::pair<int, sf::RectangleShape*>> Sorting::getElements() {
    return elements;
}

void Sorting::clearElements() {
    for (int i = 0; i < elements.size(); i++) { //Uma forma mais eficiente seria liberara a memoria de uma posicao e ja dar erase da posicao no vector.
        if (elements[i].second)
            delete elements[i].second;
    }
    elements.clear();
}

int Sorting::getTotalSwaps() {
    return swaps;
}

int Sorting::getTotalComparisons() {
    return comparisons;
}

void Sorting::reset(){
    comparisons = 0;
    swaps = 0;
    endSorting = true;
}

/*Algoritmos de ordenação*/
void Sorting::selectionSort() {
    for (int i = 0; i < elements.size(); i++) {
        int minIndex = i;
        for (int j = i + 1; j < elements.size(); j++) {
            compareElements(minIndex, j);
            if (elements[minIndex].first > elements[j].first)
                minIndex = j;
        }
        if (minIndex != i)
            swap(minIndex, i);
    }
    endSorting = true;
}

void Sorting::bubbleSort() {
    for (int i = 0; i < elements.size(); i++) {
        for (int j = 1; j < elements.size() - i; j++) {
            compareElements(j - 1, j);
            if (elements[j - 1].first > elements[j].first)
                swap(j - 1, j);
        }
    }
    endSorting = true;
}

void Sorting::insertionSort() {
    for (int i = 1; i < elements.size(); i++) {
        for (int j = i; j > 0 && elements[j - 1].first > elements[j].first; j--) {
            compareElements(j - 1, j);
            swap(j - 1, j);
        }
    }
    endSorting = true;
}

/*O swapSort é um algoritmo de ordenação desenvolvido por João Victor Laskoski.
O algoritmo não tem por objetivo ser eficiente. Ele serviu para testes durante o desenvolvimento deste projeto (https://github.com/laskoskjoao/Sorting-Algorithms)

O algoritmo é composto por duas partes:
    1- A primeira é uma derivação do selection sort, no entanto, para cada elemento encontrado menor que o elemento da posição a ser ordenada, o algoritmo realiza
    o swap entre eles. Com isso, o restante do conjunto a ser ordenado cria um padrão de "parcial ordenação invertida" (fica mais claro ao executa-lo neste programa).

    2- Com o padrão criado na primeira parte, ao chegar na metade do conjunto de dados, o algoritmo utiliza um insertion sort invertido na segunda parte. ordenando 
    assim a segunda parte em ordem decrescente. O insertion sort invertido foi utilizado aqui pois existe um certo padrão de ordenação citado no item 1.

    3- O algoritmo finaliza a ordenação invertendo as posições da segunda metado do conjunto.
*/
void Sorting::swapSort() {
    for (int i = 0; i < elements.size() / 2; i++) {
        for (int j = i + 1; j < elements.size(); j++) {
            compareElements(i, j);
            if (elements[i].first > elements[j].first)
                swap(i, j);
        }
    }

    invertedInsertionSort(elements.size() / 2);

    /*inverte segunda parte*/
    for (int i = elements.size() / 2; i < (elements.size() + elements.size() / 2) / 2; i++) {
        swap(i, elements.size() - (i - elements.size() / 2) - 1);
    }
    endSorting = true;
}

/*Algoritmo do shell sort retirado de: https://pt.wikipedia.org/wiki/Shell_sort#C%C3%B3digo_em_C++11*/
void Sorting::shellSort() {
    int h = 1;
    int i, j;
    int rep = 0;

    while (h < elements.size()) {
        h = h * 3 + 1;
    }

    while (h > 1) {
        h /= 3;

        for (i = h; i < elements.size(); i++) {
            std::pair<int, sf::RectangleShape*> aux = elements[i];
            j = i;

            while (j >= h && aux.first < elements[j - h].first) {
                compareElements(j, j - h);
                swap(j, j - h); //v[j] = v[j - h];
                j -= h;
                rep++;
            }
            insert(j, aux); //v[j] = aux;
        }
    }
}

void Sorting::mergeSort(int begin, int end) {
    if (begin < end) {
        int middle = (begin + end) / 2;

        mergeSort(begin, middle);
        mergeSort(middle + 1, end);
        merge(begin, middle, end);
    }

    /*Atualiza endSort*/
    if (begin == 0 && end == elements.size() - 1) {
        endSorting = true;
    }
}

void Sorting::merge(int begin, int middle, int end) {
    std::vector<std::pair<int, sf::RectangleShape*>> aux(end - begin + 1);        //guarda os indices na ordenação correta considerando os valores dos dos elementos (útil para fazer os swaps posteriormente)

    int i = begin;      //contador para a primeira parte
    int j = middle + 1;   //contador para a segunda parte
    int k = 0;          //contador para o vetor auxiliar

    while (i <= middle && j < end + 1)
    {
        compareElements(i, j);
        if (elements[i].first <= elements[j].first) {
            aux[k] = elements[i];
            i++;
        }
        else {
            aux[k] = elements[j];
            j++;
        }
        k++;
    }

    while (i <= middle) {
        aux[k] = elements[i];
        i++;
        k++;
    }

    while (j < end + 1) {
        aux[k] = elements[j];
        j++;
        k++;
    }

    /*swaps*/
    for (int i = begin; i < end + 1; i++) {
        insert(i, aux[i - begin]);
    }
}

void Sorting::quickSort(int begin, int end) {
    int pivot = begin;

    if (end > begin) {
        for (int i = begin + 1; i < end + 1; i++) {
            compareElements(i, pivot);
            if (elements[i].first < elements[pivot].first) {        //encontrou um elemento menor que o pivot, logo o elemento menor precisa passar a frente do pivot
                if (i > pivot + 1)
                    swap(pivot + 1, i);     //trás o elemento menor para o lado do pivot                     
                swap(pivot, pivot + 1);
                pivot++;
            }
        }
        quickSort(begin, pivot - 1);
        quickSort(pivot + 1, end);
    }

    /*Atualiza endSort*/
    if (begin == 0 && end == elements.size() - 1) {
        endSorting = true;
    }
}

void Sorting::heapSort() {
    make_heap(elements.begin(), elements.end());
    updateAllPositions();
    
    for (int i = 0; i < elements.size(); i++) {
        std::pair<int, sf::RectangleShape*> element = elements[0];
        std::pop_heap(elements.begin(), elements.end() - i);
        insert(elements.size() - 1 - i, element);
        updateAllPositions();
        //elements[0] <-> elements[i]
        //maxHeapify(0,i)
    }
}

void Sorting::countingSort() {
    /*Encontrando o maior valor do vetor*/
    int max = 0;
    for (int i = 0; i < elements.size(); i++) {
        viewElement(i);
        if (elements[i].first > max)
            max = elements[i].first;
    }

    /*Contando os elementos*/
    std::vector<int> count(max + 1);
    for (int i = 0; i < elements.size(); i++) {
        count[elements[i].first] ++;
    }

    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    std::vector<std::pair<int, sf::RectangleShape*>> sorted(elements.size());
    for (int i = 0; i < elements.size(); i++) {
        sorted[count[elements[i].first] - 1] = elements[i];   //indice correto do elements[i].first
        count[elements[i].first] --;
    }

    for (int i = 0; i < elements.size(); i++) {
        insert(i, sorted[i]);
    }

    endSorting = true;
}

void Sorting::invertedInsertionSort(int index) {
    for (int i = elements.size() - 2; i >= index; i--) {
        for (int j = i; j < elements.size() - 1 && elements[j].first < elements[j + 1].first; j++) {
            compareElements(j + 1, j);
            swap(j + 1, j);
        }
    }
}

//Funções auxiliares dos algoritmos
void Sorting::swap(int firstIndex, int secondIndex) {
    /*atualizando a cor dos elementos*/

    //cor branca para os elementos trocados anteriormente
    if (lastIndexesSwap.first > -1 && lastIndexesSwap.second > -1 && lastIndexesSwap.first < elements.size() && lastIndexesSwap.second < elements.size()) {
        elements[lastIndexesSwap.first].second->setFillColor(sf::Color::White);
        elements[lastIndexesSwap.second].second->setFillColor(sf::Color::White);
    }

    //cor vermelha para os elementos trocados
    elements[firstIndex].second->setFillColor(sf::Color::Red);
    elements[secondIndex].second->setFillColor(sf::Color::Red);

    /*swap*/

    //swap de elementos do vetor
    std::pair<int, sf::RectangleShape*> aux = elements[firstIndex];
    elements[firstIndex] = elements[secondIndex];
    elements[secondIndex] = aux;

    //atualizando as posicoes dos rectangles shapes dos elementos
    int elementWidth = width / elements.size();
    sf::Vector2f posFirst = elements[firstIndex].second->getPosition();
    posFirst.x = elementWidth * firstIndex;

    sf::Vector2f posSecond = elements[secondIndex].second->getPosition();
    posSecond.x = elementWidth * secondIndex;

    elements[firstIndex].second->setPosition(posFirst);
    elements[secondIndex].second->setPosition(posSecond);
    /*
    !!! NÃO ENTENDI PQ ISSO NAO FUNCIONOU PARA A TROCA DE POSIÇÕES:
    sf::Vector2f auxPosition = elements[firstIndex].second->getPosition();
    elements[firstIndex].second->setPosition(elements[secondIndex].second->getPosition());
    elements[secondIndex].second->setPosition(auxPosition);*/

    /*Atualizando lastIndexesSwap*/
    lastIndexesSwap.first = firstIndex;
    lastIndexesSwap.second = secondIndex;

    swaps++;

    std::this_thread::sleep_for(std::chrono::microseconds(DELAY)); //atraso para visualização
}

void Sorting::insert(int index, std::pair<int, sf::RectangleShape*> element) {
    /*Atualiza a posição*/

    /*Atualiza a cor*/
    if (lastInsertedIndex > -1 && lastInsertedIndex < elements.size()) {
        elements[lastInsertedIndex].second->setFillColor(sf::Color::White);
    }

    if (index > -1 && index < elements.size()) {
        /*Atualiza cor*/
        element.second->setFillColor(sf::Color::Red);


        /*Atualiza posição*/
        int elementWidth = width / elements.size();
        sf::Vector2f position = element.second->getPosition();
        position.x = elementWidth * index;

        element.second->setPosition(position);

        swaps++;
        std::this_thread::sleep_for(std::chrono::microseconds(DELAY));

        /*Atualiza vector elements*/
        elements[index] = element;

        lastInsertedIndex = index;
    }
}

void Sorting::viewElement(int index) {
    /*Atualiza a cor*/
    if (lastViewedElement > -1 && lastViewedElement < elements.size()) {
        elements[lastViewedElement].second->setFillColor(sf::Color::White);
    }

    if (index > -1 && index < elements.size()) {
        elements[index].second->setFillColor(sf::Color::Blue);
        lastViewedElement = index;
    }

    std::this_thread::sleep_for(std::chrono::microseconds(DELAY));
}

void Sorting::compareElements(int firstIndex, int secondIndex) {
    if (lastElementsCompared.first > -1 && lastElementsCompared.second > -1 && lastElementsCompared.first < elements.size() && lastElementsCompared.second < elements.size()) {
        elements[lastElementsCompared.first].second->setFillColor(sf::Color::White);
        elements[lastElementsCompared.second].second->setFillColor(sf::Color::White);
    }

    if (firstIndex > -1 && secondIndex > -1 && firstIndex < elements.size() && secondIndex < elements.size()) {
        elements[firstIndex].second->setFillColor(sf::Color::Blue);
        elements[secondIndex].second->setFillColor(sf::Color::Blue);
    }

    lastElementsCompared.first = firstIndex;
    lastElementsCompared.second = secondIndex;

    comparisons++;

    std::this_thread::sleep_for(std::chrono::microseconds(DELAY)); //atraso para visualização
}

void Sorting::endSort() {
    for (int i = 0; i < elements.size(); i++) {
        elements[i].second->setFillColor(sf::Color::Green);
    }
}

void Sorting::updateAllPositions() {

    for (int i = 0; i < elements.size(); i++) {
        int currentData = rand() % heigth;

        /*Atualiza posição*/
        int elementWidth = width / elements.size();
        sf::Vector2f position = elements[i].second->getPosition();
        position.x = elementWidth * i;

        elements[i].second->setPosition(position);

    }
}
