using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pacman02_UglyOOP
{
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

        static Random rnd = new Random();
        static Vec2 playerMove = new Vec2(0, 0);

        class Vec2
        {
            public int x = 0;
            public int y = 0;

            public Vec2(){}
            public Vec2(int x, int y) { this.x = x; this.y = y; }
            public Vec2 add(Vec2 other) { return new Vec2(x+other.x, y+other.y);}
            public void setNull() { x = y = 0; }
            public bool isNull() { return x == 0 && y == 0; }
        }
        
        class GameObject
        {
            public enum GO_Type
            {
                WALL,
                HERO,
                ENEMY,
                COIN
            }
            
            public void render()
            {
                System.Console.SetCursorPosition(position.x, position.y + 1);
                switch (mType)
                {
                case GO_Type.WALL:
                    System.Console.Write('#');
                    break;
                case GO_Type.COIN:
                    System.Console.Write('.');
                    break;
                case GO_Type.ENEMY:
                    System.Console.Write('@');
                    break;
                case GO_Type.HERO:
                    System.Console.Write('<');
                    break;
                }
            }

            public void update()
            {
                if (mType == GO_Type.HERO)
                {
                    move = playerMove;
                    
                }
                else if (mType == GO_Type.ENEMY)
                {
                    move.x = rnd.Next(-1, 2);
                    if (move.x == 0) // prevent diagonal moves
                        move.y = rnd.Next(-1, 2);
                }
            }

            public void allowMove()
            {
                position = position.add(move);
                move.setNull();
            }

            public void cancelMove()
            {
                move.setNull();
            }

            public GO_Type mType;
            public Vec2 position = new Vec2();
            public Vec2 move = new Vec2();
            public int score = 0;
        }

        
        class Game
        {
            GameObject[][] map;
            GameObject player = null;
                
            public void run()
            {
                int cols = mapS[0].Length;
                int rows = mapS.Length;
                map = new GameObject[rows][];
                for (int j = 0; j < rows; ++j)
                {
                    map[j] = new GameObject[cols];
                    for (int i = 0; i < cols; ++i)
                    {
                        GameObject go = new GameObject();
                        map[j][i] = go;
                        go.position = new Vec2(i, j);
                        if (mapS[j][i] == '#')
                            go.mType = GameObject.GO_Type.WALL;
                        else if (mapS[j][i] == '.')
                            go.mType = GameObject.GO_Type.COIN;
                        else if (mapS[j][i] == '<')
                        {
                            go.mType = GameObject.GO_Type.HERO;
                            player = go;
                        }
                        else if (mapS[j][i] == '@')
                            go.mType = GameObject.GO_Type.ENEMY;
                    }
                }

                //draw level
                for (int i = 0; i < cols; ++i)
                {
                    for (int j = 0; j < rows; ++j)
                    {
                        map[j][i].render();
                    }
                }
                System.Console.CursorVisible = false;
                System.Console.SetCursorPosition(0, 0);
                System.Console.Write("Score: 0");

                System.Diagnostics.Stopwatch time = new System.Diagnostics.Stopwatch();
                time.Start();
                while (true)
                {
                    processInput();

                    if (time.ElapsedMilliseconds > 100)
                    {
                        time.Restart();

                        // update() part I., update every game object
                        for (int i = 0; i < cols; ++i)
                        {
                            for (int j = 0; j < rows; ++j)
                            {
                                if (map[j][i] != null)
                                    map[j][i].update();
                            }
                        }
                        // update() part II., validate moves
                        for (int i = 0; i < cols; ++i)
                        {
                            for (int j = 0; j < rows; ++j)
                            {
                                GameObject gameObject = map[j][i];
                                if (gameObject != null)
                                {
                                    if (!gameObject.move.isNull())
                                    {
                                        Vec2 targetPosition = gameObject.position.add(gameObject.move);
                                        GameObject targetObj = map[targetPosition.y][targetPosition.x];
                                        if (targetObj == null || targetObj.mType != GameObject.GO_Type.WALL)
                                        {
                                            if (gameObject.mType == GameObject.GO_Type.HERO)
                                            {
                                                if (targetObj != null && targetObj.mType == GameObject.GO_Type.COIN)
                                                {
                                                    ++player.score;
                                                }
                                                if (targetObj != null && targetObj.mType == GameObject.GO_Type.ENEMY)
                                                {
                                                    player = null;
                                                }
                                            }
                                            else if (gameObject.mType == GameObject.GO_Type.ENEMY)
                                            {
                                                if (targetObj != null && targetObj.mType == GameObject.GO_Type.HERO)
                                                {
                                                    player = null;
                                                }
                                            }

                                            map[gameObject.position.y][gameObject.position.x] = null;
                                            gameObject.allowMove();
                                            map[gameObject.position.y][gameObject.position.x] = gameObject;
                                        }
                                        else
                                        {
                                            gameObject.cancelMove();
                                        }
                                    }
                                }
                            }
                        }

                        // render()
                        drawGUI();
                        for (int i = 0; i < cols; ++i)
                        {
                            for (int j = 0; j < rows; ++j)
                            {
                                if (map[j][i] != null)
                                {
                                    map[j][i].render();
                                }
                                else
                                {
                                    System.Console.SetCursorPosition(i, j + 1);
                                    System.Console.Write(' ');
                                }
                            }
                        }

                        resetInput();
                    }
                }
            }

            void resetInput()
            {
                playerMove.setNull();
            }

            void processInput()
            {
                if (System.Console.KeyAvailable)
                {
                    ConsoleKeyInfo keyinfo = System.Console.ReadKey(true);
                    if (keyinfo.Key == ConsoleKey.LeftArrow)
                        playerMove.x -= 1;
                    if (keyinfo.Key == ConsoleKey.RightArrow)
                        playerMove.x += 1;
                    if (keyinfo.Key == ConsoleKey.UpArrow)
                        playerMove.y -= 1;
                    if (keyinfo.Key == ConsoleKey.DownArrow)
                        playerMove.y += 1;
                    if (keyinfo.Key == ConsoleKey.Escape)
                        System.Environment.Exit(0);
                }
            }

            void drawGUI()
            {
                if(player == null)
                {
                    System.Console.SetCursorPosition(0, 0);
                    System.Console.Write("GAME OVER");
                    System.Threading.Thread.Sleep(3000);
                    System.Environment.Exit(0);
                }
                System.Console.SetCursorPosition(0, 0);
                System.Console.Write("Score: " + player.score);
            }
        }
        static void Main(string[] args)
        {
            Game game = new Game();
            game.run();
        }
    }
}