## A simple Graphs/Game Framework.

With an ECS foundation, FTGFW hopes to bring simplicity to a developer's introduction to Graphics and Video-Game programming.
Similarly, it hopes to allow for a more blank slate for developing a Windows application.

# To Start
1. Create an FTGFWProgram Object
2. Call `FTGFWProgram.initProgram()` (Check return value for success)
3. Add and set Scene Objects
4. Call `FTGFWProgram.initRenderLoop()` (Check return value for success)
   
# For Scenes
1. Extend the Scene class to make a new Scene
2. Override the `Scene.setupScene()` method
3. Override the `Scene.exitScene()` method
## Note: Use the `componentManager` and `entityManager` Objects to
      create and remove such from the Scene
