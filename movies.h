#ifndef MOVIES_H
#define MOVIES_H

#include <string.h>

class Movie 
{
  static double C;  // C for mean vote
  static int m;   // m in the formula for weighted rating
  int id;
  string title;
  string genre;
  int votes;  // number of users who rated this movie
  float rating_total; // total of all ratings
  float rating; // rating of the movie

  public:
  Movie();  // Default Constructor (USELESS)
  Movie(int, string, string);  // Para. Constructor

  // Accessors
  int getId();
  int getVotes();
  float getWeightedRating();
  float getAverageRating();
  string getTitle();

  // Mutators
  void addVote(float rating); // Add a rating 
};

#endif