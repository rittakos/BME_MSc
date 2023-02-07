using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pacman03_OOP
{
    class Coin : MovingGameObject
    {
        public override void render()
        {
            System.Console.SetCursorPosition(position.x, position.y + 1);
            System.Console.Write('.');
        }

        public override void onCollision(GameObject other)
        {
            if (other.tag == TAG_PLAYER)
            {
                Player player = (Player)other;
                player.score += 1;
                destroy = true;
            }
        }
    }
}
