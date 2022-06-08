#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#include "movies.h"

int compare_movies(const void* e1, const void* e2)				
{
  Movie* m1 = (Movie*)e1;
  Movie* m2 = (Movie*)e2;
	
  if(m1->getWeightedRating() > m2->getWeightedRating())
    return 1;
  else if(m1->getWeightedRating() < m2->getWeightedRating())
    return -1;
  return 0;
}

int main()
{
  /* First, read the files movies.csv
  and create an instance of the class 'movie'
  for each movie. Then, add that movie to the 
  array of movies. */

  ifstream infile; 
  infile.open("movies.csv"); 

  if(!infile)
  {
    cout<<"Unable to open movies.csv. Quitting.."<<endl;
    return 0;
  }

  // Create an array of movies
  Movie movies[60000];
  
  string line;
  int id, movieCount = 0;
  string title, genre;

  cout<<"1) Loading movies from movies.csv"<<endl;
  getline(infile, line); // Skip the header row.
  while(getline(infile, line)) // Read line by line
  { 
    // Now, tokenize the line by comma character
    char cline[1000];
    strcpy(cline,line.c_str());
    // cout<<"Line = "<<cline; // For debugging

    const char s[2] = ",";
    char *token;
    token = strtok(cline, s);
    int j = 0;
    while( token != NULL )
    {
      // printf("j = %d, Token: %s\n", j, token);
      switch(j)
      {
        case 0: id = atoi(token); break;
        case 1: title = string(token); break;
        case 2: genre = string(token);  break;
      }
      ++j;
      token = strtok(NULL, s);
    }

    Movie m(id, title, genre);
    movies[movieCount++] = m;
    // cout<<"Movie title = "<<movies[lineCount-1].getTitle(); 
  } 

  // Stored all movies information in the movies[] array
  cout<<"2) Loaded "<< movieCount <<" movies from movies.csv"<<endl;
  infile.close();

  // Now, process the ratings.csv file. 
  infile.open("ratings.csv");

  if(!infile)
  {
    cout<<"Unable to open ratings.csv. Quitting.."<<endl;
    return 0;
  }

  double C = 0;
  float voteCount = 0;

  cout<<"3) Loading ratings from ratings.csv"<<endl;
  cout<<"This might take a while..."<<endl;
  getline(infile, line); // Skip the header row
  while(getline(infile, line)) // Read line by line
  { 
    // Now, tokenize the line by comma character
    char cline[1000];
    strcpy(cline,line.c_str());
    // cout<<"Line = "<<cline<<endl;  // For debugging
    const char s[2] = ",";
    char *token;
    token = strtok(cline, s);
    int movieId, j = 0;
    float rating;
    while( token != NULL )
    {
      // printf("j = %d, Token: %s\n", j, token);
      switch(j)
      {
        case 0: break;  // ignore userid
        case 1: movieId = atoi(token); break;
        case 2: rating = atof(token);  break;
        case 3: break;  // ignore timestamp
      }
      ++j;
      token = strtok(NULL, s);
    } // end of while tokenizing the line

    movies[movieId-1].addVote(rating);
    ++voteCount;
    C += rating;
  } // end of while reading the csv file line by line

  // Added all movie ratings
  C/=voteCount;
  cout<<"4) Loaded ratings from ratings.csv"<<endl;
  infile.close();

  // Now, compute the weighted ratings of 
  // all movies in the movies[] array
  

  // Now, sort the movies[] array based on the rating 
  qsort(movies, movieCount, sizeof(Movie), compare_movies);
  
  // Now, print the top 250 movies
  cout<<"Index\tMovie title\tWeightedRate\tVoteCount\tAverageRate\n";
  for(int i=0;i<250;i++)
  {
    cout<<movies[i].getId()<<"\t";
    cout<<movies[i].getTitle()<<"\t";
    cout<<movies[i].getWeightedRating()<<"\t";
    cout<<movies[i].getAverageRating()<<endl;
  }
  return 0;
}