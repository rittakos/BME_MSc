using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pacman03_OOP
{
    class Mover
    {
        System.Collections.Generic.List<MovingGameObject> mObjects = new System.Collections.Generic.List<MovingGameObject>();
        public void addGameObject(MovingGameObject gameObject)
        {
            mObjects.Add(gameObject);
            mObjectsStructured[gameObject.position.y][gameObject.position.x] = gameObject;
        }
        public void removeGameObject(MovingGameObject gameObject)
        {
            mObjects.Remove(gameObject);
            mObjectsStructured[gameObject.position.y][gameObject.position.x] = null;
        }

        MovingGameObject[][] mObjectsStructured;

        bool[][] mStaticObjects;
        public void addStaticObject(Vec2 position)
        {
            mStaticObjects[position.y][position.x] = true;
        }

        public void setLevelSize(int rows, int cols)
        {
            mStaticObjects = new bool[rows][];
            mObjectsStructured = new MovingGameObject[rows][];
            for (int i = 0; i < rows; ++i)
            {
                mStaticObjects[i] = new bool[cols];
                mObjectsStructured[i] = new MovingGameObject[cols];
            }
        }

        public void update()
        {
            foreach (MovingGameObject go in mObjects)
            {
                if (!go.move.isNull())
                {
                    Vec2 targetPosition = go.position.add(go.move);
                    if (mStaticObjects[targetPosition.y][targetPosition.x])
                    {
                        go.cancelMove();
                    }
                    else
                    {
                        mObjectsStructured[go.position.y][go.position.x] = null;
                        go.allowMove();
                        GameObject other = mObjectsStructured[go.position.y][go.position.x];
                        mObjectsStructured[go.position.y][go.position.x] = go;
                        if (other != null)
                        {
                            other.onCollision(go);
                            go.onCollision(other);
                        }
                    }
                }
            }
        }
    }
}
