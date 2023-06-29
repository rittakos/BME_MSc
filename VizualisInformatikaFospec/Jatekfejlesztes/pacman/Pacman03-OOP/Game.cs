using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pacman03_OOP
{
    class Game
    {
        public static Random rnd = new Random();
        
        System.Collections.Generic.List<GameObject> mGameObjects = new System.Collections.Generic.List<GameObject>();
        static string[] mapS = {
            "##############",
            "#*.#.###@...##",
            "##.#...#.##..#",
            "##.#.###.#####",
            "##<.....%.&..#",
            "##############"
                              };
        Player player = null;
        Mover mover = new Mover();

        public void run()
        {
            init();

            System.Diagnostics.Stopwatch time = new System.Diagnostics.Stopwatch();
            time.Start();
            while (true)
            {
                Input.update();

                if (time.ElapsedMilliseconds > 100)
                {
                    time.Restart();
                    update();
                    render();
                    Input.clearInputs();
                }
            }

        }

        void init()
        {
            int cols = mapS[0].Length;
            int rows = mapS.Length;
            mover.setLevelSize(rows, cols);
            for (int j = 0; j < rows; ++j)
            {
                for (int i = 0; i < cols; ++i)
                {
                    GameObject go = null;

                    if (mapS[j][i] == '#')
                    {
                        go = new Wall();
                        go.position = new Vec2(i, j);
                        mover.addStaticObject(go.position);
                    }
                    else if (mapS[j][i] == '.')
                    {
                        Coin co = new Coin();
                        co.position = new Vec2(i, j);
                        go = co;
                        mover.addGameObject(co);
                    }
                    else if (mapS[j][i] == '<')
                    {
                        go = player = new Player();
                        go.position = new Vec2(i, j);
                        mover.addGameObject(player);
                    }
                    else if (mapS[j][i] == '@')
                    {
                        Monster mo = new Monster();
                        mo.position = new Vec2(i, j);
                        go = mo;
                        mover.addGameObject(mo);
                    }
                    else if (mapS[j][i] == '*')
                    {
                        StaticMonster mo = new StaticMonster();
                        mo.position = new Vec2(i, j);
                        go = mo;
                        mover.addGameObject(mo);
                    }
                    else if (mapS[j][i] == '&')
                    {
                        VerticalMoverMonster mo = new VerticalMoverMonster();
                        mo.position = new Vec2(i, j);
                        go = mo;
                        mover.addGameObject(mo);
                    }
                    else if (mapS[j][i] == '%')
                    {
                        FollowerMonster mo = new FollowerMonster();
                        mo.position = new Vec2(i, j);
                        go = mo;
                        mover.addGameObject(mo);
                    }
                    if (go != null)
                        mGameObjects.Add(go);
                }
            }

            foreach (GameObject go in mGameObjects)
            {
                go.render();
            }
            System.Console.CursorVisible = false;
            System.Console.SetCursorPosition(0, 0);
            System.Console.Write("Score: 0");
        }

        void update()
        {            
            foreach (GameObject go in mGameObjects)
            {
                go.update();
            }
            mover.update();

            System.Collections.Generic.List<GameObject> toBeDeleted = new System.Collections.Generic.List<GameObject>();
            foreach (GameObject go in mGameObjects)
            {
                if (go.destroy)
                    toBeDeleted.Add(go);
            }
            
            foreach (GameObject go in toBeDeleted)
            {
                if (go == player)
                    player = null;
                mGameObjects.Remove(go);
                mover.removeGameObject((MovingGameObject)go);
            }
        }

        void render()
        {
            System.Console.Clear();
            foreach (GameObject go in mGameObjects)
            {
                go.render();
            }

            if (player == null)
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
}
