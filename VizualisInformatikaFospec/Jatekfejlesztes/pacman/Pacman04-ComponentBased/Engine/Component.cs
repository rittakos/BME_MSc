using System;

namespace ConsolePlatformer
{
    class Component
    {
        public Component(String name, GameObject gameObject) { this.name = name; mGameObject = gameObject; }
        public GameObject getGameObject() { return mGameObject; }

        public virtual void onStart() { }
        public virtual void onPreUpdate() { }
        public virtual void onPostUpdate() { }
        public virtual void onDestroy() { }
        public virtual void onCollision(Collider other) { }

        public String name;
        protected GameObject mGameObject;
    }

    //basic components

    class Renderer : Component
    {
        public Renderer(String name, GameObject gameObject, string model)
            : base(name, gameObject)
        {
            mModel = model;
        }
        public override void onPostUpdate()
        {
            render();
            mLastPos.x = mGameObject.position.x;
            mLastPos.y = mGameObject.position.y;
        }
        public void render()
        {
            if (!mLastPos.equals(mGameObject.position) || mFirstRender)
            {
                mFirstRender = false;
                Console.SetCursorPosition(mLastPos.x, mLastPos.y);
                Console.Write(' ');
                if (mGameObject.position.x >= 0 && mGameObject.position.y >= 0)
                    Console.SetCursorPosition(mGameObject.position.x, mGameObject.position.y);
                Console.Write(mModel);
            }
        }

        protected string mModel;
        protected Vec2 mLastPos = new Vec2();
        protected bool mFirstRender = true;
    }

    class Collider : Component
    {
        public Collider(String name, GameObject gameObject)
            : base(name, gameObject)
        {
            CollisionHandler.registerCollider(this);
            move = new Vec2();
        }

        public override void onPostUpdate() { move.x = move.y = 0; }
        public override void onDestroy() { CollisionHandler.removeCollider(this); }

        public bool kinematic = false;
        public Vec2 move;
    }
}
