# Smith_CSCI2270_FinalProject
Final Project repo for CSCI 2270

Project Summary
	The program is a complex variation of rock paper scissors, in a sort of card game form. You have a hand of cards consisting of rock, paper, and scissors, and you attempt to beat your opponent. You play multiple cards at one time, and your cards go against your opponents cards in order to determine who wins. The goal is to reduce your opponent's health to zero, and the cards can either heal you, deal damage, or provide utility for you to win more easily. The deck and discard piles are a stack data-type, which makes the most sense because they are literally stacks. The cards in hand and in the play area are stored as vectors, as they change wildly and frequently, and need to be easy to manipulate.
	
How To Run
	Simply download the three files; "RPS War.cpp", "Player.h", and "Player.cpp". You can either drop them into your favorite IDE and run them from there, or compile them pretty easily on Linux using "g++ -std=c++11 *.cpp" followed by "./a.out" in the appropriate directory containing the three files.
	The game is very easy and *mostly* intuitive to play. Detailed instructions are provided within the game and accessed from the main menu. As you play, multiple prompts are given at regular intervals which tell the player what commands to input in order to play. Furthermore, if you make a mistake, the game will tell you what you did wrong and allow you to enter your commands again until you get it right.
	
Dependencies
	N/A - There are no additional dependencies. The generic C++ libraries are enough.
	
System Requirements
	The program should run well on any operating system (Windows, Mac, Linux). If one uses an older compiler to compile the program, it is possible that one might run into errors. Some pretty old compilers do not have support for the stoi() function which is used within the program. This is unlikely to be an issue, but if it is, using a newer compiler will fix it.
	
Group Members
	-Tyler Smith
	-Tyler Smith
	-Tyler Smith
	
Contributors
	-Zach Schadt: Offered advice on game mechanics
	
Open Issues/Bugs
	As of now, there are no known bugs. However, the program has only been tested to a reasonable degree and some bugs may be hiding yet.
	Enhancement Request: There is currently no way to exit the game while playing other than by closing the window itself. Being able to enter a command (e.g. exit, quit) at any time to leave the game would be really helpful, but adding this feature would not be an easy task due to all of the error checking that takes place around user input.
