using System;

namespace ConsolePlatformer
{
    class MainClass
	{
		public static void Main (string[] args)
		{
            Game1LevelLoader loader = new Game1LevelLoader();
            (new Game()).run(loader);
		}
	}
}
