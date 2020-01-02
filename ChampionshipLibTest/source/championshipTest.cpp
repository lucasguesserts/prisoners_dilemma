#include <Test.hpp>
#include <Strategies.hpp>
#include <Championship.hpp>

TestCase("Three players chapionship", "[Championship]")
{
	Championship championship({
		&allC,
		&allD,
		&tft
	});

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
				3, std::vector<Decision>{Match::numberOfTurns, Decision::cooperate}
			};
			std::vector<std::vector<Payoff  >> payoff    = {
				{ std::vector<Payoff>{Match::numberOfTurns, Payoff::reward } },
				{ std::vector<Payoff>{Match::numberOfTurns, Payoff::suckers} },
				{ std::vector<Payoff>{Match::numberOfTurns, Payoff::reward } },
			};
			std::vector<Strategy*> partners              = { &allC, &allD, &tft };
			check(championship.players[0].decisions == decisions );
			check(championship.players[0].payoff    == payoff    );
			check(championship.players[0].partners  == partners  );
		}
		section("Always defect")
		{
			std::vector<std::vector<Decision>> decisions = {
				3, std::vector<Decision>{Match::numberOfTurns, Decision::defect}
			};
			std::vector<std::vector<Payoff  >> payoff    = {
				{ std::vector<Payoff>{Match::numberOfTurns, Payoff::temptation} },
				{ std::vector<Payoff>{Match::numberOfTurns, Payoff::punishment} },
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
				{ std::vector<Decision>{Match::numberOfTurns, Decision::cooperate} },
				{ Decision::cooperate, Decision::defect, Decision::defect, Decision::defect, Decision::defect },
				{ std::vector<Decision>{Match::numberOfTurns, Decision::cooperate} }
			};
			std::vector<std::vector<Payoff  >> payoff    = {
				{ std::vector<Payoff>{Match::numberOfTurns, Payoff::reward} },
				{ {Payoff::suckers, Payoff::punishment, Payoff::punishment, Payoff::punishment, Payoff::punishment} },
				{ std::vector<Payoff>{Match::numberOfTurns, Payoff::reward} },
			};
			std::vector<Strategy*> partners              = { &allC, &allD, &tft };
			check(championship.players[2].decisions == decisions );
			check(championship.players[2].payoff    == payoff    );
			check(championship.players[2].partners  == partners  );
		}
	}
	return;
}
