#include <bits/stdc++.h>

using namespace std;

// Chuỗi mục tiêu
const string TARGET_SEQUENCE = "ATGCTCGACTGCAGTTACCATGGATC";

// Hằng tham số
const int POPULATION_SIZE = 50;
const double MUTATION_RATE = 0.01;
const double CROSSOVER_RATE = 0.8;
const int NUM_GENERATIONS = 1000;

//Tạo các base ngẫu nhiên (A, C, G, T)
char generateRandomBase() {
    const string BASES = "ACGT";
    int index = rand() % BASES.length();
    return BASES[index];
}

// Tạo ra các chuỗi nucleotide ngẫu nhiên
string generateRandomSequence(int len) {
    string sequence = "";
    for (int i = 0; i < len; i++) {
        sequence += generateRandomBase();
    }
    return sequence;
}

// Tính độ thích nghi
int calculateFitness(string sequence) {
    int fitness = 0;
    for (int i = 0; i < (int) sequence.length(); i++) {
        if (sequence[i] == TARGET_SEQUENCE[i]) { //TARGET_SEQUENCE: chuỗi cần kiểm tra
            fitness++;
        }
    }
    return fitness;
}

// Chọn 2 cá thể để làm bố hoặc mẹ
string tournamentSelection(vector<string> population) {
    // Chọn ngẫu nhiên
    int index1 = rand() % POPULATION_SIZE;
    int index2 = rand() % POPULATION_SIZE;
    string parent1 = population[index1];
    string parent2 = population[index2];

    int fitness1 = calculateFitness(parent1);
    int fitness2 = calculateFitness(parent2);
    if (fitness1 > fitness2) {
        return parent1;
    } 
    return parent2;
}

string crossover(string parent1, string parent2) {
    // Chọn vị trí ngẫu nhiên
    int crossoverPoint = rand() % parent1.length();
    string offspring = parent1.substr(0, crossoverPoint) + parent2.substr(crossoverPoint);
    return offspring;
}

void mutate(string& sequence) {
    if ((double)rand() / RAND_MAX < MUTATION_RATE) {
        int index = rand() % TARGET_SEQUENCE.length();
        char mutate = generateRandomBase();
        do {
            mutate = generateRandomBase();
        } while(mutate == sequence[index]);
        sequence[index] = mutate;
    }
}

int main() {
    srand(time(NULL));

    // Tạo một quần thể gồm các chuỗi nucleotide ngẫu nhiên
    vector<string> population;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population.push_back(generateRandomSequence(TARGET_SEQUENCE.length()));
    }

    for (int generation = 0; generation < NUM_GENERATIONS; generation++) {
        // Đánh giá mức độ thích nghi
        vector<int> fitnessValues;
        for (int i = 0; i < POPULATION_SIZE; i++) {
            int fitness = calculateFitness(population[i]);
            fitnessValues.push_back(fitness);
            cout << "Sequence " << i + 1 << " in generation " << generation << ": " << population[i] << ", Fitness: " << fitness << endl;
            if(fitness == (int) TARGET_SEQUENCE.length()) {
                cout << "Found target sequence: " << population[i] << endl;
                return 0;
            }

        }

        // Chọn ra đời con từ bố và mẹ tốt, tiến hóa quần thể
        vector<string> nextGeneration;
        for (int i = 0; i < POPULATION_SIZE; i++) {
            string parent1 = tournamentSelection(population);
            string parent2 = tournamentSelection(population);
            string offspring = crossover(parent1, parent2);
            mutate(offspring);
            nextGeneration.push_back(offspring);
        }

        sort(nextGeneration.begin(), nextGeneration.end(), [](string &a, string &b) {
            return calculateFitness(a) > calculateFitness(b);
        });

        population = nextGeneration;
    }

    // Không thể tìm thấy chuỗi cần kiểm tra
    cout << "Target sequence not found" << endl;
    return 0;
}


