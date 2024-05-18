#include <chrono>
#include "Menu.h"

void Menu::ToyGraph() {
    int option;
    std::string path = "../Data/Toy-Graphs/";
    while (true) {
        std::cout << "\nWhat graph?\n";
        std::cout << "\nChoose an option:\n"
                     "[1] Shipping\n"
                     "[2] Stadiums\n"
                     "[3] Tourism\n"
                     "> ";
        std::cin >> option;
        switch (option) {
            case 1:
                shipping = true;
                path.append("shipping.csv");
                break;
            case 2:
                path.append("stadiums.csv");
                break;
            case 3:
                path.append("tourism.csv");
                break;
            default:
                std::cout << "Invalid option.\n";
                continue;
        }
        network.readToyNodes(path);
        break;
    }
}

void Menu::ExtraFullyConnected() {
    int number_edges;
    std::string path = "../Data/Extra_Fully_Connected_Graphs/";
    while (true) {
        std::cout << "\nHow many edges do you want in your graph?\n"
                  << "\nOptions: [25][50][75][100][200][300][400][500][600][700][800][900]\n";
        std::cin >> number_edges;
        if (number_edges != 25 && number_edges != 50 && number_edges != 75 && number_edges != 100
            && number_edges != 200 && number_edges != 300 && number_edges != 400 && number_edges != 500
            && number_edges != 600 && number_edges != 700 && number_edges != 800 && number_edges != 900) {
            std::cout << "Choice a available option" << std::endl;
            continue;
        } else {
            network.readNodes("../Data/Extra_Fully_Connected_Graphs/nodes.csv", number_edges);
            path.append("edges_" + std::to_string(number_edges) + ".csv");
            network.readEdges(path);
            break;
        }
    }
}

void Menu::RealWorld() {
    int option, number_vertex;
    std::string path = "../Data/Real-world\ Graphs/";
    std::string pathNodes = "../Data/Real-world\ Graphs/";
    while (true) {
        std::cout << "\nWhat graph?\n";
        std::cout << "\nChoose an option:\n"
                     "[1] Graph 1\n"
                     "[2] Graph 2\n"
                     "[3] Graph 3\n"
                     "> ";
        std::cin >> option;
        switch (option) {
            case 1:
                path.append("graph1/edges.csv");
                pathNodes.append("graph1/nodes.csv");
                number_vertex = 1000;
                break;
            case 2:
                path.append("graph2/edges.csv");
                pathNodes.append("graph2/nodes.csv");
                number_vertex = 5000;
                break;
            case 3:
                path.append("graph3/edges.csv");
                pathNodes.append("graph3/nodes.csv");
                number_vertex = 10000;
                break;
            default:
                std::cout << "Invalid option.\n";
                continue;
        }
        network.readNodes(pathNodes, number_vertex);
        network.readEdges(path);
        break;
    }
}

Menu::Menu() {
    network = Manager();
    int option;
    do {
        std::cout << "\n\n"
                     "||-----------------------------||\n"
                     "||    Which Data Set Do You    ||\n"
                     "||        Want To Use ?        ||\n"
                     "||-----------------------------||\n";
        std::cout << "\nChoose an option:\n"
                     "[1] Toy-Graphs Data Set\n"
                     "[2] Extra Fully Connected Data Set\n"
                     "[3] Real World Data Set\n"
                     "> ";
        std::cin >> option;
        switch (option) {
            case 1:
                backtracking = true;
                ToyGraph();
                break;
            case 2:
                backtracking = false;
                ExtraFullyConnected();
                break;
            case 3:
                backtracking = false;
                RealWorld();
                break;
            default:
                std::cout << "Invalid option.\n";
                continue;
        }
    } while (mainMenu());
}

int Menu::mainMenu() {
    while (true) {
        std::cout << "\n\n\n"
                     "||-------------------------------------------------------------||\n"
                     "||  Routing Algorithm for Ocean Shipping and Urban Deliveries  ||\n"
                     "||-------------------------------------------------------------||\n";
        std::cout << "\nChoose an option:\n"
                     "\n[0] Quit.\n"
                     "[1] Backtracking Algorithm\n"
                     "[2] Triangular Approximation Heuristic\n"
                     "[3] Nearest Neighbor\n"
                     "[4] Adapted Christofides\n"
                     "[5] Traveling Salesman in the Real World\n"
                     "[6] Change Data Set\n"
                     "> ";
        int option;
        std::cin >> option;
        if (std::cin.fail()) {
            std::cout << "Invalid input\n"
                         "> ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            mainMenu();
        } else {
            switch (option) {
                case 0:
                    exit(0);
                case 1:
                    if (backtracking) {
                        Backtracking();
                    } else {
                        std::cout << "\nIt will take too long :(\n";
                    }
                    break;
                case 2:
                    if (shipping) {
                        std::cout << "\nIt doesn't work :(\n";
                        break;
                    }
                    Triangular_Heuristic();
                    break;
                case 3:
                    if (shipping) {
                        std::cout << "\nIt doesn't work :(\n";
                        break;
                    }
                    TSP_NearestNeighborComplete();
                    break;
                case 4:
                    if (shipping) {
                        std::cout << "\nIt doesn't work :(\n";
                        break;
                    }
                    adapted_Christofides();
                    break;
                case 5:
                    TSP_NearestNeighbor();
                    break;
                case 6:
                    shipping = false;
                    network.clearGraph();
                    return 1;
                default:
                    std::cout << "Invalid option.\n";
                    continue;
            }
        }
    }
}

void Menu::adapted_Christofides() {
    std::cout << "\nLoading... \n\n";
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    network.adapted_Christofides();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
    double time = duration.count();
    std::cout << "\nExecution Time: " << time << " milliseconds\n\n";
}

void Menu::Backtracking() {
    std::cout << "\nLoading... \n\n";
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    network.Backtracking();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
    double time = duration.count();
    std::cout << "\nExecution Time: " << time << " milliseconds\n\n";
}

void Menu::Triangular_Heuristic() {
    std::cout << "\nLoading... \n\n";
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    network.Triangular_Heuristic();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
    double time = duration.count();
    std::cout << "\nExecution Time: " << time << " milliseconds\n\n";
}

void Menu::TSP_NearestNeighbor() {
    std::cout << "\nLoading... \n\n";
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    network.TSP_NearestNeighbor();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
    double time = duration.count();
    std::cout << "\nExecution Time: " << time << " milliseconds\n\n";
}

void Menu::TSP_NearestNeighborComplete() {
    std::cout << "\nLoading... \n\n";
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    network.TSP_NearestNeighborComplete();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
    double time = duration.count();
    std::cout << "\nExecution Time: " << time << " milliseconds\n\n";
}