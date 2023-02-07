using System;

namespace ConsolePlatformer
{
    class Game1LevelLoader : LevelLoader
    {
        public override void loadLevel(Level level)
        {
            System.IO.StreamReader reader = System.IO.File.OpenText("level1.txt");
            string line;
            int y = 1;

            LevelData levelData = new LevelData(level);
            
            Player player = new Player(level);
            GUI gui = new GUI(level);
            ((GUIDrawer)gui.getComponent("drawer")).player = player;
            ((GUIDrawer)gui.getComponent("drawer")).levelData = levelData;
            level.addGameObject(gui);
                        
            while ((line = reader.ReadLine()) != null)
            {
                for(int x = 0; x < line.Length; ++x)
                {
                    char c = line[x];
                    GameObject obj = null;
                    if(c == '<')
                    {
                        obj = player;
                    }
                    else if(c == '|')
                    {
                        VWall wall = new VWall(level);
                        obj = wall;                    
                    }
                    else if (c == '-')
                    {
                        HWall wall = new HWall(level);
                        obj = wall;
                    }
                    else if (c == '#')
                    {
                        Wall wall = new Wall(level);
                        obj = wall;
                    }
                    else if (c == '.')
                    {
                        Coin coin = new Coin(level);
                        ((CoinCollectComponent) coin.getComponent("collect")).player = player;
                        ((CoinCollectComponent)coin.getComponent("collect")).levelData = levelData;
                        obj = coin;
                    }
                    else if (c == '@')
                    {
                        Monster monster = new Monster(level);
                        ((MonsterController)monster.getComponent("control")).player = player;
                        obj = monster;
                    }

                    if (obj != null)
                    {
                        obj.position.x = x;
                        obj.position.y = y;
                        level.addGameObject(obj);
                    }                    
                }
                y++;
            }
        }
    }
}
