// Andrew Niklas
// Exercise 9
// Completed 3/14/16

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
		auto comp = [target] (Chromosome c1, Chromosome c2){
				return c1.fitness(target) < c2.fitness(target); };
				
		std::sort (newPop.begin(), newPop.end(), comp);
		
		for(int i = 0; i < popSize; ++i){
			population.push_back(newPop[i]);
		}
		
		std::cout << "Iteration " << iterations << std::endl;
		std::cout << "Best: \"" << population[0] << "\"" << std::endl;
		
		if(population[0].fitness(target) == 0){
			done = true;
			std::cout << "Answer found after " << iterations << " iterations." << std::endl;
		}
	}
	
	return population[0];
}

void testSort(std::string target, int popSize){
	std::vector<Chromosome> population;
	int size = target.size();
	
	for(int i = 0; i != popSize; ++i){
		population.push_back(randomChromosome(size));
	}
	
	std::cout << "Random Popultation" << std::endl;
	for(Chromosome& c : population){
		std::cout << c << std::endl;
	}
	
	auto comp = [target] (Chromosome c1, Chromosome c2){
				return c1.fitness(target) < c2.fitness(target); };
				
	std::sort (population.begin(), population.end(), comp);
	
	std::cout << "\nSorted Popultation" << std::endl;
	for(Chromosome& c : population){
		std::cout << c << std::endl;
	}
}

void testMutate(std::string target, int popSize){
	std::vector<Chromosome> population;
	int size = target.size();
	
	for(int i = 0; i != popSize; ++i){
		population.push_back(randomChromosome(size));
	}
	
	std::cout << "Random Popultation" << std::endl;
	for(Chromosome& c : population){
		std::cout << c << std::endl;
	}
	
	std::vector<Chromosome> newPop;
	for(Chromosome& c : population){
		newPop.push_back(c.mutate());
	}
	std::cout << "\nMutated Popultation" << std::endl;
	for(Chromosome& c : newPop){
		std::cout << c << std::endl;
	}
}

void testCrossover(std::string target, int popSize){
	std::vector<Chromosome> population;
	int size = target.size();
	
	for(int i = 0; i != popSize; ++i){
		population.push_back(randomChromosome(size));
	}
	
	std::cout << "Random Popultation" << std::endl;
	for(Chromosome& c : population){
		std::cout << c << std::endl;
	}
	
	std::vector<Chromosome> newPop;
	for(Chromosome& c : population){
		int pick = rand() % popSize;
		newPop.push_back(c.crossover(population[pick]));
	}
	std::cout << "\nCrossover Popultation" << std::endl;
	for(Chromosome& c : newPop){
		std::cout << c << std::endl;
	}
}

int main(int argc, char **argv)
{
    srand(time(0));
    std::string target = argv[1];
    int popSize = atoi(argv[2]);
    double mr = atof(argv[3]);
    double cr = atof(argv[4]);
    // Chromosome answer = runGA(target, popSize, mr, cr);
	// testSort(target, popSize);
	// testMutate(target, popSize);
	testCrossover(target, popSize);

    // std::cout << "Solution found: " << answer << std::endl;
	
}