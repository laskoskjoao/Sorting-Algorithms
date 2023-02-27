#include "SortingManager.h"
#include <thread>

#define HEIGHT_WINDOW 600
#define WIDTH_WINDOW 800

#define DELAY 2   //microsegundos


SortingManager::SortingManager ():endSorting(false), lastIndexesSwap(-1,-1), lastInsertedIndex(-1), comparisons(0), swaps(0), lastViewedElement(-1), lastElementsCompared(-1, -1),
window(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "Sorting Algorithms") {
    menu();
}

SortingManager::~SortingManager() {

}

void SortingManager::generateData() {
    srand(time(NULL));  //alterando a semente do rand

    int elementWidth = WIDTH_WINDOW / size;
    //gerando dados aleatórios
    for (int i = 0; i < size; i++) {
        int currentData = rand() % HEIGHT_WINDOW;

        sf::RectangleShape* currentShape = new sf::RectangleShape();
        currentShape->setSize(sf::Vector2f(elementWidth - 1, currentData - 1));       //-1 pois considera o outlinethickness de 1 no tamanho. 
        currentShape->setOutlineColor(sf::Color::Black);
        currentShape->setOutlineThickness(1);
        currentShape->setPosition(i * elementWidth, HEIGHT_WINDOW - currentData);

        std::pair<int, sf::RectangleShape*> currentElement(currentData, currentShape);
        elements.push_back(currentElement);
    }
}

/*Coleta de entradas (algoritmo + tamanho)*/
void SortingManager::menu() {
    std::cout << "================================ Sorting Algorithms ================================" << std::endl;
    std::cout << "Choose the size of the sequence to be sorted (1 - " << WIDTH_WINDOW / 2 << "):" << std::endl;
    
    std::cin >> size;
    
    std::cout << "\nChoose the algorithm: " << std::endl;
    std::cout << "\t0. Selection Sort\tO(n^2)" << std::endl;
    std::cout << "\t1. Bubble Sort\t\tO(n^2)" << std::endl;
    std::cout << "\t2. Insertion Sort\tO(n^2)" << std::endl;
    std::cout << "\t3. My Sort\t\tO(n^2)" << std::endl;
    std::cout << "\t4. Merge Sort\t\tO(n*logn)" << std::endl;
    std::cout << "\t5. Quick Sort\t\tO(n*logn) - Average performance" << std::endl;
    std::cout << "\t6. Counting Sort\tO(n)" << std::endl;

    std::cout << "\nInput: ";

    int aux;
    std::cin >> aux;
    algorithm = (Algorithm) aux;


    for (int i = 0; i < elements.size(); i++) { //Uma forma mais eficiente seria liberara a memoria de uma posicao e ja dar erase da posicao no vector.
        if (elements[i].second)
            delete elements[i].second;
    }
    elements.clear();
    //Limpa vetor

    generateData();


    if (algorithm == Selection) {
        sort = new std::thread(&SortingManager::selectionSort, this);
    }
    else if (algorithm == Bubble) {
        sort = new std::thread(&SortingManager::bubbleSort, this);
    }
    else if (algorithm == Insertion) {
        sort = new std::thread(&SortingManager::insertionSort, this);
    }
    else if (algorithm == My) {
        sort = new std::thread(&SortingManager::mySort, this);
    }
    else if (algorithm == Merge) {
        sort = new std::thread(&SortingManager::mergeSort, this, 0, size-1);
    }
    else if (algorithm == Quick) {
        sort = new std::thread(&SortingManager::quickSort, this, 0, size - 1);
    }
    else if (algorithm == Counting) {
        sort = new std::thread(&SortingManager::countingSort, this);
    }

    endSorting = false;

    system("cls");

    mainLoop();
}

