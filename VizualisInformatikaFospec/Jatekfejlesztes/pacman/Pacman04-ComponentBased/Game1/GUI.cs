using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsolePlatformer
{
    class GUIDrawer : Component
    {
        public GUIDrawer(string name, GameObject gameObject) : base(name, gameObject) { }
        public override void onPostUpdate()
        {
            Console.SetCursorPosition(1, 0);
            Console.Write("score " + player.score + " life: " + player.life);
            if (player.life == 0)
            {
                Console.SetCursorPosition(10, 10);
                Console.Write("GAME OVER");
            }
            if(levelData.levelCompleted)
            {
                Console.SetCursorPosition(10, 10);
                Console.Write("LEVEL COMPLETED");
            }
        }
        public Player player = null;
        public LevelData levelData = null;
    }
    class GUI : GameObject
    {
        public GUI(Level level) : base(level)
        {
            GUIDrawer guiDrawer = new GUIDrawer("drawer", this);
            mComponents.Add(guiDrawer);
        }
    }
}
