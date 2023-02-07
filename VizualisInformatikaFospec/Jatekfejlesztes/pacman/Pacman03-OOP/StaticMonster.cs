﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pacman03_OOP
{
    internal class StaticMonster : MovingGameObject
    {
        public override void render()
        {
            System.Console.SetCursorPosition(position.x, position.y + 1);
            System.Console.Write('*');
        }

        public override void update()
        {
            
        }

        public override void onCollision(GameObject other)
        {
            other.destroy = true;
            /*if (other.tag == TAG_PLAYER)
            {
                Player player = (Player)other;
                player.destroy = true;
            }*/
        }

        public override void allowMove()
        {
            //System.Console.SetCursorPosition(position.x, position.y + 1);
            //System.Console.Write(" ");

            base.allowMove();

            //render();
        }
    }
}
