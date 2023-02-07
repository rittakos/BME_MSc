using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsolePlatformer
{
    class CoinCollectComponent : Component
    {
        public CoinCollectComponent(string name, GameObject gameObject) : base(name, gameObject) { }

        public override void onStart()
        {
            levelData.coinsRemain++;
        }

        public override void onCollision(Collider other)
        {
            if (other.getGameObject() == player)
            {
                player.score += 10;
                levelData.coinsRemain--;
                mGameObject.destroy();
            }
        }

        public Player player = null;
        public LevelData levelData = null;
    }
    class Coin : GameObject
    {
        public Coin(Level level)
            : base(level)
        {
            Renderer renderer = new Renderer("renderer", this, ".");
            Collider collider = new Collider("collider", this);
            CoinCollectComponent collect = new CoinCollectComponent("collect", this);
            mComponents.Add(renderer);
            mComponents.Add(collider);
            mComponents.Add(collect);
        }
    }
}
