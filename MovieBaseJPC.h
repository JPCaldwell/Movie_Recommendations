/*
 * MovieBaseJPC.h
 * Author: Jeremy Caldwell
 * Partner: Ryan Wymyczak
 */

#ifndef MOVIEBASEJPC_H_
#define MOVIEBASEJPC_H_

#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<map>
#include<queue>
#include<exception>
#include <stdexcept>

class Movie;

class MovieBase {
	std::vector<Movie> mList;		  //movies will be sorted by given index
	std::string filename;                     //file from which movie data will be read
	std::vector<double> genreAverages;

public:
	/**
	* c-tor for MovieBase
	*/
	MovieBase(std::string filename);

	/**
	 * parse movie file and create movie objects from the data using a stringStream and place the movies in mList
	 */
	void parseMovies();

	/**
	 * calculates the average for every movie
	 */
	void calcAvg();

	/**
	 * makes heap based on a user's biased ratings for the given genres (map key string is the bit string for the genre, double is that genre's biased rating)
	 * and returns the top movies stored in a priority queue
	 * Note: this function has a dependency on the user and/or user base classes as the map must be supplied by one of them
	 */
	std::priority_queue<Movie> topRatings(std::map<std::string, double> biases);
	
	std::vector<double> calcGenreAverages();
	
	void toString();
    
    void movieReviewsToString();
	
	Movie& getMovie(int id);
    
    std::vector<double>& getGenreAverages();
    
    int size();
};

class Movie {
	std::string title;
	std::string genre; //bit string, 1 for member of genre, 0 for not i.e. 110000 would be action and noir, but not light, serious, fantasy, nor history
	double aggregateRating;				//aggregate rating (i.e. not yet averaged) for the movie
	double avgRating;					//average rating for the movie;
	size_t numRatings;					//number of ratings for the movie, used for calculating the average rating

	friend class MovieBase;
	friend class UserBase;

	/**
	 * c-tor for Movie objects.  Private so only MovieBase (which is friended) can create movies.
	 */
	Movie(std::string title, std::string genre);

public:

	/**
	 * calculates the average rating from the aggregate rating and the number of ratings
	 */
	void calcAvg();

	/**
	 * returns bit string of the movie's genre(s)
	 */
	std::string getGenre() const;

	/**
	 * compares movie based on average rating, used for MovieBase heap-making in MovieBase::topRatings
	 */
	inline bool operator<(Movie rhs) const { return avgRating < rhs.avgRating; }

	/**
	 * returns the movie's title as a string
	 */
	std::string str() const;

	/**
	 * takes in a rating and adds it to the aggregate rating while increasing the number of ratings
	 */
	void addRating(int rating);
	
	inline double getAverage() { return avgRating; }
    
    double getAggregate();
};

#endif /* MOVIEBASEJPC_H_ */
