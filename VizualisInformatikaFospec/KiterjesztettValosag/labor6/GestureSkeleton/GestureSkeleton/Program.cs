using System;
using System.Diagnostics;
using System.IO;
using System.Numerics;
using System.Globalization;

namespace GestureSkeleton
{
    enum Type { Rock, Paper, Scrissor, None, Ready}
    class Program
    {
        private static Process gestureProcessor;
        private static StreamReader io;
        private static Job job;
        private static Random rnd = new Random();
        private static bool round = false;

        static void Main(string[] args)
        {
            ProcessStartInfo start = new ProcessStartInfo();
            start.FileName = "C:\\Python39\\python.exe";
            //start.Arguments = string.Format("{0} {1} {2} {3} {4}", "C:\\BME\\1.felev\\KiterjesztettValosag\\labor6\\GestureSkeleton\\GestureSkeleton\\gesture_processor.py", -1, "C:\\BME\\1.felev\\KiterjesztettValosag\\labor6\\videos\\numbersandlike.mp4", 640, 480);
            //start.Arguments = string.Format("{0} {1} {2} {3} {4}", "C:\\BME\\1.felev\\KiterjesztettValosag\\labor6\\GestureSkeleton\\GestureSkeleton\\gesture_processor.py", -1, "source.mkv", 640, 480);
            start.Arguments = string.Format("{0} {1} {2} {3} {4}", "C:\\BME\\1.felev\\KiterjesztettValosag\\labor6\\GestureSkeleton\\GestureSkeleton\\gesture_processor.py", 1, "x", 640, 480);
            start.UseShellExecute = false;
            start.RedirectStandardOutput = true;
            start.CreateNoWindow = true;
            gestureProcessor = Process.Start(start);
            io = gestureProcessor.StandardOutput;

            job = new Job();
            job.AddProcess(gestureProcessor.Id);

            while (true)
            {
                var hand = new Hand();
                hand.landmarks = new Vector3[21];
                for (int i = 0; i < 21;)
                {
                    try
                    {
                        string s = io.ReadLine();
                        if (s == null || s == "") continue;
                        var split = s.Split(',');
                        if(split.Length == 2 && split[0] == "D")
                        {
                            if (split[1] == "Left")
                                hand.handDir = HandDir.Left;
                            if (split[1] == "Right")
                                hand.handDir = HandDir.Right;
                            continue;
                        }
                            
                        Debug.Assert(split.Length == 3);
                        hand.landmarks[i].X = float.Parse(split[0], CultureInfo.InvariantCulture);
                        hand.landmarks[i].Y = float.Parse(split[1], CultureInfo.InvariantCulture);
                        hand.landmarks[i].Z = float.Parse(split[2], CultureInfo.InvariantCulture);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.Message);
                    }
                    ++i;
                }

                ProcessHand(hand);
            }
        }

        private static void ProcessHand(Hand hand)
        {
            //bool isGrab = checkGrabPoseExample(hand);
            //bool isOpen = checkOpenHandPoseExample(hand);

            //System.Console.WriteLine($"Open: {isOpen}; Grab:{isGrab}");

            //int num = getShownNumber(hand);
            //Console.WriteLine("number: {0}", num);

            //Console.WriteLine(hand.Get(Fingers.Index)[0]);

            //Console.WriteLine(hand.handDir);

            //bool like = isLike(hand);
            //Console.WriteLine(like ? "Like" : "");

            Type type = getType(hand);
            if (type == Type.Ready)
                round = true;
            if(round && type != Type.Ready && type != Type.None)
            {
                Game(type);
            }
        }

        private static void Game(Type type)
        {
            Type t = (Type)rnd.Next(0, 3);
            if (t == type)
                Console.WriteLine("Döntetlen");
            else if ((type == Type.Rock && t == Type.Scrissor) || (type == Type.Scrissor && t == Type.Paper))
                Console.WriteLine("Nyertél");
            else
                Console.WriteLine("Vesztettél");
            round = false;
        }

        private static bool checkGrabPoseExample(Hand hand)
        {
            bool allClosedFingers =
                hand.GetFingerState(Fingers.Index) == FingerState.Closed &&
                hand.GetFingerState(Fingers.Middle) == FingerState.Closed &&
                hand.GetFingerState(Fingers.Ring) == FingerState.Closed;
            return allClosedFingers;
        }

        private static bool checkOpenHandPoseExample(Hand hand)
        {
            bool allStretchedFingers =
                hand.GetFingerState(Fingers.Index) == FingerState.Stretched &&
                hand.GetFingerState(Fingers.Middle) == FingerState.Stretched &&
                hand.GetFingerState(Fingers.Ring) == FingerState.Stretched;
            return allStretchedFingers;
        }

        private static int getShownNumber(Hand hand)
        {
            int res = 0;

            if (hand.GetFingerState(Fingers.Thumb) == FingerState.Stretched)
                res += 1;
            if (hand.GetFingerState(Fingers.Index) == FingerState.Stretched)
                res += 1;
            if (hand.GetFingerState(Fingers.Middle) == FingerState.Stretched)
                res += 1;
            if (hand.GetFingerState(Fingers.Ring) == FingerState.Stretched)
                res += 1;
            if (hand.GetFingerState(Fingers.Pinky) == FingerState.Stretched)
                res += 1;

            return res;
        }

        private static bool isLike(Hand hand)
        {
            bool like = false;
            if (hand.GetFingerState(Fingers.Thumb) == FingerState.Stretched)
                like = true;
            if (hand.GetFingerState(Fingers.Middle) == FingerState.Stretched ||
                hand.GetFingerState(Fingers.Pinky) == FingerState.Stretched ||
                hand.GetFingerState(Fingers.Ring) == FingerState.Stretched ||
                hand.GetFingerState(Fingers.Index) == FingerState.Stretched)
                like = false;

            return like;
        }
    
        private static Type getType(Hand hand)
        {
            if (getShownNumber(hand) == 0)
                return Type.Rock;
            if(getShownNumber(hand) == 5)
                return Type.Paper;
            if (hand.GetFingerState(Fingers.Index) == FingerState.Stretched && 
                (getShownNumber(hand) == 1 || (getShownNumber(hand) == 2 && hand.GetFingerState(Fingers.Thumb) == FingerState.Stretched)))
                return Type.Ready;
            if (hand.GetFingerState(Fingers.Index) == FingerState.Stretched &&
                hand.GetFingerState(Fingers.Middle) == FingerState.Stretched &&
                getShownNumber(hand) == 2)
                return Type.Scrissor;
            else
                return Type.None;
        }
    }
}