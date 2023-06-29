using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsolePlatformer
{
    class LevelDataComponent :Component
    {
        public LevelDataComponent(string name, GameObject gameObject) :base(name, gameObject)
        {
            levelData = (LevelData)mGameObject;
        }
        public override void onPreUpdate()
        {
            if (levelData.coinsRemain == 0)
                levelData.levelCompleted = true;
        }
        LevelData levelData;
    }
    class LevelData : GameObject
    {
        public LevelData(Level level) : base(level)
        {
            LevelDataComponent ldc = new LevelDataComponent("data", this);
            mComponents.Add(ldc);
        }
        public int coinsRemain = -1;
        public bool levelCompleted;
    }
}
