#include <Test.hpp>
#include <Strategy.hpp>

class TestStrategy: public Strategy
{
	public:
		Decision makeDecision(
			[[maybe_unused]] std::vector<Decision> thisDecision,
			[[maybe_unused]] std::vector<Decision> partnerDecision
		){
			return Decision::cooperate;
		}
};

TestCase("strategy implementation", "[Strategy]")
{
	TestStrategy strategy;
	check( strategy.name == "" );
	check( strategy.shortName == "" );
	check( strategy.description == "" );
	check(
		strategy.makeDecision(
			std::vector<Decision>{Decision::cooperate},
			std::vector<Decision>{Decision::defect})
		== Decision::cooperate
	);
	return;
}
