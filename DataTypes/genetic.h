/**
 * genetic.h
 *
 * Contains data types for our genetic algorithm for graph partitioning
 *
 * Created by: James Paton		10/15/10
 **/

#include <vector>

class Individual : public vector<Chromosome> {
private:
	const FitnessEvaluator *evaluator;
public:
	Individual( FitnessEvaluator &evaluator const ) :
	evaluator(evaluator) { }
	
	Individual( void ) { }
	
	float fitness( void ) {
		return this->evaluator->evaluate(this);
	}
	
	void setEvaluator( FitnessEvaluator &evaluator const ) {
		this->evaluator = evaluator;
	}
	
	FitnessEvaluator getEvaluator( void ) {
		return this->evaluator;
	}
}

class Chromosome {
}
