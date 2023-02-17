#include "selector.h"
#include "player.h"

struct Unit{
	Unit(const uint64_t dna_bits_count) : dna(dna_bits_count), fitness(0.0f) {}

	void loadDNA(const DNA& new_dna){
		fitness = 0.0f;
		dna = new_dna;

		onUpdateDNA();
	}

	virtual void onUpdateDNA() = 0;

	DNA dna;
	float fitness;
};





struct AiUnit : public Unit{
	AiUnit() : Unit(0) { }

	AiUnit(const std::vector<uint64_t>& network_architecture) : Unit(Network::getParametersCount(network_architecture) * 32), network(network_architecture){
		dna.initialize<float>(16.0f);
		updateNetwork();
	}

	void execute(const std::vector<float>& inputs){
		process(network.execute(inputs));
	}

	void updateNetwork()
	{
		uint64_t index = 0;
		for (Layer& layer : network.layers) {
			const uint64_t neurons_count = layer.getNeuronsCount();
			for (uint64_t i(0); i < neurons_count; ++i) {
				layer.bias[i] = dna.get<float>(index++);
			}

			for (uint64_t i(0); i < neurons_count; ++i) {
				const uint64_t weights_count = layer.getWeightsCount();
				for (uint64_t j(0); j < weights_count; ++j) {
					layer.weights[i][j] = dna.get<float>(index++);
				}
			}
		}
	}

	void onUpdateDNA() override { updateNetwork(); }

	virtual void process(const std::vector<float>& outputs) = 0;

	Network network;
};



const std::vector<uint64_t> architecture = { 2, 6, 4, 1 };

struct Agent : public AiUnit{
	Agent()
		: AiUnit(architecture)
	{}

	Agent(const Player &player_)
		: AiUnit(architecture)
		, player(player_)
	{
	}

	void process(const std::vector<float>& outputs) override
	{
		if (outputs[0] > 0.5f) {
			player.jump();
		}
	}

	Player player;
};
