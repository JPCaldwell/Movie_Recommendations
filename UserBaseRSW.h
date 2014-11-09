/* File "UserBaseRSW.h" by Ryan Wymyczak for CSE 250, Spring 2014, Project 2 */

#ifndef USERBASERSW_H_
#define USERBASERSW_H_

#include "MovieBaseJPC.h"

class User;

class UserBase {
    
    std::vector<User> users;        // Vector of users sorted by index
    std::string usersFile;          // File from which users will be read
    std::string userReviewsFile;    // File from which user reviews will be read
    
    friend class User;
    
  public:
    /** Constructor
        @param fileName The file containing the users to create a UserBase from
    */
    UserBase(std::string usersFile, std::string userReviewsFile);
    
    /** Adds new users from the usersFile text file to the userbase.
    */
    void parseUsers();
    
    /** Adds new users from the userReviewsFile text file to the userbase and also
        adds the user's review to each Movie object in the passed in movieBase.
        @param movieBase A reference to the movie database containing the movies
                         to receive the review
    */
    void parseUserReviews(MovieBase& movieBase);
    
    /** Returns the given user from the userbase without removing 
        the user.
        @param id The unique ID of the user to return
    */
    User at(int id);
    
    /** Prints to the console the IDs of all the users in the UserBase.
    */
    void toString(); 
    
    /** Prints to the console all users' movies and reviews.
    */
    void userReviewsToString();
    
    /** Returns the size of the UserBase.
    */
    int size();
};

class User {

    int id;                             // Unique user ID
    std::map<int, int> movieRatings;    // Map of movie ID paired with the user's rating of that movie
    std::map<std::string, double>* preferenceFactors;  // Map of genre IDs paired with the user's preference factor for that genre
    
    friend class UserBase;

  public:
    /** Constructor
        @param id The user's unique ID
    */
    User(int id);
    
    /** Adds a new movie's ID and its respective rating to the map of the
        user's movies watched and ratings.
        @param movieId The ID of the movie to add to the movieRatings map
        @param rating The rating to add to the movieRatings map
    */
    void addMovieRating(int movieId, int rating);
    
    /** Returns the user's rating for the given movie.
        @param movieID The ID of the movie to return the rating of
    */
    int getMovieRating(int movieId);
    
    /** Calculates the user's preference factor for each movie genre
        and stores each preference factor in the vector preferenceFactor.
        @param globalGenreRatingAverages The average rating of all movies in a given
                                         genre in a MovieBase
        @param movieBase A MovieBase to retrieve the genre of a movie given the
                         movie's ID
    */
    void calculatePreferenceFactors(std::vector<double>& globalGenreRatingAverages, MovieBase movieBase);
    
    /** Returns the user's preference factor for the given movie genre.
        @param genreId The ID of the movie genre to return the
                       preference factor of
    */
    double getPreferenceFactor(std::string genreId);
        
    /** Returns the map of movie IDs and preference factors.
    */
    std::map<std::string, double> returnPreferenceFactors();
};

#endif
