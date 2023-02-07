using System;

namespace ConsolePlatformer
{
    class Input
    {
        public static bool left = false;
        public static bool right = false;
        public static bool up = false;
        public static bool down = false;
        public static bool exit = false;

        public static void clearInputs()
        {
            left = right = up = down = exit = false;
        }
        public static void update()
        {
            if (Console.KeyAvailable)
            {
                ConsoleKeyInfo keyinfo;
                keyinfo = Console.ReadKey(true);

                switch (keyinfo.Key)
                {
                    case ConsoleKey.UpArrow:
                        up = true;
                        break;
                    case ConsoleKey.DownArrow:
                        down = true;
                        break;
                    case ConsoleKey.LeftArrow:
                        left = true;
                        break;
                    case ConsoleKey.RightArrow:
                        right = true;
                        break;
                    case ConsoleKey.Escape:
                        exit = true;
                        break;
                }
            }
        }
    }
}
