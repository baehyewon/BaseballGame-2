#include <stdexcept>
#include <string>
#include<unordered_map>
using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question)
		: question(question)
	{
	}

	GuessResult guess(const string& guessNumber) {
		int valueMatch = 0;
		assertIllegalArgument(guessNumber);
		GuessResult guessResult{0,0,0};

		if (guessNumber == question) {
			guessResult.solved = true;
			guessResult.strikes = 3;
			guessResult.balls = 0;
			return guessResult;
		}
		
		CheckStrike(guessNumber, guessResult);

		for (const auto& pair : ansNmbers) {
			char ch = pair.first;
			int cnt = pair.second;

			if (guessNumbers.count(ch)) {
				valueMatch += min(cnt, guessNumbers[ch]);
			}
		}
		guessResult.balls = valueMatch;
		
		return guessResult;
	}

	void CheckStrike(const std::string& guessNumber, GuessResult& guessResult)
	{
		for (int i = 0; i < question.size(); ++i) {
			if (guessNumber[i] == question[i]) {
				guessResult.strikes++;
			}
			else {
				ansNmbers[question[i]]++;
				guessNumbers[guessNumber[i]]++;
			}
		}
	}

private:
	string question;
	unordered_map<char, int> ansNmbers;
	unordered_map<char, int> guessNumbers;

	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}
		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber))
		{
			throw invalid_argument("Must not have the same number");
		}
	}
	bool isDuplicatedNumber(const std::string& guessNumber)
	{
		return guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2];
	}

};