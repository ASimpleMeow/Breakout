# Breakout

---

## Game description
>Breakout is an arcade game developed and published by Atari, Inc., released on May 13, 1976.

Source: [Wiki](https://en.wikipedia.org/wiki/Breakout_(video_game))

## Technologies used
- Visual Studio 2015
- C++14
- SFML


## Features
- Multiple levels - i.e. Press numbers 1, 2, 3, etc to switch levels.
- Automatic paddle (level 2).
- Multiple balls trapped in blocks, when the main ball breaks out the ball, the ball will be active and may also break blocks (level 3).
- Different block types + randomness (level 4):
    - Normal blocks.
    - Trap blocks - will slow your ball down by 1/3 for a period of time.
    - Durable blocks - Take 3 direct hits to destory, their level of durability will be shown via colour.
        - White : Full health
        - Gray : Two hits left
        - Dark Gray : One hit left
    - Regen blocks - Take 2 direct hits to destory, but will regenerate their health over a short period of time.
- Text display for current level and score (where score in dependant on the blocks destoryed and their blockType).
- Resize feature where the ratio of the shapes sizes to the window size is preserved.
- Random ball velocity (within a limit given by two constants BALL_VELOCITY_MIN and BALL_VELOCITY_MAX).
- Looping background arcade music to make the player really annoyed.
- Automatic level transition : 
	- When you destroy all block it goes to the next level
	- Once it reaches the final level it loops back to the first level.