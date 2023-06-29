using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pacman03_OOP
{
    class MovingGameObject : GameObject
    {
        public virtual void allowMove()
        {
            position = position.add(move);
            move.setNull();
        }

        public virtual void cancelMove()
        {
            move.setNull();
        }

        public Vec2 move = new Vec2();
    }
}
