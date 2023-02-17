#include <vector>
#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm> // for std::copy
#include "number_generator.h"
#include "neural_network.h"

constexpr float MAX_RANGE = 16.0f;


struct DNA{
	using byte = uint8_t;

	DNA(const uint64_t bits_count)
		: code(bits_count / 8u + bool(bits_count % 8 && bits_count > 8))
	{}

	template<typename T>
	void initialize(const float range)
	{
		const uint64_t element_count = getElementsCount<T>();
		for (uint64_t i(element_count - 1); i--;) {
			const T value = NumberGenerator<>::getInstance().get(range);
			set(i, value);
		}
	}

	template<typename T>
	T get(const uint64_t offset) const
	{
		T result;
		const uint64_t dna_offset = offset * sizeof(T);
		memcpy(&result, &code[dna_offset], sizeof(T));
		return result;
	}

	template<typename T>
	void set(const uint64_t offset, const T& value)
	{
		const float checked_value = std::clamp(-MAX_RANGE, MAX_RANGE, value);
		const uint64_t dna_offset = offset * sizeof(T);
		memcpy(&code[dna_offset], &value, sizeof(T));
		
	}

	uint64_t getBytesCount() const
	{
		return code.size();
	}

	template<typename T>
	uint64_t getElementsCount() const
	{
		return code.size() / sizeof(T);
	}

	void print() const
	{
		for (const byte word : code) {
			std::cout << std::bitset<8>(word) << ' ';
		}
		std::cout << std::endl;
	}

	void mutateBits(const float probability)
	{
		for (byte& b : code) {
			for (uint64_t i(0); i < 8; ++i) {
				if (NumberGenerator<>::getInstance().getUnder(1.0f) < probability) {
					const uint8_t mask = 256 >> i;
					b ^= mask;
				}
			}
		}
	}

	template<typename T>
	void mutate(const float probability)
	{
		constexpr uint32_t type_size = sizeof(T);
		const uint64_t element_count = code.size() / type_size;
		for (uint64_t i(0); i < element_count; ++i) {
			if (NumberGenerator<>::getInstance().getUnder(1.0f) < probability) {
				const T value = NumberGenerator<>::getInstance().get(MAX_RANGE);
				set(i, value);
			}
		}
	}

	bool operator==(const DNA& other) const
	{
		const uint64_t code_length = getBytesCount();
		if (other.getBytesCount() != code_length) {
			return false;
		}

		for (uint64_t i(0); i < code_length; ++i) {
			if (code[i] != other.code[i]) {
				return false;
			}
		}

		return true;
	}

	std::vector<byte> code;
};







struct DNAUtils{
	static DNA crossover(const DNA& dna1, const DNA& dna2, const uint64_t cross_point)
	{
		const uint64_t code_size = dna1.code.size();
		DNA result(code_size * 8);

		for (uint64_t i(0); i < cross_point; ++i) {
			result.code[i] = dna1.code[i];
		}
		for (uint64_t i(cross_point); i < code_size; ++i) {
			result.code[i] = dna2.code[i];
		}

		return result;
	}

	template<typename T>
	static DNA makeChild(const DNA& dna1, const DNA& dna2, const float mutation_probability)
	{
		const uint64_t point1 = DNAUtils::getIntUnderNonReset(DNAUtils::as<uint32_t>(dna1.getBytesCount()));
		DNA child_dna = crossover(dna1, dna2, point1);
		const uint64_t element_count = dna1.getElementsCount<T>();
		for (uint64_t i(element_count - 1); i--;) {
			const float distrib = 1.0f + NumberGenerator<>::getInstance().get(mutation_probability);
			child_dna.set(i, child_dna.get<float>(i) * distrib);
		}
		child_dna.mutate<float>(mutation_probability);
		return child_dna;
	}

	template<typename T>
	static DNA evolve(const DNA& dna, float mutation_probability, float range)
	{
		DNA child_dna = dna;
		optimize<T>(child_dna, mutation_probability, range);
		return child_dna;
	}

	template<typename T>
	static void optimize(DNA& dna, const float probability, const float range)
	{
		const uint64_t element_count = dna.getElementsCount<T>();
		for (uint64_t i(element_count - 1); i--;) {
			if (pass(probability)) {
				const T value = dna.get<T>(i);
				const T random_offset = NumberGenerator<>::getInstance().get(range);
				dna.set(i, value + random_offset);
			}
		}
	}

	static uint32_t getIntUnderNonReset(const uint32_t max){
		std::random_device rd;
		std::mt19937 gen(0);
		std::mt19937 gen_no_reset(rd());

		std::uniform_int_distribution<std::mt19937::result_type> distr(0, max);
		return  distr(gen_no_reset);
	}

	static bool pass(float probability)
	{
		return NumberGenerator<>::getInstance().getUnder(1.0f) < probability;
	}

	template<typename T, typename U>
	static T as(const U& u){ return static_cast<T>(u); }
};
