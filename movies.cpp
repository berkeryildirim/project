#include <string.h>
#include <iostream>

using namespace std;

#include "movies.h"

Movie::Movie(){}  // Default constructor - DO NOT DELETE

// Parameterized constructor
Movie::Movie(int a, string b, string c)
{
  id = a;
  title = b;
  genre = c;
  votes = 0;
  rating = 0;
  rating_total = 0;
}

// Accessors
int Movie::getId()
{
  return id;
}

int Movie::getVotes()
{
  return votes;
}

float Movie::getWeightedRating()
{
  return rating_total/(float)votes;
}

float Movie::getAverageRating()
{
  return rating_total/(float)votes;
}

string Movie::getTitle()
{
  return title;
}

// Mutators
void Movie::addVote(float rating) // Add a rating 
{
  votes++;  // one more user has rated this movie.
  rating_total+=rating; // Rating total goes up by 'rating'
}