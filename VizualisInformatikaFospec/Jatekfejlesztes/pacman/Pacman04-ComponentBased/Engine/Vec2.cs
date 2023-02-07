using System;

namespace ConsolePlatformer
{
    class Vec2
    {
        public Vec2() { }
        public Vec2(int x, int y) { this.x = x; this.y = y; }

        public bool equals(Vec2 other) { return x == other.x && y == other.y; }
        public Vec2 add(Vec2 other) { return new Vec2(x + other.x, y + other.y); }
        public void setNull() { x = y = 0; }
        public int x = 0;
        public int y = 0;
    }
}
