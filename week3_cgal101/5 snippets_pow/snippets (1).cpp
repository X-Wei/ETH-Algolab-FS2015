#include <iostream>
//#include <list>
#include <vector>
//#include <limits.h>
#include <set>
#include <queue>
//#include <time.h>

struct word {
	int i;
	int position;
	friend bool operator< (const word& left, const word& right);
};

// operator for set
bool operator< (const word& left, const word& right){
	return left.position < right.position;
}

// operator for priority_queue
class compare {
public:
	bool operator()(const word& left, const word& right){
		return left.position > right.position;
	}
};

void testcase();

int main(void) {
	//clock_t time_start = clock();
	std::ios_base::sync_with_stdio(false);
	int tot;
	std::cin >> tot;
	while (tot--) testcase();
	//std::cout << "time spent = " << (clock() - time_start) / 1000.0 << " secs \n";
}

void testcase() {
	int W, no;
	std::cin >> W;
	// count indexes for data reading
	std::vector<int> w_counts(W);
	// list of word queues
	std::vector<std::priority_queue<word, std::vector<word>, compare> > words(W);
	// actual snippet
	std::set<word> current_words;

	// read word counts
	for (int i = 0; i < W; ++i){
		std::cin >> w_counts[i];
	}

	// read words
	for (int i = 0; i < W; ++i) {
		for (int j = 0; j < w_counts[i]; ++j) {
			std::cin >> no;
			if (j==0)
				// first put to actual snippet
				current_words.insert(*new word{ i, no });
			else
				// other enqueue
				words[i].push(*new word{ i, no });
		}
	}
	
	// min_eval - size of snippet
	int cur_eval, min_eval = (*current_words.rbegin()).position - (*current_words.begin()).position + 1;
	word w;
	std::set<word>::iterator endi;
	bool found, ending = false;

	while (current_words.size() == W) {
		w = *current_words.begin();

		// if one of word queues ended
		if (ending || words[w.i].size() == 0) {
			if (!ending) 
				ending = true;

			// look for words that did not finish yet
			found = false;
			for (endi = current_words.begin(); endi != current_words.end(); ++endi)
				if (words[endi->i].size() > 0) {
					found = true;
					w = *endi;
					break;
				}
			// finished all words
			if (found == false)
				break;
		}

		current_words.erase(w);
		current_words.insert(words[w.i].top());
		words[w.i].pop();
		cur_eval = (*current_words.rbegin()).position - (*current_words.begin()).position + 1;
		min_eval = (cur_eval < min_eval) ? cur_eval : min_eval;
	}
	
	std::cout << min_eval << "\n";
}