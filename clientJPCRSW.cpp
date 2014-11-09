/* File "clientJPCRSW.cpp" by Jeremy Caldwell and Ryan Wymyczak
   for CSE 250, Spring 2014, Project 2
*/

#include "UserBaseRSW.h"

using namespace std;

int main() {
    MovieBase movieBase("u.item"); // create movie and user databases
    UserBase userBase("u.user", "u.data");
    
    movieBase.parseMovies(); // read in text files to fill movie and user databases
    userBase.parseUsers();
    userBase.parseUserReviews(movieBase);
    
    movieBase.calcAvg(); // calculate average ratings of all movies by genre
    movieBase.calcGenreAverages();
    
    for (size_t i = 0; i < userBase.size(); i++) { // calculate all users' preference factors
        userBase.at(i+1).calculatePreferenceFactors(movieBase.getGenreAverages(), movieBase);
    }
        
    priority_queue<Movie> recommendations; // use heap to find each user's top 15 movies
    for(size_t i = 0; i < userBase.size(); i++) {
        cout << "Top 15 recommendations for user " << i+1 << endl; 
        recommendations = movieBase.topRatings(userBase.at(i+1).returnPreferenceFactors());
        int count = 1;
        while(!recommendations.empty()) {
            Movie temp = recommendations.top();
            recommendations.pop();
            cout << count << ": " << temp.str() << "\tbiased score for user: " << temp.getAverage() << endl;
            count++;
        }
        cout << "\n\n";
    }
    
    return 0;
}

/**
* The method for dealing with preference factors for movies of multiple genres chosen was to simply apply each preference factor independently.
* The rationale for choosing this method was simplicity and the idea that if a user likes action and noir, they will really like an action-noir movie
*/

