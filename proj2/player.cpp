/**********************************************************/
/*Name: Timothy Wu                                        */
/*File: player.cpp                                        */
/*Date: 5/14/19                                           */
/*Description: This is the player.cpp it handles the      */
/*decision making part of our game.                       */
/**********************************************************/
#include "player.hpp"


/**********************************************************/
/*Function name: Default Constructor                      */
/*parameters: None                                        */
/*return value: None                                      */
/*Description: When an object of the class is created it  */
/*will default to go here                                 */
/**********************************************************/
Player::Player(){
  strategy = "";
}


/**********************************************************/
/*Function name: Alternate Constructor                    */
/*parameters: string desired_strategey                    */
/*return value: None                                      */
/*Description: When this function is called it will fill  */
/*the class object's strategy with our parameter          */
/*desired_strategy.                                       */
/**********************************************************/
Player::Player(string desired_strategy){
  strategy = desired_strategy;
}


/**********************************************************/
/*Function name: Copy constructor                         */
/*parameters: const Player &p                             */
/*return value: strategy                                  */
/*Description: It copies the value from p.strategy to     */
/*strategy.                                               */
/**********************************************************/
Player::Player(const Player &p): strategy(p.strategy) {
}


/**********************************************************/
/*Function name: Destructor                               */
/*parameters: None                                        */
/*return value: None                                      */
/*Description: N/A                                        */
/*                                                        */
/**********************************************************/
Player::~Player(){
}


/**********************************************************/
/*Function name: Assignment operator                      */
/*parameters: const Player& p                             */
/*return value: *this                                     */
/*Description: Assigns value to the vector from another   */
/*and returns this                                        */
/**********************************************************/
Player& Player::operator= (const Player& p){
  strategy = p.strategy;
  return *this;
}


/**********************************************************/
/*Function name: Accesor function                         */
/*parameters: None                                        */
/*return value: string                                    */
/*Description: returns the private variable strategy.     */
/*                                                        */
/**********************************************************/
string Player::GetStrategy() const {
  return strategy;
}


/**********************************************************/
/*Function name: MakeNextDecision                         */
/*parameters: Decision opponent, string player            */
/*return value: Decision                                  */
/*Description: Based on the strategy of each player and   */
/*the opponent's last decision MakeNextDecision will      */
/*return a decision.                                      */
/**********************************************************/
Decision Player::MakeNextDecision(Decision opponent, string player){
  if (player == "p1")
    {
      int snitch_total = 0;
      if (this->GetStrategy() == "ALWAYS_SNITCH"){
	snitch_total+=1;
	return SNITCH;
      }
      if (this->GetStrategy() == "ALWAYS_SILENT") return SILENT;
      if (this->GetStrategy() == "TIT_FOR_TAT" && opponent == SNITCH)
	{
	  snitch_total+=1;
	  return SNITCH;
	}
      if (this->GetStrategy() == "TIT_FOR_TAT" && opponent == SILENT)return SILENT;
      if (this->GetStrategy() == "SPECIAL" && snitch_total > 0){
       	return SNITCH;
      }
      else
	return SILENT;
    }
  
  if (player == "p2")
    {
      int snitch_total_2 = 0;
      if (this->GetStrategy() == "ALWAYS_SNITCH"){
	return SNITCH;
	snitch_total_2+=1;
      }
      if (this->GetStrategy() == "ALWAYS_SILENT") return SILENT;
      if (this->GetStrategy() == "TIT_FOR_TAT" && opponent == SNITCH){
	snitch_total_2+=1;
	return SNITCH;
      }
      if (this->GetStrategy() == "TIT_FOR_TAT" && opponent == SILENT) return SILENT;
      if (this->GetStrategy() == "SPECIAL" && opponent == SNITCH){
	snitch_total_2+=1;
	return SNITCH;
      }
      else
	return SILENT;
    }
}
