# Diamond Hunt Game

## Gameplay

A Linux C++ game using the NCurses library to display ASCII characters on the terminal. <br>
The player (Potter - P), the villain (Malfoy - M) and the diamond are placed randomly at the beggining of the game.<br>
With each movement the player makes with the arrow keys, the villain-pc moves towards the diamond taking the shortest path.<br>
Each turn the diamond has a 3% probability of changing its position to a random valid location.<br>
The first to reach the diamond is the winnner.<br><br>


<p align="center">
  <img src="https://github.com/josezapiz/Diamond-Hunt-Game/assets/101471178/e6d6f8fb-24fa-47e2-9e36-1b191e826aed"
      width="400" 
      height="300"/>
</p>


## Technical
Executing game: ****./a.out map.txt**** <br>

The .txt file must contain a map with '*' as walls and '.' as space where objects can move. <br>
The code then converts the ascii characters to more user-friendly entitities. <br>
