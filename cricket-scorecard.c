#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct batsmen_info {
    char name[25];
    int runs_hit;
    int balls;
    int fours;
    int sixes;
} batsmen_info;

typedef struct bowler_info {
    char name[25];
    int runs_given;
    int balls_bowled;
    int wickets;
} bowler_info;

batsmen_info batsmen[11];
bowler_info bowler[11];

int extras = 0;

double cal_economy(bowler_info bowler) {
    double economy;
    double overs = bowler.balls_bowled / 6.0;
    economy = bowler.runs_given / overs;
    return economy;
}

double cal_strike_rate(batsmen_info batsmen) {
    double strike_rate;
    strike_rate = (double)batsmen.runs_hit / batsmen.balls * 100;
    return strike_rate;
}

int get_total_score(batsmen_info batsmen[]) {
    int total_score = 0;
    for (int i = 0; i < 11; i++) {
        total_score += batsmen[i].runs_hit;
    }
    return total_score + extras;
}

int get_wickets(bowler_info bowler[]) {
    int total_wickets = 0;
    for (int i = 0; i < 11; i++) {
        total_wickets += bowler[i].wickets;
    }
    return total_wickets;
}

void currentDelivery() {
    char c_batsman[25];
    char c_bowler[25];
    int c_runs, c_wicket, c_extras;

    printf("Enter current delivery events:\nBatsman name, Bowler name, Total runs on the delivery, Extra (1) or not (0), Wicket (1) or not (0)\n");
    scanf("%s %s %d %d %d", c_batsman, c_bowler, &c_runs, &c_extras, &c_wicket);
    
    for (int i = 0; i < 11; i++) {
        if (batsmen[i].runs_hit == 50) {
            printf("-------Milestone--------\n");
            printf("%s scored a Half Century\n", c_batsman);
        }
        
        if (batsmen[i].runs_hit == 100) {
            printf("-------Milestone--------\n");
            printf("%s scored a Century\n", c_batsman);
        }

        if (strcmp(c_batsman, batsmen[i].name) == 0) {
            if (!c_extras) {
                if (c_runs == 4) {
                    batsmen[i].fours++;
                }

                if (c_runs == 6) {
                    batsmen[i].sixes++;
                }

                batsmen[i].runs_hit += c_runs;
                batsmen[i].balls++;
            } else {
                extras += c_extras;
            }
        }

        if (strcmp(c_bowler, bowler[i].name) == 0) {
            if (c_wicket == 1) {
                printf("------Milestone------\n");
                printf("| %s is OUT! |\n", c_batsman);
                printf("---------------------\n");
                bowler[i].wickets++;
            }

            bowler[i].balls_bowled++;
            bowler[i].runs_given += c_runs;
        }
    }
}

void display(char team1[], char team2[], int overs) {
    double strike_rate = 0, economy = 0;
    printf("\n\tCricket Match Scorecard\n");
    printf("\nThe number of overs are: %d\n", overs);
    printf("----------------------------------------------------------\n\n");
    printf("Batting Team: %s\n", team1);
    printf("Player\tRuns\tBalls\tFours\tSixes\tStrike Rate\t\n");
    for (int i = 0; i < 11; i++) {
        double strike = 0;
        if (batsmen[i].balls) {
            strike = cal_strike_rate(batsmen[i]);
        }
        printf("%s\t%d\t%d\t%d\t%d\t%lf\t\n", batsmen[i].name, batsmen[i].runs_hit, batsmen[i].balls, batsmen[i].fours, batsmen[i].sixes, strike);
    }
    printf("--------------------------------------------------------\n\n");
    printf("Total Runs: %d / (%d)\n", get_total_score(batsmen), get_wickets(bowler));
    printf("-------------------------------------\n\n");
    printf("Bowling Team: %s\n", team2);
    printf("Player\tRuns\tWickets\tOvers\tEconomy\n");
    for (int i = 0; i < 11; i++) {
        double economy = 0;
        if (bowler[i].balls_bowled) {
            economy = cal_economy(bowler[i]);
        }
        printf("%s\t%d\t%d\t%d\t%.2f\n", bowler[i].name, bowler[i].runs_given, bowler[i].wickets, bowler[i].balls_bowled / 6, economy);
    }
    printf("-------------------------------------\n\n");
}

int main() {
    char team1[25];
    char team2[25];
    int overs;

    printf("Enter the Name of the first team: ");
    scanf("%s", team1);
    printf("Enter the Name of the second team: ");
    scanf("%s", team2);
    printf("Enter the number of overs: ");
    scanf("%d", &overs);

    printf("Enter the batsmen's details:\n");
    for (int i = 0; i < 11; i++) {
        printf("Name:\n");
        scanf("%s", batsmen[i].name);
        batsmen[i].runs_hit = 0;
        batsmen[i].balls = 0;
        batsmen[i].fours = 0;
        batsmen[i].sixes = 0;
    }

    printf("Enter the bowler's details:\n");
    for (int i = 0; i < 11; i++) {
        printf("Name:\n");
        scanf("%s", bowler[i].name);
        bowler[i].runs_given = 0;
        bowler[i].balls_bowled = 0;
        bowler[i].wickets = 0;
    }

    printf("Initial Score:\n");
    display(team1, team2, overs);

    for (int i = 0; i < overs; i++) {
        for (int j = 0; j < 6; j++) {
            currentDelivery();
        }
        display(team1, team2, overs);
    }

    return 0;
}