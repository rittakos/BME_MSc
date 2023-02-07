using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace GestureSkeleton
{
    public enum HandLandMarks
    {
        WRIST = 0,
        THUMB_0, THUMB_1, THUMB_2, THUMB_3,
        INDEX_FINGER_0, INDEX_FINGER_1, INDEX_FINGER_2, INDEX_FINGER_3,
        MIDDLE_FINGER_0, MIDDLE_FINGER_1, MIDDLE_FINGER_2, MIDDLE_FINGER_3,
        RING_FINGER_0, RING_FINGER_1, RING_FINGER_2, RING_FINGER_3,
        PINKY_0, PINKY_1, PINKY_2, PINKY_3
    }
    public enum HandDir { Left, Right }


    [Flags]
    public enum Fingers
    {
        None = 0,
        Thumb = 1 << 0,
        Index = 1 << 1,
        Middle = 1 << 2,
        Ring = 1 << 3,
        Pinky = 1 << 4
    }

    public enum FingerState
    {
        Stretched, Closed
    }

    public struct Hand
    {
        public Vector3[] landmarks;
        public HandDir handDir;

        public Vector3 Get(HandLandMarks landmark)
        {
            return landmarks[(int)landmark];
        }

        public Vector3[] Get(HandLandMarks landmark, params HandLandMarks[] rest)
        {
            var ret = new Vector3[rest.Count() + 1];
            ret[0] = Get(landmark);
            for (int i = 0; i < rest.Count(); ++i)
            {
                ret[i+1] = Get(rest[i]);
            }
            return ret;
        }

        public List<Vector3> Get(Fingers fingers)
        {
            var ret = new List<Vector3>();

            Action<int, Vector3[]> helper = (f, landmarks) =>
            {
                int from = 1 + f * 4;
                for (int i = 0; i < 4; ++i)
                {
                    ret.Add(landmarks[from + i]);
                }
            };

            if (fingers.HasFlag(Fingers.Thumb)) helper(0, landmarks);
            if (fingers.HasFlag(Fingers.Index)) helper(1, landmarks);
            if (fingers.HasFlag(Fingers.Middle)) helper(2, landmarks);
            if (fingers.HasFlag(Fingers.Ring)) helper(3, landmarks);
            if (fingers.HasFlag(Fingers.Pinky)) helper(4, landmarks);

            return ret;
        }

        public FingerState GetFingerState(Fingers finger)
        {
            var f = FingerToIndex(finger);
            Vector3 v1 = Vector3.Normalize(landmarks[f + 1] - landmarks[f]);
            Vector3 v2 = Vector3.Normalize(landmarks[f + 3] - landmarks[f + 1]);
            double angle = Vector3.Dot(v1, v2);
            if(finger == Fingers.Thumb)
                return angle < 0.2 ? FingerState.Closed : FingerState.Stretched;
            else
                return angle < -0.1 ? FingerState.Closed : FingerState.Stretched;
        }

        private int FingerToIndex(Fingers finger)
        {
            switch (finger)
            {
                case Fingers.Thumb:
                    return 1;
                case Fingers.Index:
                    return 5;
                case Fingers.Middle:
                    return 9;
                case Fingers.Ring:
                    return 13;
                case Fingers.Pinky:
                    return 17;
            }
            throw new ArgumentException("invalid fingerToIndex argument");
        }
    }
}
