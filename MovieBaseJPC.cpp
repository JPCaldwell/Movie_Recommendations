/*
 * MovieBaseJPC.cpp
 * Author: Jeremy Caldwell
 */

#include "MovieBaseJPC.h"

using std::vector;
using std::string;
using std::priority_queue;
using std::make_heap;
using std::stringstream;
using std::ifstream;
using std::map;
using std::runtime_error;
using std::cout;
using std::endl;


//class MovieBase {
MovieBase::MovieBase(string fileIn) : mList(vector<Movie>()), filename(fileIn), genreAverages(vector<double>()) {}

void MovieBase::parseMovies() {
	ifstream INPUT(filename.c_str());
	while (INPUT.good()) {
	    string name = "";
	    string tempGenre = "";
        while(INPUT.peek() != '|') {
            INPUT.ignore();
        }
        INPUT.ignore();
        while(INPUT.peek() != '|') {
            name += INPUT.get();
        }
        INPUT.ignore();
        while(INPUT.peek() != '|') {
            INPUT.ignore();
        }
        INPUT.ignore();
        INPUT.ignore();
        while(INPUT.peek() != '|') {
            INPUT.ignore();
        }
        for (int i = 0; i < 19; i++) {
            INPUT.ignore();
            tempGenre += INPUT.get();
        }
        INPUT.ignore();
        INPUT.peek();
		string genre = "000000";
		if(tempGenre.at(1) == '1' || tempGenre.at(2) == '1' || tempGenre.at(16) == '1' || tempGenre.at(18) == '1') {
			genre.at(0) = '1';
		}
		if(tempGenre.at(6) == '1' || tempGenre.at(10) == '1' || tempGenre.at(11) == '1' || tempGenre.at(13) == '1') {
			genre.at(1) = '1';
		}
		if(tempGenre.at(3) == '1' || tempGenre.at(4) == '1' || tempGenre.at(5) == '1' || tempGenre.at(12) == '1') {
			genre.at(2) = '1';
		}
		if(tempGenre.at(8) == '1' || tempGenre.at(14) == '1') {
			genre.at(3) = '1';
		}
		if(tempGenre.at(15) == '1' || tempGenre.at(9) == '1') {
			genre.at(4) = '1';
		}
		if(tempGenre.at(17) == '1' || tempGenre.at(7) == '1') {
			genre.at(5) = '1';
		}
		mList.push_back(Movie(name,genre));
	}
}

void MovieBase::calcAvg() {
	for(int i = 0; i < mList.size(); i++) {
		mList.at(i).calcAvg();
	}
}

priority_queue<Movie> MovieBase::topRatings(map<string, double> biases) {
	priority_queue<Movie> topList = priority_queue<Movie>();
	vector<Movie> tempList = mList;
	for(map<string,double>::iterator it = biases.begin(); it != biases.end(); it++) {
		for(int i = 0; i < it->first.length(); i++) {
			if(it->first.at(i) == '1') {
				for(int j = 0; j < tempList.size(); j++) {
					if(tempList.at(j).genre.at(i) == '1') {
						tempList.at(j).avgRating *= it->second;
					}
				}
			}
		}
	}
	make_heap(tempList.begin(),tempList.end());
	for(int i = 0; i < 15; i++) {
		topList.push(tempList.at(i));
		pop_heap(tempList.begin(),tempList.end());
	}
	return topList;
}

vector<double> MovieBase::calcGenreAverages() {
    for (int i = 0; i < 6; i++) {
        int total = 0;
        int count = 0;
        for(int j = 0; j < mList.size(); j++) {
            if (mList.at(j).getGenre().at(i) == '1') {
                total += mList.at(j).getAverage();
                count++;
            }
        }
        if (count == 0) {
            genreAverages.push_back(0);
        } else {
            genreAverages.push_back(total / count);
        }
    }
    return genreAverages;
}

void MovieBase::toString() {
	for (size_t i = 0; i < mList.size(); i++) {
       cout << mList.at(i).str() << " " << mList.at(i).getGenre() << endl;
    }
}

void MovieBase::movieReviewsToString() {
	for (size_t i = 0; i < mList.size(); i++) {
       cout << "Movie: " << i+1 << " Ratings total: " << mList.at(i).aggregateRating << endl;
    }
}

Movie& MovieBase::getMovie(int id) {
    return mList.at(id-1);
}

vector<double>& MovieBase::getGenreAverages() {
    return genreAverages;
}

int MovieBase::size() {
    return mList.size();
}
//};

//class Movie {
Movie::Movie(string titleIn, string genreIn) : title(titleIn), genre(genreIn), aggregateRating(0), avgRating(0), numRatings(0) {}

void Movie::calcAvg() {
	if(aggregateRating > 0 && numRatings > 0) {
		avgRating = aggregateRating / numRatings;
	}
}

void Movie::addRating(int rating) {
	aggregateRating += rating;
	numRatings++;
}

string Movie::getGenre() const{
	return genre;
}

string Movie::str() const{
	return title;
}

double Movie::getAggregate() {
    return aggregateRating;
}
//};
