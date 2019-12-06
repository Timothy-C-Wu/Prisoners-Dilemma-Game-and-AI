/**********************************************************/
/*Name: Timothy Wu                                        */
/*File: Game.cpp                                          */
/*Date: 5/14/19                                           */
/*Description: This is the game.cpp file. It holds the    */
/*implementaions of the function prototypes in the        */
/*game.hpp file. This cpp file handle the display, score, */
/*turn parts of our prisoner's dilema game.               */
/**********************************************************/
#include <iostream>
#include "game.hpp"
using namespace std;


/**********************************************************/
/*Function name: Default Constructor                      */
/*parameters: None                                        */
/*return value: None                                      */
/*Description: when an object of the game class is created*/
/*it will defaul to this constructor.                      */
/**********************************************************/
Game::Game(){
  player1 = NULL;
  player2 = NULL;
}


/**********************************************************/
/*Function name: Alternate constructor                    */
/*parameters: string p1_strategy, string p2_strategy      */
/*return value: None                                      */
/*Description: When an object of this class is created    */
/*and is passed values to populate the players' strategy  */
/*it will go through this function.                       */
/**********************************************************/
Game::Game(string p1_strategy, string p2_strategy){
  player1 = new Player(p1_strategy);
  player2 = new Player(p2_strategy);
}


/**********************************************************/
/*Function name: Copy constructor                         */
/*parameters: const Game& p                               */
/*return value: None                                      */
/*Description: This will coppy the the vector pmoves from */
/*other to this.                                          */
/**********************************************************/
Game::Game(const Game& p){
  vector<Turn>pmoves = p.pmoves;
}


/**********************************************************/
/*Function name: Destructor                               */
/*parameters: None                                        */
/*return value: None                                      */
/*Description: N/A                                        */
/*                                                        */
/**********************************************************/
Game::~Game(){
}


/**********************************************************/
/*Function name: Assignment operator                      */
/*parameters: const Game& p                               */
/*return value: pointer                                   */
/*Description: The assignment operator  set pmoves equal  */
/*to p.pmoves and returns this.                           */
/**********************************************************/
Game&Game::operator = (const Game& p){
  pmoves = p.pmoves;
  return *this;
}


/**********************************************************/
/*Function name: PlayTurn                                 */
/*parameters: None                                        */
/*return value: None                                      */
/*Description: This function will get each players next   */
/*decision and figure out how long of a sentece each      */
/*palyer will receive. At the end it will accumulate the  */
/*total sentence and pushback the decision of each player */
/* into the vector that holds moves.                      */
/**********************************************************/
void Game::PlayTurn(){
  if(p2_end == SILENT && player1->GetStrategy() == "TIT_FOR_TAT")
    p1_end = SILENT;
  if(p1_end == SNITCH && player2->GetStrategy() == "TIT_FOR_TAT")
    p2_end = SNITCH;
  if(p1_end == SILENT && player1->GetStrategy() == "TIT_FOR_TAT")
    p2_end = SILENT;
  if (p2_end == SNITCH && player1->GetStrategy() == "TIT_FOR_TAT")
    p1_end = SNITCH;
  if(p2_end == SILENT && player1->GetStrategy() == "SPECIAL")
    p1_end = SILENT;
  if(p2_end == SNITCH && player1->GetStrategy() == "SPECIAL")
    p1_end = SILENT;
  if(p1_end == SILENT && player1->GetStrategy() == "SPECIAL")
    p2_end = SILENT;
  if(p1_end == SNITCH && player1->GetStrategy() == "SPECIAL")
    p2_end = SILENT;  
  if (pmoves.size() !=0) {
    p1_end = pmoves.back().p1_decision;
    p2_end = pmoves.back().p2_decision;
  }
  Turn turn;
  turn.p1_decision = player1 -> MakeNextDecision(p1_end, "p1");
  turn.p2_decision = player2 -> MakeNextDecision(p2_end, "p2");
  if(turn.p1_decision == SNITCH && turn.p2_decision == SNITCH){
    turn.p1_time = sentence_if_both_snitch;
    turn.p2_time = sentence_if_both_snitch;
  }
  if(turn.p1_decision == SILENT && turn.p2_decision == SILENT){
    turn.p1_time = sentence_if_both_silent;
    turn.p2_time = sentence_if_both_silent;
  }
  if(turn.p1_decision == SNITCH && turn.p2_decision == SILENT){
    turn.p1_time = sentence_for_lone_snitch;
    turn.p2_time = sentence_for_lone_silent;
  }
  if(turn.p1_decision == SILENT && turn.p2_decision == SNITCH){
    turn.p1_time = sentence_for_lone_silent;
    turn.p2_time = sentence_for_lone_snitch;
    }
  total_sentence_p1+=turn.p1_time;
  total_sentence_p2+=turn.p2_time;
  pmoves.push_back(turn);
    }


/**********************************************************/
/*Function name: TurnReport                               */
/*parameters: ostream& outs, int round_num                */
/*return value: None                                      */
/*Description: This function will output the strategy of  */
/*each player, what turn it is, each player's decision,   */
/*and their sentence.                                     */
/**********************************************************/
void Game::TurnReport(ostream& outs, int round_num) const{
  if (round_num == 1){
    outs << "*****************************************" << endl;
    outs << "GAME REPORT" << endl;
    outs << "Player 1 strategy: " << player1->GetStrategy() << endl;
    outs << "Player 2 strategy: " << player2->GetStrategy() << endl;
  }
  outs << "*************** TURN " << round_num << " ******************" << endl;
  string player1 = "";
  string player2 = "";
  if (pmoves[round_num - 1].p1_decision == SILENT)
    player1 = "SILENT";
  else
    player1= "SNITCH";
  if (pmoves[round_num - 1].p2_decision == SILENT)
    player2 = "SILENT";
  else
    player2 = "SNITCH";
  outs << "Player 1: " << player1 << endl;
  outs << "Player 2: " << player2 << endl;
  outs << "Player 1 sentence: " << pmoves[round_num-1].p1_time << endl;
  outs << "Player 2 sentence: " << pmoves[round_num-1].p2_time << endl;
}


/**********************************************************/
/*Function name: Reset                                    */
/*parameters: None                                        */
/*return value: None                                      */
/*Description: resets the vector of moves.                */
/*                                                        */
/**********************************************************/
void Game::Reset(){
  pmoves.clear();
}


/**********************************************************/
/*Function name: Reset                                    */
/*parameters: string p1_strategy, string p2_strategy      */
/*return value: None                                      */
/*Description: This function resets the moves vector and  */
/*the pointers player1 and player2.                       */
/**********************************************************/
void Game::Reset(string p1_strategy, string p2_strategy){
  pmoves.clear();
  player1 = new Player(p1_strategy);
  player2 = new Player(p2_strategy);
}


/**********************************************************/
/*Function name: Output operator                          */
/*parameters: ostream& outs, const Game                   */
/*return value: None                                      */
/*Description: Outputs total sentence to go along with    */
/*TurnReport.                                             */
/**********************************************************/
ostream& operator << (ostream& outs, const Game& g){
  outs << "Player 1's total sentence: " << g.total_sentence_p1 << endl;
  outs << "Player 2's total sentence: " << g.total_sentence_p2 << endl;
}
