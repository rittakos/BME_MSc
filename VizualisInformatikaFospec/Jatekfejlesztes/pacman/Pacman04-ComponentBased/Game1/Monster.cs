using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsolePlatformer
{
    class MonsterController : Component
    {
        private static readonly System.Random random = new System.Random();

        public MonsterController(String name, GameObject gameObject) : base (name, gameObject)
        {
        }

        public override void onStart()
        {
            colliderComponent = (Collider)mGameObject.getComponent("collider");
        }
        public override void onPreUpdate()
        {
            frameID++;
            //AI???            
            if (frameID % speed != 0)
                return;
            //four directions + lasdir
            Vec2[] dirs = {lastMove, new Vec2(1,0), new Vec2(-1,0), new Vec2(0,1), new Vec2(0,-1)};
            System.Collections.Generic.List<int> good_directions = new System.Collections.Generic.List<int>();
            
            for(int i = 0; i < 5; ++i)
            {
                Vec2 dir = dirs[i];
                if(!CollisionHandler.hasKinematicItem(mGameObject.position.add(dir)))
                {
                    if(dir.equals(lastMove)) //keep going in our direction if we can
                    {
                        colliderComponent.move.x = dir.x;
                        colliderComponent.move.y = dir.y;
                        lastMove.x = dir.x;
                        lastMove.y = dir.y;
                        return;
                    }
                    good_directions.Add(i);
                }
            }
            int[] good = good_directions.ToArray();
            int rand = random.Next(0,good.Length);
            Vec2 dir2 = dirs[good[rand]];
            colliderComponent.move.x = dir2.x;
            colliderComponent.move.y = dir2.y;
            lastMove.x = dir2.x;
            lastMove.y = dir2.y;
        }
        public override void onCollision(Collider other)
        {
            if (other.getGameObject() == player)
            {
                player.life--;
                mGameObject.destroy();
            }
        }

        Collider colliderComponent;
        public Player player = null;
        protected Vec2 lastMove = new Vec2(1,0);
        private int frameID = 0;
        private int speed = 10;
    }

    class Monster : GameObject
    {
        public Monster(Level level) : base(level)
        {
            Renderer renderer = new Renderer("renderer", this, "@");
            MonsterController controller = new MonsterController("control", this);
            Collider collider = new Collider("collider", this);
            mComponents.Add(renderer);
            mComponents.Add(collider);
            mComponents.Add(controller);        
        }
    }
}
