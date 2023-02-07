using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pacman03_OOP
{
    class Player : MovingGameObject
    {
        public Player() { tag = TAG_PLAYER; }
        public override void render()
        {
            System.Console.SetCursorPosition(position.x, position.y + 1);
            System.Console.Write('<');
        }
        public override void allowMove()
        {
            //System.Console.SetCursorPosition(position.x, position.y + 1);
            //System.Console.Write(" ");

            base.allowMove();

            //render();
        }

        public override void update()
        {
            // move.setNull(); // move should be zero at the beginning of each iteration
            if (Input.left)
                move.x = -1;
            if (Input.right)
                move.x = 1;
            if (Input.up)
                move.y = -1;
            if (Input.down)
                move.y = 1;
            if (Input.exit)
                System.Environment.Exit(0);
        }

        public int score = 0;
    }
}
