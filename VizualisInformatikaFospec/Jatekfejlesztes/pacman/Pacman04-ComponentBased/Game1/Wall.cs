using System;

namespace ConsolePlatformer
{
    class HWall : GameObject
    {
        public HWall(Level level)
            : base(level)
        {
            Renderer renderer = new Renderer("renderer", this, "-");
            Collider collider = new Collider("collider", this);
            collider.kinematic = true;
            mComponents.Add(renderer);
            mComponents.Add(collider);
        }
    }

    class VWall : GameObject
    {
        public VWall(Level level)
            : base(level)
        {
            Renderer renderer = new Renderer("renderer", this, "|");
            Collider collider = new Collider("collider", this);
            collider.kinematic = true;
            mComponents.Add(renderer);
            mComponents.Add(collider);
        }
    }

    class Wall : GameObject
    {
        public Wall(Level level)
            : base(level)
        {
            Renderer renderer = new Renderer("renderer", this, "#");
            Collider collider = new Collider("collider", this);
            collider.kinematic = true;
            mComponents.Add(renderer);
            mComponents.Add(collider);
        }
    }
}