/*Algoritmos de ordenação*/
void SortingManager::selectionSort() {
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

void SortingManager::bubbleSort() {
    for (int i = 0; i < elements.size(); i++) {
        for (int j = 1; j < elements.size() - i; j++) {
            compareElements(j - 1, j);
            if (elements[j - 1].first > elements[j].first)
                swap(j - 1, j);
        }
    }
    endSorting = true;
}

void SortingManager::insertionSort() {
    for (int i = 1; i < elements.size(); i++) {
        for (int j = i; j > 0 && elements[j - 1].first > elements[j].first; j--) {
            compareElements(j - 1, j);
            swap(j - 1, j);
        }
    }
    endSorting = true;
}

void SortingManager::mergeSort(int begin, int end) {
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

void SortingManager::merge(int begin, int middle, int end) {
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

void SortingManager::quickSort(int begin, int end) {
    int pivot = begin;

    if (end > begin) {
        for (int i = begin + 1; i < end+1; i++) {
            compareElements(i,pivot);
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

void SortingManager::countingSort() {
    /*Encontrando o maior valor do vetor*/
    int max = 0;
    for (int i = 0; i < elements.size(); i++) {
        viewElement(i);
        if (elements[i].first > max)
            max = elements[i].first;
    }

    /*Contando os elementos*/
    std::vector<int> count(max+1);
    for (int i = 0; i < elements.size(); i++) {
        count[elements[i].first] ++;
    }

    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    std::vector<std::pair<int, sf::RectangleShape*>> sorted(elements.size());
    for (int i = 0; i < elements.size(); i++) {
        sorted[count[elements[i].first]-1] = elements[i];   //indice correto do elements[i].first
        count[elements[i].first] --;
    }

    for (int i = 0; i < elements.size(); i++) {
        insert(i, sorted[i]);
    }

    endSorting = true;
}

void SortingManager::mySort() {
    for (int i = 0; i < elements.size()/2; i++) {
        for (int j = i + 1; j < elements.size(); j++) {
            compareElements(i, j);
            if (elements[i].first > elements[j].first)
                swap(i, j);
        }
    }
 
    invertedInsertionSort(elements.size()/2);

    /*inverte seunda parte*/
    for (int i = elements.size() / 2; i < (elements.size() + elements.size() / 2)/2; i++) {
        swap(i, elements.size() - (i - elements.size() / 2) - 1);
    }
    endSorting = true;
}

void SortingManager::invertedInsertionSort(int index) {
    for (int i = elements.size() - 2; i >= index; i--) {
        for (int j = i; j < elements.size()-1 && elements[j].first < elements[j+1].first; j++) {
            compareElements(j + 1, j);
            swap(j + 1, j);
        }
    }
}

//Funções auxiliares dos algoritmos
void SortingManager::swap(int firstIndex, int secondIndex) {
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
    int elementWidth = WIDTH_WINDOW / size;
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

void SortingManager::insert(int index, std::pair<int, sf::RectangleShape*> element) {
    /*Atualiza a posição*/

    /*Atualiza a cor*/
    if (lastInsertedIndex > -1 && lastInsertedIndex < elements.size()) {
        elements[lastInsertedIndex].second->setFillColor(sf::Color::White);
    }

    if (index > -1 && index < elements.size()) {
        /*Atualiza cor*/
        element.second->setFillColor(sf::Color::Red);


        /*Atualiza posição*/
        int elementWidth = WIDTH_WINDOW / size;
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

void SortingManager::viewElement(int index) {
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

void SortingManager::compareElements(int firstIndex, int secondIndex) {
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

void SortingManager::endSort() {
    for (int i = 0; i < elements.size(); i++) {
        elements[i].second->setFillColor(sf::Color::Green);
    }
    draw();
}

/*Gerência da janela*/
void SortingManager::mainLoop() {
    //int i = 1;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        draw();

        if (endSorting) {
            /*Deixa os elementos marcados em comparaçao com a cor branca*/
            //Libera memória
            std::cout << "Results" << std::endl;
            std::cout << "\tComparisons = " << comparisons << std::endl;
            std::cout << "\tSwaps = " << swaps << std::endl;
            comparisons = 0;
            swaps = 0;

            endSort();

            for (int i = 0; i < elements.size(); i++) { //Uma forma mais eficiente seria liberara a memoria de uma posicao e ja dar erase da posicao no vector.
                if (elements[i].second)
                    delete elements[i].second;
            }
            elements.clear();
            //Limpa vetor
            menu();
        }
    }
}

void SortingManager::draw() {
    window.clear();
    for (int i = 0; i < elements.size(); i++) {
        window.draw(*elements[i].second);
    }
    window.display();
}

