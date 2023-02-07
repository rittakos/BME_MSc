using System;

namespace ConsolePlatformer
{
    class CollisionHandler
    {
        public static void registerCollider(Collider collider) { mColliders.Add(collider); }
        public static void removeCollider(Collider collider) { mColliders.Remove(collider); }

        public static void update()
        {
            //handle static collisions
            foreach (Collider col in mColliders)
            {
                if (!col.kinematic)
                {
                    Vec2 newPos = col.getGameObject().position.add(col.move);
                    foreach (Collider col2 in mColliders)
                    {
                        if (col2.kinematic && col2.getGameObject().position.equals(newPos)) //a kinematic object was hit
                            col.move.setNull();
                    }
                }
            }

            foreach (Collider col in mColliders)
            {
                if (!col.kinematic)
                {
                    Vec2 newPos = col.getGameObject().position.add(col.move);
                    foreach (Collider col2 in mColliders)
                    {
                        if (col2.getGameObject().position.equals(newPos))
                        {
                            col.getGameObject().onCollision(col2);
                            col2.getGameObject().onCollision(col);
                        }
                    }
                    col.getGameObject().position = newPos;
                }
            }                   
        }

        public static bool hasKinematicItem(Vec2 position)
        {
            //handle static collisions
            foreach (Collider col in mColliders)
            {
                if (col.kinematic)
                {
                    Vec2 pos = col.getGameObject().position;
                    if(pos.equals(position))
                        return true;
                }
            }
            return false;
        }

        static System.Collections.Generic.List<Collider> mColliders = new System.Collections.Generic.List<Collider>();

    }
}
