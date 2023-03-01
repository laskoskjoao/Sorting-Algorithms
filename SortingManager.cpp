#include "SortingManager.h"
#include <thread>

#define HEIGHT_WINDOW 600
#define WIDTH_WINDOW 800

SortingManager::SortingManager (): window(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "Sorting Algorithms") {
    sorting = new Sorting(WIDTH_WINDOW, HEIGHT_WINDOW);
    sort = std::thread(&Sorting::run, sorting);

    /*Carregando fonte*/
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "ERROR: Unable to initialize texts.";
    }


    /*Inicializando os textos*/

    //swaps
    swapsText.setFont(font); 
    swapsText.setCharacterSize(12); 
    swapsText.setFillColor(sf::Color::Red);

    //comparisons
    comparisonsText.setFont(font);
    comparisonsText.setCharacterSize(12);
    comparisonsText.setFillColor(sf::Color::Green);
    sf::Vector2f positionComparisonsText = swapsText.getPosition();
    positionComparisonsText.y += 12;
    comparisonsText.setPosition(positionComparisonsText);

    menu();
}

SortingManager::~SortingManager() {
    sorting->endExecution();
    delete sorting;
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
    std::cout << "\t3. Swap Sort\t\tO(n^2)" << std::endl;
    std::cout << "\t4. Shell Sort\t\tO(?)" << std::endl;
    std::cout << "\t5. Merge Sort\t\tO(n*logn)" << std::endl;
    std::cout << "\t6. Quick Sort\t\tO(n*logn) - Average performance" << std::endl;
    std::cout << "\t7. Heap Sort\t\tO(n*logn)" << std::endl;
    std::cout << "\t8. Counting Sort\tO(n)" << std::endl;

    std::cout << "\nInput: ";

    int aux;
    std::cin >> aux;
    algorithm = (Algorithm) aux;


    sorting->clearElements();
    //Limpa vetor

    sorting->generateData(size);
    sorting->setAlgorithm(algorithm);
    sorting->startSorting();

    /*if (algorithm == Selection) {
        
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
    }*/

    system("cls");

    mainLoop();
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

        if (sorting->getEndSorting()) {
            /*Deixa os elementos marcados em comparaçao com a cor branca*/
            //Libera memória
            std::cout << "Results" << std::endl;
            std::cout << "\tComparisons = " << sorting->getTotalComparisons() << std::endl;
            std::cout << "\tSwaps = " << sorting->getTotalSwaps() << std::endl;
            sorting->reset();

            draw();
            //endSort();

            //Limpa vetor
            menu();
        }
    }
}

void SortingManager::draw() {
    std::vector<std::pair<int, sf::RectangleShape*>> elements = sorting->getElements();
    window.clear();
    for (int i = 0; i < elements.size(); i++) {
        window.draw(*sorting->getElements()[i].second);
    }

    if (!sorting->getEndSorting() && algorithm != Heap) {       //Nao exibe informacoes do Heap pois a estrutura heap utilizada no momento é da biblioteca STL, portanto nao sao obtidas informacoes de comparacoes e trocas na manipulação da estrutura
        swapsText.setString("Swaps = " + std::to_string(sorting->getTotalSwaps()));
        comparisonsText.setString("Comparisons = " + std::to_string(sorting->getTotalComparisons()));
    }

    window.draw(swapsText);         //desenha o texto que exibe informacoes de swaps
    window.draw(comparisonsText);   //desenha o texto que exibe informacoes de comparisons

    window.display();
}

