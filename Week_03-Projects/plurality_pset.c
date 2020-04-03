// Week 3 Challenge - Plurality - Introduction to Computer Science Harvard

// Author: Philipp Pfister

// Implement a program that runs a plurality election.
// How a plurality election works: In the plurality vote, 
// every voter gets to vote for one candidate. At the end of the election, 
// whichever candidate has the greatest number of votes is declared the winner of the election.
// If there is a tie, the program prints all candidates who won!

// In this program a data structure was created and a bubble sort algorithm implemented!

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote, calling function vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election, calling function print_winner
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    bool r;
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(candidates[j].name, name) == 0)
        {
            candidates[j].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // implementing bubble sort:
    int c, k, tmp_votes;
    string tmp_name;
    
    for (c = 0; c < candidate_count; c++) // loop n times depending on the candidate_count size
    {
        for (k = 0; k < candidate_count - c - 1; k++) // last c elements are sorted already
        {
            if (candidates[k].votes > candidates[k + 1].votes) // swap if number in position k is bigger than number in k+1
            {
             tmp_votes = candidates[k].votes;
             tmp_name = candidates[k].name;
             candidates[k].votes = candidates[k + 1].votes;
             candidates[k + 1].votes = tmp_votes;
             candidates[k].name = candidates[k + 1].name;
             candidates[k + 1].name = tmp_name;
            }
        }
    }
    // check sorted array for one or multiple winners:
    
    // check if the most right sorted index of candidates.votes is higher than his left neighbour, if yes, than there is only one winner
    int w = candidate_count - 1;
    if (candidates[w].votes > candidates[w - 1].votes) 
    {
        printf("%s\n", candidates[w].name);
        return;
    }
    else // check for multiple winners and print them:
    {
        for (int t = 0; t <= w; t++)
        {
            if (candidates[t].votes == candidates[w].votes)
            {
                printf("%s\n", candidates[t].name);   
            }
        }
    }
}


