using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pacman03_OOP
{
    class Vec2
    {
        public int x = 0;
        public int y = 0;

        public Vec2() { }
        public Vec2(int x, int y) { this.x = x; this.y = y; }
        public Vec2 add(Vec2 other) { return new Vec2(x + other.x, y + other.y); }
        public void setNull() { x = y = 0; }
        public bool isNull() { return x == 0 && y == 0; }
    }
}
