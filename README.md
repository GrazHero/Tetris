<b><h3>Tetris</h3></b>

<p>
The game of Tetris, written in C++ using SDL2. Primarily a personal programming exercise.  
</p>
<p>
It was structurally not very well planned out. I started out mostly using C++ as if it were C.
Lots of global variables for controlling the game state, etc...
Then I started mixing in more C++ features. As a result, the project became something of a fractured mess.
Definitely very poorly optimized. Because of my lack of planning, there are several different loops through
the whole grid per frame. I'm too trigger happy with ``for`` loops in general. Ideally I'd do everything I
need in a single loop, but it's too late now.

It's just for fun though.
It's almost what I'd consider "playable", just a bit more needs to be done.

</p>
<h2>To Do</h2>
<p>
If my interest doesn't wane, I'll add
-actual graphics
-a little area to disply score and the next piece
-ability to drop the current piece down immediately
-high scores that persist after game is closed
-a title screen
-music
-ability to select speed, have it gradually increase just like in the real tetris
</p>

<h2>Compilation</h2>
<p>
Only tested with mingw32 on Windows and g++ on GNU/Linux. (The last compilation on Linux I tried was 
several commits back, but it should still work)

It will require C++14 support due to my rather ill advised use of binary literals in just one function.

I'm using SDL2.0.8. Older version might work. I was using 2.0.7, but updated because GDB was bugging out
 over it.

Some platform specific code (just enough to make an error window appear on Windows. Too bad SDL can't do that) exists inside a preprocessor
check, I'm pretty sure I kept it all contained

Hasn't been tested yet with compiler optimizations.
Also, no makefile is included yet. I've just been using CodeBlocks IDE on Windows and a bash script on Linux.
</p>