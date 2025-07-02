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
		assertIllegalArgument(guessNumber);
		
		if (IsAllCorrect(guessNumber)) return guessResult;

		CheckStrikeCountAndSetChar(guessNumber);
		CheckBallCount();
		
		return guessResult;
	}

private:
	string question;
	GuessResult guessResult{ 0,0,0 };
	unordered_map<char, int> notMachedAnsNmbers;
	unordered_map<char, int> notMachedGuessNumbers;

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

	bool IsAllCorrect(const std::string& guessNumber)
	{
		if (guessNumber != question) return false;
		guessResult.solved = true;
		guessResult.strikes = 3;
		guessResult.balls = 0;
		return true;
	}
	void CheckStrikeCountAndSetChar(const std::string& guessNumber)
	{
		for (int i = 0; i < question.size(); ++i) {
			if (guessNumber[i] == question[i]) {
				guessResult.strikes++;
			}
			else {
				notMachedAnsNmbers[question[i]]++;
				notMachedGuessNumbers[guessNumber[i]]++;
			}
		}
	}
	void CheckBallCount()
	{
		int valueMatch = 0;
		for (const auto& pair : notMachedAnsNmbers) {
			char ch = pair.first;
			int cnt = pair.second;

			if (notMachedGuessNumbers.count(ch)) {
				valueMatch += min(cnt, notMachedGuessNumbers[ch]);
			}
		}
		guessResult.balls = valueMatch;
	}
};