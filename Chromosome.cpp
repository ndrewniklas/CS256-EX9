// Andrew Niklas
// Exercise 9
// Completed 3/14/16

#include "Chromosome.h"

Chromosome::Chromosome(std::string d) : data(d)
{
}

std::string Chromosome::getData() const{
    return data;
}

Chromosome Chromosome::mutate() const{
    // implement mutation here
	
	int pos = rand() % data.size();
	std::string result = data;
	if(rand() % 2){
		if(++result[pos] > 122){
			result[pos] = 97;
		}
	}else{
		if(--result[pos] < 97){
			result[pos] = 122;
		}
	}
	
	return Chromosome(result);
}

Chromosome Chromosome::crossover(const Chromosome& c) const{
    // implement crossover here
	
	int pos = rand() % data.size();
	
	std::string subFirst = data.substr(0, pos);
	std::string subSecond = c.data.substr(pos, data.size());
	
	std::string result = subFirst;
	result.append(subSecond);
	
	return Chromosome(result);
}

int Chromosome::fitness(const std::string& target) const{
    // computes fitness by sum of differences of each character
    // smaller is better (0 is perfect)

    int diff = 0;
    for (int i = 0; i < data.size(); i++)
    {
        int change = std::abs(data[i] - target[i]);
        if (change > 13) // handles wrap around for letters
        {
            change = 26 - change;
        }
        diff += change;
    }
    return diff;
}

std::ostream& operator<<(std::ostream& os, const Chromosome& c){
    os << c.getData();
    return os;
}