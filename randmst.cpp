#include <iostream>
#include <cstdlib> // For atoi

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: ./randmst 0 numpoints numtrials dimension" << std::endl;
        return 1;
    }

    int flag = std::atoi(argv[1]);
    int numpoints = std::atoi(argv[2]);
    int numtrials = std::atoi(argv[3]);
    int dimension = std::atoi(argv[4]);

    // Your code here: Use flag, numpoints, numtrials, and dimension as needed

    std::cout << "average " << numpoints << " " << numtrials << " " << dimension << std::endl;

    return 0;
}
