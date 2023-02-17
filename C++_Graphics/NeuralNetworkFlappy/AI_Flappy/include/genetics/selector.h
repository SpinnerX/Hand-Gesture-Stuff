#include <vector>
#include "DNA.h"
#include "double_buffer.h"


const float population_conservation_ratio = 0.1f;

struct SelectionWheel{
	SelectionWheel(const uint64_t pop_size) : population_size(pop_size), fitness_acc(pop_size + 1), current_index(0){
		fitness_acc[0] = 0.0f;
	}

	void reset(){
		current_index = 0;
	}

	void addFitnessScore(float score){
		fitness_acc[current_index + 1] = fitness_acc[current_index] + score;
		current_index++;
	}

	template<typename T>
	void addFitnessScores(std::vector<T>& pop){

		reset();
		const uint64_t count = std::min<unsigned long>(population_size, pop.size());
		for (uint64_t i(0); i < count; ++i) addFitnessScore(pop[i].fitness);
	
	}

	float getAverageFitness() const{
		return fitness_acc.back() / float(population_size);
	}

	int64_t findClosestValueUnder(float f) const{
		int64_t b_inf = 0;
		int64_t b_sup = population_size;

		/*do {
			const int64_t index = (b_inf + b_sup) >> 1;
			if (fitness_acc[index] < f) {
				b_inf = index;
			}
			else {
				b_sup = index;
			}
		} while (b_inf < b_sup - 1);*/

		while(b_inf < b_sup-1){

			const int64_t index = (b_inf + b_sup) >> 1;
			if (fitness_acc[index] < f) b_inf = index;
			else b_sup = index;
		}

		return (b_inf + b_sup) >> 1;
	}

	int64_t pickTest(float value){
		int64_t result = population_size - 1;
		for (uint64_t i(1); i < population_size + 1; ++i) {
			if (fitness_acc[i] > value) {
				result = i - 1;
				break;
			}
		}

		return result;
	}


	template<typename T>
	const T& pick(const std::vector<T>& population, uint64_t* index = nullptr){
		const float pick_value = NumberGenerator<>::getInstance().getUnder(fitness_acc.back());
		uint64_t picked_index = pickTest(pick_value);

		if (index) *index = picked_index;

		return population[picked_index];
	}

	

	const uint64_t population_size;
	std::vector<float> fitness_acc;
	uint64_t current_index;
};






template<typename T>
struct Selector{
	Selector(const uint32_t agents_count) : population(agents_count),
											population_size(agents_count),
											current_iteration(0),
											survivings_count(this->as<uint32_t>(agents_count * population_conservation_ratio)),
											wheel(survivings_count) { }

	void nextGeneration(){

		// Selection parameters
		// Create selection wheel
		sortCurrentPopulation();
		std::vector<T>& current_units = population.getCurrent();
		std::vector<T>& next_units    = population.getLast();
		wheel.addFitnessScores(current_units);

		// The top best survive;
		uint32_t evolve_count = 0;
		for (uint32_t i = 0; i < survivings_count; i++) next_units[i] = current_units[i];


		// Replace the weakest
		const float mutation_proba = 1.0f / std::max(1.0f, wheel.getAverageFitness());
		std::cout << "Avg fitness: " << wheel.getAverageFitness() << " mut prob: " << mutation_proba << std::endl;
		
		for (uint32_t i(survivings_count); i < population_size; ++i) {
			const T& unit_1 = wheel.pick(current_units);
			const T& unit_2 = wheel.pick(current_units);

			if (unit_1.dna == unit_2.dna) {
				evolve_count++;
				next_units[i].loadDNA(DNAUtils::evolve<float>(unit_1.dna, mutation_proba, 0.1f));
			}
			else next_units[i].loadDNA(DNAUtils::makeChild<float>(unit_1.dna, unit_2.dna, mutation_proba));
		}

		switchPopulation();
	}

	// grabs the the current population and sorting the population with the best fitness.
	void sortCurrentPopulation(){
		std::vector<T>& current_units = population.getCurrent();
		std::sort(current_units.begin(), current_units.end(), [&](const T& a1, const T& a2) {return a1.fitness > a2.fitness; });
	}

	const T& getBest() const{
		return getNextPopulation()[0];
	}

	void switchPopulation(){
		population.swap();
		current_iteration++;
	}

	std::vector<T>& getCurrentPopulation(){
		return population.getCurrent();
	}

	std::vector<T>& getNextPopulation(){
		return population.getLast();
	}

	const std::vector<T>& getNextPopulation() const{
		return population.getLast();
	}

	template<typename _Tp, typename U>
	_Tp as(const U& u){ return static_cast<_Tp>(u); }

	const uint32_t population_size;
	const uint32_t survivings_count;
	DoubleObject<std::vector<T> > population;
	SelectionWheel wheel;

	uint32_t current_iteration;
};