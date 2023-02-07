using System;

namespace ConsolePlatformer
{
    class GameObject
    {
        static int TAG_NONE = 0;
        static int TAG_PLAYER = 1;
        static int TAG_ENEMY = 2;
        static int TAG_COLLECTABE = 3;
        
        public GameObject(Level level)
        {
            mLevel = level;
        }
        public void destroy()
        {
            destroyMark = true;            
        }

        public void finalizeDestroy()
        {
            if (destroyMark)
            {
                foreach (Component c in mComponents)
                    c.onDestroy();
                mLevel.removeGameObject(this);
            }
        }

        public Level getLevel() { return mLevel; }
        public void onStart()
        {
            foreach (Component c in mComponents)
                c.onStart();
        }
        public void onPreUpdate()
        {
            foreach (Component c in mComponents)
                c.onPreUpdate();
        }
        public void onPostUpdate()
        {
            foreach (Component c in mComponents)
                c.onPostUpdate();
        }
        public void onCollision(Collider other)
        {
            foreach (Component c in mComponents)
                c.onCollision(other);
        }
        public Component getComponent(String name)
        {
            foreach (Component c in mComponents)
                if (c.name.Equals(name))
                    return c;
            return null;
        }

        public Vec2 position = new Vec2();
        public int tag = TAG_NONE;
        public bool destroyMark = false;
        
        protected Level mLevel;
        protected System.Collections.Generic.List<Component> mComponents = new System.Collections.Generic.List<Component>();
    }
}
