using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pacman03_OOP
{
    class GameObject
    {
        public virtual void render() { }
        public virtual void update() { }
        public virtual void onCollision(GameObject other) { }

        public Vec2 position = new Vec2();
        public int tag;
        public bool destroy;

        public static int TAG_NONE = 0;
        public static int TAG_PLAYER = 1;
    }
}
