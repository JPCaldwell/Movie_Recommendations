/* File "UserBaseRSW.cpp" by Ryan Wymyczak for CSE 250, Spring 2014, Project 2 */

#include "UserBaseRSW.h"

using std::string;
using std::vector;
using std::range_error;
using std::map;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

// class UserBase {
UserBase::UserBase(string usersFile, string userReviewsFile) 
    : users(vector<User>())
    , usersFile(usersFile)
    , userReviewsFile(userReviewsFile) 
    {}

void UserBase::parseUsers() {
    ifstream INPUT(usersFile.c_str());
    while (INPUT.good()) {  // loop until end-of-file flag is thrown
        string word = "";
        while(INPUT.peek() != '|') { // get user ID
            word += INPUT.get();
        }
        while(INPUT.peek() != '\n') { // get end of line
            INPUT.ignore();
        }
        INPUT.ignore();
        INPUT.peek(); // sets end-of-file flag at the end
        istringstream WORD(word); // convert string to int
        int num;
        WORD >> num;
        users.push_back(User(num));
    }
}

void UserBase::parseUserReviews(MovieBase& movieBase) {
    ifstream INPUT(userReviewsFile.c_str());
    while (INPUT.good()) { // loop until end-of-file flag is thrown
        string user = "";
        string movie = "";
        string review = "";
        while (INPUT.peek() != '\t') { // get user ID
            user += INPUT.get();
        }
        INPUT.ignore();
        while (INPUT.peek() != '\t') { // get movie ID
            movie += INPUT.get();
        }
        INPUT.ignore();
        while (INPUT.peek() != '\t') { // get user's review of movie
            review += INPUT.get();
        }
        while (INPUT.peek() != '\n') { // get end of line
            INPUT.ignore();
        }
        INPUT.ignore();
        INPUT.peek(); // sets end-of-file flag at the end
        istringstream USER(user); // convert all strings to ints
        istringstream MOVIE(movie);
        istringstream REVIEW(review);
        int userInt;
        int movieInt;
        int reviewInt;
        USER >> userInt;
        MOVIE >> movieInt;
        REVIEW >> reviewInt;
        users.at(userInt-1).movieRatings[movieInt] = reviewInt; // add data to movieRatings map
        movieBase.getMovie(movieInt).addRating(reviewInt);      // and MovieBase
    }
}

User UserBase::at(int id) {
    if ((id-1) >= users.size()) {
        throw range_error("Attempt to get user that is not in UserBase map");
    }
    return users.at(id-1);
}

void UserBase::toString() { // debugging method
    for (size_t i = 0; i < users.size(); i++) {
        cout << users.at(i).id << endl;
    }
}

void UserBase::userReviewsToString() {  // debugging method
    for (size_t i = 0; i < users.size(); i++) {
        for (map<int, int>::iterator it = users.at(i).movieRatings.begin(); it != users.at(i).movieRatings.end(); it++) {
            cout << "User " << i+1 << " Movie: " << it->first << " Rating: " << it->second << endl;
        }
    }
}

int UserBase::size() {
    return users.size();
}
//};




// class User {
User::User(int id) : id(id), movieRatings(map<int, int>()), preferenceFactors(new map<string, double>()) {}

void User::addMovieRating(int movieId, int rating) {
    movieRatings[movieId] = rating;
}

int User::getMovieRating(int movieId) {
    if (movieRatings.find(movieId) == movieRatings.end()) {
        throw range_error("Attempt to get movie rating that is not in a user's movieRatings map");
    }
    return movieRatings[movieId];
}

void User::calculatePreferenceFactors(vector<double>& globalGenreRatingAverages, MovieBase movieBase) {
    for (int i = 0; i < 6; i++) { // loop through number of genres
        double userGenreRatingAverage = 0;
        string bitString = "000000";
        bitString.at(i) = '1'; // set bit string of current genre
        double genreRatingTotal = 0;
        int moviesInGenre = 0;
        for (map<int, int>::iterator it = movieRatings.begin(); it != movieRatings.end(); it++) { 
            if (movieBase.getMovie(it->first).getGenre().at(i) == '1') { // if a movie in a user's movieRatings map
                genreRatingTotal += it->second;                          // matches current genre, prepare to calculate
                moviesInGenre++;                                         // user's average rating for genre
            }
        }
        if (moviesInGenre == 0) { // user did not review any movies in current genre
            (*preferenceFactors)[bitString] = 1;
        } else { // user reviewed movies in genre, calculate user's genre average and divide by global average for pug
            userGenreRatingAverage = genreRatingTotal / moviesInGenre;
            (*preferenceFactors)[bitString] = userGenreRatingAverage / globalGenreRatingAverages.at(i);
        }
    }
}

double User::getPreferenceFactor(string genreId) {
    return (*preferenceFactors)[genreId];
}


    
map<string, double> User::returnPreferenceFactors() {
    return *preferenceFactors;
}

