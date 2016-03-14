#include "Chromosome.h"

Chromosome randomChromosome(int size)
{
    std::ostringstream sout;
    for (int i = 0; i < size; i++)
    {
        sout << (char) ((rand() % 26) + 97);
    }
    return Chromosome(sout.str());
}

Chromosome runGA(std::string target, int popSize, double mr, double cr)
{
    // implement genetic algorithm here

    // use a vector<Chromosome> for the population
    // I recommend using STL algorithms such as std::sort

    // remember, the GA is a loop until you find a chromosome
    // of fitness 0

    // on each iteration, you should be generating a new population
    // of twice the size of popSize, filling it with chromosomes
    // that have been mutated, crossed, and/or copied based on
    // the probabilities given by mr and cr
    // then sort it and keep only the best half as the population
    // for the next iteration
    // when you find a chromosome of fitness 0, you have finished and
    // you should return it
	
	bool done = false;
	int iterations = 0;
	std::vector<Chromosome> population;
	int size = target.size();
	
	for(int i = 0; i != popSize; ++i){
		population.push_back(randomChromosome(size));
	}
	
	while(!done){
		++iterations;
		
		std::vector<Chromosome> newPop;
		for(int i = 0; i < popSize * 2; ++i){
			int pick = rand() % popSize;
			if(rand() % 1 <= mr){
				newPop.push_back(population[pick].mutate());
			}else if(rand() % 1 <= cr){
				int pick2 = rand() % popSize;
				newPop.push_back(population[pick].crossover(population[pick2]));
			}else{
				newPop.push_back(population[pick]);
			}
		}
		std::sort (newPop.begin(), newPop.end(), Chromosome::fitness)
		
		for(auto itr newPop.begin(); itr != population.end(); ++itr){
			population.push_back(newPop[itr]);
		}
		
		if(population[0].fitness == 0){
			done = true;
			std::cout << "After " << iterations << " iterations." << std::endl;
			return population[0];
		}
		
		std::cout << "iteration: " << iterations << std::endl;
		std::cout << population[0] << std::endl;
	}
}

int main(int argc, char **argv)
{
    srand(time(0));
    std::string target = argv[1];
    int popSize = atoi(argv[2]);
    double mr = atof(argv[3]);
    double cr = atof(argv[4]);
    Chromosome answer = runGA(target, popSize, mr, cr);

    std::cout << "Solution found: " << answer << std::endl;
	
}