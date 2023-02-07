using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pacman03_OOP
{
    class Wall : GameObject
    {
        public override void render()
        {
            System.Console.SetCursorPosition(position.x, position.y + 1);
            System.Console.Write('#');
        }
    }
}
