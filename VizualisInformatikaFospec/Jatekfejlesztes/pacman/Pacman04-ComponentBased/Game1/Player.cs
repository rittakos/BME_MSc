using System;

namespace ConsolePlatformer
{
    class PlayerController : Component
    {
        public PlayerController(String name, GameObject gameObject)
            : base(name, gameObject)
        {
        }
        public override void onStart()
        {
            colliderComponent = (Collider)mGameObject.getComponent("collider");
        }
        public override void onPreUpdate()
        {
            if (((Player)mGameObject).life == 0)
                return;

            if (Input.left)
                colliderComponent.move.x -= 1;
            if (Input.right)
                colliderComponent.move.x += 1;
            if (Input.up)
                colliderComponent.move.y -= 1;
            if (Input.down)
                colliderComponent.move.y += 1;
        }
        
        Collider colliderComponent;        
    }

    class Player : GameObject
    {
        public Player(Level level)
            : base(level)
        {
            Renderer renderer = new Renderer("renderer", this, "<");
            PlayerController controller = new PlayerController("control", this);
            Collider collider = new Collider("collider", this);
            mComponents.Add(renderer);
            mComponents.Add(collider);
            mComponents.Add(controller);

            position.x = 0;
            position.y = 0;
        }
       
        public int score = 0;
        public int life = 5;
    }
}
