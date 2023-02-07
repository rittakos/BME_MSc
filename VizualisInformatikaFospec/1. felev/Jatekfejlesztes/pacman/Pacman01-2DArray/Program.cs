using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pacman01_2DArray
{
    class Monster
    {
        public int X;
        public int Y;
        public int oldX;
        public int oldY;
        public Monster(int x, int y)
        {
            X = x;
            Y = y;
        }
        public void move(int x, int y)
        {
            oldX = X;
            oldY = Y;

            X = oldX + x;
            Y = oldY + y;
        }
    }
    class Program
    {
        static string[] mapS = {
            "##############",
            "#..#.###@...##",
            "##.#...#.##..#",
            "##.#.###.#####",
            "##<..........#",
            "##############"
                               };
        static char[][] map;
        static int moveX = 0;
        static int moveY = 0;
        static int playerPosX = 0;
        static int playerPosY = 0;
        static int oldPlayerPosX;
        static int oldPlayerPosY;
        static int score = 0;
        static int life = 1;

        static List<Monster> monsters = new List<Monster>();

        static void moveMonsters()
        {
            Random rnd = new Random(4);
            foreach (Monster monster in monsters)
            {
                bool succes = false;
                while (!succes)
                {
                    int dir = rnd.Next();
                    if (dir == 0)
                    {
                        moveY = 1;
                        moveX = 0;
                    }

                    if (dir == 1)
                    {
                        moveY = -1;
                        moveX = 0;
                    }

                    if (dir == 2)
                    {
                        moveY = 0;
                        moveX = 1;
                    }

                    if (dir == 3)
                    {
                        moveY = 0;
                        moveX = -1;
                    }

                    int newX = monster.X + moveX;
                    int newY = monster.Y + moveY;

                    char obj = map[newX][newY];
                    if (obj != '#')
                    {
                        monster.move(moveX, moveY);
                        succes = true;
                    }

                }
            }
        }

        static void Main(string[] args)
        {
            init();

            while (true)
            {
                processInput();
                update();
                render();
            }

        }

        static void init()
        {
            int cols = mapS[0].Length;
            int rows = mapS.Length;
            map = new char[rows][];
            for (int j = 0; j < rows; ++j)
            {
                map[j] = new char[cols];
                for (int i = 0; i < cols; ++i)
                {
                    map[j][i] = mapS[j][i];
                }
            }

            //draw level
            for (int i = 0; i < cols; ++i)
            {
                for (int j = 0; j < rows; ++j)
                {
                    System.Console.SetCursorPosition(i, j + 1);
                    char obj = map[j][i];
                    if (obj == '@')
                        monsters.Add(new Monster(i, j));
                    System.Console.Write(obj);
                    if (obj == '<')
                    {
                        playerPosX = i;
                        playerPosY = j;
                    }
                }
            }
            System.Console.CursorVisible = false;
            System.Console.SetCursorPosition(0, 0);
            System.Console.Write("Score: 0");
        }

        static void resetInput()
        {
            moveX = moveY = 0;
        }

        static void processInput()
        {
            resetInput();

            if (System.Console.KeyAvailable)
            {
                ConsoleKeyInfo keyinfo = System.Console.ReadKey(true);
                if (keyinfo.Key == ConsoleKey.LeftArrow)
                    moveX -= 1;
                if (keyinfo.Key == ConsoleKey.RightArrow)
                    moveX += 1;
                if (keyinfo.Key == ConsoleKey.UpArrow)
                    moveY -= 1;
                if (keyinfo.Key == ConsoleKey.DownArrow)
                    moveY += 1;
                if (keyinfo.Key == ConsoleKey.Escape)
                    System.Environment.Exit(0);
            }
        }

        static void update()
        {
            oldPlayerPosX = playerPosX;
            oldPlayerPosY = playerPosY;
            int newPlayerPosX = playerPosX + moveX;
            int newPlayerPosY = playerPosY + moveY;

            moveMonsters();

            char obj = map[newPlayerPosY][newPlayerPosX];
            if (obj != '#') //not a wall hit
            {
                if (obj == '.')
                {
                    score++;
                    map[newPlayerPosY][newPlayerPosX] = ' ';
                }
                else if (obj == '@')
                {
                    --life;
                    if (life <= 0)
                    {
                        System.Console.SetCursorPosition(0, 0);
                        System.Console.Write("GAME OVER");
                        System.Threading.Thread.Sleep(3000);
                        System.Environment.Exit(0);
                    }
                }
                playerPosX = newPlayerPosX;
                playerPosY = newPlayerPosY;
            }
        }

        static void render()
        {
            System.Console.SetCursorPosition(0, 0);
            System.Console.Write("Score: " + score);

            System.Console.SetCursorPosition(oldPlayerPosX, oldPlayerPosY + 1);
            System.Console.Write(" ");

            foreach(Monster monster in monsters)
            {
                System.Console.SetCursorPosition(monster.oldX, monster.oldY);
                System.Console.Write(" ");
                System.Console.SetCursorPosition(monster.X, monster.Y);
                System.Console.Write("@");
            }

            System.Console.SetCursorPosition(playerPosX, playerPosY + 1);
            System.Console.Write("<");
        }
    }
}