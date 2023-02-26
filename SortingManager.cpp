#include "SortingManager.h"
#include <thread>

#define HEIGHT_WINDOW 600
#define WIDTH_WINDOW 800

#define SPEED_COMPARE            //microsegundos
#define SPEED_SWAP               //microsegundos

SortingManager::SortingManager ():endSort(false), lastIndexesSwap(-1,-1), lastElementsCompared(-1,-1), window(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "Sorting Algorithms") {
    menu();
}

SortingManager::~SortingManager() {

}

void SortingManager::menu() {
    std::cout << "================================ Sorting Algorithms ================================" << std::endl;
    std::cout << "Choose the size of the sequence to be sorted: ";
    
    std::cin >> size;
    
    std::cout << "\nChoose the algorithm: " << std::endl;
    std::cout << "\t0. Selection Sort" << std::endl;
    std::cout << "\t1. Bubble Sort" << std::endl;

    std::cout << "\nInput: ";

    

    int aux;
    std::cin >> aux;
    algorithm = (Algorithm) aux;

    generateData();

    
    if (algorithm == Selection) {
        std::thread* sort = new std::thread(&SortingManager::selectionSort, this);
    }

    system("cls");

    mainLoop();
}

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
       /* int first = rand() % size;
        int second = rand() % size;
        int firstA = rand() % size;
        int secondA = rand() % size;
        swap(first, second);
        compareElements(firstA, secondA);
        i++;
        if (i >= 50)
            i = 0;*/
        if (endSort) {
            /*Deixa os elementos marcados em comparaçao com a cor branca*/
            //Libera memória
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

void SortingManager::generateData() {
    srand(time(NULL));  //alterando a semente do rand
    
    int elementWidth = WIDTH_WINDOW / size;
    //gerando dados aleatórios
    for (int i = 0; i < size; i++) {
        int currentData = rand() % HEIGHT_WINDOW;

        sf::RectangleShape* currentShape = new sf::RectangleShape();
        currentShape->setSize(sf::Vector2f(elementWidth-1, HEIGHT_WINDOW-1));       //-1 pois considera o outlinethickness de 1 no tamanho. 
        currentShape->setOutlineColor(sf::Color::Black);
        currentShape->setOutlineThickness(1);
        currentShape->setPosition(i*elementWidth, HEIGHT_WINDOW - currentData);

        std::pair<int, sf::RectangleShape*> currentElement(currentData,currentShape);
        elements.push_back(currentElement);
    }
}

void SortingManager::draw() {
    window.clear();
    for (int i = 0; i < elements.size(); i++) {
        window.draw(*elements[i].second);
    }
    window.display();
}


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
 
    //draw();
    std::this_thread::sleep_for(std::chrono::microseconds(20000)); //atraso para visualização
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

    //draw();
    std::this_thread::sleep_for(std::chrono::microseconds(500)); //atraso para visualização
}

void SortingManager::selectionSort() {
    for (int i = 0; i < elements.size(); i++) {
        int minIndex = i;
        for (int j = i+1; j < elements.size(); j++) {           //visualizando elementos "elements[j]"
            compareElements(minIndex, j);
            if (elements[minIndex].first > elements[j].first)
                minIndex = j;
        }
        if(minIndex != i)
            swap(minIndex, i);
    }
    endSort = true;
}