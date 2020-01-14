#include <Test.hpp>
#include <Strategies.hpp>
#include <Championship.hpp>

TestCase("Three players chapionship", "[Championship]")
{
	const unsigned numberOfTurns = 5;
	Championship championship({
		&allC,
		&allD,
		&tft
	},
	numberOfTurns);

	section("Championship constructor", "[Championship]")
	{
		check( championship.players[0].strategy == &allC );
		check( championship.players[1].strategy == &allD );
		check( championship.players[2].strategy == &tft );
	}

	section("Compete", "[Championship]")
	{
		championship.compete();
		section("Always cooperate")
		{
			std::vector<std::vector<Decision>> decisions = {
				3, std::vector<Decision>{numberOfTurns, Decision::cooperate}
			};
			std::vector<std::vector<Payoff  >> payoff    = {
				{ std::vector<Payoff>{numberOfTurns, Payoff::reward } },
				{ std::vector<Payoff>{numberOfTurns, Payoff::suckers} },
				{ std::vector<Payoff>{numberOfTurns, Payoff::reward } },
			};
			std::vector<Strategy*> partners              = { &allC, &allD, &tft };
			check(championship.players[0].decisions == decisions );
			check(championship.players[0].payoff    == payoff    );
			check(championship.players[0].partners  == partners  );
		}
		section("Always defect")
		{
			std::vector<std::vector<Decision>> decisions = {
				3, std::vector<Decision>{numberOfTurns, Decision::defect}
			};
			std::vector<std::vector<Payoff  >> payoff    = {
				{ std::vector<Payoff>{numberOfTurns, Payoff::temptation} },
				{ std::vector<Payoff>{numberOfTurns, Payoff::punishment} },
				{ {Payoff::temptation, Payoff::punishment, Payoff::punishment, Payoff::punishment, Payoff::punishment} },
			};
			std::vector<Strategy*> partners              = { &allC, &allD, &tft };
			check(championship.players[1].decisions == decisions );
			check(championship.players[1].payoff    == payoff    );
			check(championship.players[1].partners  == partners  );
		}
		section("Tit for Tat")
		{
			std::vector<std::vector<Decision>> decisions = {
				{ std::vector<Decision>{numberOfTurns, Decision::cooperate} },
				{ Decision::cooperate, Decision::defect, Decision::defect, Decision::defect, Decision::defect },
				{ std::vector<Decision>{numberOfTurns, Decision::cooperate} }
			};
			std::vector<std::vector<Payoff  >> payoff    = {
				{ std::vector<Payoff>{numberOfTurns, Payoff::reward} },
				{ {Payoff::suckers, Payoff::punishment, Payoff::punishment, Payoff::punishment, Payoff::punishment} },
				{ std::vector<Payoff>{numberOfTurns, Payoff::reward} },
			};
			std::vector<Strategy*> partners              = { &allC, &allD, &tft };
			check(championship.players[2].decisions == decisions );
			check(championship.players[2].payoff    == payoff    );
			check(championship.players[2].partners  == partners  );
		}
	}
	section("rank")
	{
		championship.compete();
		championship.rank();
		check( championship.players[0].strategy == &allD ); // score = 18
		check( championship.players[1].strategy == &tft  ); // score = 20
		check( championship.players[2].strategy == &allC ); // score = 25
	}
	return;
}
