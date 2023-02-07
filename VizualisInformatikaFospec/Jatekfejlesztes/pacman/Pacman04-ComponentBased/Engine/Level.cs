using System;

namespace ConsolePlatformer
{
    class LevelLoader
    {
        public virtual void loadLevel(Level level)
        {

        }
    }

    class Level
    {
        System.Collections.Generic.List<GameObject> mLevelObjects = new System.Collections.Generic.List<GameObject>();

        public void start(LevelLoader loader)
        {
            loader.loadLevel(this);

            foreach (GameObject go in mLevelObjects)
                go.onStart();
        }
        public void update()
        {
            System.Collections.Generic.List<GameObject> destroyList = new System.Collections.Generic.List<GameObject>();
            foreach (GameObject go in mLevelObjects)
                if (go.destroyMark)
                    destroyList.Add(go);
            foreach (GameObject go in destroyList)
                go.finalizeDestroy();

            foreach (GameObject go in mLevelObjects)
                go.onPreUpdate();
            
            CollisionHandler.update();

            foreach (GameObject go in mLevelObjects)
                go.onPostUpdate();
        }
        public void addGameObject(GameObject gameObject)
        {
            mLevelObjects.Add(gameObject);
        }
        public void removeGameObject(GameObject gameObject)
        {
            mLevelObjects.Remove(gameObject);
        }
    }
}
