using System;

namespace ConsolePlatformer
{
    class Game
    {
        public void run(LevelLoader loader)
        {
            System.Console.CursorVisible = false;
            mLevel = new Level();
            mLevel.start(loader);
            System.Diagnostics.Stopwatch time = new System.Diagnostics.Stopwatch();
            time.Start();
            while (!Input.exit)
            {
                Input.update();
                if (time.ElapsedMilliseconds > 100)
                {
                    time.Restart();
                    mLevel.update();
                    Input.clearInputs();                                    
                }
                
            }
        }

        protected Level mLevel;
    }
}
