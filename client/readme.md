# Blinkenlights Client

## How to add a new animation

  1. Write a sneaky animation function and add it to [animatios.ino](animations.ino#L35)
  2. Increase the number of the functions `NUM_ANIMATION_FUNCTIONS`
  3. Add function pointer to array in [animatios.ino](animations.ino#L27)

After that, the animation can be addressed by its index in the array.
