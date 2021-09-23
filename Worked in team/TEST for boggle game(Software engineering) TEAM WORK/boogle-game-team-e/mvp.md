# Descrption of MVP

The Minimal Viable Product for the game Boggle would be a program which runs and takes into account all of the rules of Boggle except for checking if a word exists.
In the MVP it is important to have the basic of hte game complete allowing the user to show what the game is intended to do.
When the game is started a 4 x 4 grid is set up. 16 letters are randomly asssigned to the grid.
The player is then required to type in any letters which he finds in the grid by following the rules of Boggle during the allocated time.
The program then calculates the score of the user by counting the number of letters in each word.
The program will not be checking if words are valid at this point.
Every word the player types in is added onto the score of the player.
The player is allowed to type in words as long as the timer hasn't ran out.
The words must be a minimum of 3 letters long.
Once the timer runs out the game is stopped and the players final score is shown to the screen.
To restart the game the player must exit the program and play it again.


## List of features of the MVP

1. 16 Randomised Letters assigned to a 4 x 4 grid.
2. A Timer is set and it counts down while the player types in words.
3. The program counts the letters to calculate the score.
4. The score is counted after a player enters a word.
5. The total score is shown on screen when the timer runs out.

## Define "out-of-scope"

Things we will not implement in the MVP Phase.

1. The ability to press "R" to restart the game.
2. Storing the players previous highest score.
3. Checking the validity of a word(Checking if it exists).
4. Graphics and Audio
5. Checking for word duplication.
6. Allow for more than one player.
7. Play the game against the computer.
8. Voice Recognition Input(Allow player to say the words instead of typing)
9. Show the possible number of words to be created.
10. Letter repetition prevention (Prevents the random letters from being the same too frequently)

# List of stories needed to complete the MVP


1. The Player, wants to see the letters offered to them, to be able to connect the words.
-The letters will be displayed in the console in 4 rows and 4 columns allowing for 16 letters to be displayed.

2. The Player, wants to type in a word which they found in the game, so that the game adds to their score.
-After the player enters the word of their choice the game adds the number of letters from the word to a total.
Everytime the player enters a word the game adds the number of letters to the total.

3. The Player, wants to see his score at the end of the game , so that they wont have to do the math themself.
- Once the timer runs out the game doesnt count any more inputs from the player.
The game calculates the players score by adding the letters of the words that the player enters.
The game then displays the final score of the player in the console.

4. The Player, wants to see the timer displayed on the screen, so that they know how much time they have left.
-The timer starts after the letters are Randomised. The timer counts down from 3 minutes, once it hits 0 the player score is displayed in the console
The timer is shown in the console while the player types in the words which they find.

5. The Player, types in a word which uses letters that are not it the grid, to see if the program will still count it towards their score.
-The game checks to see if the letters used by the player are in the grid of letters
If the letters are not in the grid the game outputs to the console "Illegal letters used, please use letters from the grid"