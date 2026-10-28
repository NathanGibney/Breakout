# Breakout

W Kavanagh & N Merchant. Summer 2024 (last maintained, Oct 26)

## Controls

Move mouse to move paddle.
P to pause.
Enter to continue/restart when prompted.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)
tracker (purple)

# Tasklist

You are to spend between three and eight hours improving this simple Breakout implementation in a way to best demonstrate your capabilities as a games programmer. 

## Suggested tasks

* Implement mouse input for pad
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* Add an actual game loop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball, brick-tracking ball)
    * Note: smallPaddle is too simple to be impressive.
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as Ollama

# Time Details and Changelist
(27/10/2026) (90 minutes spent)
Game loop - Game no longer ends once all bricks are broken. advance to a new stage to play infinitely 
Scoring - Earn point for breaking bricks. score increases further with consecutive hits and at higher levels 
(28/10/2026) (120 minutes spent)
Increasing difficulty - The number of bricks and the speed of the ball will increase with each level 
Tracking powerup - Pick this up to cause the ball to track your paddle for easy recovery
Particle effects - bricks now create particles on destruction 
Mouse input - paddle is now moved using the mouse instead of the keyboard

---

### Change log
* 2025 - Naman made it harder
* 2026 - William made it easier again

---

Curse you, fast ball!
